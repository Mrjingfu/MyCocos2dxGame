//
//  BagShopLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#include "BagShopLayer.hpp"
#include "BagMangerLayerUI.h"
#include "PlayerProperty.hpp"
#include "PopupUILayerManager.h"
#include "ItemShopSellPopupUI.hpp"
#include "ShopPopupUI.h"
BagShopLayer::BagShopLayer()
{
    
}
BagShopLayer::~BagShopLayer()
{
    
}

void BagShopLayer::refreshUIView()
{
    BagLayer::refreshUIView();
    
    //商店界面没有扩展按钮
    if (m_pBtnBagExtend) {
        m_pBtnBagExtend->setVisible(false);
    }
}

void BagShopLayer::bagItemOpe(int itemId)
{
    if (itemId==-1)
        return;
    
    PickableItemProperty* itemProp = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(itemId));
    if (!itemProp)
    {
        CCLOG("itemProp is empty");
        return;
    }
    
    //判断点击的武器 是否已经有装备过
    int weaponId = int(PlayerProperty::getInstance()->getEquipedWeaponID());
    int armorId = int(PlayerProperty::getInstance()->getEquipedArmorID());
    int OrnamentId = int(PlayerProperty::getInstance()->getEquipedOrnamentsID());
    int secondWeaponId = int(PlayerProperty::getInstance()->getEquipedSecondWeaponID());
    int equipId = -1;
    ItemPopupUI* Equippopupui = nullptr;
    if (itemProp->getPickableItemPropertyType() == PickableItemProperty::PIPT_WEAPON && itemId !=weaponId )
    {
        equipId = weaponId;
    }else if (itemProp->getPickableItemPropertyType() == PickableItemProperty::PIPT_ARMOR && itemId !=armorId )
    {
        equipId = armorId;
    }else if (itemProp->getPickableItemPropertyType() == PickableItemProperty::PIPT_MAGIC_ORNAMENT && itemId !=OrnamentId )
    {
        equipId = OrnamentId;
    }else if (itemProp->getPickableItemPropertyType() == PickableItemProperty::PIPT_SECOND_WEAPON && itemId !=secondWeaponId )
    {
        equipId = secondWeaponId;
    }
    
    ItemShopSellPopupUI* shopItem = static_cast<ItemShopSellPopupUI*>( PopupUILayerManager::getInstance()->openPopup(ePopupItemShopSell));
    if (shopItem) {
        shopItem->setItemId(itemId);
        shopItem->registerCloseCallback(CC_CALLBACK_0(BagShopLayer::refreshUIView, this));
        
        //如果有装备过 打开装备过的武器
        if (equipId!=-1)
        {
            ItemPopupUI* Equippopupui = static_cast<ItemPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupType::ePopupEquipItem));
            if (Equippopupui)
            {
                Equippopupui->setItemId(equipId);
                Equippopupui->setDarkLayerVisble(false);
                cocos2d::Size itemRootNode = shopItem->getRootNode()->getContentSize();
                cocos2d::Size equipRootNode = Equippopupui->getRootNode()->getContentSize();
                float y = 0.0f;
                if (equipRootNode.height > itemRootNode.height) {
                    y = SCREEN_HEIGHT*0.5 + equipRootNode.height*0.5;
                }else
                    y = SCREEN_HEIGHT*0.5 + itemRootNode.height*0.5;
                
                Equippopupui->getRootNode()->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
                shopItem->getRootNode()->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
                shopItem->getRootNode()->setPosition(cocos2d::Vec2(SCREEN_WIDTH*0.5+5+itemRootNode.width*0.5,y));
                Equippopupui->getRootNode()->setPosition(cocos2d::Vec2(SCREEN_WIDTH*0.5-equipRootNode.width*0.5,y));
                
            }
        }

    }
}

std::vector<PickableItemProperty*> BagShopLayer::getItems()
{

    std::vector<PickableItemProperty*> bagItems = BagLayer::getItems();
    std::vector<PickableItemProperty*> items;
    int weaponId = int(PlayerProperty::getInstance()->getEquipedWeaponID());
    int armorId = int(PlayerProperty::getInstance()->getEquipedArmorID());
    int OrnamentId = int(PlayerProperty::getInstance()->getEquipedOrnamentsID());
    int secondWeaponId = int(PlayerProperty::getInstance()->getEquipedSecondWeaponID());
    
    for (int i =0 ; i<bagItems.size(); i++)
    {
        PickableItemProperty* itemProp =bagItems[i];
        if (!itemProp) {
            continue;
        }
        
        if (weaponId ==  itemProp->getInstanceID()) {
            continue;
        }
        if (armorId ==  itemProp->getInstanceID()) {
             continue;
        }
        if (OrnamentId ==  itemProp->getInstanceID()) {
            continue;
        }
        if (secondWeaponId ==  itemProp->getInstanceID()) {
            continue;
        }
        
        if (itemProp->getPickableItemType()>=PickableItem::PIT_KEY_BOSS && itemProp->getPickableItemType()<=PickableItem::PIT_KEY_ROOM) {
            continue;
        }

        items.push_back(itemProp);
    }

    return items;
}
void BagShopLayer::sortItem(BagLayer::eSortBagType sortType, std::vector<PickableItemProperty *> &items)
{
    
//    std::sort(items.begin(), items.end(), [](PickableItemProperty* prop1,PickableItemProperty* prop2){
//        return prop1->getPickableItemPropertyType() > prop2->getPickableItemPropertyType();
//    });
//    
//    m_bisItemSort = false;
}