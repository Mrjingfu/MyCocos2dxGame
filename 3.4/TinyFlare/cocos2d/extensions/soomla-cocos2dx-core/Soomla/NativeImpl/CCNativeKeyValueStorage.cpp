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

#include "CCNativeKeyValueStorage.h"
#include "CCError.h"
#include "CCNdkBridge.h"
#include "CCSoomlaUtils.h"

namespace soomla {
    
    #define TAG "SOOMLA NativeKeyValueStorage"
    
    USING_NS_CC;
    
    const char *CCNativeKeyValueStorage::getValue(const char *key) const {
        CCError *error = NULL;
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeKeyValueStorage::getValue"), "method");
        params->setObject(__String::create(key), "key");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
            return NULL;
        }
        
        if (retParams == NULL) {
            return NULL;
        }
        
        __String *retValue = (__String *) retParams->objectForKey("return");
        if (!retValue) {
            return NULL;
        }
        
        return retValue->getCString();
    }

    void CCNativeKeyValueStorage::setValue(const char *key, const char *val) {
        CCError *error = NULL;
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeKeyValueStorage::setValue"), "method");
        params->setObject(__String::create(key), "key");
        params->setObject(__String::create(val), "val");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }

    void CCNativeKeyValueStorage::deleteKeyValue(const char *key) {
        CCError *error = NULL;
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeKeyValueStorage::deleteKeyValue"), "method");
        params->setObject(__String::create(key), "key");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }

    void CCNativeKeyValueStorage::purge() {
        CCError *error = NULL;
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeKeyValueStorage::purge"), "method");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }
    
}