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

#include "CCNativeStoreInfo.h"
#include "CCNdkBridge.h"
#include "CCSoomlaUtils.h"

namespace soomla {
    #define TAG "SOOMLA NativeStoreInfo"
    
    USING_NS_CC;
    
    CCNativeStoreInfo::~CCNativeStoreInfo() {
        
    }
    
    void CCNativeStoreInfo::setStoreAssets(CCStoreAssets *storeAssets) {
        CCSoomlaUtils::logDebug(TAG, "pushing CCStoreAssets to StoreInfo on native side");
        __Dictionary *storeAssetsObj = storeAssetsToDictionary(storeAssets);
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCStoreAssets::init"), "method");
        params->setObject(__Integer::create(storeAssets->getVersion()), "version");
        params->setObject(storeAssetsObj, "storeAssets");
        CCNdkBridge::callNative (params, NULL);
        
        CCSoomlaUtils::logDebug(TAG, "done! (pushing data to StoreAssets on native side)");
    }
    
    void CCNativeStoreInfo::save() {
        CCStoreInfo::save();
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCStoreInfo::loadFromDB"), "method");
        CCNdkBridge::callNative (params, NULL);
    }
}