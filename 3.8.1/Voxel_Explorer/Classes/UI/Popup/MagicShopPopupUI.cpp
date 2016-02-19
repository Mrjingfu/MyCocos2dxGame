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



