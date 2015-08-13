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
    

}
GameUI::~GameUI()
{
}
void GameUI::onEnter()
{
    Layer::onEnter();
        Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RUNNER_LOSE, std::bind(&GameUI::onRunnerLose, this, std::placeholders::_1));
}
void GameUI::onExit()
{
    Layer::onExit();
        Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_RUNNER_LOSE);
}
bool GameUI::init()
{
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /640.f;
    
    cocos2d::ui::Button* button = cocos2d::ui::Button::create("button_retry_up.png",
                                                              "button_retry_down.png");
    button->setPosition(Vec2(size.width * 0.8f, size.height * 0.8f));
    button->setScale(scale);
    button->setPressedActionEnabled(true);
    button->addClickEventListener([=](Ref* sender){
        auto scene = MainScene::createScene();
        Director::getInstance()->replaceScene(scene);
    });
    addChild(button);
    
    
    SkillButton* skillBtn = SkillButton::create("button_retry_up.png", "stencil.png");
    if(!skillBtn)
        return false;
    skillBtn->setScale(scale);
    skillBtn->setPosition(Vec2(size.width * 0.1f, size.height * 0.1f));
    addChild(skillBtn);
    
    return true;
}
void GameUI::onRunnerLose(cocos2d::EventCustom* sender)
{
    CCLOG("GAME OVER");
    runAction(Sequence::create(DelayTime::create(0.5),CallFunc::create(CC_CALLBACK_0(GameUI::onDelayTimeRunnerLose,this)), NULL));
}
void GameUI::onDelayTimeRunnerLose()
{
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_CONTINUE);
    UIManager::getInstance()->showPopUp(true,BasePopUpUI::POPUP_HORIZONTAL);
}

