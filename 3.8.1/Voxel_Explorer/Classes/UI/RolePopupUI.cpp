//
//  RolePopUpUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/22.
//
//

#include "RolePopupUI.h"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "PopupUILayerManager.h"
#include "ItemPopupUI.h"
#include "EventConst.h"
#include "GameFormula.hpp"
#include "KeyProperty.hpp"
#include "BagManngerLayerUI.h"
#include "BagLayer.h"
USING_NS_CC;
RolePopupUI::RolePopupUI()
{
    m_cActionType           = eNone;
    m_pBtnClose             = nullptr;
    m_pBtnChangeBag         = nullptr;
    m_pBtnWeaponBag         = nullptr;
    m_pBtnPotionBag         = nullptr;
    m_pBtnAllBag         = nullptr;
    m_pWeaponUi             = nullptr;
    m_pArmorUi              = nullptr;
    m_pOrnamentUi           = nullptr;
    m_pSecondWeaponUi       = nullptr;
    m_pRoleHp               = nullptr;
    m_pRoleMp               = nullptr;
    m_pRoleExp              = nullptr;
    m_pRoleAttack           = nullptr;
    m_pRoleDefense            = nullptr;
    m_pRoleLightDis         = nullptr;
    m_pRoleSearchDis        = nullptr;
    m_pRoleMargicFind       = nullptr;
    m_pRoleCriticalStrike   = nullptr;
    m_pRoleBlock            = nullptr;
    m_pRoleDodge            = nullptr;
    m_pShopBtn              = nullptr;
    m_pBagLayer              = nullptr;
    m_pGridFrame            = nullptr;
    
}
RolePopupUI::~RolePopupUI()
{
    
}
void RolePopupUI::onEnter()
{

    EventListenerCustom *listener = EventListenerCustom::create(EVENT_PLAYER_PROPERTY_DIRTY, CC_CALLBACK_1(RolePopupUI::onEventUpdateData,this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_BAG_EXTEND_OK, CC_CALLBACK_1(RolePopupUI::onEventBagExtend, this));
        Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_BAG_EXTEND_HAS_REACH_MAXTIMES, CC_CALLBACK_1(RolePopupUI::onEventBagExtendHasReachMaxtimes, this));
    PopupUILayer::onEnter();
}
void RolePopupUI::onExit()
{
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_BAG_EXTEND_OK);
     Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_BAG_EXTEND_HAS_REACH_MAXTIMES);
    PopupUILayer::onExit();
}
bool RolePopupUI::initUi()
{
    
    Node* charNode = cocos2d::CSLoader::createNode("characterLayer.csb");
    if (!charNode)
        return  false;
    charNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    charNode->setPosition(WINDOW_CENTER);
    m_pRootLayer->addChild(charNode);
    Layout* equipFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(charNode, "equip_frame"));
    if (!equipFrame)
        return false;
     m_pGridFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(charNode, "grid_frame"));
    if (!m_pGridFrame)
        return false;
    m_pBtnChangeBag = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(charNode, "prop_btn_change_bag"));
    if (!m_pBtnChangeBag)
        return false;
    m_pBtnWeaponBag= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(charNode, "prop_btn_bag_wepon"));
    if (!m_pBtnWeaponBag)
        return false;
    m_pBtnPotionBag = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(charNode, "prop_btn_bag_poition"));
    if (!m_pBtnPotionBag)
        return false;
    m_pBtnAllBag= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(charNode, "prop_btn_bag_all"));
    if (!m_pBtnAllBag)
        return false;
    m_pRoleHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_hp"));
    if (!m_pRoleHp)
        return false;
    m_pRoleMp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_mp"));
    if (!m_pRoleMp)
        return false;
    m_pRoleAttack = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_attack"));
    if (!m_pRoleAttack)
        return false;
    
    m_pRoleDefense = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_armor"));
    if (!m_pRoleDefense)
        return false;
    
    m_pRoleExp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_exp"));
    if (!m_pRoleExp)
        return false;
    m_pRoleLightDis = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_light"));
    if (!m_pRoleLightDis)
        return false;
    m_pRoleSearchDis = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_search"));
    if (!m_pRoleSearchDis)
        return false;
    m_pRoleMargicFind = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_magic"));
    if (!m_pRoleMargicFind)
        return false;
    m_pRoleCriticalStrike = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_critical_strike"));
    if (!m_pRoleCriticalStrike)
        return false;
    m_pRoleBlock = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_block"));
    if (!m_pRoleBlock)
        return false;
    m_pRoleDodge = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_dodge"));
    if (!m_pRoleDodge)
        return false;
    m_pRoleHp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleMp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleExp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleLightDis->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleSearchDis->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleCriticalStrike->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleMargicFind->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleBlock->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleDodge->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleAttack->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleDefense->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    
    
   
    

    m_pBtnChangeBag->addClickEventListener(CC_CALLBACK_1(RolePopupUI::onClickChnageBag, this));
    m_pBtnWeaponBag->addTouchEventListener(CC_CALLBACK_2(RolePopupUI::onClickSortEquip, this));
    m_pBtnPotionBag->addTouchEventListener(CC_CALLBACK_2(RolePopupUI::onClickSortPotion, this));
    m_pBtnAllBag->addTouchEventListener(CC_CALLBACK_2(RolePopupUI::onClickSortAll, this));
    
    m_pWeaponUi = cocos2d::ui::ImageView::create();
    m_pWeaponUi->setScale9Enabled(true);
    m_pWeaponUi->setContentSize(cocos2d::Size(45,45));
    m_pWeaponUi->loadTexture("ui_weapon_icon.png",TextureResType::PLIST);
    m_pWeaponUi->setPosition(Vec2(m_pWeaponUi->getContentSize().width*0.5+8, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pWeaponUi);
    
    
    m_pSecondWeaponUi = cocos2d::ui::ImageView::create();
    m_pSecondWeaponUi->setScale9Enabled(true);
    m_pSecondWeaponUi->setContentSize(cocos2d::Size(45,45));
    m_pSecondWeaponUi->loadTexture("ui_secondweapon_icon.png",TextureResType::PLIST);
    m_pSecondWeaponUi->setPosition(Vec2(m_pWeaponUi->getContentSize().width*0.5+8+m_pWeaponUi->getContentSize().width*1+2, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pSecondWeaponUi);

    m_pArmorUi = cocos2d::ui::ImageView::create();
    m_pArmorUi->setScale9Enabled(true);
    m_pArmorUi->setContentSize(cocos2d::Size(45,45));
    m_pArmorUi->loadTexture("ui_armor_icon.png",TextureResType::PLIST);
    m_pArmorUi->setPosition(Vec2(m_pWeaponUi->getContentSize().width*0.5+8+m_pWeaponUi->getContentSize().width*2+4, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pArmorUi);
    
    m_pOrnamentUi = cocos2d::ui::ImageView::create();
    m_pOrnamentUi->setScale9Enabled(true);
    m_pOrnamentUi->setContentSize(cocos2d::Size(45,45));
    m_pOrnamentUi->loadTexture("ui_ornament_icon.png",TextureResType::PLIST);
    m_pOrnamentUi->setPosition(Vec2(m_pWeaponUi->getContentSize().width*0.5+8+m_pWeaponUi->getContentSize().width*3+6, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pOrnamentUi);

    
    m_pShopBtn = ImageView::create("ui_shop_icon.png",TextureResType::PLIST);
    m_pShopBtn->setScale9Enabled(true);
    m_pShopBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    m_pShopBtn->setContentSize(cocos2d::Size(45,45));
    m_pShopBtn->setPosition(Vec2(8+m_pWeaponUi->getContentSize().width*4+8, equipFrame->getContentSize().height*0.5));
    m_pShopBtn->setTouchEnabled(true);
    m_pShopBtn->addClickEventListener(CC_CALLBACK_1(RolePopupUI::onClickShop, this));
    equipFrame->addChild(m_pShopBtn);
    
    
    m_pEquipFrame = Layout::create();
    m_pEquipFrame->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    m_pEquipFrame->setContentSize(equipFrame->getContentSize());
    m_pEquipFrame->setPosition(equipFrame->getContentSize()*0.5);
    equipFrame->addChild(m_pEquipFrame);
    
    m_pBagLayer = BagLayer::create(m_pGridFrame->getContentSize());
    m_pBagLayer->setPosition(m_pGridFrame->getContentSize()*0.5);
    m_pGridFrame->addChild(m_pBagLayer);

    m_pBtnClose = ui::Button::create("ui_btn_back_1.png","","",TextureResType::PLIST);
    m_pBtnClose->setScale9Enabled(true);
    m_pBtnClose->setPosition(Vec2(SCREEN_WIDTH*0.9, SCREEN_HEIGHT*0.95));
    m_pRootLayer->addChild(m_pBtnClose);
    m_pBtnClose->addClickEventListener(CC_CALLBACK_1(RolePopupUI::onClickColse, this));
  
    
    updateItems();
    
    return true;
}

void RolePopupUI::updateRoleProp()
{
    m_pRoleHp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("ROLE_SHOW_HP").c_str(),int(PlayerProperty::getInstance()->getCurrentHP()),int(PlayerProperty::getInstance()->getMaxHP())));
    m_pRoleMp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("ROLE_SHOW_MP").c_str(),int(PlayerProperty::getInstance()->getCurrentMP()),int(PlayerProperty::getInstance()->getMaxMP())));
    m_pRoleExp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("ROLE_SHOW_EXP").c_str(),int(PlayerProperty::getInstance()->getExp()),int(GameFormula::getNextLevelExp(PlayerProperty::getInstance()->getLevel()))));
    m_pRoleLightDis->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_LIGHT_DIS").c_str(),int(PlayerProperty::getInstance()->getLightDistance())));
    m_pRoleSearchDis->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_SEARCH_DIS").c_str(),int(PlayerProperty::getInstance()->getSearchDistance())));
    m_pRoleCriticalStrike ->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_CRITICAL_STRIKE").c_str(),int(PlayerProperty::getInstance()->getCriticalStrikeRate())));
    m_pRoleMargicFind->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_MARGIC_FIND").c_str(),int(PlayerProperty::getInstance()->getMagicItemFindRate())));
    m_pRoleBlock->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_BLOCK").c_str(),int(PlayerProperty::getInstance()->getBlockRate())));
    m_pRoleDodge->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_DODGE").c_str(),int(PlayerProperty::getInstance()->getDodgeRate())));
    CCLOG("role minAttack:%d,maxAttack:%d",int(PlayerProperty::getInstance()->getMinAttack()),int(PlayerProperty::getInstance()->getMaxAttack()));
    m_pRoleAttack->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_ATTACK").c_str(),int(PlayerProperty::getInstance()->getMinAttack()),int(PlayerProperty::getInstance()->getMaxAttack())));
    m_pRoleDefense->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_DEFENSE").c_str(),int(PlayerProperty::getInstance()->getDefense())));
    
}
void RolePopupUI::updateEquipProp()
{
    //清除装备栏信息
    if (m_pEquipFrame)
        m_pEquipFrame->removeAllChildren();
    std::vector<PickableItemProperty*> bagItems = PlayerProperty::getInstance()->getPlayerBag();
    int weaponId = int(PlayerProperty::getInstance()->getEquipedWeaponID());
    int armorId = int(PlayerProperty::getInstance()->getEquipedArmorID());
    int OrnamentId = int(PlayerProperty::getInstance()->getEquipedOrnamentsID());
    int secondWeaponId = int(PlayerProperty::getInstance()->getEquipedSecondWeaponID());
    for (int i =0; i<bagItems.size(); i++)
    {
        PickableItemProperty* itemProp =bagItems[i];
        if (!itemProp) {
            continue;
        }
        
        if ( m_pWeaponUi && itemProp->getInstanceID() == weaponId) {
           
            setEquipItem(m_pWeaponUi->getPosition(),itemProp->getIconRes());
        }
        if (m_pArmorUi &&  itemProp->getInstanceID() == armorId) {
           
            setEquipItem(m_pArmorUi->getPosition(),itemProp->getIconRes());
        }
        if (m_pOrnamentUi &&  itemProp->getInstanceID() == OrnamentId) {
           
            setEquipItem(m_pOrnamentUi->getPosition(),itemProp->getIconRes());
        }
        if (m_pSecondWeaponUi &&  itemProp->getInstanceID() == secondWeaponId) {
           
            setEquipItem(m_pSecondWeaponUi->getPosition(),itemProp->getIconRes());
        }

    }
}

void RolePopupUI::onEventUpdateData(cocos2d::EventCustom *sender)
{
    updateItems();
}
void RolePopupUI::onEventBagExtend(cocos2d::EventCustom *sender)
{
    if (m_pBagLayer)
        m_pBagLayer->extendBag();
    updateItems();
    
}
void RolePopupUI::onEventBagExtendHasReachMaxtimes(cocos2d::EventCustom *sender)
{
    //扩展次数到达上线,给出提示
    CCLOG("onEventBagExtendHasReachMaxtimes");
}
void RolePopupUI::updateItems(bool _isOpenIdentify)
{
    if (_isOpenIdentify) {
        m_pBtnAllBag->setEnabled(true);
        m_pBtnPotionBag->setEnabled(true);
        m_pBtnWeaponBag->setEnabled(false);
    }
    
    if (m_pBagLayer) {
        BagLayer::eSortBagType sortType = BagLayer::SBT_ALL;
        if (!m_pBtnWeaponBag->isEnabled())
        {
            sortType = BagLayer::SBT_EQUIP;
            
        }else if (!m_pBtnPotionBag->isEnabled())
        {
            sortType = BagLayer::SBT_POTION;
        }
        m_pBagLayer->updateBagProp(_isOpenIdentify, sortType);
    }
    updateRoleProp();
    updateEquipProp();
}

void RolePopupUI::onClickChnageBag(Ref* ref)
{
    CHECK_ACTION(ref);
    PlayerProperty::getInstance()->extendBagSpace();
}
void RolePopupUI::onClickColse(Ref* ref)
{
    CHECK_ACTION(ref);
    if (m_pBagLayer) {
        if (m_pBagLayer->isIdentIfy()) {
            
            m_pBtnAllBag->setEnabled(false);
            m_pBtnPotionBag->setEnabled(true);
            m_pBtnWeaponBag->setEnabled(true);
            
            updateItems();
        }else
        {
            closePopup();
        }
    }
    
}
void RolePopupUI::onClickSortAll(cocos2d::Ref * ref, Widget::TouchEventType type)
{
    CHECK_ACTION(ref);
    if (type == Widget::TouchEventType::BEGAN) {
            m_pBtnAllBag->setEnabled(false);
            m_pBtnPotionBag->setEnabled(true);
            m_pBtnWeaponBag->setEnabled(true);
    }
    
    useIndetifyUpdate();
}
void RolePopupUI::onClickSortEquip(cocos2d::Ref * ref, Widget::TouchEventType type)
{
    CHECK_ACTION(ref);
    if (type == Widget::TouchEventType::BEGAN) {
            m_pBtnAllBag->setEnabled(true);
            m_pBtnPotionBag->setEnabled(true);
            m_pBtnWeaponBag->setEnabled(false);
    }
    useIndetifyUpdate();
}
void RolePopupUI::onClickSortPotion(cocos2d::Ref * ref, Widget::TouchEventType type)
{
    CHECK_ACTION(ref);
    if (type == Widget::TouchEventType::BEGAN) {
            m_pBtnAllBag->setEnabled(true);
            m_pBtnPotionBag->setEnabled(false);
            m_pBtnWeaponBag->setEnabled(true);
        
    }
    useIndetifyUpdate();
}
void RolePopupUI::onClickShop(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    PopupUILayerManager::getInstance()->closeCurrentPopup();
    
    PopupUILayerManager::getInstance()->openPopup(ePopupShop);
}
void RolePopupUI::useIndetifyUpdate()
{
    if (m_pBagLayer->isIdentIfy()) {
        updateItems(true);
    }else{
        updateItems();
    }
}
void RolePopupUI::setEquipItem(cocos2d::Vec2 pt, std::string itemIcon)
{
    if (m_pEquipFrame) {
        ui::ImageView* img = ui::ImageView::create(itemIcon,ui::TextureResType::PLIST);
        img->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        img->setPosition(pt);
        img->setScale(0.9);
        img->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pEquipFrame->addChild(img);
    }
}

