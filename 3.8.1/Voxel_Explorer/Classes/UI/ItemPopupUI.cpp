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
    m_pBtnDrop     =nullptr;
    m_pBtnThrow    =nullptr;
    m_pBtnEquip    =nullptr;
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
    m_pBtnDrop = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_btn_drop"));
    if (!m_pBtnDrop)
        return false;
    m_pBtnThrow = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_btn_throw"));
    if (!m_pBtnDrop)
        return false;
    m_pBtnEquip = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_btn_equip"));
    if (!m_pBtnDrop)
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
    
    m_pBtnDrop->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickDrop, this));
    m_pBtnThrow->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickThrow, this));
    m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickEquip, this));
    
    registerCloseCallback(CC_CALLBACK_0(ItemPopupUI::notifyRolePopup, this));
    return true;
}
void ItemPopupUI::updateItemPopup(int itemId)
{
    m_nItemId = itemId;
    
    PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    m_pItemIcon->loadTexture(itemprop->getIconRes());
    m_pItemName->setString(itemprop->getName());
    m_pItemDesc->setString(itemprop->getDesc());
    m_pItemlv->setString(Value(int(itemprop->getLevel())).asString());
    
    if (PlayerProperty::getInstance()->getEquipedWeaponID() == m_nItemId ||
        PlayerProperty::getInstance()->getEquipedArmorID() == m_nItemId ||
        PlayerProperty::getInstance()->getEquipedOrnamentsID() == m_nItemId||
        !itemprop->isEquipable()) {
        m_pBtnEquip->setVisible(false);
    }
    
    
    m_pItemIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
}
void ItemPopupUI::onClickDrop(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickDrop");
}
void ItemPopupUI::onClickEquip(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);

    PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    
    if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_WEAPON) {
        
        PlayerProperty::getInstance()->EquipWeapon(CChaosNumber(m_nItemId));
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_ARMOR){
        
        PlayerProperty::getInstance()->EquipArmor(CChaosNumber(m_nItemId));
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_MAGIC_ORNAMENT)
    {
        PlayerProperty::getInstance()->EquipOrnaments(CChaosNumber(m_nItemId));
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_SECOND_WEAPON)
    {
        PlayerProperty::getInstance()->EquipSecondWeapon(CChaosNumber(m_nItemId));
    }
    m_pBtnEquip->setVisible(false);
    
    
}
void ItemPopupUI::onClickThrow(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickThrow");
}
void ItemPopupUI::notifyRolePopup()
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_UI_UPDATE_ROLE_DATA);
}