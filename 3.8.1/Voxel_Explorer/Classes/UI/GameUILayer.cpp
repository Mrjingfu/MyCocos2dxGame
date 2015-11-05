//
//  GameUILayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/16.
//
//

#include "GameUILayer.h"
#include "UtilityHelper.h"
#include "GameConfig.h"
#include "PopupUILayerManager.h"
#include "PlayerProperty.hpp"
#include "GameFormula.hpp"
#include "VoxelExplorer.h"
#include "EventConst.h"
#include "ui/CocosGUI.h"
#include "NoteUi.h"
#include "StandardMonster.hpp"

USING_NS_CC;
GameUILayer::GameUILayer()
{
    m_pRoleBtn          = nullptr;
    m_pRoleHpBar        = nullptr;
    m_pRoleCurHp        = nullptr;
    m_pRoleMaxHp        = nullptr;
    m_pRoleMpBar        = nullptr;
    m_pRoleCurMp        = nullptr;
    m_pRoleMaxMp        = nullptr;
    m_pRoleExpBar       = nullptr;
    m_pRoleLevel        = nullptr;
    
    m_pMonsterLayout    = nullptr;
    m_pMonsterCurHp     = nullptr;
    m_pMonsterMaxHp     = nullptr;
    m_pMonsterLevel     = nullptr;
    m_pMonsterName      = nullptr;
    m_pMonsterHpBar     = nullptr;
    m_pMonsterBtn       = nullptr;
    
    m_pGameMapBtn       = nullptr;
    m_pGameMsgBtn       = nullptr;
    m_pGameSearchBtn    = nullptr;
    
    for (int i = 1 ; i<9; i++) {
        m_pRoleBuffers[i] = nullptr;
        m_pMonsterBuffers[i] = nullptr;
    }
    
    m_pListMsgs = nullptr;
    _isOpenSmailMap = false;
    
}
GameUILayer::~GameUILayer()
{
    
}

bool GameUILayer::addEvents()
{
      
    m_pRoleBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "btn_role"));
    if (!m_pRoleBtn)
        return false;
     m_pRoleHpBar = dynamic_cast<ui::LoadingBar*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_blood"));
    if (!m_pRoleHpBar)
        return false;
    m_pRoleMpBar = dynamic_cast<ui::LoadingBar*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_margic"));
    if (!m_pRoleMpBar)
        return false;

    m_pRoleCurHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_blood_num"));
    if (!m_pRoleCurHp)
        return false;

    m_pRoleMaxHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_blood_maxnum"));
    if(!m_pRoleMaxHp)
        return false;

    m_pRoleCurMp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_margic_num"));
    if (!m_pRoleCurMp)
        return false;

    
    m_pRoleMaxMp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_margic_maxnum"));
    if(!m_pRoleMaxMp)
        return false;

    
    m_pRoleExpBar = dynamic_cast<ui::LoadingBar*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_exp"));
    if(!m_pRoleExpBar)
        return false;

    
    m_pRoleLevel = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_lv_num"));
    if (!m_pRoleLevel)
        return false;
    
    for (int i=1 ; i<9; i++)
    {
        m_pRoleBuffers[i] =  dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, StringUtils::format("role_buffer_%d",i)));
        if(!m_pRoleBuffers[i])
            return false;
        m_pRoleBuffers[i]->setVisible(false);
    }
    
    
    m_pMonsterLayout =  dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "Panel_monster"));
    if (!m_pMonsterLayout)
        return false;

    m_pMonsterCurHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_monster_blood_num"));
    if (!m_pMonsterCurHp)
        return false;
    
    m_pMonsterHpBar = dynamic_cast<ui::LoadingBar*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_monster_blood"));
    if (!m_pMonsterHpBar)
        return false;
    
    m_pMonsterBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "btn_monster"));
    if (!m_pMonsterBtn)
        return false;
    m_pMonsterIcon = dynamic_cast<Sprite*>(UtilityHelper::seekNodeByName(m_pRootNode, "monster_icon"));
    if (!m_pMonsterIcon)
        return false;
    
    m_pMonsterMaxHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_monster_blood_maxnum"));
    if(!m_pMonsterMaxHp)
        return false;
   
    m_pMonsterName = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "monster_name"));
    if(!m_pMonsterName)
        return false;
    
    m_pMonsterLevel = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "monster_lv_num"));
    if (!m_pMonsterLevel)
        return false;
   
    
    for (int i=1 ; i<9; i++)
    {
        m_pMonsterBuffers[i] =  dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, StringUtils::format("monster_buffer_%d",i)));
        if(!m_pMonsterBuffers[i])
            return false;
        m_pMonsterBuffers[i]->setVisible(false);
    }

    m_pGameMsgBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_msg"));
    if (!m_pGameMsgBtn)
        return false;
    m_pGameMapBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_map"));
    if (!m_pGameMapBtn)
        return false;
    m_pGameSearchBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_search"));
    if (!m_pGameSearchBtn)
        return false;
    
    ui::ImageView* toolBarImg = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_toolbar_bg"));
    if (!toolBarImg)
        return false;
    
    m_pListMsgs = ui::ListView::create();
    m_pListMsgs->setBackGroundImageScale9Enabled(true);
    m_pListMsgs->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pListMsgs->setTouchEnabled(true);
    m_pListMsgs->setItemsMargin(5);
    m_pListMsgs->setDirection(ui::ScrollView::Direction::VERTICAL);
    m_pListMsgs->setBackGroundImage("ui_frame_5.png",cocos2d::ui::TextureResType::PLIST);
    m_pListMsgs->setContentSize(cocos2d::Size(SCREEN_WIDTH,SCREEN_HEIGHT*0.3));
    m_pListMsgs->setPosition(Vec2(WND_CENTER_X,toolBarImg->getPosition().y+toolBarImg->getContentSize().height));
    m_pRootLayer->addChild(m_pListMsgs);
    m_pListMsgs->setVisible(false);
    
    m_pGameMapBtn->setTouchEnabled(true);
    m_pGameMapBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickMap, this));
    m_pGameSearchBtn->setTouchEnabled(true);
    m_pGameSearchBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickSearch, this));
    m_pGameMsgBtn->setTouchEnabled(true);
    m_pGameMsgBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickMsg, this));
    m_pRoleBtn->setTouchEnabled(true);
    m_pRoleBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickRole, this));
    m_pRoleHpBar->setScale9Enabled(true);
    m_pRoleExpBar->setScale9Enabled(true);
    m_pRoleMpBar->setScale9Enabled(true);

    
    m_pMonsterLayout->setVisible(false);
    m_pMonsterHpBar->setPercent(100);
    m_pMonsterName->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    
    updateRoleUi();
    
    
    return true;
}

void GameUILayer::onEventRoleLevelUp(cocos2d::EventCustom *sender)
{
    
}

void GameUILayer::onEventUpdateRoleProp(cocos2d::EventCustom *sender)
{
    CCLOG("onEventUpdateProp");
    updateRoleUi();
}

void GameUILayer::onEventRoleDead(cocos2d::EventCustom *sender)
{
    
}
void GameUILayer::onEvenetRoleHud(cocos2d::EventCustom *sender)
{
    
}
void GameUILayer::onEvenetMonsterDead(cocos2d::EventCustom *sender)
{
    CCLOG("onEvenetMonsterDead");
    BaseMonster* monster = static_cast<BaseMonster*>(sender->getUserData());
    if (monster->getState() == BaseMonster::MonsterState::MS_DEATH) {
        m_pMonsterLayout->setVisible(false);
        m_pMonsterHpBar->setPercent(100);
    }

}

void GameUILayer::onEventMonsterHud(cocos2d::EventCustom *sender)
{
    HurtData* hurData = static_cast<HurtData*>(sender->getUserData());
     Vec2 pt = VoxelExplorer::getInstance()->getMainCamera()->projectGL(hurData->m_vPos);
    if (hurData->m_bDodge) {
       
        PopupUILayerManager::getInstance()->showStatus(TIP_DODGE, Vec2(pt.x, pt.y+TerrainTile::CONTENT_SCALE*2.5), StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_DODGE").c_str(),hurData->m_nDamage));
        CCLOG("monster 闪避");
    }else {
        if((hurData->m_bBlocked && hurData->m_bCriticalStrike) || hurData->m_bBlocked)
        {
            PopupUILayerManager::getInstance()->showStatus(TIP_BOLOCK, Vec2(pt.x, pt.y+TerrainTile::CONTENT_SCALE*2.5), StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_BOLOCK").c_str(),hurData->m_nDamage));
            CCLOG("monster 格挡");
        }else if (hurData->m_bCriticalStrike)
        {
            PopupUILayerManager::getInstance()->showStatus(TIP_CRITICAL_STRIKE, Vec2(pt.x, pt.y+TerrainTile::CONTENT_SCALE*2.5),StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_CRITICAL_STRIKE").c_str(),hurData->m_nDamage));
             CCLOG("monster 暴击");
        }else{
            PopupUILayerManager::getInstance()->showStatus(TIP_NEGATIVE, Vec2(pt.x, pt.y+TerrainTile::CONTENT_SCALE*2.5), Value(hurData->m_nDamage).asString());
            CCLOG("pt x:%f y%f",pt.x,pt.y);
        }

    }
    

}
void GameUILayer::onEventUpdateMonsterProp(cocos2d::EventCustom *sender)
{
    BaseMonster* monster = static_cast<BaseMonster*>(sender->getUserData());
    if (monster->getState() != BaseMonster::MonsterState::MS_DEATH) {
        m_pMonsterLayout->setVisible(true);
        float hpPer =monster->getMonsterProperty()->getCurrentHP().GetFloatValue()/PlayerProperty::getInstance()->getMaxHp().GetFloatValue() *100.0f;
        m_pMonsterHpBar->setPercent(hpPer);
        m_pMonsterCurHp->setString(StringUtils::format("%d",int(monster->getMonsterProperty()->getCurrentHP())));
        m_pMonsterMaxHp->setString(StringUtils::format("%d",int(monster->getMonsterProperty()->getMaxHP())));
        m_pMonsterLevel->setString(StringUtils::format("%d",int(monster->getMonsterProperty()->getLevel())));
        m_pMonsterName->setString(monster->getName());
    }
}

void GameUILayer::onEnter()
{
    WrapperUILayer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_PROPERTY_DIRTY, CC_CALLBACK_1(GameUILayer::onEventUpdateRoleProp,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_LEVEL_UP, CC_CALLBACK_1(GameUILayer::onEventRoleLevelUp,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_DEATH, CC_CALLBACK_1(GameUILayer::onEventRoleDead,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_HURT, CC_CALLBACK_1(GameUILayer::onEvenetRoleHud,this));
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MONSTER_HURT, CC_CALLBACK_1(GameUILayer::onEventMonsterHud,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MONSTER_PROPERTY_DIRTY, CC_CALLBACK_1(GameUILayer::onEventUpdateMonsterProp,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MONSTER_DEATH, CC_CALLBACK_1(GameUILayer::onEvenetMonsterDead,this));
    
}
void GameUILayer::onExit()
{
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_PROPERTY_DIRTY);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_LEVEL_UP);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_DEATH);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_HURT);
    
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MONSTER_HURT);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MONSTER_PROPERTY_DIRTY);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MONSTER_DEATH);

    WrapperUILayer::onExit();
}
void GameUILayer::updateRoleUi()
{
    float hpPer =PlayerProperty::getInstance()->getCurrentHp().GetFloatValue()/PlayerProperty::getInstance()->getMaxHp().GetFloatValue() *100.0f;
    m_pRoleHpBar->setPercent(hpPer);
    float mpPer =PlayerProperty::getInstance()->getCurrentMp().GetFloatValue()/PlayerProperty::getInstance()->getMaxMp().GetFloatValue() *100.0f;
    m_pRoleMpBar->setPercent(mpPer);
    m_pRoleCurHp->setString(Value(int(PlayerProperty::getInstance()->getCurrentHp())).asString());
    m_pRoleMaxHp->setString(Value(int(PlayerProperty::getInstance()->getMaxHp())).asString());
    m_pRoleCurMp->setString(Value(int(PlayerProperty::getInstance()->getCurrentHp())).asString());
    m_pRoleMaxMp->setString(Value(int(PlayerProperty::getInstance()->getMaxHp())).asString());
    float ExpPer =PlayerProperty::getInstance()->getExp().GetLongValue()/GameFormula::getNextLevelExp(PlayerProperty::getInstance()->getLevel()) *100.0f;
    CCLOG("EXPPER:%f",ExpPer);
    m_pRoleExpBar->setPercent(ExpPer);
    m_pRoleLevel->setString(Value(int(PlayerProperty::getInstance()->getLevel())).asString());

}


void GameUILayer::onClickRole(Ref* ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickRole");
    PopupUILayerManager::getInstance()->openPopup(ePopupRole);
}
void GameUILayer::onClickMap(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickMap");
    if (_isOpenSmailMap) {
        VoxelExplorer::getInstance()->getCurrentLevel()->showMap(false);
        _isOpenSmailMap = false;
    }else{
        VoxelExplorer::getInstance()->getCurrentLevel()->showMap(true);
         _isOpenSmailMap = true;
    }
}
void GameUILayer::onClickMsg(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickMsg");
    if (m_pListMsgs->isVisible())
    {
        m_pListMsgs->setVisible(false);
    }else
    {
        m_pListMsgs->setVisible(true);
    }
}
void GameUILayer::onClickSearch(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickSearch");
    if (m_pMonsterLayout->isVisible()) {
        m_pMonsterLayout->setVisible(false);
    }else{
        m_pMonsterLayout->setVisible(true);
    }
}
