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

#include "CCUpgradeVG.h"
#include "CCStoreInfo.h"
#include "CCSoomlaUtils.h"
#include "CCVirtualGoodsStorage.h"

namespace soomla {
    USING_NS_CC;
    
    #define TAG "SOOMLA UpgradeVG"
    
    CCUpgradeVG *CCUpgradeVG::create(__String *goodItemId, __String *prevItemId, __String *nextItemId, __String *name, __String *description, __String *itemId, CCPurchaseType *purchaseType) {
        CCUpgradeVG *ret = new CCUpgradeVG();
        if (ret->init(goodItemId, prevItemId, nextItemId, name, description, itemId, purchaseType)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCUpgradeVG::init(__String *goodItemId, __String *prevItemId, __String *nextItemId, __String *name, __String *description, __String *itemId, CCPurchaseType *purchaseType) {
        bool res = CCLifetimeVG::init(name, description, itemId, purchaseType);
        if (res) {
            setGoodItemId(goodItemId);
            setPrevItemId(prevItemId);
            setNextItemId(nextItemId);
            return true;
        } else {
            return false;
        }
    }

    bool CCUpgradeVG::initWithDictionary(__Dictionary *dict) {
        bool res = CCLifetimeVG::initWithDictionary(dict);
        if (res) {
            fillGoodItemIdFromDict(dict);
            fillPrevItemIdFromDict(dict);
            fillNextItemIdFromDict(dict);
            return true;
        } else {
            return false;
        }
    }

    __Dictionary *CCUpgradeVG::toDictionary() {
        __Dictionary *dict = CCLifetimeVG::toDictionary();

        putGoodItemIdToDict(dict);
        if (mPrevItemId != NULL) {
            putPrevItemIdToDict(dict);
        } else {
            dict->setObject(__String::create(""), CCStoreConsts::JSON_VGU_PREV_ITEM_ID);
        }
        if (mNextItemId != NULL) {
            putNextItemIdToDict(dict);
        } else {
            dict->setObject(__String::create(""), CCStoreConsts::JSON_VGU_NEXT_ITEM_ID);
        }

        return dict;
    }
    
    bool CCUpgradeVG::canBuy() {
        CCError *error = NULL;
        const char *goodItemId = getGoodItemId()->getCString();
        CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(goodItemId, &error));
        if ((error != NULL) || (good == NULL)) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat("VirtualGood with itemId: %s doesn't exist! Returning false (can't buy).", goodItemId)->getCString());
            if (error != NULL) {
                CCSoomlaUtils::logException(TAG, error);
            }
            return false;
        }
        
        CCUpgradeVG *upgradeVG = CCVirtualGoodsStorage::getInstance()->getCurrentUpgrade(good);
        
        return ((upgradeVG == NULL && CCSoomlaUtils::isNullOrEmpty(getPrevItemId())) ||
                (upgradeVG != NULL && ((upgradeVG->getNextItemId()->isEqual(getItemId())) ||
                                       (upgradeVG->getPrevItemId()->isEqual(getItemId())))))
                && CCLifetimeVG::canBuy();
    }
    
    int CCUpgradeVG::give(int amount, bool notify, CCError **error) {
        const char *goodItemId = getGoodItemId()->getCString();
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Assigning %s to: %s",
                                                                getName()->getCString(),
                                                                goodItemId)->getCString());
        
        CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(goodItemId, error));
        
        if (good == NULL) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat("VirtualGood with itemId: %s doesn't exist! Can't upgrade.",
                                                                    goodItemId)->getCString());
            return 0;
        }
        
        CCVirtualGoodsStorage::getInstance()->assignCurrentUpgrade(good, this, notify, error);
        
        return CCLifetimeVG::give(amount, notify, error);
    }
    
    int CCUpgradeVG::take(int amount, bool notify, CCError **error) {
        const char *goodItemId = getGoodItemId()->getCString();
        CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(goodItemId, error));
        
        if (good == NULL) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat("VirtualGood with itemId: %s doesn't exist! Can't downgrade.",
                                                                    goodItemId)->getCString());
            return 0;
        }
        
        CCUpgradeVG *upgradeVG = CCVirtualGoodsStorage::getInstance()->getCurrentUpgrade(good, error);
        
        // Case: Upgrade is not assigned to this Virtual Good
        if (upgradeVG != this) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat("You can't take an upgrade that's not currently assigned. The UpgradeVG %s is not assigned to the VirtualGood: %s",
                                                                    getName()->getCString(), good->getName()->getCString())->getCString());
            return 0;
        }
        
        if (!CCSoomlaUtils::isNullOrEmpty(getPrevItemId())) {
            const char* prevItemId = getPrevItemId()->getCString();
            CCUpgradeVG *prevUpgradeVG = dynamic_cast<CCUpgradeVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(prevItemId, error));
            
            // Case: downgrade is not possible because previous upgrade does not exist
            if (prevUpgradeVG == NULL) {
                CCSoomlaUtils::logError(TAG, __String::createWithFormat("Previous UpgradeVG with itemId: %s doesn't exist! Can't downgrade.",
                                                                        prevItemId)->getCString());
                return 0;
            }
            
            // Case: downgrade is successful!
            CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Downgrading %s to: %s",
                                                                    good->getName()->getCString(), prevUpgradeVG->getName()->getCString())->getCString());

            CCVirtualGoodsStorage::getInstance()->assignCurrentUpgrade(good, prevUpgradeVG, notify, error);
        }
        
        // Case: first Upgrade in the series - so we downgrade to NO upgrade.
        else {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat("Downgrading %s to NO-UPGRADE",
                                                                    good->getName()->getCString())->getCString());
            CCVirtualGoodsStorage::getInstance()->removeUpgrades(good, notify, error);
        }
        
        return CCLifetimeVG::take(amount, notify, error);
    }


    const char *CCUpgradeVG::getType() const {
        return CCStoreConsts::JSON_JSON_TYPE_UPGRADE_VG;
    }

    CCUpgradeVG::~CCUpgradeVG() {
        CC_SAFE_RELEASE(mGoodItemId);
        CC_SAFE_RELEASE(mPrevItemId);
        CC_SAFE_RELEASE(mNextItemId);
    }
}
