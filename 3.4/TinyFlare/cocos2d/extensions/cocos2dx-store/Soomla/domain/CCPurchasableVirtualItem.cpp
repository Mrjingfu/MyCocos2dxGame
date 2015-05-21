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



#include "CCPurchasableVirtualItem.h"

#include "../PurchaseTypes/CCPurchaseWithVirtualItem.h"
#include "../PurchaseTypes/CCPurchaseWithMarket.h"

namespace soomla {
    
    using namespace cocos2d;
    
    bool CCPurchasableVirtualItem::init(cocos2d::__String* name, cocos2d::__String* description, cocos2d::__String* itemId, CCPurchaseType * purchaseType) {
        bool bRet = CCVirtualItem::init(itemId, name, description);
        if (bRet) {
            setPurchaseType(purchaseType);
            
            purchaseType->setAssociatedItemId(getItemId());
        }
        return bRet;
    }
    
    bool CCPurchasableVirtualItem::initWithDictionary(cocos2d::__Dictionary* dict) {
        bool bRet = CCVirtualItem::initWithDictionary(dict);
        if (bRet) {
            fillPurchaseTypeFromDict(dict);
            return true;
        } else {
            return false;
        }
    }

    CCPurchasableVirtualItem::~CCPurchasableVirtualItem() {
        CC_SAFE_RELEASE(mPurchaseType);
    }
    
    cocos2d::__Dictionary*CCPurchasableVirtualItem::toDictionary() {
        __Dictionary* dict = CCVirtualItem::toDictionary();

        putPurchaseTypeToDict(dict);

        return dict;
    }
    
    bool CCPurchasableVirtualItem::canAfford(CCError **error) {
        return getPurchaseType()->canAfford(error);
    }
    
    void CCPurchasableVirtualItem::buy(const char* payload, CCError **error) {
        if (!canBuy()) {
            return;
        }
        
        if (payload == NULL) {
            payload = "";
        }
        
        getPurchaseType()->buy(payload, error);
    }

    void CCPurchasableVirtualItem::fillPurchaseTypeFromDict(__Dictionary *dict) {
        __Dictionary *purchasableDict = dynamic_cast<__Dictionary *>(dict->objectForKey(CCStoreConsts::JSON_PURCHASABLE_ITEM));
        CC_ASSERT(purchasableDict);
        __String* purchaseTypeStr = dynamic_cast<__String *>(purchasableDict->objectForKey(CCStoreConsts::JSON_PURCHASE_TYPE));
        CCAssert(purchaseTypeStr != NULL, "invalid object type in dictionary");
        if (purchaseTypeStr->compare(CCStoreConsts::JSON_PURCHASE_TYPE_MARKET) == 0) {
            __Dictionary *marketItemDict = dynamic_cast<__Dictionary *>(purchasableDict->objectForKey(CCStoreConsts::JSON_PURCHASE_MARKET_ITEM));
            CC_ASSERT(marketItemDict);
            setPurchaseType(CCPurchaseWithMarket::createWithMarketItem(
                    CCMarketItem::createWithDictionary(marketItemDict)));
        } else if (purchaseTypeStr->compare(CCStoreConsts::JSON_PURCHASE_TYPE_VI) == 0) {
            __String *itemId = dynamic_cast<__String *>(purchasableDict->objectForKey(CCStoreConsts::JSON_PURCHASE_VI_ITEM_ID));
            CC_ASSERT(itemId);
            __Integer *amount = dynamic_cast<__Integer *>(purchasableDict->objectForKey(CCStoreConsts::JSON_PURCHASE_VI_AMOUNT));
            CC_ASSERT(amount);

            setPurchaseType(CCPurchaseWithVirtualItem::create(itemId, amount));
        } else {
            CC_ASSERT(false);
            cocos2d::log("Couldn't determine what type of class is the given purchaseType.");
        }
        
        CCPurchaseType *purchaseType = getPurchaseType();
        if (purchaseType != NULL) {
            purchaseType->setAssociatedItemId(getItemId());
        }
    }

    void CCPurchasableVirtualItem::putPurchaseTypeToDict(__Dictionary *dict) {
        __Dictionary *purchasableObj = __Dictionary::create();

        if (dynamic_cast<CCPurchaseWithMarket *>(mPurchaseType)) {
            purchasableObj->setObject(__String::create(CCStoreConsts::JSON_PURCHASE_TYPE_MARKET), CCStoreConsts::JSON_PURCHASE_TYPE);

            CCPurchaseWithMarket *purchaseWithMarket = (CCPurchaseWithMarket *)mPurchaseType;
            CCMarketItem *mi = purchaseWithMarket->getMarketItem();
            purchasableObj->setObject(mi->toDictionary(), CCStoreConsts::JSON_PURCHASE_MARKET_ITEM);
        }
        else if (dynamic_cast<CCPurchaseWithVirtualItem *>(mPurchaseType)) {
            CCPurchaseWithVirtualItem *purchaseWithVirtualItem = (CCPurchaseWithVirtualItem *)mPurchaseType;
            purchasableObj->setObject(__String::create(CCStoreConsts::JSON_PURCHASE_TYPE_VI), CCStoreConsts::JSON_PURCHASE_TYPE);
            purchasableObj->setObject(purchaseWithVirtualItem->getItemId(), CCStoreConsts::JSON_PURCHASE_VI_ITEM_ID);
            purchasableObj->setObject(purchaseWithVirtualItem->getAmount(), CCStoreConsts::JSON_PURCHASE_VI_AMOUNT);
        } else {
            CC_ASSERT(false);
        }

        dict->setObject(purchasableObj, CCStoreConsts::
        JSON_PURCHASABLE_ITEM);
    }


}