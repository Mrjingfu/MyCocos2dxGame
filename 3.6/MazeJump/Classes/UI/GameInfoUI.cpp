//
//  GameUI.cpp
//
//
//
//

#include "GameInfoUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "UIManager.h"
#include "GameConst.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

GameInfoUI* GameInfoUI::create()
{
    GameInfoUI *pRet = new(std::nothrow) GameInfoUI();
    if (pRet&& pRet->init() )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

GameInfoUI::GameInfoUI()
{
     goldTv             = nullptr;
     heartTv            = nullptr;
     m_maxLevelTv       = nullptr;
     m_CurrentLevelTv   = nullptr;
     maxLayer           = nullptr;
     currentLayer       = nullptr;
}
GameInfoUI::~GameInfoUI()
{
}

bool GameInfoUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    
    goldAni = cocos2d::ui::ImageView::create("ui_gold.png",cocos2d::ui::TextureResType::PLIST);
    goldAni->setPosition(Vec2(70*scale, size.height*0.95));
    goldAni->setScale(scale);
    addChild(goldAni);
    
    goldTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()).asString(),TextHAlignment::RIGHT);
    goldTv->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    goldTv->setPosition(Vec2(size.width*0.15,size.height*0.95 +5*scale ));
    goldTv->setScale(scale);
    addChild(goldTv);
    
    
    heartAni = cocos2d::ui::ImageView::create("ui_heart.png",cocos2d::ui::TextureResType::PLIST);
    heartAni->setPosition(Vec2(70*scale, size.height*0.95-goldAni->getContentSize().height*scale - 5*scale));
    heartAni->setScale(scale);
    addChild(heartAni);
    
    heartTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(Value(localStorageGetItem(USER_HEART_NUM)).asInt()).asString(),TextHAlignment::RIGHT);
    heartTv->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    heartTv->setPosition(Vec2(size.width*0.15, size.height*0.95-goldAni->getContentSize().height*scale - 3*scale));
    heartTv->setScale(scale);
    addChild(heartTv);
    
    
    maxLayer = Layer::create();
    addChild(maxLayer);
    
    currentLayer = Layer::create();
    currentLayer->setPosition(Vec2(0, 50*scale));
    addChild(currentLayer);
    
    cocos2d::ui::ImageView* bestImg = cocos2d::ui::ImageView::create(UtilityHelper::getLocalString("UI_GAME_BEST_TV"),cocos2d::ui::TextureResType::PLIST);
    bestImg->setAnchorPoint(Vec2(1, 0.5));
    bestImg->setPosition(Vec2(size.width*0.62,size.height*0.95));
    bestImg->setScale(scale);
    maxLayer->addChild(bestImg);
    
    
     m_maxLevelTv =Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(Value(localStorageGetItem(USER_MAX_LEVEL)).asInt()).asString(),TextHAlignment::RIGHT);
    m_maxLevelTv->setPosition(Vec2(size.width*0.72, size.height*0.948));
    m_maxLevelTv->setScale(scale);
    m_maxLevelTv->setAnchorPoint(Vec2(1, 0.5));
    maxLayer->addChild(m_maxLevelTv);
    
    
    cocos2d:: ui::ImageView* currentImg = cocos2d::ui::ImageView::create(UtilityHelper::getLocalString("UI_GAME_CURRENT_TV"),cocos2d::ui::TextureResType::PLIST);
    currentImg->setPosition(Vec2(size.width*0.5,size.height*0.9));
    currentImg->setScale(scale);
    currentLayer->addChild(currentImg);
    
    
    m_CurrentLevelTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(Value(localStorageGetItem(USER_LAST_LEVEL)).asInt()).asString());
    m_CurrentLevelTv->setPosition(Vec2(size.width*0.72, size.height*0.898));
    m_CurrentLevelTv->setScale(scale);
    m_CurrentLevelTv->setAnchorPoint(Vec2(1, 0.5));
    currentLayer->addChild(m_CurrentLevelTv);
    

    maxLayer->setVisible(false);
    currentLayer->setVisible(true);
    
    return true;
}

void GameInfoUI::setCurrentLayerVisible(bool isVisible)
{
    if (currentLayer) {
        currentLayer->setVisible(isVisible);
    }
}
 void GameInfoUI::onEnter()
{
    Layer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RUNNER_LOSE_CHANGE_VIEW, std::bind(&GameInfoUI::onRunnerLoseChangeView, this, std::placeholders::_1));

        Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MAX_DISTANCE_CHANGE, std::bind(&GameInfoUI::onMaxDistanceChange, this, std::placeholders::_1));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_GOLD_CHANGE, std::bind(&GameInfoUI::onGoldChange, this, std::placeholders::_1));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_HEART_CHANGE, std::bind(&GameInfoUI::onHeartChange, this, std::placeholders::_1));


}
 void GameInfoUI::onExit()
{
    
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_RUNNER_LOSE_CHANGE_VIEW);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MAX_DISTANCE_CHANGE);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_GOLD_CHANGE);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_HEART_CHANGE);
    Layer::onExit();
}

void GameInfoUI::onRunnerLoseChangeView(cocos2d::EventCustom* sender)
{
    CCLOG("GAME OVER");
    if (maxLayer&&m_maxLevelTv) {
        maxLayer->setVisible(true);
        currentLayer->setPosition(Vec2::ZERO);
        m_maxLevelTv->setString(Value(Value(localStorageGetItem(USER_MAX_LEVEL)).asInt()).asString());
    }

}

void GameInfoUI::onMaxDistanceChange(cocos2d::EventCustom *sender)
{
    if (m_CurrentLevelTv) {
        m_CurrentLevelTv->setString(localStorageGetItem(USER_LAST_LEVEL));
    }
}

void GameInfoUI::onhideEndPopup()
{
    
}
void GameInfoUI::onGoldChange(cocos2d::EventCustom* sender)
{
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    
    if(goldTv)
        goldTv->setString(localStorageGetItem(USER_GOLD_NUM));
    if (goldAni) {
        JumpBy* jumpByAct = JumpBy::create(0.2, Vec2::ZERO, 40*scale, 1);
//        CallFunc* fun = CallFunc::create(CC_CALLBACK_0(GameInfoUI::goldActionEnd,this));
        goldAni->runAction(Sequence::create(jumpByAct, NULL));
    }
    
}

void GameInfoUI::onHeartChange(cocos2d::EventCustom* sender)
{
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    
    if (heartTv)
        heartTv->setString(localStorageGetItem(USER_HEART_NUM));
    if (heartAni) {
        heartAni->setVisible(true);
        JumpBy* jumpByAct = JumpBy::create(0.2, Vec2::ZERO, 40*scale, 1);
//        CallFunc* fun = CallFunc::create(CC_CALLBACK_0(GameInfoUI::goldActionEnd,this));
        heartAni->runAction(Sequence::create(jumpByAct, NULL));
    }
}






