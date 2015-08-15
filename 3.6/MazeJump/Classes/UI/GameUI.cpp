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
    conut = 3;
    isRecover = false;
}
GameUI::~GameUI()
{
}
void GameUI::onEnter()
{
    Layer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RUNNER_RECOVER_PAUSE, std::bind(&GameUI::onRecoverPause, this, std::placeholders::_1));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RUNNER_PAUSE_RESUME, std::bind(&GameUI::onEventSetResume, this, std::placeholders::_1));

}
void GameUI::onExit()
{
    Layer::onExit();

    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_RUNNER_RECOVER_PAUSE);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_RUNNER_PAUSE_RESUME);
   
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
    
    
    m_maskLayerBg = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 150));
    m_maskLayerBg->setContentSize(size);
    addChild(m_maskLayerBg);
    m_maskLayerBg->setVisible(false);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan =  CC_CALLBACK_2(GameUI::onTouchBegan, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,m_maskLayerBg);
    
    resmueLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"3");
    resmueLabel->setScale(scale*2);
    resmueLabel->setPosition(Vec2(size.width*0.5, size.height*0.5));
    resmueLabel->setVisible(false);
    addChild(resmueLabel);
    return true;
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
    isRecover = true;
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_PAUSE);
    UIManager::getInstance()->showPopUp(true,BasePopUpUI::POPUP_HORIZONTAL,CC_CALLBACK_0(GameUI::setPause, this));

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
    resmueLabel->setVisible(true);
    conut=3;
    this->schedule(schedule_selector(GameUI::onResumeAn), 1.0f);
    
}
void GameUI::onResumeAn(float dt)
{
    resmueLabel->setString(Value(--conut).asString());
    CCLOG("count:%d",conut);
    if (conut<=0) {

            setResume();
            m_maskLayerBg->setVisible(false);
            resmueLabel->setVisible(false);
            resmueLabel->setString("3");
            isRecover = false;
            unschedule(schedule_selector(GameUI::onResumeAn));
        
    }
}
