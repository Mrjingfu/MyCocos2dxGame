//
//  ItemShopPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#include "ItemSelectPopupUI.hpp"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "AlertPopupUI.hpp"
#include "PopupUILayerManager.h"
ItemSelectPopupUI::ItemSelectPopupUI()
{
    
}
ItemSelectPopupUI::~ItemSelectPopupUI()
{
    
}



void ItemSelectPopupUI::refreshUIView()
{
    ItemPopupUI::refreshUIView();
    
    
    m_pBtnDiscard->setVisible(true);
    m_pBtnDiscard->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_CANCEL"));
  
    m_pBtnEquip->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_SELECT"));
   
    m_pBtnEquip->setPosition(cocos2d::Vec2(m_pBottomFrame->getContentSize().width*0.7442,m_pBtnEquip->getPositionY()));
    
    m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemSelectPopupUI::onClickSelect, this));
    
    m_pBtnDiscard->addClickEventListener(CC_CALLBACK_1(ItemSelectPopupUI::onClickCancel, this));
}
void ItemSelectPopupUI::updateBottomUi()
{
    //如果当前道具就是装备道具不添加底部UI
    if (PlayerProperty::getInstance()->getEquipedWeaponID() == m_nItemId ||
        PlayerProperty::getInstance()->getEquipedArmorID() == m_nItemId ||
        PlayerProperty::getInstance()->getEquipedOrnamentsID() == m_nItemId||
        PlayerProperty::getInstance()->getEquipedSecondWeaponID() == m_nItemId){
        
        m_pItemEquipDist->setVisible(true);
        m_pItemEquipDist->setString(UtilityHelper::getLocalStringForUi("ITEM_ALREDY_EQUIP"));
        m_pItemEquipDist->setColor(cocos2d::Color3B(144,248,144));
    }
        addBottomUI();
}
void ItemSelectPopupUI::onClickSelect(Ref* ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickSelect");
    PickableItemProperty* itemProp =  PlayerProperty::getInstance()->getItemFromBag(m_nItemId);
    if (itemProp)
    {
        setCloseCallbackParamO(itemProp);
        
    }
    closePopup();
    
}
void ItemSelectPopupUI::onClickCancel(Ref* ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickCancel");
    closePopup();
}


