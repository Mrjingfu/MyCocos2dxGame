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

#include "CCNativeVirtualCurrencyStorage.h"

#include "CCNativeVirtualGoodsStorage.h"
#include "CCSoomlaUtils.h"
#include "CCNdkBridge.h"
#include "CCStoreInfo.h"
#include "CCUpgradeVG.h"

namespace soomla {
#define TAG "SOOMLA NativeVirtualCurrencyStorage"
    
    USING_NS_CC;
    
    CCNativeVirtualCurrencyStorage::CCNativeVirtualCurrencyStorage() {
        
    }
    
    CCNativeVirtualCurrencyStorage::~CCNativeVirtualCurrencyStorage() {
        
    }
    
    int CCNativeVirtualCurrencyStorage::getBalance(CCVirtualItem *item, CCError **error) {
        const char *itemId = item->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("SOOMLA/COCOS2DX Calling getBalance with: %s", itemId)->getCString());
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeVirtualCurrencyStorage::getBalance"), "method");
        params->setObject(__String::create(itemId), "itemId");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, error);
        
        if (retParams == NULL) {
            return 0;
        }
        
        __Integer *retValue = (__Integer *) retParams->objectForKey("return");
        if (retValue) {
            return retValue->getValue();
        } else {
            return 0;
        }
    }
    
    int CCNativeVirtualCurrencyStorage::setBalance(CCVirtualItem *item, int balance, bool notify, CCError **error) {
        const char *itemId = item->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("SOOMLA/COCOS2DX Calling setBalance with: %s", itemId)->getCString());
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeVirtualCurrencyStorage::setBalance"), "method");
        params->setObject(__String::create(itemId), "itemId");
        params->setObject(__Integer::create(balance), "balance");
        params->setObject(__Bool::create(notify), "notify");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, error);
        
        if (retParams == NULL) {
            return 0;
        }
        
        __Integer *retValue = (__Integer *) retParams->objectForKey("return");
        if (retValue) {
            return retValue->getValue();
        } else {
            return 0;
        }
    }
    
    int CCNativeVirtualCurrencyStorage::add(CCVirtualItem *item, int amount, bool notify, CCError **error) {
        const char *itemId = item->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("SOOMLA/COCOS2DX Calling add with: %s", itemId)->getCString());
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeVirtualCurrencyStorage::add"), "method");
        params->setObject(__String::create(itemId), "itemId");
        params->setObject(__Integer::create(amount), "amount");
        params->setObject(__Bool::create(notify), "notify");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, error);
        
        if (retParams == NULL) {
            return 0;
        }
        
        __Integer *retValue = (__Integer *) retParams->objectForKey("return");
        if (retValue) {
            return retValue->getValue();
        } else {
            return 0;
        }
    }
    
    int CCNativeVirtualCurrencyStorage::remove(CCVirtualItem *item, int amount, bool notify, CCError **error) {
        const char *itemId = item->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("SOOMLA/COCOS2DX Calling remove with: %s", itemId)->getCString());
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeVirtualCurrencyStorage::remove"), "method");
        params->setObject(__String::create(itemId), "itemId");
        params->setObject(__Integer::create(amount), "amount");
        params->setObject(__Bool::create(notify), "notify");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, error);
        
        if (retParams == NULL) {
            return 0;
        }
        
        __Integer *retValue = (__Integer *) retParams->objectForKey("return");
        if (retValue) {
            return retValue->getValue();
        } else {
            return 0;
        }
    }
}