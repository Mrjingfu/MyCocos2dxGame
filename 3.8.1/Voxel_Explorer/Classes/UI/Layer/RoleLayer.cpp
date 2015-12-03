//
//  RoleLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#include "RoleLayer.hpp"
#include "UtilityHelper.h"
#include "BagMangerLayerUI.h"
#include "PlayerProperty.hpp"
#include "GameFormula.hpp"
#include "PopupUILayerManager.h"
USING_NS_CC;
RoleLayer::RoleLayer()
{
    m_pEquipFrame           = nullptr;
    m_pWeaponUi             = nullptr;
    m_pArmorUi              = nullptr;
    m_pOrnamentUi           = nullptr;
    m_pSecondWeaponUi       = nullptr;
    m_pRoleHp               = nullptr;
    m_pRoleMp               = nullptr;
    m_pRoleExp              = nullptr;
    m_pRoleAttack           = nullptr;
    m_pRoleDefense          = nullptr;
    m_pRoleLightDis         = nullptr;
    m_pRoleSearchDis        = nullptr;
    m_pRoleMargicFind       = nullptr;
    m_pRoleCriticalStrike   = nullptr;
    m_pRoleBlock            = nullptr;
    m_pRoleDodge            = nullptr;
    m_pShopBtn              = nullptr;

}
RoleLayer::~RoleLayer()
{
    
}
bool RoleLayer::initUi()
{
    if (!load("roleLayer.csb",false))
        return false;
    setContentSize(m_pRootNode->getContentSize());
    m_pRootNode->setPosition(getContentSize()*0.5);
    return true;
}

bool RoleLayer::addEvents()
{
    Layout* equipFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "equip_frame"));
    if (!equipFrame)
        return false;

    m_pRoleHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_hp"));
    if (!m_pRoleHp)
        return false;
    m_pRoleMp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_mp"));
    if (!m_pRoleMp)
        return false;
    m_pRoleAttack = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_attack"));
    if (!m_pRoleAttack)
        return false;
    
    m_pRoleDefense = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_armor"));
    if (!m_pRoleDefense)
        return false;
    
    m_pRoleExp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_exp"));
    if (!m_pRoleExp)
        return false;
    m_pRoleLightDis = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_light"));
    if (!m_pRoleLightDis)
        return false;
    m_pRoleSearchDis = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_search"));
    if (!m_pRoleSearchDis)
        return false;
    m_pRoleMargicFind = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_magic"));
    if (!m_pRoleMargicFind)
        return false;
    m_pRoleCriticalStrike = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_critical_strike"));
    if (!m_pRoleCriticalStrike)
        return false;
    m_pRoleBlock = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_block"));
    if (!m_pRoleBlock)
        return false;
    m_pRoleDodge = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_dodge"));
    if (!m_pRoleDodge)
        return false;
    
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
    
    
    m_pShopBtn = cocos2d::ui::ImageView::create("ui_shop_icon.png",TextureResType::PLIST);
    m_pShopBtn->setScale9Enabled(true);
    m_pShopBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    m_pShopBtn->setContentSize(cocos2d::Size(45,45));
    m_pShopBtn->setPosition(Vec2(8+m_pWeaponUi->getContentSize().width*4+8, equipFrame->getContentSize().height*0.5));
    m_pShopBtn->setTouchEnabled(true);
    m_pShopBtn->addClickEventListener(CC_CALLBACK_1(RoleLayer::onClickShop, this));
    equipFrame->addChild(m_pShopBtn);
    
    
    m_pEquipFrame = BagMangerLayerUI::create(equipFrame->getContentSize());
    m_pEquipFrame->setPosition(equipFrame->getContentSize()*0.5);
    equipFrame->addChild(m_pEquipFrame);
    
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
    
    
    return true;
}
void RoleLayer::refreshUIView()
{
    updateEquipProp();
    updateRoleProp();
}
void RoleLayer::updateRoleProp()
{
    m_pRoleHp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("ROLE_SHOW_HP").c_str(),int(PlayerProperty::getInstance()->getCurrentHP()),int(PlayerProperty::getInstance()->getMaxHP())));
    m_pRoleMp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("ROLE_SHOW_MP").c_str(),int(PlayerProperty::getInstance()->getCurrentMP()),int(PlayerProperty::getInstance()->getMaxMP())));
    m_pRoleExp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("ROLE_SHOW_EXP").c_str(),int(PlayerProperty::getInstance()->getExp()),int(GameFormula::getNextLevelExp(PlayerProperty::getInstance()->getLevel()))));
    m_pRoleLightDis->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_LIGHT_DIS").c_str(),int(PlayerProperty::getInstance()->getLightDistance())));
    m_pRoleSearchDis->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_SEARCH_DIS").c_str(),int(PlayerProperty::getInstance()->getSearchDistance())));
    m_pRoleCriticalStrike ->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_CRITICAL_STRIKE").c_str(),int(PlayerProperty::getInstance()->getCriticalStrikeRate().GetLongValue()*100.0)));
    m_pRoleMargicFind->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_MARGIC_FIND").c_str(),int(PlayerProperty::getInstance()->getMagicItemFindRate().GetLongValue()*100.0)));
    m_pRoleBlock->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_BLOCK").c_str(),int(PlayerProperty::getInstance()->getBlockRate().GetLongValue()*100.0)));
    m_pRoleDodge->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_DODGE").c_str(),int(PlayerProperty::getInstance()->getDodgeRate().GetLongValue()*100.0)));
    CCLOG("role minAttack:%d,maxAttack:%d",int(PlayerProperty::getInstance()->getMinAttack()),int(PlayerProperty::getInstance()->getMaxAttack()));
    m_pRoleAttack->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_ATTACK").c_str(),int(PlayerProperty::getInstance()->getMinAttack()),int(PlayerProperty::getInstance()->getMaxAttack())));
    m_pRoleDefense->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_DEFENSE").c_str(),int(PlayerProperty::getInstance()->getDefense())));
    
}
void RoleLayer::updateEquipProp()
{
    //清除装备栏信息
    if (m_pEquipFrame)
        m_pEquipFrame->removeItems();
    std::vector<PickableItemProperty*> bagItems = PlayerProperty::getInstance()->getPlayerBag();
    int weaponId = int(PlayerProperty::getInstance()->getEquipedWeaponID());
    int armorId = int(PlayerProperty::getInstance()->getEquipedArmorID());
    int OrnamentId = int(PlayerProperty::getInstance()->getEquipedOrnamentsID());
    int secondWeaponId = int(PlayerProperty::getInstance()->getEquipedSecondWeaponID());
    
    if (weaponId!=-1) {
        PickableItemProperty* weaponProp = PlayerProperty::getInstance()->getItemFromBag(weaponId);
        m_pEquipFrame->addItem(1, weaponId, m_pWeaponUi->getPosition(), weaponProp->getIconRes());
    }
    
    if (secondWeaponId!=-1) {
        PickableItemProperty* weaponProp = PlayerProperty::getInstance()->getItemFromBag(secondWeaponId);
        m_pEquipFrame->addItem(2, weaponId, m_pSecondWeaponUi->getPosition(), weaponProp->getIconRes());
    }
    
    if (armorId!=-1) {
        PickableItemProperty* weaponProp = PlayerProperty::getInstance()->getItemFromBag(armorId);
        m_pEquipFrame->addItem(3, armorId, m_pArmorUi->getPosition(), weaponProp->getIconRes());
    }
    
    if (OrnamentId!=-1) {
        PickableItemProperty* weaponProp = PlayerProperty::getInstance()->getItemFromBag(OrnamentId);
        m_pEquipFrame->addItem(4, weaponId, m_pOrnamentUi->getPosition(), weaponProp->getIconRes());
    }
}
void RoleLayer::onClickShop(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
   
}