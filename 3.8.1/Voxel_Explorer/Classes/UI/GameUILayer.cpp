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
#include "RandomDungeon.hpp"
#include "StandardMonster.hpp"
#include "MessageManager.h"
#include "InfoPopupUI.h"
#include "BaseDoor.hpp"
#include "PotionsProperty.hpp"
#include "ScrollProperty.hpp"
#include "RolePopupUI.h"
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
    m_pRoleName         = nullptr;
    
    m_pMonsterLayout    = nullptr;
    m_pMonsterCurHp     = nullptr;
    m_pMonsterMaxHp     = nullptr;
    m_pMonsterLevel     = nullptr;
    m_pMonsterName      = nullptr;
    m_pMonsterHpBar     = nullptr;
    m_pMonsterBtn       = nullptr;
    m_pMonsterMpBar     = nullptr;
    m_pMonsterCurMp     = nullptr;
    m_pMonsterMaxMp     = nullptr;
    
    m_pGameMapBtn       = nullptr;
    m_pGameMsgBtn       = nullptr;
    m_pGameSearchBtn    = nullptr;
    m_pGameGoldNum      = nullptr;
    m_pGameSilverNum    = nullptr;
    m_pGameCopperNum    = nullptr;
    m_pGameLevelInfoName    = nullptr;
    m_pGameLevelInfoFloor   = nullptr;
    for (int i = 1 ; i<9; i++) {
        m_pRoleBuffers[i] = nullptr;
        m_pMonsterBuffers[i] = nullptr;
    }
    
    m_pListMsgs = nullptr;
    _isOpenSmailMap = false;
    _isDist = false;
    m_pMsgFrame = nullptr;
    m_pGameDistTipsFrame  = nullptr;
    m_pGameDistFrameCloseBtn = nullptr;
    m_pGameDistFrameDesc  = nullptr;
    m_pGameBagBtn = nullptr;;
    m_pGameDistBtn = nullptr;;
    m_pGamePauseBtn = nullptr;;

}
GameUILayer::~GameUILayer()
{
    
}

bool GameUILayer::addEvents()
{
    //角色
    m_pRoleBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "btn_role"));
    if (!m_pRoleBtn)
        return false;
    
    m_pRoleName =dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "role_name"));
    if (!m_pRoleName)
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
    
    //怪物
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
   
    m_pMonsterMpBar = dynamic_cast<ui::LoadingBar*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_monster_margic"));
    if (!m_pMonsterMpBar)
        return false;
    
    m_pMonsterCurMp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_monster_margic_num"));
    if (!m_pMonsterCurMp)
        return false;
    
    m_pMonsterMaxMp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_monster_margic_maxnum"));
    if (!m_pMonsterMaxMp)
        return false;
    
    for (int i=1 ; i<9; i++)
    {
        m_pMonsterBuffers[i] =  dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, StringUtils::format("monster_buffer_%d",i)));
        if(!m_pMonsterBuffers[i])
            return false;
        m_pMonsterBuffers[i]->setVisible(false);
    }

    //游戏
    m_pGameMsgBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_msg"));
    if (!m_pGameMsgBtn)
        return false;
    m_pGameMapBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_map"));
    if (!m_pGameMapBtn)
        return false;
    m_pGameSearchBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_search"));
    if (!m_pGameSearchBtn)
        return false;
    m_pGameBagBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_bag"));
    if (!m_pGameBagBtn)
        return false;
    m_pGameDistBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_dist"));
    if (!m_pGameDistBtn)
        return false;
    m_pGamePauseBtn = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_pause"));
    if (!m_pGamePauseBtn)
        return false;
    
    m_pGameGoldNum   = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_gold_num"));
    if (!m_pGameGoldNum)
        return false;
    m_pGameSilverNum    = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_silver_num"));
    if (!m_pGameSilverNum)
        return false;
    m_pGameCopperNum    = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_copper_num"));
    if (!m_pGameCopperNum)
        return false;
    
    m_pGameLevelInfoName    = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_level_info_name"));
    if (!m_pGameLevelInfoName)
        return false;
    m_pGameLevelInfoFloor   = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_level_info_floor"));
    if (!m_pGameLevelInfoFloor)
        return false;
    
    m_pMsgFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_msg_frame"));
    if (!m_pMsgFrame)
        return false;
    
    m_pGameDistTipsFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_dist_dialog"));
    if (!m_pGameDistTipsFrame)
        return false;
    m_pGameDistFrameDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_dist_tips_desc"));
    if (!m_pGameDistFrameDesc)
        return false;
    m_pGameDistFrameCloseBtn= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_dist_btn_close"));
    if (!m_pGameDistFrameCloseBtn)
        return false;
    
   
    if (!registerTouchEvent()) {
        return false;
    }
    
    m_pListMsgs = ui::ListView::create();
    m_pListMsgs->setBackGroundImageScale9Enabled(true);
    m_pListMsgs->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pListMsgs->setScrollBarEnabled(false);
    m_pListMsgs->setDirection(ui::ScrollView::Direction::VERTICAL);
    m_pListMsgs->setContentSize(cocos2d::Size(m_pMsgFrame->getContentSize().width*0.95,m_pMsgFrame->getContentSize().height*0.9));
    m_pListMsgs->setPosition(m_pMsgFrame->getContentSize()*0.5);
    m_pMsgFrame->addChild(m_pListMsgs);
    m_pMsgFrame->setVisible(false);
    
    m_pGameMapBtn->setTouchEnabled(true);
    m_pGameMapBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickMap, this));
    m_pGameSearchBtn->setTouchEnabled(true);
    m_pGameSearchBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickSearch, this));
    m_pGameMsgBtn->setTouchEnabled(true);
    m_pGameMsgBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickMsg, this));
    m_pGameBagBtn->setTouchEnabled(true);
    m_pGameBagBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickRole, this));
    m_pGameDistBtn->setTouchEnabled(true);
    m_pGameDistBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickDist, this));
    m_pGamePauseBtn->setTouchEnabled(true);
    m_pGamePauseBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickPause, this));
    
    m_pRoleBtn->setTouchEnabled(true);
    m_pRoleBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickRole, this));

    m_pRoleName->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleCurHp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleMaxHp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleCurMp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleMaxMp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleLevel->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    
    m_pGameLevelInfoName->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pGameLevelInfoFloor->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pGameGoldNum->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pGameSilverNum->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pGameCopperNum->setFontName(UtilityHelper::getLocalString("FONT_NAME"));

    m_pMonsterLayout->setVisible(false);
    m_pMonsterHpBar->setPercent(100);
    m_pMonsterName->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pMonsterCurHp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pMonsterMaxHp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pMonsterLevel->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    
    m_pGameDistTipsFrame->setVisible(false);
    m_pGameDistFrameDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pGameDistFrameDesc->setString(UtilityHelper::getLocalStringForUi("GAME_SERACH_EXPLAIN"));
    m_pGameDistFrameCloseBtn->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickDistTipsFrame, this));
    
    updateRoleUi(); 
    updateGameInfo();
    initMessageFrame();
    return true;
}
bool GameUILayer::registerTouchEvent()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    if(touchListener == nullptr)
        return false;
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameUILayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameUILayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameUILayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}
bool GameUILayer::onTouchBegan(Touch *touch, Event *event)
{

    return _isDist;
}
void GameUILayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return;
}
void GameUILayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Ray ray;
    Vec2 pt = touch->getLocationInView();
    UtilityHelper::getCameraToViewportRay(VoxelExplorer::getInstance()->getMainCamera(), pt, &ray);
    Vec3 playerpt = VoxelExplorer::getInstance()->getPlayer()->getPosition3D();
    std::string infostr;
    std::string infoKey;
    if(checkSearchMapInfo(ray,infostr,infoKey))
    {
        InfoPopupUI* infoUi = static_cast<InfoPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupInfo));
        onClickDistTipsFrame(nullptr);
        infoUi->setDarkLayerVisble(false);
    }
    CCLOG("PT X:%f y:%f z:%f",ray._origin.x,ray._origin.y,ray._origin.z);
    

    return;
}
bool GameUILayer::checkSearchMapInfo(const cocos2d::Ray ray,std::string& infoIcon,std::string& infoDesc)
{
    
    if (ray.intersects(VoxelExplorer::getInstance()->getPlayer()->getAABB())) {
        CCLOG("playerpt X:%f y:%f z:%f",VoxelExplorer::getInstance()->getPlayer()->getPosition3D().x,VoxelExplorer::getInstance()->getPlayer()->getPosition3D().y,VoxelExplorer::getInstance()->getPlayer()->getPosition3D().z);
        return true;
    }
    
    Layer* pickableLayer = VoxelExplorer::getInstance()->getPickableItemsLayer();
    for (auto child : pickableLayer->getChildren())
    {
         PickableItem* item = dynamic_cast<PickableItem*>(child);
        if (item&& ray.intersects(item->getAABB())) {
            CCLOG("pickable Actor");
            CCLOG("PT X:%f y:%f z:%f",item->getPosition3D().x,item->getPosition3D().y,item->getPosition3D().z);
            return true;
        }
    }
    
    Layer* monsterLayer = VoxelExplorer::getInstance()->getMonstersLayer();
    for (auto child : monsterLayer->getChildren())
    {
        BaseMonster* monster = dynamic_cast<BaseMonster*>(child);
        if (monster&& ray.intersects(monster->getAABB())) {
            CCLOG("PT X:%f y:%f z:%f",monster->getPosition3D().x,monster->getPosition3D().y,monster->getPosition3D().z);
            CCLOG("BaseMonster");
            return true;
        }
    }
    
    Layer* doorLayer = VoxelExplorer::getInstance()->getTerrainDoorsLayer();
    for (auto child : doorLayer->getChildren())
    {
        BaseDoor* door = dynamic_cast<BaseDoor*>(child);
        if (door&& ray.intersects(door->getAABB())) {
            CCLOG("PT X:%f y:%f z:%f",door->getPosition3D().x,door->getPosition3D().y,door->getPosition3D().z);
            CCLOG("BaseDoor");
            return true;
        }
    }

    
    Layer* terrainTiles = VoxelExplorer::getInstance()->getTerrainTilesLayer();
    for (auto child : terrainTiles->getChildren())
    {
        TerrainTile* tile = dynamic_cast<TerrainTile*>(child);
        if (tile&& ray.intersects(tile->getAABB())) {
            CCLOG("TerrainTile");
            CCLOG("PT X:%f y:%f z:%f",tile->getPosition3D().x,tile->getPosition3D().y,tile->getPosition3D().z);
            return true;
        }
    }
    return false;

}
void GameUILayer::onEvenetUserPotion(cocos2d::EventCustom *sender)
{
    CCLOG("onEvenetUserPotion");
    PopupUILayerManager::getInstance()->closeCurrentPopup();
    
    //窗口都未关闭,回调后来判断是否关闭
    Vec2 pt = VoxelExplorer::getInstance()->getMainCamera()->projectGL(VoxelExplorer::getInstance()->getPlayer()->getPosition3D());
    pt = Vec2(pt.x, pt.y+TerrainTile::CONTENT_SCALE*2.5);
    PotionsProperty* potionsProperty = static_cast<PotionsProperty*>(sender->getUserData());
    PickableItem::PickableItemType itemType = potionsProperty->getPickableItemType();
    switch (itemType) {
        case PickableItem::PIT_POTION_MINORHEALTH:
        case PickableItem::PIT_POTION_LESSERHEALTH:
        case PickableItem::PIT_POTION_HEALTH:
            CCLOG("使用治疗药水");
            PopupUILayerManager::getInstance()->showStatus(TIP_POSITIVE, StringUtils::format(UtilityHelper::getLocalStringForUi("USE_POTION_ TREAT").c_str(),int(potionsProperty->getValue())),pt);
             PopupUILayerManager::getInstance()->closeCurrentPopup();
            //治疗药水
            break;
        case PickableItem::PIT_POTION_MINORMANA:
        case PickableItem::PIT_POTION_LESSERMANA:
        case PickableItem::PIT_POTION_MANA:
            CCLOG("使用魔法药水");
            //魔法药水
            PopupUILayerManager::getInstance()->showStatus(TIP_BLUE, StringUtils::format(UtilityHelper::getLocalStringForUi("USE_POTION_ MAGIC").c_str(),int(potionsProperty->getValue())),pt);
             PopupUILayerManager::getInstance()->closeCurrentPopup();
            break;
        case PickableItem::PIT_POTION_MINORRECOVERY:
        case PickableItem::PIT_POTION_LESSERRECOVERY:
        case PickableItem::PIT_POTION_RECOVERY:
            //恢复药水
            CCLOG("恢复药水");
            break;
        case PickableItem::PIT_POTION_DETOXIFICATION:
        case PickableItem::PIT_POTION_SPECIFIC:
            //解毒药水
            CCLOG("解毒药水");
            break;
        default:
            break;
    }

}
void GameUILayer::onEvenetUserScroll(cocos2d::EventCustom *sender)
{
    PopupUILayerManager::getInstance()->closeCurrentPopup();
    //窗口都未关闭,回调后来判断是否关闭
    CCLOG("onEvenetUserScroll");
    ScrollProperty* scrollProperty = static_cast<ScrollProperty*>(sender->getUserData());
    
    if (scrollProperty->getPickableItemType() == PickableItem::PIT_SCROLL_INDENTIFY)
    {
         //鉴定卷轴
        PopupUILayer* popup = nullptr;
        RolePopupUI* rolePopup = nullptr;
        if(PopupUILayerManager::getInstance()->isOpenPopup(ePopupRole, popup)){
            rolePopup = static_cast<RolePopupUI*>(popup);
        }else{
            rolePopup = static_cast<RolePopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupRole));
        }
        if (rolePopup) {
            rolePopup->setStateIdentify(true);
        }
        
    }else if(scrollProperty->getPickableItemType() == PickableItem::PIT_SCROLL_TELEPORT)
    {
        //传送卷轴
    }else if(scrollProperty->getPickableItemType() == PickableItem::PIT_SCROLL_SPEED)
    {
        //速度卷轴

    }else if(scrollProperty->getPickableItemType() == PickableItem::PIT_SCROLL_STEALTH)
    {
        //隐身卷轴
//        
    }else if(scrollProperty->getPickableItemType() == PickableItem::PIT_SCROLL_DESTINY)
    {
       //命运卷轴
    }
}

void GameUILayer::onEventRoleLevelUp(cocos2d::EventCustom *sender)
{
    CCLOG("onEventRoleLevelUp");
    updateRoleUi();
    PopupUILayerManager::getInstance()->showStatusImport(TIP_DEFAULT, UtilityHelper::getLocalStringForUi("GAME_MESSAGE_LEVEL_UP"));
    sendMessage(UtilityHelper::getLocalStringForUi("GAME_MESSAGE_LEVEL_UP"),PopupUILayerManager::getInstance()->getTipsColor(TIP_NEUTRAL));
}

void GameUILayer::onEventUpdateRoleProp(cocos2d::EventCustom *sender)
{
    CCLOG("onEventUpdateProp");
    updateRoleUi();
    updateGameInfo();
}

void GameUILayer::onEventRoleDead(cocos2d::EventCustom *sender)
{
    CCLOG("onEventRoleDead");
    updateRoleUi();
}
void GameUILayer::onEvenetRoleHud(cocos2d::EventCustom *sender)
{
       CCLOG("onEvenetRoleHud");
    HurtData* hurData = static_cast<HurtData*>(sender->getUserData());
    Vec2 pt = VoxelExplorer::getInstance()->getMainCamera()->projectGL(hurData->m_vPos);
    pt = Vec2(pt.x, pt.y+TerrainTile::CONTENT_SCALE*2.5);
    //    PopupUILayerManager::getInstance()->showPromptSign(TIP_QUESTION, pt);
    
    if (hurData->m_bDodge) {
        
        PopupUILayerManager::getInstance()->showStatus(TIP_DODGE,  StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_DODGE").c_str(),hurData->m_nDamage),pt);
        CCLOG("monster 闪避");
    }else {
        if((hurData->m_bBlocked && hurData->m_bCriticalStrike) || hurData->m_bBlocked)
        {
            PopupUILayerManager::getInstance()->showStatus(TIP_BOLOCK, StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_BOLOCK").c_str(),hurData->m_nDamage),pt);
            CCLOG("monster 格挡");
        }else if (hurData->m_bCriticalStrike)
        {
            PopupUILayerManager::getInstance()->showStatus(TIP_CRITICAL_STRIKE, StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_CRITICAL_STRIKE").c_str(),hurData->m_nDamage),pt);
            CCLOG("monster 暴击");
        }else{
            PopupUILayerManager::getInstance()->showStatus(TIP_NEGATIVE, Value(hurData->m_nDamage).asString(),pt);
            CCLOG("pt x:%f y%f",pt.x,pt.y);
        }
        
    }
    
}
void GameUILayer::onEvenetMonsterDead(cocos2d::EventCustom *sender)
{
    CCLOG("onEvenetMonsterDead");
    BaseMonster* monster = static_cast<BaseMonster*>(sender->getUserData());
    if (!monster)
        return;
    Vec2 pt = VoxelExplorer::getInstance()->getMainCamera()->projectGL(monster->getPosition3D());
    pt = Vec2(pt.x, pt.y+TerrainTile::CONTENT_SCALE*2.5);
    if (monster->getState() == BaseMonster::MonsterState::MS_DEATH) {
        m_pMonsterLayout->setVisible(false);
        m_pMonsterHpBar->setPercent(100);
        int roleLevel = PlayerProperty::getInstance()->getLevel();
        int monsterLevel = monster->getMonsterProperty()->getLevel();
        int exp = GameFormula::getKillNormalMonsterExp(roleLevel, monsterLevel);
        if (monster->getMonsterProperty()->isElite()) {
            exp = GameFormula::getKillEliteMonsterExp(roleLevel, monsterLevel);
        }
        PopupUILayerManager::getInstance()->showStatus(TIP_POSITIVE, StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_EXP").c_str(),exp),pt);
    }
 

}

void GameUILayer::onEventMonsterHud(cocos2d::EventCustom *sender)
{
        CCLOG("onEventMonsterHud");
    HurtData* hurData = static_cast<HurtData*>(sender->getUserData());
    Vec2 pt = VoxelExplorer::getInstance()->getMainCamera()->projectGL(hurData->m_vPos);
    pt = Vec2(pt.x, pt.y+TerrainTile::CONTENT_SCALE*2.5);
//    PopupUILayerManager::getInstance()->showPromptSign(TIP_QUESTION, pt);

    if (hurData->m_bDodge) {
       
        PopupUILayerManager::getInstance()->showStatus(TIP_DODGE,  StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_DODGE").c_str(),hurData->m_nDamage),pt);
        CCLOG("monster 闪避");
    }else {
        if((hurData->m_bBlocked && hurData->m_bCriticalStrike) || hurData->m_bBlocked)
        {
            PopupUILayerManager::getInstance()->showStatus(TIP_BOLOCK, StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_BOLOCK").c_str(),hurData->m_nDamage),pt);
            CCLOG("monster 格挡");
        }else if (hurData->m_bCriticalStrike)
        {
            PopupUILayerManager::getInstance()->showStatus(TIP_CRITICAL_STRIKE, StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_CRITICAL_STRIKE").c_str(),hurData->m_nDamage),pt);
             CCLOG("monster 暴击");
        }else{
            PopupUILayerManager::getInstance()->showStatus(TIP_NEUTRAL, Value(hurData->m_nDamage).asString(),pt);
            CCLOG("pt x:%f y%f",pt.x,pt.y);
        }
    }
    
}
void GameUILayer::onEventUpdateMonsterProp(cocos2d::EventCustom *sender)
{
    CCLOG("onEventUpdateMonsterProp");
    BaseMonster* monster = static_cast<BaseMonster*>(sender->getUserData());
    if (monster->getState() != BaseMonster::MonsterState::MS_DEATH) {
        m_pMonsterLayout->setVisible(true);
        float hpPer =monster->getMonsterProperty()->getCurrentHP().GetFloatValue()/monster->getMonsterProperty()->getMaxHP().GetFloatValue() *100.0f;
        m_pMonsterHpBar->setPercent(hpPer);
        m_pMonsterCurHp->setString(StringUtils::format("%d",int(monster->getMonsterProperty()->getCurrentHP())));
        m_pMonsterMaxHp->setString(StringUtils::format("%d",int(monster->getMonsterProperty()->getMaxHP())));
        m_pMonsterLevel->setString(StringUtils::format("%d",int(monster->getMonsterProperty()->getLevel())));
        std::string monsterName =UtilityHelper::getLocalString(MONSTER_MODEL_NAMES[monster->getMonsterType()]);
        if (monster->getMonsterProperty()->isElite()) {
            m_pMonsterName->setColor(PopupUILayerManager::getInstance()->getTipsColor(TIP_POSITIVE));
            monsterName = StringUtils::format(UtilityHelper::getLocalStringForUi("MONSTER_ELITE_NAME").c_str(),monsterName.c_str());
        }else{
            m_pMonsterName->setColor(PopupUILayerManager::getInstance()->getTipsColor(TIP_DEFAULT));
        }
         m_pMonsterName->setString(monsterName);
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
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_USE_POTION, CC_CALLBACK_1(GameUILayer::onEvenetUserPotion,this));

    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_USE_SCROLL, CC_CALLBACK_1(GameUILayer::onEvenetUserScroll,this));
    
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
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_USE_POTION);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_USE_SCROLL);
    WrapperUILayer::onExit();
}
void GameUILayer::sendMessage(std::string msg,Color3B msgColor)
{
    if (MessageManager::getInstance()->isExceedMsgMax()) {
        m_pListMsgs->removeItem(0);
        MessageManager::getInstance()->removeMsg(0);
    }
    MessageManager::getInstance()->setMsg(msg, msgColor);
    setMsgItem(msg,msgColor);

}
void GameUILayer::setMsgItem(std::string msg,cocos2d::Color3B msgColor )
{
    NoteUi* noteui = NoteUi::create();
    noteui->setMsg(msg,msgColor);
    m_pListMsgs->pushBackCustomItem( noteui);
    if ( m_pListMsgs->getItems().size()*noteui->getContentSize().height > m_pListMsgs->getContentSize().height) {
//        m_pListMsgs->scrollToBottom(0.5,false);
        m_pListMsgs->jumpToBottom();
    }
}
void GameUILayer::initMessageFrame()
{
    Vector<MsgData*> msgList = MessageManager::getInstance()->getMsgList();
    if (msgList.empty())
    {
        std::string rungenName =RandomDungeon::getInstance()->getCurrentDungeonNode()->m_strDungeonName.c_str();
        int flood =  int(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth);
        sendMessage(StringUtils::format(UtilityHelper::getLocalStringForUi("GAME_MESSAGE_NOT").c_str(),rungenName.c_str(),flood));
        return;
    }
    for(Vector<MsgData*>::iterator iter = msgList.begin();iter!=msgList.end();iter++)
    {
        MsgData* msgData = (*iter);
        setMsgItem(msgData->getMsg(),msgData->getMsgColor());
    }
}
void GameUILayer::updateGameInfo()
{
    m_pGameLevelInfoName->setString(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_strDungeonName.c_str());
    m_pGameLevelInfoFloor->setString(Value(int(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth)).asString());
    CCLOG(" gold: %s",StringUtils::format("%d",int(PlayerProperty::getInstance()->getGold())).c_str());
    CCLOG(" silver: %s",StringUtils::format("%d",int(PlayerProperty::getInstance()->getGold())).c_str());
    CCLOG(" copper: %s",StringUtils::format("%d",int(PlayerProperty::getInstance()->getGold())).c_str());
    
    
    m_pGameGoldNum->setString(StringUtils::format("%d",int(PlayerProperty::getInstance()->getGold())));
    m_pGameSilverNum->setString(StringUtils::format("%d",int(PlayerProperty::getInstance()->getSilver())));
    m_pGameCopperNum->setString(StringUtils::format("%d",int(PlayerProperty::getInstance()->getCopper())));
}

void GameUILayer::updateRoleUi()
{
    float hpPer =PlayerProperty::getInstance()->getCurrentHP().GetFloatValue()/PlayerProperty::getInstance()->getMaxHP().GetFloatValue() *100.0f;

    float mpPer =PlayerProperty::getInstance()->getCurrentMP().GetFloatValue()/PlayerProperty::getInstance()->getMaxMP().GetFloatValue() *100.0f;
    CCLOG("hpPer:%f mpPer:%f",hpPer,mpPer);
    m_pRoleMpBar->setPercent(mpPer);
    m_pRoleHpBar->setPercent(hpPer);
//    m_pRoleName->setString("")角色名
    m_pRoleCurHp->setString(Value(int(PlayerProperty::getInstance()->getCurrentHP())).asString());
    m_pRoleMaxHp->setString(Value(int(PlayerProperty::getInstance()->getMaxHP())).asString());
    m_pRoleCurMp->setString(Value(int(PlayerProperty::getInstance()->getCurrentMP())).asString());
    m_pRoleMaxMp->setString(Value(int(PlayerProperty::getInstance()->getMaxMP())).asString());
    float playerExp = float(PlayerProperty::getInstance()->getExp());
    float nextLevelExp = GameFormula::getNextLevelExp(PlayerProperty::getInstance()->getLevel());
    float ExpPer = playerExp/nextLevelExp *100.0f;
    
    CCLOG("player Exp:%f,nexExp:%f,EXPPER:%f",playerExp,nextLevelExp,ExpPer);
    m_pRoleExpBar->setPercent(ExpPer);
    m_pRoleLevel->setString(Value(int(PlayerProperty::getInstance()->getLevel())).asString());
    
}


void GameUILayer::onClickRole(Ref* ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickRole");
    PopupUILayerManager::getInstance()->openPopup(ePopupRole);
    onClickDistTipsFrame(nullptr);
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
     onClickDistTipsFrame(nullptr);
}
void GameUILayer::onClickDistTipsFrame(cocos2d::Ref *ref)
{
//     CHECK_ACTION(ref);
     CCLOG("onClickSearchTipsFrame");
    if (m_pGameDistTipsFrame&& _isDist) {
        m_pGameDistTipsFrame->setVisible(false);
        if (m_pMsgFrame->isVisible())
        {
            m_pGameDistTipsFrame->setPosition(Vec2(m_pGameDistTipsFrame->getPositionX(), m_pGameDistTipsFrame->getPositionY()-m_pMsgFrame->getContentSize().height));
        }
    }
    _isDist = false;
    
}

void GameUILayer::onClickMsg(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickMsg");
    if (_isOpenSmailMap) {
        return;
    }
     onClickDistTipsFrame(nullptr);
    if (m_pMsgFrame->isVisible())
    {
         m_pMsgFrame->setVisible(false);
    }else
    {
        m_pMsgFrame->setVisible(true);
        m_pListMsgs->scrollToBottom(0.5,false);
    }
   
}
void GameUILayer::onClickDist(cocos2d::Ref *ref)
{
    
    if (_isDist || _isOpenSmailMap)
        return;
    _isDist = true;
    if (m_pGameDistTipsFrame ) {
        if (m_pMsgFrame->isVisible()) {
            m_pGameDistTipsFrame->setPosition(Vec2(m_pGameDistTipsFrame->getPositionX(), m_pGameDistTipsFrame->getPositionY()+m_pMsgFrame->getContentSize().height));
        }
        m_pGameDistTipsFrame->setVisible(true);
    }
}
void GameUILayer::onClickPause(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickPause");
}
void GameUILayer::onClickSearch(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickSearch");

//    NoteUi* noteui = NoteUi::create();
//    noteui->setMsg(UtilityHelper::getLocalStringForUi("STATUS_TEXT_DODGE"),UtilityHelper::randomColor());
//    m_pListMsgs->pushBackCustomItem(noteui);
//    CCLOG("m_pListMsgs innerSize height:%f contentSize:%f",m_pListMsgs->getInnerContainerSize().height,m_pListMsgs->getContentSize().height);
//    if ( m_pListMsgs->getItems().size()*noteui->getContentSize().height > m_pListMsgs->getContentSize().height) {
//         m_pListMsgs->scrollToBottom(0.5,false);
//    }
   
}
