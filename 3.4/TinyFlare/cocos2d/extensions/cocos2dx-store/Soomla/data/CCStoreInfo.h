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



#ifndef __CCStoreInfo_H_
#define __CCStoreInfo_H_

#include "cocos2d.h"
#include "CCStoreAssets.h"
#include "../domain/CCVirtualItem.h"
#include "../domain/virtualGoods/CCUpgradeVG.h"
#include "../domain/CCVirtualCategory.h"
#include "CCError.h"

namespace soomla {
	/** 
     @class CCStoreInfo
     @brief An interface to the native `StoreInfo` class.
     
     This class holds the store's metadata including:
     virtual currencies,
     virtual currency packs,
     all virtual goods,
     virtual categories, and
     non-consumables
	*/
	class CCStoreInfo: cocos2d::Ref {
        CC_SYNTHESIZE_RETAIN(cocos2d::__Dictionary *, mVirtualItems, VirtualItems);
        CC_SYNTHESIZE_RETAIN(cocos2d::__Dictionary *, mPurchasableItems, PurchasableItems);
        CC_SYNTHESIZE_RETAIN(cocos2d::__Dictionary *, mGoodsCategories, GoodsCategories);
        CC_SYNTHESIZE_RETAIN(cocos2d::__Dictionary *, mGoodsUpgrades, GoodsUpgrades);
        CC_SYNTHESIZE_RETAIN(cocos2d::__Array*, mCurrencies, Currencies);
        CC_SYNTHESIZE_RETAIN(cocos2d::__Array*, mCurrencyPacks, CurrencyPacks);
        CC_SYNTHESIZE_RETAIN(cocos2d::__Array*, mGoods, Goods);
        CC_SYNTHESIZE_RETAIN(cocos2d::__Array*, mCategories, Categories);
    public:
        
		/**
         This class is a singleton, use this function to access it.
		*/
        static CCStoreInfo *sharedStoreInfo();
        
        /**
         Initializes `CCStoreInfo` on native side and allows using its
         functions.
         @param storeAssets An instance of your store's assets class.
		 */
        static void createShared(CCStoreAssets *storeAssets);
        
        virtual bool init(CCStoreAssets *storeAssets);
        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);
        
        CCStoreInfo() : mVirtualItems(NULL), mPurchasableItems(NULL), mGoodsCategories(NULL),
        mGoodsUpgrades(NULL), mCurrencies(NULL), mCurrencyPacks(NULL), mGoods(NULL), mCategories(NULL) {}

		/**
         Retrieves a single `CCVirtualItem` that resides in the metadata.
         @param itemId The item id of the item to be fetched.
         @param error A `CCError` for error checking.
         @return The virtual item with the given `itemId`.
		 */
        CCVirtualItem *getItemByItemId(const char *itemId, CCError **error = NULL);

		/**
         Retrieves a single `CCPurchasableVirtualItem` that resides in the
         metadata.
         IMPORTANT: The retrieved `CCPurchasableVirtualItem` has a purchaseType 
         of `CCPurchaseWithMarket`. This is why we fetch here with `productId` 
         and not with `itemId` (`productId` is the id of the product in the App
         Store).
         @param productId The product id of the item to be fetched.
         @param error A `CCError` for error checking.
         @return The purchasable virtual item with the given `productId`.
		*/
		CCPurchasableVirtualItem *getPurchasableItemWithProductId(const char *productId, CCError **error = NULL);

		/**
         Retrieves the `CCVirtualCategory` that the `CCVirtualGood` with the 
         given `goodItemId` belongs to.
         @param goodItemId The item id of the virtual good whose category is 
                being retrieved.
         @param error A `CCError` for error checking.
         @return The `CCVirtualCategory` for the `CCVirtualGood` with the given
         `goodItemId`.
		*/
		CCVirtualCategory *getCategoryForVirtualGood(const char *goodItemId, CCError **error = NULL);

		/**
         Retrieves the first `CCUpgradeVG` for the`CCVirtualGood` with the given
         `itemId`.
         @param goodItemId The `CCVirtualGood` whose upgrade is being retrieved.
         @return The first `CCUpgradeVG` for the virtual good with the given
                `itemId`.
		*/
        CCUpgradeVG *getFirstUpgradeForVirtualGood(const char *goodItemId = NULL);

		/**
         Retrieves the last `CCUpgradeVG` for the`CCVirtualGood` with the given
         `itemId`.
         @param goodItemId the `CCVirtualGood` we're searching the upgrade for.
         @return The last `CCUpgradeVG` for the virtual good with the given
                `ItemId`.
		*/
		CCUpgradeVG *getLastUpgradeForVirtualGood(const char *goodItemId = NULL);

		/**
         Retrieves all `CCUpgradeVG`s for the `CCVirtualGood` with the given
         `itemId`.
         @param goodItemId the `CCVirtualGood` we're searching the upgrades for.
         @return Array of all upgrades for the good with the given item id.
         */
        cocos2d::__Array *getUpgradesForVirtualGood(const char *goodItemId = NULL);

        /**
         Replaces the given virtual item, and then saves the store's metadata.
         @param virtualItem The virtual item to save.
         @param saveToDB should the data persist to the local DB.
         */
        void saveItem(CCVirtualItem *virtualItem, bool saveToDB = true);
        
        /**
         Replaces the given virtual items, and then saves the store's metadata.
         @param virtualItems The virtual items to save.
         @param saveToDB should the data persist to the local DB.
         */
        void saveItems(cocos2d::__Array *virtualItems, bool saveToDB = true);
        
        /**
         Saves the store's metadata in the database as JSON.
         */
        virtual void save();
        
        /**
         Converts the store info into a `CCDictionary`.
         @return `CCDictionary` representation of `CCStoreInfo`.
         */
        virtual cocos2d::__Dictionary* toDictionary();
    protected:
        virtual void setStoreAssets(CCStoreAssets *storeAssets);
        virtual void initializeFromDB();
        void updateAggregatedLists();
        void replaceVirtualItem(CCVirtualItem *virtualItem);
        cocos2d::__Dictionary *storeAssetsToDictionary(CCStoreAssets *storeAssets);
    private:
        cocos2d::Ref *createWithRetParams(cocos2d::__Dictionary *retParams);
    };
};

#endif //__CCStoreInfo_H_
