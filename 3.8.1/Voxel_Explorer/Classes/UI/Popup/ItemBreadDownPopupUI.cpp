//
//  ItemShopPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#include "ItemBreadDownPopupUI.hpp"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "AlertPopupUI.hpp"
#include "PopupUILayerManager.h"
ItemBreadDownPopupUI::ItemBreadDownPopupUI()
{
    
}
ItemBreadDownPopupUI::~ItemBreadDownPopupUI()
{
    
}



void ItemBreadDownPopupUI::refreshUIView()
{
    ItemPopupUI::refreshUIView();
    
    
    m_pBtnDiscard->setVisible(true);
    m_pBtnDiscard->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_CANCEL"));
  
    m_pBtnEquip->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_BREADDOWN"));
   
    m_pBtnEquip->setPosition(cocos2d::Vec2(m_pBottomFrame->getContentSize().width*0.7442,m_pBtnEquip->getPositionY()));
    
    m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemBreadDownPopupUI::onClickBreadDown, this));
    
    m_pBtnDiscard->addClickEventListener(CC_CALLBACK_1(ItemBreadDownPopupUI::onClickCancel, this));
}

void ItemBreadDownPopupUI::onClickBreadDown(Ref* ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickBreadDown");
    std::map<PickableItem::PickableItemType,CChaosNumber> resultDatas;
    bool isSucess =  PlayerProperty::getInstance()->equipBreadDown(m_nItemId,resultDatas);
    if (!isSucess) {
        CCLOG("breadDown fail");
    }
    setCloseCallbackParamD(&resultDatas);
    closePopup();
    
}
void ItemBreadDownPopupUI::onClickCancel(Ref* ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickCancel");
    closePopup();
}

