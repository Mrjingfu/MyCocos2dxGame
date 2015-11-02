//
//  ItemPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "ItemPopupUI.h"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "EventConst.h"
USING_NS_CC;
ItemPopupUI::ItemPopupUI()
{
    
    m_cActionType = eNone;
    m_pItemIcon    =nullptr;
    m_pItemName    =nullptr;
    m_pItemlv      =nullptr;
    m_pItemDesc    =nullptr;
    m_pBtnItemFrame    =nullptr;
    m_pPropFrame    =nullptr;
    m_pDescItemFrame    =nullptr;
    m_pBtnDiscard    =nullptr;
    m_pBtnUse    =nullptr;
    m_pBtnEquip    =nullptr;
    m_pBackGround    =nullptr;
   
    m_nItemId = -2;
}
ItemPopupUI::~ItemPopupUI()
{
    
}
bool ItemPopupUI::init()
{
    if (PopupUILayer::init())
    {
        this->load("itemPopupLayer.csb",false);
        enableDarkLayer(false);
        return true;
    }
    return false;
}
bool ItemPopupUI::addEvents()
{
    
    m_pBtnItemFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_event__layer"));
    if (!m_pBtnItemFrame)
        return false;
    m_pPropFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_layer"));
    if (!m_pBtnItemFrame)
        return false;
    m_pDescItemFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_desc_layer"));
    if (!m_pBtnItemFrame)
        return false;
    
     m_pBtnDiscard = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_btn_discard"));
    if (!m_pBtnDiscard)
        return false;
    m_pBtnUse = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_btn_use"));
    if (!m_pBtnUse)
        return false;
     m_pBtnEquip = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_btn_equip"));
    if (!m_pBtnEquip)
        return false;
    
    m_pBackGround =   dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_background"));
    if (!m_pBackGround)
        return false;

    m_pItemIcon =   dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_icon"));
    if (!m_pItemIcon)
        return false;
 
    m_pItemName = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_name_text"));
    if (!m_pItemName)
        return false;
    m_pItemlv = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_lv_num_text"));
    if (!m_pItemlv)
        return false;
    m_pItemDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_desc_text"));
    if (!m_pItemDesc)
        return false;
    m_pItemCount = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_count_text"));
    if (!m_pItemCount)
        return false;
    m_pItemCount->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemName->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemlv->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
//    m_pItemDesc->ignoreContentAdaptWithSize(false);
//    m_pItemDesc->setContentSize(cocos2d::Size(200,m_pItemDesc->getCustomSize().height));
//    m_pItemDesc->setTextHorizontalAlignment(TextHAlignment::LEFT);
    m_pItemCount->setVisible(false);
    
    m_pBtnDiscard->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickDiscard, this));
    m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickEquip, this));
    m_pBtnUse->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickUser, this));
  
    
    
    registerCloseCallback(CC_CALLBACK_0(ItemPopupUI::notifyRolePopup, this));
    return true;
}
void ItemPopupUI::equipFrame()
{
    m_pBtnUse->setVisible(false);
    m_pBtnDiscard->setContentSize(cocos2d::Size(m_pBtnDiscard->getContentSize().width+10,m_pBtnDiscard->getContentSize().height));
    m_pBtnDiscard->setPosition(Vec2(m_pBtnItemFrame->getContentSize().width*0.15, m_pBtnItemFrame->getContentSize().height*0.5));
    
    m_pBtnEquip->setContentSize(cocos2d::Size(m_pBtnEquip->getContentSize().width+10,m_pBtnEquip->getContentSize().height));
    m_pBtnEquip->setPosition(Vec2(m_pBtnItemFrame->getContentSize().width*0.15+m_pBtnDiscard->getContentSize().width+10, m_pBtnItemFrame->getContentSize().height*0.5));
    
}
void ItemPopupUI::itemFrame()
{
    m_pBtnEquip->setVisible(false);
    m_pBtnUse->setContentSize(cocos2d::Size(m_pBtnUse->getContentSize().width+10,m_pBtnUse->getContentSize().height));
    m_pBtnUse->setPosition(Vec2(m_pBtnItemFrame->getContentSize().width*0.15, m_pBtnItemFrame->getContentSize().height*0.5));
    
    m_pBtnDiscard->setContentSize(cocos2d::Size(m_pBtnDiscard->getContentSize().width+10,m_pBtnDiscard->getContentSize().height));
    m_pBtnDiscard->setPosition(Vec2(m_pBtnItemFrame->getContentSize().width*0.15+m_pBtnUse->getContentSize().width+10, m_pBtnItemFrame->getContentSize().height*0.5));
}
void ItemPopupUI::displayFrame()
{
    m_pBtnItemFrame->setVisible(false);
    CCLOG("old m_pRootNode width%f height:%f",m_pRootNode->getContentSize().width,m_pRootNode->getContentSize().height);
    m_pRootNode->setContentSize(cocos2d::Size(m_pRootNode->getContentSize().width,m_pRootNode->getContentSize().height-m_pBtnItemFrame->getContentSize().height));
    CCLOG("new m_pRootNode width%f height:%f",m_pRootNode->getContentSize().width,m_pRootNode->getContentSize().height);
    m_pBackGround->setContentSize(m_pRootNode->getContentSize());
    m_pBackGround->setPosition(m_pBackGround->getContentSize()*0.5);
    m_pPropFrame->setPosition(Vec2(0, m_pRootNode->getContentSize().height));
    m_pDescItemFrame->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    m_pDescItemFrame->setPosition(Vec2::ZERO);
}
void ItemPopupUI::updateItemPopup(int itemId)
{
    m_nItemId = itemId;
    CCLOG("m_nItemId:%d",m_nItemId);
    
    PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    m_pItemIcon->loadTexture(itemprop->getIconRes());
    m_pItemName->setString(itemprop->getName());
    std::string str = "传说由来自天魔星的魔矿打造，会逐渐控制主人的心智，使之入魔。";
    m_pItemDesc->setString(str);
    m_pItemlv->setString(StringUtils::format("LV.%ld",itemprop->getLevel().GetLongValue()));
    
    if (itemprop->isStackable()) {
        m_pItemCount->setVisible(true);
        PickableItemProperty::PickableItemPropertyType itemtype =itemprop->getPickableItemPropertyType() ;
        if ( itemtype == PickableItemProperty::PIPT_KEY) {
            
            CCLOG("合并 PIPT_KEY");
            
        }else if (itemtype == PickableItemProperty::PIPT_MATERIAL){
            
            CCLOG("合并 PIPT_MATERIAL");
            
        }else if(itemtype == PickableItemProperty::PIPT_POTIONS)
        {
            CCLOG("合并 PIPT_POTIONS");
        }
    }
    
    if (itemprop->isEquipable() ) {
        if (!(PlayerProperty::getInstance()->getEquipedWeaponID() == m_nItemId ||
            PlayerProperty::getInstance()->getEquipedArmorID() == m_nItemId ||
            PlayerProperty::getInstance()->getEquipedOrnamentsID() == m_nItemId||
              PlayerProperty::getInstance()->getEquipedSecondWeaponID() == m_nItemId)){
            equipFrame();
        }else
        {
            displayFrame();
        }
    }else
    {
        m_pBtnItemFrame->setVisible(true);
    }
    
    m_pItemIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
}
void ItemPopupUI::onClickDiscard(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickDiscard");
    if(PlayerProperty::getInstance()->removeItemFromBag(CChaosNumber(m_nItemId)))
        closePopup();
    
}
void ItemPopupUI::onClickEquip(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);

    PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    bool isEquipSucess = false;
    if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_WEAPON) {
        
        isEquipSucess = PlayerProperty::getInstance()->EquipWeapon(CChaosNumber(m_nItemId));
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_ARMOR){
        
        isEquipSucess = PlayerProperty::getInstance()->EquipArmor(CChaosNumber(m_nItemId));
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_MAGIC_ORNAMENT)
    {
        isEquipSucess = PlayerProperty::getInstance()->EquipOrnaments(CChaosNumber(m_nItemId));
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_SECOND_WEAPON)
    {
        isEquipSucess = PlayerProperty::getInstance()->EquipSecondWeapon(CChaosNumber(m_nItemId));
    }
    if (isEquipSucess) {
        closePopup();
    }
  
    
    
}
void ItemPopupUI::onClickUser(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickUser");
}
void ItemPopupUI::notifyRolePopup()
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_UI_UPDATE_ROLE_DATA);
}