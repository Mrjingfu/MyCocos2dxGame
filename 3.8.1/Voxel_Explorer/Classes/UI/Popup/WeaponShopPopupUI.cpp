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
WeaponShopPopupUI::WeaponShopPopupUI()
{
    m_cActionType       = eNone;


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

void WeaponShopPopupUI::updateShopDataItems()
{
//    for (int i=0; i<NpcDataManager::getInstance()->getMagicShop().size(); i++)
//    {
//        PickableItemProperty* property = NpcDataManager::getInstance()->getMagicShop()[i];
//        ui::ImageView* img =static_cast<ui::ImageView*>( m_pShopGridView->getItem(i));
//        if (property && img)
//        {
//            m_pShopMangerLayer->addItem(i, property->getInstanceID(), img->getPosition(), property->getIconRes());
//        }
//    }
}
void WeaponShopPopupUI::shopItemOpe(int itemId)
{
    
}

