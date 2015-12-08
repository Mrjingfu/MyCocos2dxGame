//
//  WeirdoPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/1.
//
//

#include "GambleShopPopupUI.hpp"
#include "ItemShopBuyPopupUI.hpp"
#include "PopupUILayerManager.h"
#include "NpcDataManager.hpp"
#include "BagMangerLayerUI.h"
GambleShopPopupUI::GambleShopPopupUI()
{
    m_cActionType       = eNone;
    m_eShopType         = ST_GAMBLE;
    
}
GambleShopPopupUI::~GambleShopPopupUI()
{
    
}
bool GambleShopPopupUI::init()
{
    if (!ShopPopupUI::init())
        return false;
    
    return true;
    
}
bool GambleShopPopupUI::addEvents()
{
    if (!ShopPopupUI::addEvents())
        return false;
    return true;
}
const std::vector<PickableItemProperty*>& GambleShopPopupUI::getShopItems() const
{
    return NpcDataManager::getInstance()->getTheifRoom();
}

void GambleShopPopupUI::updateShopDataItems()
{
    std::vector<PickableItemProperty*> itemProps = getShopItems();
    
    for (int i=0; i<itemProps.size(); i++)
    {
        PickableItemProperty* property = itemProps[i];
        ui::ImageView* img =static_cast<ui::ImageView*>( m_pShopGridView->getItem(i));
        if (property && img)
        {
            m_pShopMangerLayer->addItem(i, property->getInstanceID(), img->getPosition(), property->getIconRes());
            if (!property->isIdentified()) {
                m_pShopMangerLayer->setItemInIentify(property->getInstanceID(), img->getPosition());
            }
        }
    }

}
void GambleShopPopupUI::shopItemOpe(int itemId)
{
    ItemShopBuyPopupUI* shopItem = static_cast<ItemShopBuyPopupUI*>( PopupUILayerManager::getInstance()->openPopup(ePopupItemShopBuy));
    if (shopItem) {
        shopItem->setItemShopProp(m_eShopType,itemId);
        shopItem->registerCloseCallback(CC_CALLBACK_0(ShopPopupUI::refreshUIView, this));
    }

}
