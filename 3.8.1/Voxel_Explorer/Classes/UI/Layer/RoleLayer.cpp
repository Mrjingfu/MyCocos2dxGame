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
    m_pRoleLevel            = nullptr;
}
RoleLayer::~RoleLayer()
{
    
}
bool RoleLayer::initUi()
{
    if (!load("rolenewLayer.csb",false))
        return false;
    setContentSize(m_pRootNode->getContentSize());
    m_pRootNode->setPosition(getContentSize()*0.5);
    return true;
}

bool RoleLayer::addEvents()
{

    
    
    m_pRoleHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_hp_num"));
    if (!m_pRoleHp)
        return false;
    ui::Text* m_pRoleHpDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_hp"));
    if (!m_pRoleHpDesc)
        return false;
    
    m_pRoleMp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_mp_num"));
    if (!m_pRoleMp)
        return false;
    ui::Text* m_pRoleMpDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_mp"));
    if (!m_pRoleMpDesc)
        return false;
    
    m_pRoleAttack = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_attack_num"));
    if (!m_pRoleAttack)
        return false;
    ui::Text* m_pRoleAttackDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_attack"));
    if (!m_pRoleAttackDesc)
        return false;
    
    m_pRoleDefense = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_armor_num"));
    if (!m_pRoleDefense)
        return false;
    ui::Text* m_pRoleDefenseDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_armor"));
    if (!m_pRoleDefenseDesc)
        return false;
    
    m_pRoleExp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_exp_num"));
    if (!m_pRoleExp)
        return false;
    ui::Text* m_pRoleExpDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_exp"));
    if (!m_pRoleExpDesc)
        return false;
    
    m_pRoleLightDis = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_light_num"));
    if (!m_pRoleLightDis)
        return false;
    ui::Text* m_pRoleLightDisDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_light"));
    if (!m_pRoleLightDisDesc)
        return false;
    
    m_pRoleSearchDis = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_search_num"));
    if (!m_pRoleSearchDis)
        return false;
    ui::Text* m_pRoleSearchDisDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_search"));
    if (!m_pRoleSearchDisDesc)
        return false;
    
    m_pRoleMargicFind = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_magic_num"));
    if (!m_pRoleMargicFind)
        return false;
    ui::Text* m_pRoleMargicFindDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_magic"));
    if (!m_pRoleMargicFindDesc)
        return false;
    
    m_pRoleCriticalStrike = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_critical_strike_num"));
    if (!m_pRoleCriticalStrike)
        return false;
    ui::Text* m_pRoleCriticalStrikeDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_critical_strike"));
    if (!m_pRoleCriticalStrikeDesc)
        return false;
    
    m_pRoleBlock = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_block_num"));
    if (!m_pRoleBlock)
        return false;
    ui::Text* m_pRoleBlockDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_block"));
    if (!m_pRoleBlockDesc)
        return false;
    
    m_pRoleDodge = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_dodge_num"));
    if (!m_pRoleDodge)
        return false;
    ui::Text* m_pRoleDodgeDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_prop_dodge"));
    if (!m_pRoleDodgeDesc)
        return false;
    
    m_pRoleLevel = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_lv_num"));
    if (!m_pRoleLevel)
        return false;
   
    m_pWeaponUi = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_weapon"));
    if (!m_pWeaponUi)
        return false;
    
    m_pArmorUi = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_armor"));
    if (!m_pArmorUi)
        return false;
    
    m_pOrnamentUi = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_ornament"));
    if (!m_pOrnamentUi)
        return false;
    
    m_pSecondWeaponUi = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_second_equip"));
    if (!m_pSecondWeaponUi)
        return false;
    
    m_pShopBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_shop"));
    if (!m_pShopBtn)
        return false;
    
    m_pBtnClose = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_btn_close"));
    if (!m_pBtnClose)
        return false;
    
    m_pEquipFrame = BagMangerLayerUI::create(cocos2d::Size(m_pRootNode->getContentSize().width*0.55,m_pRootNode->getContentSize().height));
    m_pEquipFrame->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    m_pEquipFrame->setPosition(cocos2d::Vec2(0,m_pRootNode->getContentSize().height));
    m_pRootNode->addChild(m_pEquipFrame);
    
    cocos2d::ui::ImageView*  roleImg = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_icon"));
    if (roleImg) {
        roleImg->loadTexture("chr_sword.png",TextureResType::PLIST);
    }
    
    m_pRoleHpDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleHpDesc->setString(UtilityHelper::getLocalStringForUi("ROLE_SHOW_HP"));
    
    m_pRoleMpDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleMpDesc->setString(UtilityHelper::getLocalStringForUi("ROLE_SHOW_MP"));
    
    m_pRoleExpDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleExpDesc->setString(UtilityHelper::getLocalStringForUi("ROLE_SHOW_EXP"));
    
    m_pRoleLightDisDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleLightDisDesc->setString(UtilityHelper::getLocalStringForUi("PROP_SHOW_LIGHT_DIS"));
    
    m_pRoleSearchDisDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleSearchDisDesc->setString(UtilityHelper::getLocalStringForUi("PROP_SHOW_SEARCH_DIS"));
    
    m_pRoleCriticalStrikeDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleCriticalStrikeDesc ->setString(UtilityHelper::getLocalStringForUi("PROP_SHOW_CRITICAL_STRIKE"));
    
    m_pRoleMargicFindDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleMargicFindDesc->setString(UtilityHelper::getLocalStringForUi("PROP_SHOW_MARGIC_FIND"));
    
    m_pRoleBlockDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleBlockDesc->setString(UtilityHelper::getLocalStringForUi("PROP_SHOW_BLOCK"));
    
    m_pRoleDodgeDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleDodgeDesc->setString(UtilityHelper::getLocalStringForUi("PROP_SHOW_DODGE"));
    
    m_pRoleAttackDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleAttackDesc->setString(UtilityHelper::getLocalStringForUi("PROP_SHOW_ATTACK"));
    
    m_pRoleDefenseDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleDefenseDesc->setString(UtilityHelper::getLocalStringForUi("PROP_SHOW_DEFENSE"));
    
    
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
    
    
    m_pBtnClose->addClickEventListener(CC_CALLBACK_1(RoleLayer::onClickClose, this));
    m_pShopBtn->addClickEventListener(CC_CALLBACK_1(RoleLayer::onClickShop, this));
    
    
    return true;
}
void RoleLayer::refreshUIView()
{
    updateEquipProp();
    updateRoleProp();
}
void RoleLayer::updateRoleProp()
{
    m_pRoleLevel->setString(Value(int(PlayerProperty::getInstance()->getLevel())).asString());
    m_pRoleHp->setString(StringUtils::format("%d/%d",int(PlayerProperty::getInstance()->getCurrentHP()),int(PlayerProperty::getInstance()->getMaxHP())));
    m_pRoleMp->setString(StringUtils::format("%d/%d",int(PlayerProperty::getInstance()->getCurrentMP()),int(PlayerProperty::getInstance()->getMaxMP())));
    m_pRoleExp->setString(StringUtils::format("%d/%d",int(PlayerProperty::getInstance()->getExp()),int(GameFormula::getNextLevelExp(PlayerProperty::getInstance()->getLevel()))));
    m_pRoleLightDis->setString(StringUtils::format("%d",int(PlayerProperty::getInstance()->getLightDistance())));
    m_pRoleSearchDis->setString(StringUtils::format("%d",int(PlayerProperty::getInstance()->getSearchDistance())));
    m_pRoleCriticalStrike ->setString(StringUtils::format("%d%%",int(PlayerProperty::getInstance()->getCriticalStrikeRate().GetFloatValue()*100.0)));
    m_pRoleMargicFind->setString(StringUtils::format("%d%%",int(PlayerProperty::getInstance()->getMagicItemFindRate().GetFloatValue()*100.0)));
    m_pRoleBlock->setString(StringUtils::format("%d%%",int(PlayerProperty::getInstance()->getBlockRate().GetFloatValue()*100.0)));
    m_pRoleDodge->setString(StringUtils::format("%d%%",int(PlayerProperty::getInstance()->getDodgeRate().GetFloatValue()*100.0)));
    CCLOG("role minAttack:%d,maxAttack:%d",int(PlayerProperty::getInstance()->getMinAttack()),int(PlayerProperty::getInstance()->getMaxAttack()));
    m_pRoleAttack->setString(StringUtils::format("%d-%d",int(PlayerProperty::getInstance()->getMinAttack()),int(PlayerProperty::getInstance()->getMaxAttack())));
    m_pRoleDefense->setString(StringUtils::format("%d",int(PlayerProperty::getInstance()->getDefense())));
    
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
    clickEffect();
   
}
void RoleLayer::onClickClose(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    PopupUILayer* popupLayer = PopupUILayerManager::getInstance()->getCurrentPopUpLayer();
    if (popupLayer) {
        popupLayer->closePopup();
    }
}