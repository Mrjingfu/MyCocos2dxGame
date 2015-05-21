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

#include "CCStoreInventory.h"
#include "CCSoomlaUtils.h"
#include "CCStoreInfo.h"
#include "CCPurchasableVirtualItem.h"
#include "CCVirtualCurrencyStorage.h"
#include "CCVirtualGoodsStorage.h"
#include "CCSoomlaEventDispatcher.h"

namespace soomla {
#define TAG "SOOMLA StoreInventory"

    USING_NS_CC;

    static CCStoreInventory *s_SharedStoreInventory = NULL;

    CCStoreInventory *CCStoreInventory::sharedStoreInventory() {
        if (!s_SharedStoreInventory) {
          s_SharedStoreInventory = new CCStoreInventory();
          s_SharedStoreInventory->init();
        }

        return s_SharedStoreInventory;
    }

    CCStoreInventory::~CCStoreInventory() {

    }

    bool CCStoreInventory::init() {
        
        // support reflection call to refreshLocalInventory
        CCSoomlaEventDispatcher::getInstance()->registerEventHandler("Reflection::CCStoreInventory::refreshLocalInventory",
                                                                     [this](__Dictionary *parameters) {
                                                                         this->refreshLocalInventory();
                                                                     });
        return true;
    }
    
    bool CCStoreInventory::canAfford(const char *itemId, CCError **error) {
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Checking can afford: %s", itemId)->getCString());
        
        CCPurchasableVirtualItem *pvi = dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId, error));
        return pvi->canAfford();
    }

    void CCStoreInventory::buyItem(char const *itemId, CCError **error) {
        buyItem(itemId, nullptr, error);
    }

    void CCStoreInventory::buyItem(char const *itemId, const char *payload, CCError **error) {
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Buying: %s", itemId)->getCString());
        
        CCPurchasableVirtualItem *pvi = dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId, error));
        if (pvi != NULL) {
            pvi->buy(payload, error);
        }
    }

    int CCStoreInventory::getItemBalance(char const *itemId, CCError **error) {
        __Integer *amount = dynamic_cast<__Integer *>(mLocalItemBalances->objectForKey(itemId));
        if (amount != NULL) {
            return amount->getValue();
        }
        
        CCVirtualItem *item = CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId, error);
        if (item == NULL) {
            return 0;
        }
        return item->getBalance(error);
    }

    void CCStoreInventory::giveItem(char const *itemId, int amount, CCError **error) {
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Giving: %d pieces of: %s", amount, itemId)->getCString());
        
        CCVirtualItem *item = CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId, error);
        if (item != NULL) {
            item->give(amount, error);
        }
    }

    void CCStoreInventory::takeItem(char const *itemId, int amount, CCError **error) {
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Taking: %d pieces of: %s", amount, itemId)->getCString());
        
        CCVirtualItem *item = CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId, error);
        if (item != NULL) {
            item->take(amount, error);
        }
    }

    void CCStoreInventory::equipVirtualGood(char const *itemId, CCError **error) {
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Equipping: %s", itemId)->getCString());
        
        CCEquippableVG *good = dynamic_cast<CCEquippableVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId, error));
        if (good != NULL) {
            good->equip(error);
        }
   }

    void CCStoreInventory::unEquipVirtualGood(char const *itemId, CCError **error) {
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("UnEquipping: %s", itemId)->getCString());
        
        CCEquippableVG *good = dynamic_cast<CCEquippableVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId, error));
        if (good != NULL) {
            good->unequip(error);
        }
    }

    bool CCStoreInventory::isVirtualGoodEquipped(char const *itemId, CCError **error) {
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Checking if %s is equipped", itemId)->getCString());
        
        CCEquippableVG *good = dynamic_cast<CCEquippableVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId, error));
        if (good != NULL) {
            return CCVirtualGoodsStorage::getInstance()->isEquipped(good, error);
        }
        
        return false;
    }

    int CCStoreInventory::getGoodUpgradeLevel(char const *goodItemId, CCError **error) {
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Checking %s upgrade level", goodItemId)->getCString());
        
        CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(goodItemId, error));
        if (good == NULL) {
            CCSoomlaUtils::logError(TAG, "You tried to get the level of a non-existant virtual good.");
            return 0;
        }
        CCUpgradeVG *upgradeVG = CCVirtualGoodsStorage::getInstance()->getCurrentUpgrade(good, error);
        if (upgradeVG == NULL) {
            return 0; //no upgrade
        }
        
        CCUpgradeVG *first = CCStoreInfo::sharedStoreInfo()->getFirstUpgradeForVirtualGood(goodItemId);
        int level = 1;
        while (!first->getItemId()->isEqual(upgradeVG->getItemId())) {
            first = dynamic_cast<CCUpgradeVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(first->getNextItemId()->getCString(), error));
            level++;
        }
        
        return level;
    }

    std::string CCStoreInventory::getGoodCurrentUpgrade(char const *goodItemId, CCError **error) {
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Checking %s current upgrade", goodItemId)->getCString());
        
        CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(goodItemId, error));
        if (good == NULL) {
            return "";
        }
        
        CCUpgradeVG *upgradeVG = CCVirtualGoodsStorage::getInstance()->getCurrentUpgrade(good, error);
        if (upgradeVG == NULL) {
            return "";
        }
        return upgradeVG->getItemId()->getCString();
    }

    void CCStoreInventory::upgradeGood(char const *goodItemId, CCError **error) {
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Upgrading Good with: %s", goodItemId)->getCString());
        CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(goodItemId, error));
        if (good == NULL) {
            return;
        }
        
        CCUpgradeVG *upgradeVG = CCVirtualGoodsStorage::getInstance()->getCurrentUpgrade(good, error);
        
        if (upgradeVG != NULL) {
            __String *nextItemId = upgradeVG->getNextItemId();
            if (CCSoomlaUtils::isNullOrEmpty(nextItemId)) {
                return;
            }
            CCUpgradeVG *vgu = dynamic_cast<CCUpgradeVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(nextItemId->getCString(), error));
            if (vgu != NULL) {
                vgu->buy("");
            }
        }
        else {
            CCUpgradeVG *first = dynamic_cast<CCUpgradeVG *>(CCStoreInfo::sharedStoreInfo()->getFirstUpgradeForVirtualGood(goodItemId));
            if (first != NULL) {
                first->buy("");
            }
        }
    }

    void CCStoreInventory::removeGoodUpgrades(char const *goodItemId, CCError **error) {
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Removing Good Upgrades for: %s", goodItemId)->getCString());
        
        __Array *upgrades = CCStoreInfo::sharedStoreInfo()->getUpgradesForVirtualGood(goodItemId);
        Ref *obj;
        CCARRAY_FOREACH(upgrades, obj) {
            CCUpgradeVG *upgrade = dynamic_cast<CCUpgradeVG *>(obj);
            CCVirtualGoodsStorage::getInstance()->remove(upgrade, 1, true, error);
        }
        
        CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(goodItemId, error));
        CCVirtualGoodsStorage::getInstance()->removeUpgrades(good, error);
    }
    
    void CCStoreInventory::refreshLocalInventory() {
        if (mLocalItemBalances != NULL) {
            CC_SAFE_RELEASE(mLocalItemBalances);
        }
        mLocalItemBalances = __Dictionary::create();
        CC_SAFE_RETAIN(mLocalItemBalances);
        
        if (mLocalUpgrades != NULL) {
            CC_SAFE_RELEASE(mLocalUpgrades);
        }
        mLocalUpgrades = __Dictionary::create();
        CC_SAFE_RETAIN(mLocalUpgrades);
        
        if (mLocalEquippedGoods != NULL) {
            CC_SAFE_RELEASE(mLocalEquippedGoods);
        }
        mLocalEquippedGoods = __Set::create();
        CC_SAFE_RETAIN(mLocalEquippedGoods);
        
        Ref *obj;
        CCARRAY_FOREACH(CCStoreInfo::sharedStoreInfo()->getCurrencies(), obj) {
            CCVirtualCurrency *item = dynamic_cast<CCVirtualCurrency *>(obj);
            CC_ASSERT(item);
            mLocalItemBalances->setObject(__Integer::create(CCVirtualCurrencyStorage::getInstance()->getBalance(item)), item->getItemId()->getCString());
        }
        
        CCARRAY_FOREACH(CCStoreInfo::sharedStoreInfo()->getGoods(), obj) {
            CCVirtualGood *item = dynamic_cast<CCVirtualGood *>(obj);
            CC_ASSERT(item);
            int balance = CCVirtualGoodsStorage::getInstance()->getBalance(item);
            mLocalItemBalances->setObject(__Integer::create(balance), item->getItemId()->getCString());
            
            CCUpgradeVG *upgrade = CCVirtualGoodsStorage::getInstance()->getCurrentUpgrade(item);
            if (upgrade != NULL) {
                int upgradeLevel = getGoodUpgradeLevel(item->getItemId()->getCString());
                CCLocalUpgrade *localUpgrade = CCLocalUpgrade::create();
                localUpgrade->setItemId(upgrade->getItemId());
                localUpgrade->setLevel(__Integer::create(upgradeLevel));
                mLocalUpgrades->setObject(localUpgrade, item->getItemId()->getCString());
            }
            
            CCEquippableVG *equippableVG = dynamic_cast<CCEquippableVG *>(item);
            if (equippableVG != NULL) {
                if (CCVirtualGoodsStorage::getInstance()->isEquipped(equippableVG)) {
                    mLocalEquippedGoods->addObject(equippableVG);
                }
            }
        }
    }
    
    void CCStoreInventory::refreshOnGoodUpgrade(CCVirtualGood *vg, CCUpgradeVG *uvg) {
        if (uvg == NULL) {
            mLocalUpgrades->removeObjectForKey(vg->getItemId()->getCString());
        }
        else {
            int upgradeLevel = getGoodUpgradeLevel(vg->getItemId()->getCString());
            CCLocalUpgrade *upgrade = dynamic_cast<CCLocalUpgrade *>(mLocalUpgrades->objectForKey(vg->getItemId()->getCString()));
            if (upgrade != NULL) {
                upgrade->setItemId(uvg->getItemId());
                upgrade->setLevel(__Integer::create(upgradeLevel));
            }
            else {
                CCLocalUpgrade *localUpgrade = CCLocalUpgrade::create();
                localUpgrade->setItemId(uvg->getItemId());
                localUpgrade->setLevel(__Integer::create(upgradeLevel));
                mLocalUpgrades->setObject(localUpgrade, vg->getItemId()->getCString());
            }
        }
    }
    
    void CCStoreInventory::refreshOnGoodEquipped(CCEquippableVG *equippable) {
        mLocalEquippedGoods->addObject(equippable->getItemId());
    }
    
    void CCStoreInventory::refreshOnGoodUnEquipped(CCEquippableVG *equippable) {
        mLocalEquippedGoods->removeObject(equippable->getItemId());
    }
    
    void CCStoreInventory::refreshOnCurrencyBalanceChanged(CCVirtualCurrency *virtualCurrency, int balance, int amountAdded) {
        updateLocalBalance(virtualCurrency->getItemId()->getCString(), balance);
    }
    
    void CCStoreInventory::refreshOnGoodBalanceChanged(CCVirtualGood *good, int balance, int amountAdded) {
        updateLocalBalance(good->getItemId()->getCString(), balance);
    }
    
    void CCStoreInventory::updateLocalBalance(const char *itemId, int balance) {
        mLocalItemBalances->setObject(__Integer::create(balance), itemId);
    }
    
    CCStoreInventory::CCLocalUpgrade *CCStoreInventory::CCLocalUpgrade::create() {
        CCLocalUpgrade *ret = new CCLocalUpgrade();
        ret->autorelease();
        return ret;
    }
}
