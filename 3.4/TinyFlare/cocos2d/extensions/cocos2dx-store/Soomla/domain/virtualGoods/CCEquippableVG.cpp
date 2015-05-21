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

#include "CCEquippableVG.h"
#include "CCVirtualGoodsStorage.h"
#include "CCVirtualCategory.h"
#include "CCSoomlaUtils.h"
#include "CCStoreInfo.h"

#define EQUIPPING_MODEL_LOCAL "local"
#define EQUIPPING_MODEL_CATEGORY "category"
#define EQUIPPING_MODEL_GLOBAL "global"

namespace soomla {
    
    USING_NS_CC;
    
    #define TAG "SOOMLA EquippableVG"

    CCEquippableVG *CCEquippableVG::create(__Integer *equippingModel, __String *name, __String *description, __String *itemId, CCPurchaseType *purchaseType) {
        CCEquippableVG *ret = new CCEquippableVG();
        if (ret->init(equippingModel, name, description, itemId, purchaseType)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCEquippableVG::init(__Integer *equippingModel, __String *name, __String *description, __String *itemId, CCPurchaseType *purchaseType) {
        bool res = CCLifetimeVG::init(name, description, itemId, purchaseType);
        if (res) {
            setEquippingModel(equippingModel);
            return true;
        } else {
            return false;
        }
    }
    
    bool CCEquippableVG::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool res = CCLifetimeVG::initWithDictionary(dict);
        if (res) {
            fillEquippingModelFromDict(dict);
            return true;
        } else {
            return false;
        }
    }

    __Dictionary *CCEquippableVG::toDictionary() {
        __Dictionary *dict = CCPurchasableVirtualItem::toDictionary();

        putEquippingModelToDict(dict);

        return dict;
    }

    const char *CCEquippableVG::getType() const {
        return CCStoreConsts::JSON_JSON_TYPE_EQUIPPABLE_VG;
    }

    void CCEquippableVG::fillEquippingModelFromDict(__Dictionary *dict) {
        __String*equippingModelStr = dynamic_cast<__String *>(dict->objectForKey(CCStoreConsts::JSON_EQUIPPABLE_EQUIPPING));
        CCAssert(equippingModelStr != NULL, "invalid object type in dictionary");
        if (equippingModelStr->compare(EQUIPPING_MODEL_LOCAL) == 0) {
            setEquippingModel(__Integer::create(kLocal));
        }
        else if (equippingModelStr->compare(EQUIPPING_MODEL_CATEGORY) == 0) {
            setEquippingModel(__Integer::create(kCategory));
        }
        else if (equippingModelStr->compare(EQUIPPING_MODEL_GLOBAL) == 0) {
            setEquippingModel(__Integer::create(kGlobal));
        } else {
            CC_ASSERT(false);
        }
    }

    void CCEquippableVG::putEquippingModelToDict(__Dictionary *dict) {
        EquippingModel equippingModel = (EquippingModel) getEquippingModel()->getValue();
        __String *strEquippingModel;
        switch (equippingModel) {
            case kLocal: {
                strEquippingModel = __String::create(EQUIPPING_MODEL_LOCAL);
                break;
            }
            case kCategory: {
                strEquippingModel = __String::create(EQUIPPING_MODEL_CATEGORY);
                break;
            }
            case kGlobal: {
                strEquippingModel = __String::create(EQUIPPING_MODEL_GLOBAL);
                break;
            }
            default: {
                CC_ASSERT(false);
                strEquippingModel = __String::create("ERROR");
            }
        }
        dict->setObject(strEquippingModel, CCStoreConsts::JSON_EQUIPPABLE_EQUIPPING);
    }

    CCEquippableVG::~CCEquippableVG() {
        CC_SAFE_RELEASE(mEquippingModel);
    }
    
    void CCEquippableVG::equip(bool notify, CCError **error) {
        // only if the user has bought this EquippableVG, the EquippableVG is equipped.
        if (CCVirtualGoodsStorage::getInstance()->getBalance(this) > 0){
            EquippingModel equippingModel = (EquippingModel) getEquippingModel()->getValue();
            if (equippingModel == kCategory) {
                const char *itemId = getItemId()->getCString();
                CCVirtualCategory *category = CCStoreInfo::sharedStoreInfo()->getCategoryForVirtualGood(itemId, error);
                if (category == NULL) {
                    CCSoomlaUtils::logError(TAG, __String::createWithFormat("Tried to unequip all other category VirtualGoods but there was no associated category. virtual good itemId: %s",
                                                                            itemId)->getCString());
                    return;
                }
                
                Ref* obj;
                __Array *goodItemIds = category->getGoodItemIds();
                CCARRAY_FOREACH(goodItemIds, obj) {
                    __String *goodItemIdStr = dynamic_cast<__String *>(obj);
                    const char *goodItemId = goodItemIdStr->getCString();
                    CCEquippableVG *equippableVG = dynamic_cast<CCEquippableVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(goodItemId, error));
                    if (equippableVG == NULL) {
                        CCSoomlaUtils::logError(TAG, __String::createWithFormat("On equip, couldn't find one of the itemIds in the category. Continuing to the next one. itemId: %s",
                                                                                goodItemId)->getCString());
                    }
                    else if (equippableVG != this) {
                        equippableVG->unequip(notify, error);
                    }
                }
            } else if (equippingModel == kGlobal) {
                Ref* obj;
                __Array *virtualGoods = CCStoreInfo::sharedStoreInfo()->getGoods();
                CCARRAY_FOREACH(virtualGoods, obj) {
                    CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(virtualGoods);
                    CCEquippableVG *equippableVG = dynamic_cast<CCEquippableVG *>(good);
                    if ((good != this) && (equippableVG != NULL)) {
                        equippableVG->unequip(notify, error);
                    }
                }
            }
            
            CCVirtualGoodsStorage::getInstance()->equip(this, notify, error);
        }
        else {
            __String *errorStr = __String::createWithFormat("You tried to equip virtual good with itemId: %s \
                                                            but you don't have any of it.", getItemId()->getCString());
            CCError::tryFillError(error, errorStr, TAG);
        }
    }
    
    void CCEquippableVG::unequip(bool notify, CCError **error) {
        CCVirtualGoodsStorage::getInstance()->unequip(this, notify, error);
    }
}
