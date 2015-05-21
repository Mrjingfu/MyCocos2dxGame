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

#include "CCNativeVirtualGoodsStorage.h"
#include "CCSoomlaUtils.h"
#include "CCNdkBridge.h"
#include "CCStoreInfo.h"
#include "CCUpgradeVG.h"

namespace soomla {
    #define TAG "SOOMLA NativeVirtualGoodsStorage"
    
    USING_NS_CC;
    
    CCNativeVirtualGoodsStorage::CCNativeVirtualGoodsStorage() {
        
    }
    
    CCNativeVirtualGoodsStorage::~CCNativeVirtualGoodsStorage() {
        
    }
    
    int CCNativeVirtualGoodsStorage::getBalance(CCVirtualItem *item, CCError **error) {
        const char *itemId = item->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("SOOMLA/COCOS2DX Calling getBalance with: %s", itemId)->getCString());
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeVirtualGoodsStorage::getBalance"), "method");
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
    
    int CCNativeVirtualGoodsStorage::setBalance(CCVirtualItem *item, int balance, bool notify, CCError **error) {
        const char *itemId = item->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("SOOMLA/COCOS2DX Calling setBalance with: %s", itemId)->getCString());
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeVirtualGoodsStorage::setBalance"), "method");
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
    
    int CCNativeVirtualGoodsStorage::add(CCVirtualItem *item, int amount, bool notify, CCError **error) {
        const char *itemId = item->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("SOOMLA/COCOS2DX Calling add with: %s", itemId)->getCString());
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeVirtualGoodsStorage::add"), "method");
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
    
    int CCNativeVirtualGoodsStorage::remove(CCVirtualItem *item, int amount, bool notify, CCError **error) {
        const char *itemId = item->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("SOOMLA/COCOS2DX Calling remove with: %s", itemId)->getCString());
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeVirtualGoodsStorage::remove"), "method");
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
    
    void CCNativeVirtualGoodsStorage::removeUpgrades(CCVirtualGood *good, bool notify, CCError **error) {
        const char *itemId = good->getId()->getCString();

        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("SOOMLA/COCOS2DX Calling removeUpgrades with: %s", itemId)->getCString());
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeVirtualGoodsStorage::removeUpgrades"), "method");
        params->setObject(__String::create(itemId), "itemId");
        params->setObject(__Bool::create(notify), "notify");
        CCNdkBridge::callNative (params, error);
    }
    
    void CCNativeVirtualGoodsStorage::assignCurrentUpgrade(CCVirtualGood *good, CCUpgradeVG *upgradeVG, bool notify, CCError **error) {
        const char *itemId = good->getId()->getCString();
        const char *upgradeItemId = upgradeVG->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("SOOMLA/COCOS2DX Calling assignCurrentUpgrade with: %s", itemId)->getCString());
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeVirtualGoodsStorage::assignCurrentUpgrade"), "method");
        params->setObject(__String::create(itemId), "itemId");
        params->setObject(__String::create(upgradeItemId), "upgradeItemId");
        params->setObject(__Bool::create(notify), "notify");
        CCNdkBridge::callNative (params, error);
    }
    
    CCUpgradeVG *CCNativeVirtualGoodsStorage::getCurrentUpgrade(CCVirtualGood *good, CCError **error) {
        const char *itemId = good->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("SOOMLA/COCOS2DX Calling getCurrentUpgrade with: %s", itemId)->getCString());
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeVirtualGoodsStorage::getCurrentUpgrade"), "method");
        params->setObject(__String::create(itemId), "itemId");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, error);
        
        if (retParams == NULL) {
            return NULL;
        }
        
        __String *retItemId = (__String *) retParams->objectForKey("return");
        if (retItemId != NULL) {
            return dynamic_cast<CCUpgradeVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(retItemId->getCString(), error));
        }
        
        return NULL;
    }
    
    bool CCNativeVirtualGoodsStorage::isEquipped(CCEquippableVG *good, CCError **error) {
        const char *itemId = good->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("SOOMLA/COCOS2DX Calling isEquipped with: %s", itemId)->getCString());
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeVirtualGoodsStorage::isEquipped"), "method");
        params->setObject(__String::create(itemId), "itemId");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, error);
        
        if (retParams == NULL) {
            return false;
        }
        
        __Bool *retValue = (__Bool *) retParams->objectForKey("return");
        if (retValue != NULL) {
            return retValue->getValue();
        }
        
        return false;
    }
    
    void CCNativeVirtualGoodsStorage::equip(CCEquippableVG *good, bool notify, CCError **error) {
        const char *itemId = good->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("SOOMLA/COCOS2DX Calling equip with: %s", itemId)->getCString());
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeVirtualGoodsStorage::equip"), "method");
        params->setObject(__String::create(itemId), "itemId");
        params->setObject(__Bool::create(notify), "notify");
        CCNdkBridge::callNative (params, error);
    }
    
    void CCNativeVirtualGoodsStorage::unequip(CCEquippableVG *good, bool notify, CCError **error) {
        const char *itemId = good->getId()->getCString();
        
        CCSoomlaUtils::logDebug(TAG,
                                __String::createWithFormat("SOOMLA/COCOS2DX Calling unequip with: %s", itemId)->getCString());
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCNativeVirtualGoodsStorage::unequip"), "method");
        params->setObject(__String::create(itemId), "itemId");
        params->setObject(__Bool::create(notify), "notify");
        CCNdkBridge::callNative (params, error);
    }
}