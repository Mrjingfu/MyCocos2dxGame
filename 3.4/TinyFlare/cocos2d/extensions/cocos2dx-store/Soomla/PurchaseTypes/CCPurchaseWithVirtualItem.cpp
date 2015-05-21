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

#include "CCPurchaseWithVirtualItem.h"
#include "CCSoomlaUtils.h"
#include "CCStoreInfo.h"
#include "CCPurchasableVirtualItem.h"
#include "CCStoreEventDispatcher.h"
#include "CCVirtualGoodsStorage.h"
#include "CCVirtualCurrencyStorage.h"

namespace soomla {
    USING_NS_CC;
    
    #define TAG "SOOMLA PurchaseWithVirtualItem"
    
    CCPurchaseWithVirtualItem *CCPurchaseWithVirtualItem::create(cocos2d::__String *itemId, cocos2d::__Integer *amount) {
        CCPurchaseWithVirtualItem *ret = new CCPurchaseWithVirtualItem();
        if (ret->init(itemId, amount)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCPurchaseWithVirtualItem::init(cocos2d::__String *itemId, cocos2d::__Integer *amount) {
        setItemId(itemId);
        setAmount(amount);

        return true;
    }
    
    void CCPurchaseWithVirtualItem::buy(const char* payload, CCError **error) {
        const char *associatedItemId = getAssociatedItemId()->getCString();
        if (payload == NULL) {
            payload = "";
        }
        CCPurchasableVirtualItem *associatedItem = dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(associatedItemId, error));
        if (associatedItem == NULL) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat("Trying to buy an non-existing associated item: %s", associatedItemId)->getCString());
            return;
        }
        
        const char *targetItemId = getItemId()->getCString();
        int amount = getAmount()->getValue();
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Trying to buy a %s with %d pieces of %s",
                                                                associatedItem->getName()->getCString(),
                                                                amount,
                                                                targetItemId)->getCString());
        
        CCVirtualItem *item = CCStoreInfo::sharedStoreInfo()->getItemByItemId(targetItemId, error);
        if (item == NULL) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat("Target virtual item %s doesn't exist !", targetItemId)->getCString());
            return;
        }
        
        CCStoreEventDispatcher::getInstance()->onItemPurchaseStarted(associatedItem, true);
        
        int balance = item->getBalance(error);
        
        if (balance < amount){
            __String *errorStr = __String::createWithFormat("You tried to buy with itemId: %s but you don't have enough funds to buy it.",
                                                            item->getItemId()->getCString());
            CCError::tryFillError(error, errorStr, TAG);
            return;
        }
        
        item->take(amount);
        
        associatedItem->give(1);
        
        CCStoreEventDispatcher::getInstance()->onItemPurchased(associatedItem, __String::create(payload), true);
    }
    
    bool CCPurchaseWithVirtualItem::canAfford(CCError **error) {
        const char *associatedItemId = getAssociatedItemId()->getCString();
        CCPurchasableVirtualItem *associatedItem = dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(associatedItemId, error));
        if (associatedItem == NULL) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat("Trying to buy an non-existing associated item: %s", associatedItemId)->getCString());
            return false;
        }
        
        const char *targetItemId = getItemId()->getCString();
        int amount = getAmount()->getValue();
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Checking affordability of %s with %d pieces of %s",
                                                                associatedItem->getName()->getCString(),
                                                                amount,
                                                                targetItemId)->getCString());
        
        CCVirtualItem *item = CCStoreInfo::sharedStoreInfo()->getItemByItemId(targetItemId, error);
        if (item == NULL) {
            CCSoomlaUtils::logError(TAG, __String::createWithFormat("Target virtual item %s doesn't exist !", targetItemId)->getCString());
            return false;
        }
        
        int balance = item->getBalance(error);
        
        return balance >= amount;
    }

    CCPurchaseWithVirtualItem::~CCPurchaseWithVirtualItem() {
        CC_SAFE_RELEASE(mItemId);
        CC_SAFE_RELEASE(mAmount);
    }
}
