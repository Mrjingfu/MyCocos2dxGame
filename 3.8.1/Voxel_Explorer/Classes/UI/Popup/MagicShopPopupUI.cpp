//
//  ShopPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "MagicShopPopupUI.h"
#include "NpcDataManager.hpp"
#include "BagMangerLayerUI.h"
#include "ItemShopBuyPopupUI.hpp"
#include "PopupUILayerManager.h"
#include "ItemShopBuyPopupUI.hpp"
MagicShopPopupUI::MagicShopPopupUI()
{
    m_cActionType       = eNone;
    m_eShopType         = ST_MAGIC;

}
MagicShopPopupUI::~MagicShopPopupUI()
{
    
}
bool MagicShopPopupUI::init()
{
    if (!ShopPopupUI::init())
        return false;
    
    return true;
    
}
bool MagicShopPopupUI::addEvents()
{
    if (!ShopPopupUI::addEvents())
        return false;
    return true;
}
const std::vector<PickableItemProperty*>& MagicShopPopupUI::getShopItems() const
{
    return NpcDataManager::getInstance()->getMagicShop();
}

void MagicShopPopupUI::shopItemOpe(int itemId)
{
    ItemShopBuyPopupUI* shopItem = static_cast<ItemShopBuyPopupUI*>( PopupUILayerManager::getInstance()->openPopup(ePopupItemShopBuy));
    if (shopItem) {
        shopItem->setItemShopProp(m_eShopType,itemId);
        shopItem->registerCloseCallback(CC_CALLBACK_0(ShopPopupUI::refreshUIView, this));
    }
}


