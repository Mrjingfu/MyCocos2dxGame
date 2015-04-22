//
//  PauseUI.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/22.
//
//

#include "PauseUI.h"
#include "GameController.h"
USING_NS_CC;

PauseUI* PauseUI::create()
{
    PauseUI *pRet = new(std::nothrow) PauseUI();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

PauseUI::PauseUI()
{
    m_pRankBtn      = nullptr;
    m_pRemoveADSBtn = nullptr;
    m_pHelpBtn      = nullptr;
    m_pBackBtn      = nullptr;
    
    m_pPanelBg  = nullptr;
    m_pPlayText = nullptr;
}
PauseUI::~PauseUI()
{
}
bool PauseUI::init()
{
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height/640.0f;
    m_pPanelBg = ui::ImageView::create("menubg.png");
    if(!m_pPanelBg)
        return false;
    m_pPanelBg->setScale9Enabled(true);
    m_pPanelBg->setCapInsets(Rect(0,2,128,0.5f));
    m_pPanelBg->setContentSize(Size(size.width,size.height*0.7f));
    m_pPanelBg->setPosition(Vec2(size.width*0.5f, size.height*0.5f));
    m_pPanelBg->setScale(0);
    addChild(m_pPanelBg);
    
//    m_pRankBtn = ui::Button::create("rank.png");
//    if(!m_pRemoveADSBtn)
//        return false;
//    m_pRankBtn->addTouchEventListener(CC_CALLBACK_2(PauseUI::pressRankBtn, this));
//    m_pRankBtn->setPosition(Vec2(size.width - m_pRankBtn->getContentSize().width*scale*2.1f, size.height*0.8f));
//    m_pRankBtn->setScale(0.4f*scale);
//    m_pRankBtn->setVisible(false);
//    addChild(m_pRankBtn);
    
    
    m_pRemoveADSBtn = ui::Button::create("removeads.png");
    if(!m_pRemoveADSBtn)
        return false;
    m_pRemoveADSBtn->addTouchEventListener(CC_CALLBACK_2(PauseUI::pressRemoveADSBtn, this));
    m_pRemoveADSBtn->setPosition(Vec2(size.width - m_pRemoveADSBtn->getContentSize().width*scale*2.1f, size.height*0.08f));
    m_pRemoveADSBtn->setScale(0.4f*scale);
    m_pPanelBg->addChild(m_pRemoveADSBtn);
    
    m_pHelpBtn = ui::Button::create("help.png");
    if(!m_pHelpBtn)
        return false;
    m_pHelpBtn->addTouchEventListener(CC_CALLBACK_2(PauseUI::pressHelpBtn, this));
    m_pHelpBtn->setPosition(Vec2(size.width - m_pHelpBtn->getContentSize().width*scale*1.4f, size.height*0.08f));
    m_pHelpBtn->setScale(0.4f*scale);
    m_pPanelBg->addChild(m_pHelpBtn);
    
    m_pBackBtn = ui::Button::create("exit.png");
    if(!m_pBackBtn)
        return false;
    m_pBackBtn->addTouchEventListener(CC_CALLBACK_2(PauseUI::pressBackBtn, this));
    m_pBackBtn->setPosition(Vec2(size.width - m_pBackBtn->getContentSize().width*scale*0.7f, size.height*0.08f));
    m_pBackBtn->setScale(0.4f*scale);
    m_pPanelBg->addChild(m_pBackBtn);

    return true;
}
void PauseUI::beginToPause()
{
    if(m_pPanelBg)
    {
        ScaleTo* scaleTo1 = ScaleTo::create(0.2f, 0, 1.0f);
        ScaleTo* scaleTo2 = ScaleTo::create(0.2f, 1.0f, 1.0f);
        Spawn* spawn = Spawn::createWithTwoActions(scaleTo1, scaleTo2);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GameController::pauseStart, GameController::getInstance()));
        Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
        m_pPanelBg->runAction(sequnce);
    }
}
void PauseUI::endToPause()
{
    if(m_pPanelBg)
    {
        m_pPanelBg->stopAllActions();
        ScaleTo* scaleTo1 = ScaleTo::create(0.2f, 1.0f, 0.0f);
        ScaleTo* scaleTo2 = ScaleTo::create(0.2f, 0.0f, 0.0f);
        Spawn* spawn = Spawn::createWithTwoActions(scaleTo1, scaleTo2);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GameController::pauseEnd, GameController::getInstance()));
        Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
        m_pPanelBg->runAction(sequnce);
    }
}
void PauseUI::pressRankBtn(Ref* p,TouchEventType eventType)
{
}
void PauseUI::pressRemoveADSBtn(Ref* p,TouchEventType eventType)
{
}
void PauseUI::pressHelpBtn(Ref* p,TouchEventType eventType)
{
}
void PauseUI::pressBackBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        Director::getInstance()->end();
    }
}
