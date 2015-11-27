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
#include "ItemShopPopupUI.hpp"
BagShopLayer::BagShopLayer()
{
    
}
BagShopLayer::~BagShopLayer()
{
    
}

void BagShopLayer::refreshUIView()
{
    BagLayer::refreshUIView();
    
    if (m_BagMsgLayer) {
        m_BagMsgLayer->removeCountForItems();
    }
    
    std::vector<PickableItemProperty*> bagItems = getItems();
    
    for (int i =0; i<bagItems.size(); i++)
    {
        PickableItemProperty* itemProp =bagItems[i];
        ui::ImageView* itemUi = static_cast<ui::ImageView*>( m_pGridView->getItem(i));
        
        if (itemProp && itemUi && itemProp) {
            
            //查看是否可以合并
            if(itemProp->isStackable())
            {
                int count = itemProp->getCount();
           
                //背包剩余商品个数等于总个数-过滤掉的商品个数
                for (auto sellIter = m_vSellItems.begin(); sellIter!=m_vSellItems.end(); sellIter++)
                {
                    if (itemProp->getInstanceID() == (*sellIter)->getItemId()) {
                        count = count -(*sellIter)->getItemCount();
                        break;
                    }
                }
                if (count>1) {
                    m_BagMsgLayer->setItemCount(itemProp->getInstanceID(),itemUi->getPosition(), count);
                }
            }
        }
    }
}

void BagShopLayer::bagItemOpe(int itemId)
{
    if (itemId==-1)
        return;
    ItemShopPopupUI* shopItem = static_cast<ItemShopPopupUI*>( PopupUILayerManager::getInstance()->openPopup(epopupItemShop));
    if (shopItem) {
        shopItem->updateItemPopup(ItemShopPopupUI::IST_SELL,itemId);
        shopItem->registerCloseCallback(CC_CALLBACK_0(BagShopLayer::updatePopupItems, this));
    }
}
void BagShopLayer::removeItemForSell(int itemId)
{
    SellItem* sellitem = nullptr;
    
    for (auto iter = m_vSellItems.begin(); iter!=m_vSellItems.end(); iter++)
    {
        if (itemId == (*iter)->getItemId()) {
            sellitem = (*iter);
        }
    }
    if (sellitem) {
        m_vSellItems.eraseObject(sellitem);
    }
}

void BagShopLayer::updateItemSplit(void * count ,SellItem* sellItem,int ItemId)
{
    
    if (sellItem) {
        sellItem->setItemCount(*(int*)count);
    }else
    {
        SellItem* sellItem  = SellItem::create(ItemId,*(int*)count);
        m_vSellItems.pushBack(sellItem);
    }
    updatePopupItems();
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
        
//        //如果是在商店贩卖界面 过滤掉需要贩卖的道具
//   
//            bool isExistId = false;
//            for (auto sellIter = m_vSellItems.begin(); sellIter!=m_vSellItems.end(); sellIter++)
//            {
//                //过滤掉不可合并的
//                if (itemProp->getInstanceID() == (*sellIter)->getItemId() && !itemProp->isStackable()) {
//                    isExistId = true;
//                    break;
//                }
//                //过滤掉商品个数到达上限的
//                if (itemProp->getInstanceID() == (*sellIter)->getItemId()
//                    && itemProp->isStackable() && (*sellIter)->getItemCount()==int(itemProp->getCount())) {
//                    isExistId = true;
//                    break;
//                }
//                
//            }
//            if (isExistId) {
//                continue;
//            }
        items.push_back(itemProp);
    }
    return items;
}