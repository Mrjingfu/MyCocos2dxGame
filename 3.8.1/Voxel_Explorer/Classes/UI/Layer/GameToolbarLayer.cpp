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
#include "ShopPopupUI.h"
#include "InformationPopupUI.h"
#include "NpcDataManager.hpp"
#include "AlertPopupUI.hpp"
#include "LevelResourceManager.h"
#include "SimpleAudioEngine.h"
#include "AchieveItemLayer.hpp"
#include "AchieveItemUI.hpp"
USING_NS_CC;
GameToolbarLayer::GameToolbarLayer()
{
    m_bIsDist                   = false;
    
    m_pListMsgs                 = nullptr;
    m_pMsgFrame                 = nullptr;
    m_pGameMsgBtn               = nullptr;
    m_pGameMapBtn               = nullptr;
    m_pGameSearchBtn            = nullptr;
    m_pGameBagBtn               = nullptr;
    m_pGameDistBtn              = nullptr;
    m_pGamePauseBtn             = nullptr;
    m_pGameMsgBtnIcon           = nullptr;
    m_pGameMapBtnIcon           = nullptr;
    m_pGameSearchBtnIcon        = nullptr;
    m_pGameBagBtnIcon           = nullptr;
    m_pGameDistBtnIcon          = nullptr;
    m_pGamePauseBtnIcon         = nullptr;
    
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
    
    m_pGameMsgBtnIcon = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_msg_icon"));
    if (!m_pGamePauseBtn)
        return false;
    m_pGameMapBtnIcon = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_map_icon"));
    if (!m_pGamePauseBtn)
        return false;
    m_pGameSearchBtnIcon = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_search_icon"));
    if (!m_pGamePauseBtn)
        return false;
    m_pGameBagBtnIcon  = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_bag_icon"));
    if (!m_pGamePauseBtn)
        return false;
    m_pGameDistBtnIcon = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_dist_icon"));
    if (!m_pGamePauseBtn)
        return false;
    m_pGamePauseBtnIcon  = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_btn_pause_icon"));
    if (!m_pGamePauseBtn)
        return false;
    

    m_pMsgFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_msg_frame"));
    if (!m_pMsgFrame)
        return false;
    
    m_pGameDistTipsFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_dist_dialog"));
    if (!m_pGameDistTipsFrame)
        return false;
    m_pGameDistFrameDesc = dynamic_cast<ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_dist_tips_desc"));
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
    m_pGameMapBtn->addTouchEventListener(CC_CALLBACK_2(GameToolbarLayer::onClickMap, this));
    m_pGameSearchBtn->setTouchEnabled(true);
    m_pGameSearchBtn->addTouchEventListener(CC_CALLBACK_2(GameToolbarLayer::onClickSearch, this));
    m_pGameMsgBtn->setTouchEnabled(true);
    m_pGameMsgBtn->addTouchEventListener(CC_CALLBACK_2(GameToolbarLayer::onClickMsg, this));
    m_pGameBagBtn->setTouchEnabled(true);
    m_pGameBagBtn->addTouchEventListener(CC_CALLBACK_2(GameToolbarLayer::onClickBag, this));
    m_pGameDistBtn->setTouchEnabled(true);
    m_pGameDistBtn->addTouchEventListener(CC_CALLBACK_2(GameToolbarLayer::onClickDist, this));
    m_pGamePauseBtn->setTouchEnabled(true);
    m_pGamePauseBtn->addTouchEventListener(CC_CALLBACK_2(GameToolbarLayer::onClickPause, this));

    m_pGameDistTipsFrame->setVisible(false);
    m_pGameDistFrameDesc->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
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
    noteui->setContentSize(noteui->getContentSize()+cocos2d::Size(0,10));
    m_pListMsgs->pushBackCustomItem( noteui);
    noteui->setMsg(msg,msgColor);
    if ( m_pListMsgs->getItems().size()*noteui->getContentSize().height > m_pListMsgs->getContentSize().height) {
        //        m_pListMsgs->scrollToBottom(0.5,false);
        m_pListMsgs->forceDoLayout();
        m_pListMsgs->scrollToBottom(0.8,false);
    }
}
void GameToolbarLayer::onTouchToolBtn(Widget::TouchEventType type,Ref* ref,cocos2d::ui::ImageView* img,float targetScale,float sourceScale,float time,const std::function<void()> &func,bool isPlaySound)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            if (isPlaySound)
                clickEffect();
            if (img)
                img->setScale(targetScale);
            break;
        case Widget::TouchEventType::ENDED:
            if (img)
                img->runAction(Sequence::createWithTwoActions(EaseBackOut::create(ScaleTo::create(time, sourceScale)), CallFunc::create(func)));
        default:
            if (img)
                img->runAction(EaseBackInOut::create(ScaleTo::create(time, sourceScale)));
            break;
    }
}
void GameToolbarLayer::initMessageFrame()
{
    Vector<MsgData*> msgList = MessageManager::getInstance()->getMsgList();

    for(Vector<MsgData*>::iterator iter = msgList.begin();iter!=msgList.end();iter++)
    {
        MsgData* msgData = (*iter);
        setMsgItem(msgData->getMsg(),msgData->getMsgColor());
    }
   
    std::string initMsg;
    if(RandomDungeon::getInstance()->getCurrentDungeonNode()->isBossDepth())
    {
         std::string dungenName = RandomDungeon::getInstance()->getCurrentDungeonNode()->m_strDungeonBossName.c_str();
        initMsg = StringUtils::format(UtilityHelper::getLocalStringForUi("GAME_MESSAGE_BOSS_NOT").c_str(),dungenName.c_str());
    }
    else
    {
        std::string dungenName = RandomDungeon::getInstance()->getCurrentDungeonNode()->m_strDungeonName.c_str();
        int floor =  int(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth);
        LanguageType lt= Application::getInstance()->getCurrentLanguage();
        switch (lt) {
            case LanguageType::CHINESE:
                initMsg = StringUtils::format(UtilityHelper::getLocalStringForUi("GAME_MESSAGE_NOT").c_str(),dungenName.c_str(),cocos2d::Value(floor).asString().c_str());
                break;
            default:
                initMsg = StringUtils::format(UtilityHelper::getLocalStringForUi("GAME_MESSAGE_NOT").c_str(),cocos2d::Value(floor).asString().c_str(),dungenName.c_str());
                break;
        }
    }
    runAction(Sequence::create(DelayTime::create(0.5f),CallFunc::create([initMsg](){
        PopupUILayerManager::getInstance()->showStatusImport(TIP_POSITIVE, initMsg);
    }), nullptr));
    sendMessage(initMsg);

}
void GameToolbarLayer::onClickBag(Ref* ref,Widget::TouchEventType type)
{

    onTouchToolBtn(type,ref,m_pGameBagBtnIcon,0.6f,0.7f,0.1f,[this,ref](){
    
        CCLOG("onClickRole");
        if (m_bIsDist) {
            return;
        }
        PopupUILayerManager::getInstance()->openPopup(ePopupRole);
//        PopupUILayerManager::getInstance()->openPopup(ePopupMagicShop);
        setDistTipsFrame();
        
        
    
    });

}
void GameToolbarLayer::onClickMap(Ref* ref,Widget::TouchEventType type)
{
    onTouchToolBtn(type,ref,m_pGameMapBtnIcon,0.6f,0.7f,0.1f,[this,ref](){
        
        CCLOG("onClickMap");
        if (m_bIsDist) {
            return;
        }
        if (VoxelExplorer::getInstance()->getCurrentLevel()->hasShowMap()) {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("UI_BTN_MAP_CLOSE");
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            
            VoxelExplorer::getInstance()->getCurrentLevel()->showMap(false);
        }else{
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("UI_BTN_MAP_OPEN");
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            
            VoxelExplorer::getInstance()->getCurrentLevel()->showMap(true);
            
        }
        setDistTipsFrame();
        
    },false);
    

}
void GameToolbarLayer::setDistTipsFrame()
{
    if (m_pGameDistTipsFrame&& m_bIsDist) {
        m_pGameDistTipsFrame->setVisible(false);
        if (m_pMsgFrame->isVisible())
        {
            m_pGameDistTipsFrame->setPosition(Vec2(m_pGameDistTipsFrame->getPositionX(), m_pGameDistTipsFrame->getPositionY()-m_pMsgFrame->getContentSize().height));
        }
    }
    m_bIsDist = false;
}
void GameToolbarLayer::onClickDistTipsFrame(cocos2d::Ref *ref)
{
//CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickSearchTipsFrame");
    setDistTipsFrame();
    
}

void GameToolbarLayer::onClickMsg(Ref* ref,Widget::TouchEventType type)
{
    onTouchToolBtn(type,ref,m_pGameMsgBtnIcon,0.9f,1.0f,0.1f,[this,ref](){
        
        CCLOG("onClickMsg");
        if (m_bIsDist) {
            return;
        }
        
        setDistTipsFrame();
        if (m_pMsgFrame->isVisible())
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("UI_BTN_CHAT_CLOSE");
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            m_pMsgFrame->setVisible(false);
        }else
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("UI_BTN_CHAT_OPEN");
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
            
            m_pMsgFrame->setVisible(true);
            m_pListMsgs->forceDoLayout();
            m_pListMsgs->scrollToBottom(0.5,false);
        }
        
    },false);

    
}
void GameToolbarLayer::onClickDist(Ref* ref,Widget::TouchEventType type)
{
    
    onTouchToolBtn(type,ref,m_pGameDistBtnIcon,0.9f,1.0f,0.1f,[this,ref](){
        
        CCLOG("onClickDist");
        if (m_bIsDist )
            return;
        m_bIsDist = true;
        if (m_pGameDistTipsFrame ) {
            if (m_pMsgFrame->isVisible()) {
                m_pGameDistTipsFrame->setPosition(Vec2(m_pGameDistTipsFrame->getPositionX(), m_pGameDistTipsFrame->getPositionY()+m_pMsgFrame->getContentSize().height));
            }
            m_pGameDistTipsFrame->setVisible(true);
        }
        
    });

}
void GameToolbarLayer::onClickPause(Ref* ref,Widget::TouchEventType type)
{
    onTouchToolBtn(type,ref,m_pGamePauseBtnIcon,0.9f,1.0f,0.1f,[this,ref](){
        
        
        CCLOG("onClickPause");
        PopupUILayerManager::getInstance()->openPopup(ePopupPause);
        
        
        //    PopupUILayerManager::getInstance()->showAchieveItem("achieve_icon_44.png", "Be thrifty at home and spend liberally while travelling", "Kill zombies, skeletons, ghost, ghosts, ghouls, Gargoyle each kind of one hundred.");
        //    AchieveItemLayer* layer = AchieveItemLayer::create();
        //    if (layer) {
        //        layer->showAchieveItem("achieve_icon_76.png", "听爷爷讲那过去的故事", "杀死亡灵怪物僵尸,骷髅,怨魂,幽灵,食尸鬼,石像鬼各100个");
        //    }
        //    layer->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
        //    m_pRootNode->addChild(layer);
        //    layer->setPosition(m_pRootNode->getContentSize()*0.5);
        //    PopupUILayerManager::getInstance()->openPopup(ePopupPause);
        //    InformationPopupUI* popupUi = static_cast<InformationPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupRandomMsg));
        //    if (popupUi) {
        //        popupUi->setInfoIcon("chr_man.png");
        //        popupUi->setInfoVector(NpcDataManager::getInstance()->getOldManRoomInfo());
        //        ValueVector aaa = cocos2d::FileUtils::getInstance()->getValueVectorFromFile("random_events_english.plist");
        //        std::string str = aaa.at(11).asValueMap()["EVENT_DESC"].asString();
        //        popupUi->setInfoDesc("The color of the dagger like shit, to smell the smell of your hand.");
        //    }
        //     AlertPopupUI* popupUi = static_cast<AlertPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupAlert));
        //    if (popupUi) {
        //        popupUi->setMessage("丰盛的萨芬爱死发生的方式爱死撒的发是飞洒飞");
        //        
        //    }
        
    });

    
}
void GameToolbarLayer::onClickSearch(Ref* ref,Widget::TouchEventType type)
{
    onTouchToolBtn(type,ref,m_pGameSearchBtnIcon,0.4f,0.5f,0.1f,[this,ref](){
        
        CCLOG("onClickSearch");
        if (m_bIsDist)
            return;
        VoxelExplorer::getInstance()->searchAndCheck();
       
        
    });

    
}

