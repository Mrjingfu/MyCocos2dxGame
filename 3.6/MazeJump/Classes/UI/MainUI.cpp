//
//  MainUI.cpp
//
//
//
//

#include "MainUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "StarPopUpUI.h"
#include "UIManager.h"
#include "AudioEngine.h"
#include "UtilityHelper.h"
#include "storage/local-storage/LocalStorage.h"
#include "GameCenterController.h"
#include "AudioEngine.h"
#include "NativeBridge.h"
USING_NS_CC;
using namespace experimental;

MainUI* MainUI::create()
{
    MainUI *pRet = new(std::nothrow) MainUI();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

MainUI::MainUI()
{
    m_nBgID = AudioEngine::INVALID_AUDIO_ID;

}
MainUI::~MainUI()
{
    AudioEngine::stop(m_nBgID);
}

bool MainUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    
    cocos2d::ui::ImageView* titleView = cocos2d::ui::ImageView::create(UtilityHelper::getLocalString("UI_TITLE_TEX"),cocos2d::ui::TextureResType::PLIST);
    titleView->setPosition(Vec2(size.width*0.5, size.height*0.77));
    titleView->setScale(scale);
    addChild(titleView);
    
    if(cocos2d::experimental::AudioEngine::isEnable())
    {
        soundBtn = cocos2d::ui::Button::create("btn_sounds_on.png","","",cocos2d::ui::TextureResType::PLIST);
        m_nBgID = AudioEngine::play2d("menubg.mp3", true, 0.5f);
    }
    else
    soundBtn = cocos2d::ui::Button::create("btn_sounds_off.png","","",cocos2d::ui::TextureResType::PLIST);
    soundBtn->setScale(scale);
    soundBtn->setPosition(Vec2(size.width*0.9, size.height*0.93));
    addChild(soundBtn);
    
    cocos2d::ui::Button* shopBtn = cocos2d::ui::Button::create("btn_shop_normal.png","btn_shop_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    shopBtn->setScale(scale);
    shopBtn->setPosition(Vec2(size.width*0.9,size.height*0.27));
    addChild(shopBtn);
    
    cocos2d::ui::Button* rankBtn = cocos2d::ui::Button::create("btn_rank_normal.png","btn_rank_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    rankBtn->setScale(scale);
    rankBtn->setPosition(Vec2(size.width*0.9,size.height*0.27-shopBtn->getContentSize().height*scale-20*scale));
    addChild(rankBtn);
    
   cocos2d::ui::Button* commonentBtn = cocos2d::ui::Button::create("btn_rate_normal.png","btn_rate_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    commonentBtn->setScale(scale);
    commonentBtn->setPosition(Vec2(size.width*0.9,size.height*0.27-rankBtn->getContentSize().height*scale*2-40*scale));
    addChild(commonentBtn);

    soundBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onSound, this));
    rankBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onRank, this));
    shopBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onShop, this));
    commonentBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onComment, this));

    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(MainUI::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
    return true;
}


void MainUI::onShop(cocos2d::Ref *ref)
{
    CCLOG("Shop");
    UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
    UIManager::getInstance()->showPopUp(true,BasePopUpUI::POPUP_HORIZONTAL);

}
void MainUI::onRank(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playBtnSound();
    CCLOG("rank");
    GameCenterController::getInstance()->openLeaderBoard();
}
void MainUI::onSound(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playBtnSound();
    if(cocos2d::experimental::AudioEngine::isEnable())
    {
        cocos2d::experimental::AudioEngine::setEnable(false);
        soundBtn->loadTextureNormal("btn_sounds_off.png",cocos2d::ui::TextureResType::PLIST);
    }else
    {
        cocos2d::experimental::AudioEngine::setEnable(true);
        soundBtn->loadTextureNormal("btn_sounds_on.png",cocos2d::ui::TextureResType::PLIST);
        if(m_nBgID == AudioEngine::INVALID_AUDIO_ID)
            m_nBgID = AudioEngine::play2d("menubg.mp3", true, 0.5f);
    }
}
void MainUI::onComment(cocos2d::Ref *ref)
{
    UIManager::getInstance()->playBtnSound();
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    NativeBridge::getInstance()->openItunesURL();
#endif
}
void MainUI::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
        CCLOG("MainUI onKeyPressed");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        NativeBridge::getInstance()->exitGame();
#endif
    }
}