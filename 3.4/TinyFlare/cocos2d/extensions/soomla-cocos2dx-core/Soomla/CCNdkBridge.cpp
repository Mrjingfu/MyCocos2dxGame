/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "CCNdkBridge.h"
#include "CCJsonHelper.h"
#include "CCSoomlaUtils.h"

USING_NS_CC;

#define LOG_JSON 0

#if (LOG_JSON == 1)
#define TAG "JSON"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "platform/android/jni/JniHelper.h"
    #include <jni.h>
    #include <string>
    #include "CCSoomlaEventDispatcher.h"
#ifdef COCOS2D_JAVASCRIPT
    #include "jsb/JSBinding.h"
#endif

    #define CLASS_NAME "com/soomla/cocos2dx/common/NdkGlue"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#import "CCNdkBridgeIos.h"

#endif

namespace soomla {
    extern "C"
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        // Method for receiving NDK messages
        void Java_com_soomla_cocos2dx_common_NdkGlue_sendCppMessage(JNIEnv* env, jobject thiz, jstring json)
        {
            std::string jsonString = JniHelper::jstring2string(json);
            const char *jsonCharArray = jsonString.c_str();

            json_error_t error;
            json_t *root;
            root = json_loads(jsonCharArray, 0, &error);

            if (!root)
                {
                    fprintf(stderr, "error: at line #%d: %s\n", error.line, error.text);
                    return;
                }

            cocos2d::Ref *dataToPass = CCJsonHelper::getCCObjectFromJson(root);

#ifdef COCOS2D_JAVASCRIPT
            Soomla::JSBinding::callCallback((cocos2d::__Dictionary *) dataToPass);
#else
            CCSoomlaEventDispatcher::getInstance()->ndkCallback((cocos2d::__Dictionary *)dataToPass);
#endif

            json_decref(root);
        }
#endif

        cocos2d::Ref *CCNdkBridge::callNative(cocos2d::__Dictionary *params, CCError **pError) {
            cocos2d::__Dictionary *methodParams = params;

            json_t *toBeSentJson = CCJsonHelper::getJsonFromCCObject(methodParams);
            json_t *retJsonParams = NULL;

#if (LOG_JSON == 1)
            CCSoomlaUtils::logDebug(TAG, __String::createWithFormat(
                    "to native JSON: %s", json_dumps(toBeSentJson, JSON_COMPACT | JSON_ENSURE_ASCII))->getCString());
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            JniMethodInfo t;

            if (JniHelper::getStaticMethodInfo(t,
                                               CLASS_NAME,
                                               "receiveCppMessage",
                                               "(Ljava/lang/String;)Ljava/lang/String;")) {

                char* jsonStrLocal = json_dumps(toBeSentJson, JSON_COMPACT | JSON_ENSURE_ASCII);
                std::string jsonStr(jsonStrLocal);
                free(jsonStrLocal);

                jstring stringArg1 = t.env->NewStringUTF(jsonStr.c_str());
                jstring retString = (jstring) t.env->CallStaticObjectMethod(t.classID, t.methodID, stringArg1);

                t.env->DeleteLocalRef(stringArg1);
                t.env->DeleteLocalRef(t.classID);

                const char *nativeString = t.env->GetStringUTFChars(retString, 0);
                std::string retParamsStr(nativeString);
                t.env->ReleaseStringUTFChars(retString, nativeString);


                const char *jsonCharArray = retParamsStr.c_str();

                json_error_t error;
                retJsonParams = json_loads(jsonCharArray, 0, &error);

                if (!retJsonParams) {
                    fprintf(stderr, "error: at line #%d: %s\n", error.line, error.text);
                    return __Dictionary::create();
                }
            }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            retJsonParams = soomla::CCNdkBridgeIos::receiveCppMessage(toBeSentJson);
#endif

#if (LOG_JSON == 1)
            CCSoomlaUtils::logDebug(TAG, __String::createWithFormat(
                    "from native JSON: %s", json_dumps(retJsonParams, JSON_COMPACT | JSON_ENSURE_ASCII))->getCString());
#endif

            json_decref(toBeSentJson);
            Ref *retParams = CCJsonHelper::getCCObjectFromJson(retJsonParams);

            if (retJsonParams) {
                json_decref(retJsonParams);
            }

            CCError *error = CCError::createWithObject(retParams);
            if (error != NULL) {
                if (pError != NULL) {
                    *pError = error;
                }
                else {
                    CCSoomlaUtils::logException("SOOMLA NdkBridge", error);
                }
            }

            return retParams;
        }
    }
}
