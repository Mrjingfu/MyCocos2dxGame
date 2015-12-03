//
//  OldLadyPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/1.
//
//

#include "AlchemyShopPopupUI.hpp"
#include "MagicShopPopupUI.h"
#include "NpcDataManager.hpp"
#include "BagMangerLayerUI.h"
#include "ItemShopBuyPopupUI.hpp"
#include "PopupUILayerManager.h"
#include "ItemShopBuyPopupUI.hpp"
AlchemyShopPopupUI::AlchemyShopPopupUI()
{
    m_cActionType       = eNone;
    m_eShopType         = ST_ALCHEMY;
    
}
AlchemyShopPopupUI::~AlchemyShopPopupUI()
{
    
}
bool AlchemyShopPopupUI::init()
{
    if (!ShopPopupUI::init())
        return false;
    
    return true;
    
}
bool AlchemyShopPopupUI::addEvents()
{
    if (!ShopPopupUI::addEvents())
        return false;
    return true;
}
const std::vector<PickableItemProperty*>& AlchemyShopPopupUI::getShopItems() const
{
    return NpcDataManager::getInstance()->getAlchemistRoom();
}

void AlchemyShopPopupUI::shopItemOpe(int itemId)
{
    ItemShopBuyPopupUI* shopItem = static_cast<ItemShopBuyPopupUI*>( PopupUILayerManager::getInstance()->openPopup(ePopupItemShopBuy));
    if (shopItem) {
        shopItem->setItemShopProp(m_eShopType,itemId);
        shopItem->registerCloseCallback(CC_CALLBACK_0(ShopPopupUI::refreshUIView, this));
    }
}