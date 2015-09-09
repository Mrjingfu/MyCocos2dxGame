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
#include "MenuScene.h"
#include "GameScene.h"
#include "ShopPopUpUI.h"
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
    modeLayer = nullptr;
    mazeBtn= nullptr;
    rainbowBtn= nullptr;
    soundBtn= nullptr;
    isTouchRoleMenu = false;
}
MainUI::~MainUI()
{
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
        soundBtn = cocos2d::ui::Button::create("btn_sounds_on.png","","",cocos2d::ui::TextureResType::PLIST);
    else
        soundBtn = cocos2d::ui::Button::create("btn_sounds_off.png","","",cocos2d::ui::TextureResType::PLIST);
    if(soundBtn)
    {
        soundBtn->setScale(scale);
        soundBtn->setPosition(Vec2(size.width*0.9, size.height*0.93));
        addChild(soundBtn);
    }
    
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
    
    modeLayer = Layer::create();
    addChild(modeLayer);
    
    mazeBtn = cocos2d::ui::Button::create(UtilityHelper::getLocalString("UI_MENU_MAZE_BTN"),"","",cocos2d::ui::TextureResType::PLIST);
    mazeBtn->setPosition(Vec2(size.width*0.63, size.height*0.38));
    mazeBtn->setScale(scale);
    mazeBtn->setCascadeOpacityEnabled(true);
    modeLayer->addChild(mazeBtn);
    
    rainbowBtn = cocos2d::ui::Button::create(UtilityHelper::getLocalString("UI_MENU_RAINBOW_BTN"),"","",cocos2d::ui::TextureResType::PLIST);
    rainbowBtn->setPosition(Vec2(size.width*0.63, size.height*0.38+mazeBtn->getContentSize().height*scale+20*scale));
    rainbowBtn->setScale(scale);
    rainbowBtn->setCascadeOpacityEnabled(true);
    modeLayer->addChild(rainbowBtn);
    
    modeLayer->setCascadeOpacityEnabled(true);
    modeLayer->setOpacity(0);
    
    mazeBtn->setTouchEnabled(false);
    rainbowBtn->setTouchEnabled(false);
    mazeBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onMazeGame, this));
    rainbowBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onPlayRainbowGame, this));
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
        MenuScene* menuScene = static_cast<MenuScene*>(UIManager::getInstance()->getParent());
        if(menuScene)
            menuScene->playBackgroundMusic();
    }
}
void MainUI::onEnter()
{
    Layer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MAIN_SHOW_MODE_BTN, std::bind(&MainUI::onShowModeBtn, this, std::placeholders::_1));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MENU_HIDE_MODE_BTN, std::bind(&MainUI::onHideModeBtn, this, std::placeholders::_1));
}
void MainUI::onExit()
{
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MAIN_SHOW_MODE_BTN);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MENU_HIDE_MODE_BTN);
    Layer::onExit();
}
void MainUI::onShowModeBtn(cocos2d::EventCustom *sender)
{
    if (isTouchRoleMenu) {
        return;
    }
    if (modeLayer) {
        EaseExponentialOut* fadeIn = EaseExponentialOut::create(FadeIn::create(1.0f));
        modeLayer->runAction(Sequence::create(fadeIn,CallFunc::create(CC_CALLBACK_0(MainUI::fadeinEnd, this)), NULL));
    }
    
}
void MainUI::onHideModeBtn(cocos2d::EventCustom *sender)
{
    isTouchRoleMenu = true;
    if (mazeBtn) {
        mazeBtn->setTouchEnabled(false);
    }
    if (rainbowBtn) {
        rainbowBtn->setTouchEnabled(false);
    }
    if (modeLayer) {
        EaseExponentialOut* fadeOut = EaseExponentialOut::create(FadeOut::create(1.0f));
        modeLayer->runAction(Sequence::create(fadeOut,CallFunc::create(CC_CALLBACK_0(MainUI::fadeoutEnd, this)), NULL));
    }

}
void MainUI::fadeoutEnd()
{
    
    isTouchRoleMenu =false;
}
void MainUI::fadeinEnd()
{
    if (mazeBtn) {
        mazeBtn->setTouchEnabled(true);
    }
    if (rainbowBtn) {
        rainbowBtn->setTouchEnabled(true);
    }
}
void MainUI::onPlayRainbowGame(cocos2d::Ref *ref)
{
        UIManager::getInstance()->playBtnSound();
        int maxLevel = Value(localStorageGetItem(USER_MAX_LEVEL)).asInt();
        if (maxLevel > 0) {
            UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_START);
            UIManager::getInstance()->showPopUp();
            
        }else
        {
            MenuScene* menuScene = static_cast<MenuScene*>(UIManager::getInstance()->getParent());
            if(menuScene)
                menuScene->fadeOutMainScene();
        }
}
void MainUI::onMazeGame(cocos2d::Ref *ref)
{
    
    UIManager::getInstance()->playBtnSound();
    MenuScene* menuScene = static_cast<MenuScene*>(UIManager::getInstance()->getParent());
    if (menuScene)
    {
        menuScene->setIsMaze(true);
        menuScene->fadeOutGameScene();
    }
    if (mazeBtn) {
        mazeBtn->setTouchEnabled(false);
    }
    if (rainbowBtn) {
        rainbowBtn->setTouchEnabled(false);
    }
}

void MainUI::onComment(cocos2d::Ref *ref)
{
    UIManager::getInstance()->playBtnSound();
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    NativeBridge::getInstance()->openItunesURL();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    NativeBridge::getInstance()->openGooglePlay();
#endif
}
void MainUI::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
        CCLOG("MainUI onKeyPressed");
        StarPopUpUI* startPopUi = static_cast<StarPopUpUI*>(UIManager::getInstance()->getPopUpUI(BasePopUpUI::POPUP_START));
        ShopPopUpUI* shopPopUi = static_cast<ShopPopUpUI*>(UIManager::getInstance()->getPopUpUI(BasePopUpUI::POPUP_SHOP));
        if (startPopUi || shopPopUi)
            return;
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        NativeBridge::getInstance()->exitGame();
#endif
    }
}