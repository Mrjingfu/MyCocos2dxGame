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



#ifndef __CCVirtualCurrencyPack_H_
#define __CCVirtualCurrencyPack_H_

#include "CCSoomlaMacros.h"
#include "../CCPurchasableVirtualItem.h"
#include "CCStoreConsts.h"

namespace soomla {
	/** 
     @class CCVirtualCurrencyPack
     @brief A virtual currency pack.

     Every game has its virtual currencies. Here you represent a pack of a 
     specific `CCVirtualCurrency`. Real Game Example: If virtual currency in 
     your game is a 'Coin', you will sell packs of 'Coins' (e.g. "10 Coins Set" 
     or "Super Saver Pack").
     
     NOTE: In case you want this item to be available for purchase in the native 
     store (with real money) you'll need to define the item in the App Store,
     Google Play, etc..
     
     Inheritance: CCVirtualCurrencyPack > CCPurchasableVirtualItem > 
     CCVirtualItem
	 */
    class CCVirtualCurrencyPack : public CCPurchasableVirtualItem {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__Integer *, mCurrencyAmount, CurrencyAmount, CCStoreConsts::JSON_CURRENCY_PACK_CURRENCY_AMOUNT);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mCurrencyItemId, CurrencyItemId, CCStoreConsts::JSON_CURRENCY_PACK_CURRENCY_ITEM_ID);
    public:
	CCVirtualCurrencyPack(): CCPurchasableVirtualItem(), mCurrencyAmount(NULL), mCurrencyItemId(NULL) {};

		/**
         Creates a `CCVirtualCurrencyPack`.
         @param name see parent.
         @param description see parent.
         @param itemId see parent.
         @param currencyAmount The amount of currency in the pack.
         @param currencyItemId The itemId of the currency associated with this 
                pack.
         @param purchaseType see parent.
         @return The currency pack.
		*/
        static CCVirtualCurrencyPack *create(cocos2d::__String* name, cocos2d::__String* description,
											 cocos2d::__String* itemId, cocos2d::__Integer* currencyAmount, cocos2d::__String* currencyItemId,
											 CCPurchaseType * purchaseType);
        bool init(cocos2d::__String* name, cocos2d::__String* description,
                cocos2d::__String* itemId, cocos2d::__Integer* currencyAmount, cocos2d::__String* currencyItemId,
                CCPurchaseType * purchaseType);

		/**
         Creates a `CCVirtualCurrencyPack`.
         @param dict A dictionary containing keys to each of the parameters 
                required by the create function.
         @return The pack.
		*/
        SL_CREATE_WITH_DICTIONARY(CCVirtualCurrencyPack);
        bool initWithDictionary(cocos2d::__Dictionary *dict);

        /**
        Converts this `CCVirtualCurrencyPack` to a `CCDictionary`.
        @return `CCDictionary` representation of this `CCVirtualCurrencyPack`.
        */
        cocos2d::__Dictionary *toDictionary();

        virtual ~CCVirtualCurrencyPack();

        virtual const char *getType() const;
        
        /**
         See parent
         */
        virtual bool canBuy() { return true; }
        
        /**
         See parent
         */
        virtual int give(int amount, bool notify, CCError **error = NULL);
        
        /**
         See parent
         */
        virtual int take(int amount, bool notify, CCError **error = NULL);
        
        /**
         See parent
         */
        virtual int resetBalance(int balance, bool notify, CCError **error = NULL);
        /**
         See parent
         */
        virtual int getBalance(CCError **error = NULL);
    };
};


#endif //__CCVirtualCurrencyPack_H_
