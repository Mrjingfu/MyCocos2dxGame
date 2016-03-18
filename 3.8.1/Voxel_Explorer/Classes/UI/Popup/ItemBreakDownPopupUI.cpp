//
//  ItemShopPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#include "ItemBreakDownPopupUI.hpp"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "AlertPopupUI.hpp"
#include "PopupUILayerManager.h"
ItemBreakDownPopupUI::ItemBreakDownPopupUI()
{
    
}
ItemBreakDownPopupUI::~ItemBreakDownPopupUI()
{
    
}



void ItemBreakDownPopupUI::refreshUIView()
{
    ItemPopupUI::refreshUIView();
    
    
    m_pBtnDiscard->setVisible(true);
    m_pBtnDiscard->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_CANCEL"));
  
    m_pBtnEquip->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_BREADDOWN"));
   
    m_pBtnEquip->setPosition(cocos2d::Vec2(m_pBottomFrame->getContentSize().width*0.7442,m_pBtnEquip->getPositionY()));
    
    m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemBreakDownPopupUI::onClickBreadDown, this));
    
    m_pBtnDiscard->addClickEventListener(CC_CALLBACK_1(ItemBreakDownPopupUI::onClickCancel, this));
}

void ItemBreakDownPopupUI::onClickBreadDown(Ref* ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickBreadDown");
    std::map<PickableItem::PickableItemType,CChaosNumber> resultDatas;
    bool isSucess =  PlayerProperty::getInstance()->equipBreakDown(m_nItemId,resultDatas);
    if (!isSucess) {
        CCLOG("breadDown fail");
    }
    setCloseCallbackParamD(&resultDatas);
    closePopup();
    
}
void ItemBreakDownPopupUI::onClickCancel(Ref* ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickCancel");
    closePopup();
}

