//
//  GameUI.cpp
//
//
//
//

#include "GameUI.h"
#include "SkillButton.h"
#include "MainScene.h"
#include "GameConst.h"
#include "UIManager.h"
#include "UtilityHelper.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

GameUI* GameUI::create()
{
    GameUI *pRet = new(std::nothrow) GameUI();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

GameUI::GameUI()
{
    m_conut = 3;
    m_maskLayerBg = nullptr;
    m_countDonwImg = nullptr;
    pauseImg = nullptr;
    helpLayer = nullptr;
    isRecover = false;
    isShwoHelp= false;
    isDead = false;
}
GameUI::~GameUI()
{
}
void GameUI::onEnter()
{
    Layer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RUNNER_RECOVER_PAUSE, std::bind(&GameUI::onRecoverPause, this, std::placeholders::_1));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RUNNER_PAUSE_RESUME, std::bind(&GameUI::onEventSetResume, this, std::placeholders::_1));
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RUNNER_LOSE, std::bind(&GameUI::onRunnerLose, this, std::placeholders::_1));
        Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_GAME_PAUSE, std::bind(&GameUI::onPauseEvent, this, std::placeholders::_1));
}
void GameUI::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_RUNNER_LOSE);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_RUNNER_RECOVER_PAUSE);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_RUNNER_PAUSE_RESUME);
   Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_GAME_PAUSE);
}

bool GameUI::init()
{
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    
    
    ui::Button* goldBuyBtn = ui::Button::create("btn_plus_normal.png","btn_plus_pressed.png");
    goldBuyBtn->setPosition(Vec2(25*scale, size.height*0.95));
    goldBuyBtn->setScale(scale);
    addChild(goldBuyBtn);
    
    
    ui::Button* heartBuyBtn = ui::Button::create("btn_plus_normal.png","btn_plus_pressed.png");
    heartBuyBtn->setPosition(Vec2(25*scale, size.height*0.95-50*scale));
    heartBuyBtn->setScale(scale);
    addChild(heartBuyBtn);
    
        
    pauseImg = ui::Button::create("btn_pause_normal.png","btn_pause_pressed.png");
    pauseImg->setPosition(Vec2(size.width*0.9, size.height*0.93));
    pauseImg->setScale(scale);
    addChild(pauseImg);
    pauseImg->addClickEventListener(CC_CALLBACK_1(GameUI::onPause, this));
 
    
    SkillButton* skillBtn = SkillButton::create("btn_skill_normal.png", "btn_skill_mask.png");
    if(!skillBtn)
        return false;
    skillBtn->setScale(scale);
    skillBtn->setPosition(Vec2(size.width * 0.1f, size.height * 0.05f));
    addChild(skillBtn);
    
    ui::Button* helpBtn = ui::Button::create("question.png");
    helpBtn->setPosition(Vec2(size.width*0.93, size.height*0.03));
    helpBtn->setScale(scale);
    addChild(helpBtn);
    
    m_maskLayerBg = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 150));
    m_maskLayerBg->setContentSize(size);
    addChild(m_maskLayerBg);
    m_maskLayerBg->setVisible(false);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan =  CC_CALLBACK_2(GameUI::onTouchBegan, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,m_maskLayerBg);
    
    m_countDonwImg = cocos2d::ui::ImageView::create(StringUtils::format("ui_count_down_%d.png",m_conut));
    m_countDonwImg->setScale(scale);
    m_countDonwImg->setPosition(Vec2(size.width*0.5, size.height*0.5));
    m_countDonwImg->setVisible(false);
    addChild(m_countDonwImg);
    
 
    
    helpLayer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 150));
    helpLayer->setContentSize(size);
    addChild(helpLayer);
    
    auto helplistener = EventListenerTouchOneByOne::create();
    helplistener->setSwallowTouches(true);
    helplistener->onTouchBegan =  [this](Touch * ,Event *)
    {
        if (isShwoHelp) {
            UIManager::getInstance()->playSound();
            isShwoHelp = false;
            helpLayer->setVisible(false);
            return true;
        }else{
            return false;
        }
        
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(helplistener,helpLayer);
    

    
    cocos2d::ui::ImageView* handleTipsImg = ui::ImageView::create(UtilityHelper::getLocalString("UI_GAME_HANDLE_TIPS"));
    handleTipsImg->setPosition(Vec2(size.width*0.5, size.height*0.5));
    handleTipsImg->setScale(scale);
    helpLayer->addChild(handleTipsImg);
    
    cocos2d::ui::ImageView* pauseTipsImg = ui::ImageView::create(UtilityHelper::getLocalString("UI_GAME_PAUSE_TIPS"));
    pauseTipsImg->setPosition(Vec2(size.width*0.8, size.height*0.8));
    pauseTipsImg->setScale(scale);
    helpLayer->addChild(pauseTipsImg);
    
    cocos2d::ui::ImageView* infoTipsImg = ui::ImageView::create(UtilityHelper::getLocalString("UI_GAMEINFO_TIPS"));
    infoTipsImg->setPosition(Vec2(size.width*0.18, size.height*0.8));
    infoTipsImg->setScale(scale);
    helpLayer->addChild(infoTipsImg);
    
    cocos2d::ui::ImageView* modeTipsImg = ui::ImageView::create(UtilityHelper::getLocalString("UI_GAME_MODE_TIPS"));
    modeTipsImg->setPosition(Vec2(size.width*0.23, size.height*0.15));
    modeTipsImg->setScale(scale);
    helpLayer->addChild(modeTipsImg);
    
    cocos2d::ui::ImageView* helpTipsImg = ui::ImageView::create(UtilityHelper::getLocalString("UI_HELP_TIPS"));
    helpTipsImg->setPosition(Vec2(size.width*0.85, size.height*0.15));
    helpTipsImg->setScale(scale);
    helpLayer->addChild(helpTipsImg);
    
    helpBtn->addClickEventListener(CC_CALLBACK_1(GameUI::onHelp, this));
    
    
    int maxLevel = Value(localStorageGetItem(USER_MAX_LEVEL)).asInt();
    if (maxLevel<=0) {
        helpLayer->setVisible(true);
        isShwoHelp= true;
    }else
    {
        helpLayer ->setVisible(false);
    }
    

    return true;
}
void GameUI::onHelp(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playSound();
    if (!isShwoHelp) {
        helpLayer->setVisible(true);
        isShwoHelp = true;
    }
    
}
bool GameUI::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (isRecover) {
        
        return true;
    }else{
        return false;
    }
}
void GameUI::onPause(cocos2d::Ref *ref)
{
    
    if (isDead)
        return;
    showPause();
}

void GameUI::onPauseEvent(cocos2d::EventCustom *sender)
{
    showPause();
}

void GameUI::showPause()
{
    isRecover = true;
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_PAUSE);
    UIManager::getInstance()->showPopUp(true,BasePopUpUI::POPUP_HORIZONTAL,CC_CALLBACK_0(GameUI::setPause, this));
    UIManager::getInstance()->playSound();
}

void GameUI::setPause()
{
    std::set<void*> _m_pBeforeTargetSets = Director::getInstance()->getScheduler()->pauseAllTargets();
    
    for(std::set<void*>::iterator it=_m_pBeforeTargetSets.begin();it!=_m_pBeforeTargetSets.end();it++)
    {
        Director::getInstance()->getScheduler()->pauseTarget(*it);
    }
}

void GameUI::setResume()
{
    std::set<void*> _m_pBeforeTargetSets = Director::getInstance()->getScheduler()->pauseAllTargets();
    
    for(std::set<void*>::iterator it=_m_pBeforeTargetSets.begin();it!=_m_pBeforeTargetSets.end();it++)
    {
        Director::getInstance()->getScheduler()->resumeTarget(*it);
    }
}

void GameUI::onEventSetResume(cocos2d::EventCustom *sender)
{
    setResume();
}
void GameUI::onRecoverPause(cocos2d::EventCustom *sender)
{
    CCLOG("onRecoverPause");
    m_maskLayerBg->setVisible(true);
    m_countDonwImg->setVisible(true);
    m_conut=3;
    this->schedule(schedule_selector(GameUI::onResumeAn), 1.0f);
    
}
void GameUI::onResumeAn(float dt)
{
    m_countDonwImg->loadTexture(StringUtils::format("ui_count_down_%d.png",--m_conut));
    CCLOG("count:%d",m_conut);
    if (m_conut<=0) {

            setResume();
            m_maskLayerBg->setVisible(false);
            m_countDonwImg->setVisible(false);
            m_countDonwImg->loadTexture(StringUtils::format("ui_count_down_%d.png",3));
            isRecover = false;
            unschedule(schedule_selector(GameUI::onResumeAn));
        
    }
}
void GameUI::onRunnerLose(cocos2d::EventCustom* sender)
{
    isDead = true;
    runAction(Sequence::createWithTwoActions(DelayTime::create(0.5), CCCallFunc::create(CC_CALLBACK_0(GameUI::onDelayTimeRunnerLose, this))));
}
void GameUI::onDelayTimeRunnerLose()
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_RUNNER_LOSE_CHANGE_VIEW);
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_DEATH);
    UIManager::getInstance()->showPopUp(true,BasePopUpUI::POPUP_HORIZONTAL,CC_CALLBACK_0(GameUI::onShowLosePopUpEnd, this));
}
void GameUI::onShowLosePopUpEnd()
{
    isDead = false;
}
