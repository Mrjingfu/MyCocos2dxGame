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



#ifndef __CCVirtualCategory_H_
#define __CCVirtualCategory_H_


#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCDomain.h"
#include "CCStoreConsts.h"

namespace soomla {
	/** 
     @class CCVirtualCategory
     @brief A category for virtual items.

     This class is a definition of a category. A single category can be 
     associated with many virtual goods. Virtual categories help in organizing 
     your economy's virtual goods.
	 */
    class CCVirtualCategory : public CCDomain {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String*, mName, Name, CCStoreConsts::JSON_CATEGORY_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__Array*, mGoodItemIds, GoodItemIds, CCStoreConsts::JSON_CATEGORY_GOODS_ITEM_IDS);
    public:
	CCVirtualCategory(): mName(NULL), mGoodItemIds(NULL) {};

		/**
         Creates a virtual category.
         @param name The name of the category.
         @param goodItemIds An array containing the item ids of all the items 
                in this category.
         @return The virtual category.
		 */
        static CCVirtualCategory *create(cocos2d::__String *name, cocos2d::__Array *goodItemIds);

		/**
         Creates a virtual category.
         @param dict A dictionary containing keys to each of the parameters
                required by the create function.
         @return The virtual category.
		*/
        SL_CREATE_WITH_DICTIONARY(CCVirtualCategory);

        bool init(cocos2d::__String *name, cocos2d::__Array *goodItemIds);
        bool initWithDictionary(cocos2d::__Dictionary *dict);

        /**
        Converts this `~CCVirtualCategory` to a `CCDictionary`.
        @return `CCDictionary` representation of this `~CCVirtualCategory`.
        */
        cocos2d::__Dictionary *toDictionary();

        virtual ~CCVirtualCategory();
    };
};


#endif //__CCVirtualCategory_H_
