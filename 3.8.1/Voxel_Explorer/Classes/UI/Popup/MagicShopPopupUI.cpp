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
MagicShopPopupUI::MagicShopPopupUI()
{
    m_cActionType       = eNone;
   

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
void MagicShopPopupUI::updateShopDataItems()
{
    
}
void MagicShopPopupUI::shopItemOpe(int itemId)
{
//    for (int i=0; i<NpcDataManager::getInstance()->getMagicShop().size(); i++) {
//        PickableItemProperty* property = NpcDataManager::getInstance()->getMagicShop()[i];
//        ui::ImageView* img =static_cast<ui::ImageView*>( m_pShopGridView->getItem(i));
//        if (property && img) {
//            m_pShopMangerLayer->addItem(i, property->getInstanceID(), img->getPosition(), property->getIconRes());
//        }
//    }
}


