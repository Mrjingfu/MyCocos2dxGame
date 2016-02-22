//
//  DeadPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "DeadPopupUI.h"
#include "UtilityHelper.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "ArchiveManager.h"
#include "VoxelExplorer.h"
#include "GameUILayer.h"
#include "PopupUILayerManager.h"
#include "NativeBridge.h"
#include "RandomDungeon.hpp"

USING_NS_CC;

DeadPopupUI::DeadPopupUI()
{
    m_pBtnDead  = nullptr;
    m_nIsPause = false;
    m_nIsBlankClose = false;
    m_pAdaIcon = nullptr;
    m_pAdaDesc = nullptr;
    m_pContinueNum = nullptr;
    m_nCountDownNum = 6;
    m_nReviveTouchNum = 4;
}
DeadPopupUI::~DeadPopupUI()
{
    
}

bool DeadPopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    
    return load("deadLayer.csb",false);
    
}
bool DeadPopupUI::addEvents()
{

    m_pAdaIcon = dynamic_cast<cocos2d::ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode,"dead_ada_icon"));
    if (!m_pAdaIcon)
        return false;
    m_pAdaDesc = dynamic_cast<cocos2d::ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode,"dead_ada_desc"));
    if(!m_pAdaDesc)
        return false;
    m_pContinueNum = dynamic_cast<cocos2d::ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode,"dead_continue_text"));
    if(!m_pContinueNum)
        return false;
    
    m_pBtnDead = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"dead_btn_restart"));
    if (!m_pBtnDead)
        return false;
    
    m_pDepthReviveText = dynamic_cast<cocos2d::ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode,"dead_boos_reveive_text"));
    if (!m_pDepthReviveText)
        return false;
    
    ui::ImageView* title = dynamic_cast<cocos2d::ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode,"dead_title"));
    if (!title)
        return false;
    title->loadTexture(UtilityHelper::getLocalStringForUi("DEAD_RES"),TextureResType::PLIST);
    m_pDepthReviveText->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pDepthReviveText->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("DEAD_BOOS_DEPTH_REVIVE_TXT").c_str(),VoxelExplorer::getInstance()->getReviveCount()));
   
    
    
    m_pAdaDesc->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pAdaDesc->setString(UtilityHelper::getLocalStringForUi("BTN_TEXT_ADA_REVIVE"));
    m_pContinueNum->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pContinueNum->setString(Value(m_nCountDownNum).asString());
    m_pContinueNum->runAction(RepeatForever::create(Sequence::create(EaseBackIn::create(ScaleTo::create(0.3, 0.8)),EaseBackOut::create(ScaleTo::create(0.3, 1)), nil)));
    m_pBtnDead->addClickEventListener(CC_CALLBACK_1(DeadPopupUI::onClickAda, this));
     m_pDepthReviveText->setVisible(false);
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if (!NativeBridge::getInstance()->isNetworkAvailable() ) {
        
        updateRestartUi();
        return true;
    }
    if(!NativeBridge::getInstance()->isInterstitialAdsReady())
    {
        updateRestartUi();
        NativeBridge::getInstance()->playInterstitialAds();
        return true;
    }

#endif

    if (VoxelExplorer::getInstance()->getReviveCount() >0) {
        m_pDepthReviveText->setVisible(true);
        this->schedule(schedule_selector(DeadPopupUI::CountDown), 1.0f);
    }else
    {
         m_pDepthReviveText->setVisible(false);
         updateRestartUi();
    }

    return true;
}
void DeadPopupUI::CountDown(float dt)
{
    if (m_nCountDownNum>0) {
        --m_nCountDownNum;
        m_pContinueNum->setString(Value(m_nCountDownNum).asString());
    }
    if(m_nCountDownNum<=0)
    {
        updateRestartUi();
    }
}
void DeadPopupUI::updateRestartUi()
{
    m_pAdaIcon->setVisible(false);
    m_pContinueNum->setVisible(false);
    m_pDepthReviveText->setVisible(false);
    this->unschedule(schedule_selector(DeadPopupUI::CountDown));
    m_pAdaDesc->setString(UtilityHelper::getLocalStringForUi("BTN_TEXT_RESTART_GAME"));
    m_pAdaDesc->setCameraMask((unsigned short)m_nCamerFlag);
    m_pAdaDesc->setPosition(m_pBtnDead->getContentSize()*0.5);
    m_pBtnDead->addClickEventListener(CC_CALLBACK_1(DeadPopupUI::onClickRestart, this));

}
void DeadPopupUI::updateReviveUi()
{
    m_pAdaIcon->setVisible(false);
    m_pContinueNum->setVisible(false);
    m_pDepthReviveText->setVisible(false);
    m_pAdaDesc->setPosition(m_pBtnDead->getContentSize()*0.5);
    m_pBtnDead->addClickEventListener(CC_CALLBACK_1(DeadPopupUI::onClickRevive, this));

}
void DeadPopupUI::onClickAda(cocos2d::Ref* ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    VoxelExplorer::getInstance()->declineReviveCount();
    this->unschedule(schedule_selector(DeadPopupUI::CountDown));
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#elif  CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    NativeBridge::getInstance()->playInterstitialAds();
#endif
    updateReviveUi();
    if(m_pBtnDead)
    {
        m_pBtnDead->setTouchEnabled(false);
        m_pBtnDead->setEnabled(false);
    }
     m_pAdaDesc->setString(Value(m_nReviveTouchNum).asString());
    this->schedule(schedule_selector(DeadPopupUI::reveiveCountDown), 1.0f);
    
}
void DeadPopupUI::reveiveCountDown(float dt)
{
    if (m_nReviveTouchNum>0) {
        --m_nReviveTouchNum;
        m_pAdaDesc->setString(Value(m_nReviveTouchNum).asString());
    }
    if(m_nReviveTouchNum<=0)
    {
        if(m_pBtnDead)
        {
            this->unschedule(schedule_selector(DeadPopupUI::reveiveCountDown));
            m_pBtnDead->setTouchEnabled(true);
            m_pBtnDead->setEnabled(true);
            m_pAdaDesc->setString(UtilityHelper::getLocalStringForUi("BTN_TEXT_REVIVE"));
            
        }
    }
}
void DeadPopupUI::onClickRevive(cocos2d::Ref *ref)
{
    PopupUILayerManager::getInstance()->closeCurrentPopup();
    VoxelExplorer::getInstance()->respawnPlayer();
}
void DeadPopupUI::onClickRestart(cocos2d::Ref *ref)
{

    ArchiveManager::getInstance()->loadGame();
    cocos2d::Scene* scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
    
}
