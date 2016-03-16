//
//  BagEquipLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/15.
//
//

#include "BagWashLayer.hpp"
#include "BagMangerLayerUI.h"
#include "PlayerProperty.hpp"
#include "ItemPopupUI.h"
#include "ItemBreadDownPopupUI.hpp"
#include "PopupUILayerManager.h"
BagWashLayer::BagWashLayer()
{
    
}
BagWashLayer::~BagWashLayer()
{
    
}
std::vector<PickableItemProperty*> BagWashLayer::getItems()
{
    std::vector<PickableItemProperty*> bagItems = BagEquipLayer::getItems();
     std::vector<PickableItemProperty*> items;
    
    for (int i =0 ; i<bagItems.size(); i++)
    {
        PickableItemProperty* itemProp =bagItems[i];
        if (itemProp && itemProp->getQuality() != PICKABLEITEM_QUALITY::PIQ_GENERAL)
        {
            items.push_back(itemProp);
        }
    }
    return items;
}
void BagWashLayer::bagItemOpe(int itemId)
{
    if (itemId==-1)
        return;
    
    PickableItemProperty* itemProp = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(itemId));
    if (!itemProp)
    {
        CCLOG("itemProp is empty");
        return;
    }
    setCloseCallbackParamO(itemProp);
    executeCloseBackO();
}

