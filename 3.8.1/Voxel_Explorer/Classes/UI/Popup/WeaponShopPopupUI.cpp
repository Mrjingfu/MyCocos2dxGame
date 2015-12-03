//
//  ShopPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "WeaponShopPopupUI.h"
#include "NpcDataManager.hpp"
#include "BagMangerLayerUI.h"
#include "ItemShopBuyPopupUI.hpp"
#include "PopupUILayerManager.h"
WeaponShopPopupUI::WeaponShopPopupUI()
{
    m_cActionType       = eNone;
    m_eShopType         = ST_WEAPON;

}
WeaponShopPopupUI::~WeaponShopPopupUI()
{
    
}
bool WeaponShopPopupUI::init()
{
    if (!ShopPopupUI::init())
        return false;
    return true;
    
}
bool WeaponShopPopupUI::addEvents()
{
    if (!ShopPopupUI::addEvents())
        return false;

    
    return true;
}

const std::vector<PickableItemProperty*>& WeaponShopPopupUI::getShopItems() const
{
    return NpcDataManager::getInstance()->getEquipMentShop();
}


void WeaponShopPopupUI::shopItemOpe(int itemId)
{
    ItemShopBuyPopupUI* shopItem = static_cast<ItemShopBuyPopupUI*>( PopupUILayerManager::getInstance()->openPopup(ePopupItemShopBuy));
    if (shopItem) {
        shopItem->setItemShopProp(m_eShopType,itemId);
        shopItem->registerCloseCallback(CC_CALLBACK_0(ShopPopupUI::refreshUIView, this));
    }
}


