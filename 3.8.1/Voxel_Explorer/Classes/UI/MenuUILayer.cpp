//
//  MenuUILayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/20.
//
//

#include "MenuUILayer.h"
#include "UtilityHelper.h"
#include "GameConfig.h"
#include "GameScene.h"
#include "PopupUILayerManager.h"
#include "AchievePopupUI.h"
#include "ArchiveManager.h"
#include "ArchiveLayer.hpp"
#include "LoadingLayer.hpp"
#include "LevelResourceManager.h"
#include "SimpleAudioEngine.h"
#include "NativeBridge.h"
#include "AlertPopupUI.hpp"
#include "GameCenterController.h"
#include "VoxelExplorer.h"
#include "AchievementManager.h"
USING_NS_CC;

MenuUILayer::MenuUILayer()
{
    m_pAchievePopupUI = nullptr;
    m_pArchiveStart = nullptr;
    m_pArchiveRestart= nullptr;
    m_pMuiscImg = nullptr;
    m_pMenutitle = nullptr;
}
MenuUILayer::~MenuUILayer()
{
    
}
bool MenuUILayer::addEvents()
{
    
    
    cocos2d::ui::Button* btn_achieve = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"btn_achieve"));
    if (!btn_achieve)
        return false;

    cocos2d::ui::Button* btn_rank = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"btn_rank"));
    if (!btn_rank)
        return false;
    cocos2d::ui::Button* btn_rate = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"btn_rate"));
    if (!btn_rate)
        return false;

    
    m_pEyes = dynamic_cast<cocos2d::Sprite*>(UtilityHelper::seekNodeByName(m_pRootNode,"menu_eyes"));
    if (!m_pEyes)
        return false;
    
     m_pMenutitle = dynamic_cast<cocos2d::ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode,"menu_title"));
    if (!m_pMenutitle)
        return false;
    
    m_pArchiveStart = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"menu_archive_item_start"));
    if (!m_pArchiveStart)
        return false;

    m_pArchiveRestart = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"menu_archive_item_restart"));
    if (!m_pArchiveRestart)
        return false;
    
   cocos2d::ui::Button*  m_pLangugaeBtn = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"menu_langugae_btn"));
    if (!m_pLangugaeBtn)
        return false;
    m_pLangugaeBtn->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickLangugae, this));

    m_pMuiscImg = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "menu_music_img"));
    if (!m_pMuiscImg)
        return false;
    m_pMuiscImg->setTouchEnabled(true);
    m_pWhiteLayer = LayerColor::create(Color4B::BLACK);
    if(!m_pWhiteLayer)
        return false;
    m_pRootNode->addChild(m_pWhiteLayer);
    EaseExponentialOut* fadeOut = EaseExponentialOut::create(FadeOut::create(1.0f));
    m_pWhiteLayer->runAction(fadeOut);
    
    m_pArchiveStart->setTitleFontName(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pArchiveStart->getTitleRenderer()->setScale(0.8);

    m_pArchiveRestart->setTitleFontName(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pArchiveRestart->getTitleRenderer()->setScale(0.8);
    
    
    m_pMenutitle->loadTexture(UtilityHelper::getLocalStringForUi("SPLASH_RES"));
    
    m_pAchievePopupUI = AchievePopupUI::create();
    m_pAchievePopupUI->openPopup();
    m_pAchievePopupUI->setVisible(false);
    m_pRootNode->addChild(m_pAchievePopupUI,eZOrderPopupUILayer);
    m_pAchievePopupUI->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    
    btn_achieve->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickAchieve, this));
    m_pMuiscImg->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickMuisc, this));
#if (CHINA_CHANEL==0)
    btn_rank->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickRank, this));
#endif
    btn_rate->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickRate, this));
    
    m_pArchiveStart->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickStart, this));
    m_pArchiveRestart->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClikcRestart, this));
    
    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(MenuUILayer::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

    return true;
}
void MenuUILayer::refreshUIView()
{
    if (ArchiveManager::getInstance()->isExistArchive())
    {
        m_pArchiveStart->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_CONTINUE_GAME"));
        
        m_pArchiveRestart->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_RESTART_GAME"));
    }else
    {
        m_pArchiveStart->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.5,m_pRootNode->getContentSize().height*0.23));
        m_pArchiveStart->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_NEW_GAME"));
        m_pArchiveRestart->setVisible(false);
    }

    if (CocosDenshion::SimpleAudioEngine::getInstance()->getPauseSound())
    {
        m_pMuiscImg->loadTexture("ui_btn_sound_off.png",TextureResType::PLIST);
    }else
    {
        m_pMuiscImg->loadTexture("ui_btn_sound_on.png",TextureResType::PLIST);
    }
    m_pMuiscImg->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
}

void MenuUILayer::onClickAchieve(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onTouchAchieve");
    if (m_pAchievePopupUI)
    {
        if (m_pAchievePopupUI->isVisible())
        {
            m_pAchievePopupUI->setVisible(false);
        }
        else
        {
            m_pAchievePopupUI->setVisible(true);
            m_pAchievePopupUI->refreshUIView();
        }
        
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    GameCenterController::getInstance()->openAchievementBoard();
#endif
}
void MenuUILayer::onEventGameChangeLanguage(cocos2d::EventCustom *sender)
{

    
}
void MenuUILayer::onEnter()
{
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_GAME_CHANGE_LANGUAGE, CC_CALLBACK_1(MenuUILayer::onEventGameChangeLanguage, this));
    
    refreshUIView();
    WrapperUILayer::onEnter();
}
void MenuUILayer::onExit()
{
    WrapperUILayer::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_GAME_CHANGE_LANGUAGE);
}
void MenuUILayer::onClickRank(cocos2d::Ref *ref)
{
    
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onTouchRank");
//    PopupUILayerManager::getInstance()->openPopup(ePopupInfo);
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    GameCenterController::getInstance()->openLeaderBoard();
#endif
    
}
void MenuUILayer::onClikcRestart(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClikcRestart");
    AlertPopupUI* popupt = static_cast<AlertPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupAlert));
    if (popupt) {
        popupt->setPositiveListerner([this](Ref* ref){
            if (m_pArchiveStart && m_pArchiveRestart)
            {
                m_pArchiveStart->setVisible(false);
                m_pArchiveRestart->setVisible(false);
                
                if(!ArchiveManager::getInstance()->restartArchive())
                    CCLOGERROR("Load Game failed!");
                
                VoxelExplorer::getInstance()->setHasDownStairs();
                
                startGameAction();
                
            }
        });
        popupt->setNegativeListerner([](Ref* ref){});
        popupt->setMessage(UtilityHelper::getLocalStringForUi("ARCHIVE_RESTART_TIPS_DESC"));
    }

    


}
void MenuUILayer::onClickStart(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onTouchStart");
    if (m_pArchiveStart && m_pArchiveRestart) {
        
        m_pArchiveStart->setVisible(false);
        m_pArchiveStart->setTouchEnabled(false);
        m_pArchiveRestart->setVisible(false);
        m_pArchiveRestart->setTouchEnabled(false);
        if(!ArchiveManager::getInstance()->loadGame())
            CCLOGERROR("Load Game failed!");
 
        startGameAction();
        
    }
    
    
}
void MenuUILayer::startGameAction()
{
    std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("START_GAME_EYES");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    EaseSineOut* fadein = EaseSineOut::create(FadeIn::create(0.5));
    EaseSineOut* fadeout = EaseSineOut::create(FadeOut::create(0.5));
    CallFunc* func = CallFunc::create([this](){
        
        switchToGameScene();
    });
    
    m_pEyes->runAction(Sequence::create(fadein, fadeout,func,nullptr));

}
void MenuUILayer::switchToGameScene()
{
    if(m_pWhiteLayer)
    {
        EaseExponentialOut* fadeIn = EaseExponentialOut::create(FadeIn::create(1.0f));
        CallFunc* callFunc = CallFunc::create([](){
            
            auto scene = GameScene::createScene();
            Director::getInstance()->replaceScene(scene);
        });
        Sequence* sequence = Sequence::create(fadeIn, callFunc, NULL);
        m_pWhiteLayer->runAction(sequence);
    }
}
void MenuUILayer::onClickMuisc(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    if (!m_pMuiscImg)
        return ;
    if (CocosDenshion::SimpleAudioEngine::getInstance()->getPauseSound())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->setPauseSound(false);
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
        refreshUIView();
        
    }else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->setPauseSound(true);
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
        
        refreshUIView();
    }
    
    
}
void MenuUILayer::onClickRate(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onTouchRate");
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    NativeBridge::getInstance()->openGooglePlay();
#elif  CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    NativeBridge::getInstance()->openItunesURL();
#endif
    
}
void MenuUILayer::onClickLangugae(Ref* ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    PopupUILayerManager::getInstance()->openPopup(ePopupLangugae);
}
void MenuUILayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
   if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
            if (m_pAchievePopupUI &&m_pAchievePopupUI->isVisible())
            {
                m_pAchievePopupUI->setVisible(false);
            }
            else
            {
                PopupUILayer* popupLayer = PopupUILayerManager::getInstance()->getCurrentPopUpLayer();
                if (popupLayer )
                {
                    popupLayer->onKeyBackClick();
                }else
                {
                    CCLOG("EXIT GAME");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    NativeBridge::getInstance()->exitGame();
#endif
                }
            }
    }

}