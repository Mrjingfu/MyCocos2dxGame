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

#include "CCVirtualGoodsStorage.h"
#include "CCKeyValueStorage.h"
#include "CCStoreEventDispatcher.h"
#include "CCStoreInfo.h"
#include "CCSoomlaUtils.h"
#include "CCNativeVirtualGoodsStorage.h"

namespace soomla {
#define TAG "SOOMLA VirtualGoodsStorage"
    
    USING_NS_CC;
    
    static CCVirtualGoodsStorage *s_SharedVirtualGoodsStorage = NULL;
    
    CCVirtualGoodsStorage *CCVirtualGoodsStorage::getInstance() {
        if (!s_SharedVirtualGoodsStorage)
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            s_SharedVirtualGoodsStorage = new CCNativeVirtualGoodsStorage();
#else
            s_SharedVirtualGoodsStorage = new CCVirtualGoodsStorage();
#endif
//            s_SharedVirtualGoodsStorage->retain();
        }
        return s_SharedVirtualGoodsStorage;
    }
    
    CCVirtualGoodsStorage::CCVirtualGoodsStorage() {
    
    }
    
    CCVirtualGoodsStorage::~CCVirtualGoodsStorage() {
        
    }
    
    void CCVirtualGoodsStorage::removeUpgrades(CCVirtualGood *good, bool notify, CCError **error) {
        const char *itemId = good->getId()->getCString();
        const char *key = keyGoodUpgrade(itemId);
        
        CCKeyValueStorage::getInstance()->deleteKeyValue(key);
        
        if (notify) {
            CCStoreEventDispatcher::getInstance()->onGoodUpgrade(good, NULL);
        }
    }
    
    void CCVirtualGoodsStorage::assignCurrentUpgrade(CCVirtualGood *good, CCUpgradeVG *upgradeVG, bool notify, CCError **error) {
        CCUpgradeVG *upgrade = getCurrentUpgrade(good, error);
        if ((upgrade != NULL) && (upgrade->getId()->isEqual(upgradeVG->getId()))) {
            return;
        }
        
        const char *itemId = good->getId()->getCString();
        const char *key = keyGoodUpgrade(itemId);
        const char *upItemId = upgradeVG->getId()->getCString();
        
        CCKeyValueStorage::getInstance()->setValue(key, upItemId);
        
        if (notify) {
            CCStoreEventDispatcher::getInstance()->onGoodUpgrade(good, upgradeVG);
        }
    }
    
    CCUpgradeVG *CCVirtualGoodsStorage::getCurrentUpgrade(CCVirtualGood *good, CCError **error) {
        const char *itemId = good->getId()->getCString();
        const char *key = keyGoodUpgrade(itemId);
        
        const char *upItemId = CCKeyValueStorage::getInstance()->getValue(key);
        
        if (upItemId == NULL) {
            CCSoomlaUtils::logDebug(TAG,
                                    __String::createWithFormat("You tried to fetch the current upgrade of %s but there's not upgrade to it.", itemId)->getCString());
            return NULL;
        }
        
        CCVirtualItem *item = CCStoreInfo::sharedStoreInfo()->getItemByItemId(upItemId, error);
        if (item == NULL) {
            return NULL;
        }
        
        CCUpgradeVG *upgrade = dynamic_cast<CCUpgradeVG *>(item);
        if (upgrade == NULL) {
            CCSoomlaUtils::logDebug(TAG, "The current upgrade's itemId from the DB is not an UpgradeVG.");
            return NULL;
        }
        
        return upgrade;
    }
    
    bool CCVirtualGoodsStorage::isEquipped(CCEquippableVG *good, CCError **error) {
        const char *itemId = good->getId()->getCString();
        const char *key = keyGoodEquipped(itemId);
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        
        return (val != NULL);
    }
    
    void CCVirtualGoodsStorage::equip(CCEquippableVG *good, bool notify, CCError **error) {
        if (isEquipped(good)) {
            return;
        }
        
        equipPriv(good, true, notify);
    }
    
    void CCVirtualGoodsStorage::unequip(CCEquippableVG *good, bool notify, CCError **error) {
        if (!isEquipped(good)) {
            return;
        }
        
        equipPriv(good, false, notify);
    }
    
    void CCVirtualGoodsStorage::equipPriv(CCEquippableVG *good, bool equip, bool notify, CCError **error) {
        const char *itemId = good->getId()->getCString();
        const char *key = keyGoodEquipped(itemId);
        
        if (equip) {
            CCKeyValueStorage::getInstance()->setValue(key, "yes");
            if (notify) {
                CCStoreEventDispatcher::getInstance()->onGoodEquipped(good);
            }
        } else {
            CCKeyValueStorage::getInstance()->deleteKeyValue(key);
            if (notify) {
                CCStoreEventDispatcher::getInstance()->onGoodUnEquipped(good);
            }
        }
    }
    
    const char* CCVirtualGoodsStorage::keyBalance(const char *itemId) const {
        return keyGoodBalance(itemId);
    }
    
    void CCVirtualGoodsStorage::postBalanceChangeEvent(CCVirtualItem *item, int balance, int amountAdded) {
        CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(item);
        if (good == NULL) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat("Trying to post good balance changed with a non VirtualGood item %s", item->getId()->getCString())->getCString());
            return;
        }
        
        CCStoreEventDispatcher::getInstance()->onGoodBalanceChanged(good, balance, amountAdded);
    }
    
    const char *CCVirtualGoodsStorage::keyGoodBalance(const char *itemId) {
        return __String::createWithFormat("good.%s.balance", itemId)->getCString();
    }
    
    const char *CCVirtualGoodsStorage::keyGoodEquipped(const char *itemId) {
        return __String::createWithFormat("good.%s.equipped", itemId)->getCString();
    }
    
    const char *CCVirtualGoodsStorage::keyGoodUpgrade(const char *itemId) {
        return __String::createWithFormat("good.%s.currentUpgrade", itemId)->getCString();
    }
}