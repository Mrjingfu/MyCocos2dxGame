//
//  BagEquipLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/15.
//
//

#include "BagRefineLayer.hpp"
#include "BagMangerLayerUI.h"
#include "PlayerProperty.hpp"
#include "ItemPopupUI.h"
#include "ItemSelectPopupUI.hpp"
#include "PopupUILayerManager.h"
BagRefineLayer::BagRefineLayer()
{
    
}
BagRefineLayer::~BagRefineLayer()
{
    
}
bool BagRefineLayer::init()
{
    if (!BagLayer::init())
        return false;
    
    
    //商店界面没有扩展按钮
    if (m_pBtnBagExtend) {
        m_pBtnBagExtend->setVisible(false);
    }
    if (m_pBtnAllBag) {
        m_pBtnAllBag->setVisible(false);
    }
    if (m_pBtnWeaponBag) {
        m_pBtnWeaponBag->setVisible(false);
    }
    if (m_pBtnPotionBag) {
        m_pBtnPotionBag->setVisible(false);
    }
    
    
    return true;
}
std::vector<PickableItemProperty*> BagRefineLayer::getItems()
{
   std::vector<PickableItemProperty*> bagItems = BagLayer::getItems();
   std::vector<PickableItemProperty*> items;
    
    for (int i =0 ; i<bagItems.size(); i++)
    {
        PickableItemProperty* itemProp =bagItems[i];
        
        if (!itemProp) {
            continue;
        }
        
        PickableItemProperty::PickableItemPropertyType itemtype =itemProp->getPickableItemPropertyType();
        
        if (!(itemtype ==PickableItemProperty::PIPT_WEAPON ||itemtype ==PickableItemProperty::PIPT_SECOND_WEAPON||
              itemtype ==PickableItemProperty::PIPT_ARMOR ||itemtype ==PickableItemProperty::PIPT_MAGIC_ORNAMENT) )
            continue;

        if (itemProp->getQuality() == PICKABLEITEM_QUALITY::PIQ_GENERAL) {
            continue;
        }

        
        items.push_back(itemProp);
    }
    return items;
}
void BagRefineLayer::bagItemOpe(int itemId)
{
    if (itemId==-1)
        return;
    
    PickableItemProperty* itemProp = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(itemId));
    if (!itemProp)
    {
        CCLOG("itemProp is empty");
        return;
    }
    
    PopupUILayer* ItemPopup = nullptr;
    PopupUILayer* equipPopup = nullptr;
    bool isOpenPopup =PopupUILayerManager::getInstance()->isOpenPopup(ePopupType::ePopupItemSelect,ItemPopup);
    bool isEquipPopup =PopupUILayerManager::getInstance()->isOpenPopup(ePopupType::ePopupItem,equipPopup);
    if (isOpenPopup || isEquipPopup) {
        return;
    }
    
    //判断点击的武器 是否已经有装备过
    int weaponId = int(PlayerProperty::getInstance()->getEquipedWeaponID());
    int armorId = int(PlayerProperty::getInstance()->getEquipedArmorID());
    int OrnamentId = int(PlayerProperty::getInstance()->getEquipedOrnamentsID());
    int secondWeaponId = int(PlayerProperty::getInstance()->getEquipedSecondWeaponID());
    int equipId = -1;
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
    
    ItemSelectPopupUI* shopItem = static_cast<ItemSelectPopupUI*>( PopupUILayerManager::getInstance()->openPopup(ePopupItemSelect));
    if (shopItem) {
        shopItem->setItemId(itemId);
        shopItem->registerCloseCallbackO([this](Ref* ref){
        
            if(ref)
            {
                this->setCloseCallbackParamO(ref);
                this->executeCloseBackO();
            }
            
        });
        
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

