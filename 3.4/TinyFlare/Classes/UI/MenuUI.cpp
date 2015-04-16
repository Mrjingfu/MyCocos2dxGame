//
//  MenuUI.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/15.
//
//

#include "MenuUI.h"
#include "UtilityHelper.h"
#include "GameController.h"
USING_NS_CC;

MenuUI* MenuUI::create()
{
    MenuUI *pRet = new(std::nothrow) MenuUI();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

MenuUI::MenuUI()
{
    m_pPlayGameBtn      = nullptr;
    m_pRankBtn          = nullptr;
    m_pShareBtn         = nullptr;
    m_pHelpBtn          = nullptr;
    m_pMenuBg           = nullptr;
    m_pGameTitle        = nullptr;
    m_pPlayText         = nullptr;
}
MenuUI::~MenuUI()
{
}
bool MenuUI::init()
{
    bool ret = ui::Layout::init();
    auto size = Director::getInstance()->getVisibleSize();
    m_pMenuBg = ui::ImageView::create("menubg.png");
    if(!m_pMenuBg)
        return false;
    m_pMenuBg->setScale9Enabled(true);
    m_pMenuBg->setCapInsets(Rect(0,1,128,2));
    m_pMenuBg->setContentSize(Size(size.width,size.height*0.3f));
    m_pMenuBg->setPosition(Vec2(size.width*0.5f, size.height*0.65f));
    m_pMenuBg->setScale(0);
    addChild(m_pMenuBg);
    
    ScaleTo* scaleTo1 = ScaleTo::create(0.2f, 0, 1.0f);
    ScaleTo* scaleTo2 = ScaleTo::create(0.2f, 1.0f, 1.0f);
    Spawn* spawn = Spawn::createWithTwoActions(scaleTo1, scaleTo2);
    m_pMenuBg->runAction(spawn);
    
    m_pGameTitle = ui::TextBMFont::create(UtilityHelper::getLocalString("GAME_NAME"), "v5prophit.fnt");
    m_pGameTitle->setScale(0.45f, 0.6f);
    m_pGameTitle->setPosition(Vec2(size.width*1.5f, size.height*0.65f));
    addChild(m_pGameTitle);
    
    DelayTime* delay = DelayTime::create(0.2f);
    MoveTo* moveTo = MoveTo::create(0.2f, Vec2(size.width*0.5f, size.height*0.65f));
    Sequence* sequence = Sequence::createWithTwoActions(delay, moveTo);
    m_pGameTitle->runAction(sequence);
    
    m_pPlayGameBtn = ui::Button::create("menubg.png");
    m_pPlayGameBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressPlayGameBtn, this));
    m_pPlayGameBtn->setScale9Enabled(true);
    m_pPlayGameBtn->setCapInsets(Rect(0,2,128,0.5f));
    m_pPlayGameBtn->setContentSize(Size(size.width,size.height*0.1f));
    m_pPlayGameBtn->setPosition(Vec2(size.width*0.5f, size.height*0.3f));
    m_pPlayGameBtn->setScale(0);
    addChild(m_pPlayGameBtn);
    
    Sequence* sequence2 = Sequence::createWithTwoActions(delay, spawn);
    m_pPlayGameBtn->runAction(sequence2);
    
    m_pPlayText = ui::Text::create(UtilityHelper::getLocalString("PRESS_BEGIN"), "FZXS12.TTF", size.height*0.05f);
    m_pPlayText->setPosition(Size(size.width*0.5f,size.height*0.3f));
    m_pPlayText->setOpacity(0);
    m_pPlayText->setColor(Color3B(208,255,208));
    addChild(m_pPlayText);
    
    EaseSineOut* easeOut1 = EaseSineOut::create(FadeIn::create(0.5f));
    EaseSineOut* easeOut2 = EaseSineOut::create(FadeOut::create(0.5f));
    Sequence* sequence3 = Sequence::create(easeOut1, delay, easeOut2, NULL);
    RepeatForever* repeat = RepeatForever::create(sequence3);
    m_pPlayText->runAction(repeat);
    
    float scale = 256.0f/size.height;
    m_pRankBtn = ui::Button::create("rank.png");
    m_pRankBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressRankBtn, this));
    m_pRankBtn->setPosition(Vec2(size.width*0.80f, size.height*0.1f));
    m_pRankBtn->setScale(scale);
    addChild(m_pRankBtn);
    
    m_pShareBtn = ui::Button::create("share.png");
    m_pShareBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressShareBtn, this));
    m_pShareBtn->setPosition(Vec2(size.width*0.80f + m_pRankBtn->getContentSize().width*0.5f, size.height*0.1f));
    m_pShareBtn->setScale(scale);
    addChild(m_pShareBtn);
    
    m_pHelpBtn = ui::Button::create("help.png");
    m_pHelpBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressHelpBtn, this));
    m_pHelpBtn->setPosition(Vec2(size.width*0.80f + m_pShareBtn->getContentSize().width, size.height*0.1f));
    m_pHelpBtn->setScale(scale);
    addChild(m_pHelpBtn);
    return ret;
}
void MenuUI::pressPlayGameBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
        GameController::getInstance()->setGameState(GS_GAME);
}
void MenuUI::pressRankBtn(Ref* p,TouchEventType eventType)
{
}
void MenuUI::pressShareBtn(Ref* p,TouchEventType eventType)
{
}
void MenuUI::pressHelpBtn(Ref* p,TouchEventType eventType)
{
}

void MenuUI::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
        Director::getInstance()->end();
}