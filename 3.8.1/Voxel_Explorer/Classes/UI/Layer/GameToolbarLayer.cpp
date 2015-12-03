//
//  GameToolbarLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#include "GameToolbarLayer.hpp"
#include "MessageManager.h"
#include "NoteUi.h"
#include "UtilityHelper.h"
#include "RandomDungeon.hpp"
#include "PopupUILayerManager.h"
#include "VoxelExplorer.h"
#include "GameFormula.hpp"
USING_NS_CC;
GameToolbarLayer::GameToolbarLayer()
{
    m_bIsOpenSmailMap           = false;
    m_bIsDist                   = false;
    
    m_pListMsgs                 = nullptr;
    m_pMsgFrame                 = nullptr;
    m_pGameMsgBtn               = nullptr;
    m_pGameMapBtn               = nullptr;
    m_pGameSearchBtn            = nullptr;
    m_pGameBagBtn               = nullptr;
    m_pGameDistBtn              = nullptr;
    m_pGamePauseBtn             = nullptr;
    
    m_pGameDistTipsFrame        = nullptr;
    m_pGameDistFrameCloseBtn    = nullptr;
    m_pGameDistFrameDesc        = nullptr;
    m_pRoleExpBar               = nullptr;
}
GameToolbarLayer::~GameToolbarLayer()
{
    
}
bool GameToolbarLayer::initUi()
{
    if (!load("gametoolbarLayer.csb",false))
        return false;
    setContentSize(m_pRootNode->getContentSize());
    m_pRootNode->setPosition(getContentSize()*0.5);
    return true;
}
bool GameToolbarLayer::addEvents()
{
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

    m_pMsgFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_msg_frame"));
    if (!m_pMsgFrame)
        return false;
    
    m_pGameDistTipsFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_dist_dialog"));
    if (!m_pGameDistTipsFrame)
        return false;
    m_pGameDistFrameDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_dist_tips_desc"));
    if (!m_pGameDistFrameDesc)
        return false;
    m_pGameDistFrameCloseBtn= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_dist_btn_close"));
    if (!m_pGameDistFrameCloseBtn)
        return false;

    m_pRoleExpBar = dynamic_cast<ui::LoadingBar*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_exp"));
    if(!m_pRoleExpBar)
        return false;
    
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
    m_pGameMapBtn->addClickEventListener(CC_CALLBACK_1(GameToolbarLayer::onClickMap, this));
    m_pGameSearchBtn->setTouchEnabled(true);
    m_pGameSearchBtn->addClickEventListener(CC_CALLBACK_1(GameToolbarLayer::onClickSearch, this));
    m_pGameMsgBtn->setTouchEnabled(true);
    m_pGameMsgBtn->addClickEventListener(CC_CALLBACK_1(GameToolbarLayer::onClickMsg, this));
    m_pGameBagBtn->setTouchEnabled(true);
    m_pGameBagBtn->addClickEventListener(CC_CALLBACK_1(GameToolbarLayer::onClickBag, this));
    m_pGameDistBtn->setTouchEnabled(true);
    m_pGameDistBtn->addClickEventListener(CC_CALLBACK_1(GameToolbarLayer::onClickDist, this));
    m_pGamePauseBtn->setTouchEnabled(true);
    m_pGamePauseBtn->addClickEventListener(CC_CALLBACK_1(GameToolbarLayer::onClickPause, this));

    m_pGameDistTipsFrame->setVisible(false);
    m_pGameDistFrameDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pGameDistFrameDesc->setString(UtilityHelper::getLocalStringForUi("GAME_SERACH_EXPLAIN"));
    m_pGameDistFrameCloseBtn->addClickEventListener(CC_CALLBACK_1(GameToolbarLayer::onClickDistTipsFrame, this));

    
    initMessageFrame();
    return true;
}

void GameToolbarLayer::refreshUIView()
{
    float playerExp = PlayerProperty::getInstance()->getExp().GetFloatValue();
    float nextLevelExp = GameFormula::getNextLevelExp(PlayerProperty::getInstance()->getLevel());
    float ExpPer = playerExp/nextLevelExp *100.0f;
    
    CCLOG("player Exp:%f,nexExp:%f,EXPPER:%f",playerExp,nextLevelExp,ExpPer);
    m_pRoleExpBar->setPercent(ExpPer);

}
void GameToolbarLayer::sendMessage(std::string msg,Color3B msgColor)
{
    if (MessageManager::getInstance()->isExceedMsgMax()) {
        m_pListMsgs->removeItem(0);
        MessageManager::getInstance()->removeMsg(0);
    }
    MessageManager::getInstance()->setMsg(msg, msgColor);
    setMsgItem(msg,msgColor);
    
}
void GameToolbarLayer::setMsgItem(std::string msg,cocos2d::Color3B msgColor )
{
    NoteUi* noteui = NoteUi::create();
    noteui->setMsg(msg,msgColor);
    m_pListMsgs->pushBackCustomItem( noteui);
    if ( m_pListMsgs->getItems().size()*noteui->getContentSize().height > m_pListMsgs->getContentSize().height) {
        //        m_pListMsgs->scrollToBottom(0.5,false);
        m_pListMsgs->forceDoLayout();
        m_pListMsgs->jumpToBottom();
    }
}
void GameToolbarLayer::initMessageFrame()
{
    Vector<MsgData*> msgList = MessageManager::getInstance()->getMsgList();
    if (msgList.empty())
    {
        std::string rungenName;
        if(RandomDungeon::getInstance()->getCurrentDungeonNode()->isBossDepth())
            rungenName = RandomDungeon::getInstance()->getCurrentDungeonNode()->m_strDungeonBossName.c_str();
        else
            rungenName = RandomDungeon::getInstance()->getCurrentDungeonNode()->m_strDungeonName.c_str();
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
void GameToolbarLayer::onClickBag(Ref* ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickRole");
    if (m_bIsDist||m_bIsOpenSmailMap) {
        return;
    }
    
    PopupUILayerManager::getInstance()->openPopup(ePopupRole);
    onClickDistTipsFrame(nullptr);
}
void GameToolbarLayer::onClickMap(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickMap");
    if (m_bIsDist) {
        return;
    }
    if (m_bIsOpenSmailMap) {
        VoxelExplorer::getInstance()->getCurrentLevel()->showMap(false);
        m_bIsOpenSmailMap = false;
    }else{
        VoxelExplorer::getInstance()->getCurrentLevel()->showMap(true);
        m_bIsOpenSmailMap = true;
    }
    onClickDistTipsFrame(nullptr);
}
void GameToolbarLayer::onClickDistTipsFrame(cocos2d::Ref *ref)
{
    //     CHECK_ACTION(ref);
    CCLOG("onClickSearchTipsFrame");
    if (m_pGameDistTipsFrame&& m_bIsDist) {
        m_pGameDistTipsFrame->setVisible(false);
        if (m_pMsgFrame->isVisible())
        {
            m_pGameDistTipsFrame->setPosition(Vec2(m_pGameDistTipsFrame->getPositionX(), m_pGameDistTipsFrame->getPositionY()-m_pMsgFrame->getContentSize().height));
        }
    }
    m_bIsDist = false;
    
}

void GameToolbarLayer::onClickMsg(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickMsg");
    if (m_bIsDist||m_bIsOpenSmailMap) {
        return;
    }
    onClickDistTipsFrame(nullptr);
    if (m_pMsgFrame->isVisible())
    {
        m_pMsgFrame->setVisible(false);
    }else
    {
        m_pMsgFrame->setVisible(true);
        m_pListMsgs->forceDoLayout();
        m_pListMsgs->scrollToBottom(0.5,false);
    }
    
}
void GameToolbarLayer::onClickDist(cocos2d::Ref *ref)
{
    CCLOG("onClickDist");
    if (m_bIsDist || m_bIsOpenSmailMap)
        return;
    m_bIsDist = true;
    if (m_pGameDistTipsFrame ) {
        if (m_pMsgFrame->isVisible()) {
            m_pGameDistTipsFrame->setPosition(Vec2(m_pGameDistTipsFrame->getPositionX(), m_pGameDistTipsFrame->getPositionY()+m_pMsgFrame->getContentSize().height));
        }
        m_pGameDistTipsFrame->setVisible(true);
    }
}
void GameToolbarLayer::onClickPause(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickPause");
    PopupUILayerManager::getInstance()->openPopup(ePopupPause);
}
void GameToolbarLayer::onClickSearch(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickSearch");
    if (m_bIsDist || m_bIsOpenSmailMap)
        return;
    VoxelExplorer::getInstance()->searchAndCheck();
    
}

