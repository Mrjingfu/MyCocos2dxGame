//
//  MainUi.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/9/19.
//
//

#include "MainUi.h"
#include "PopupUILayerManager.h"
USING_NS_CC;
using namespace ui;
MainUi::MainUi()
{
    
}
MainUi::~MainUi()
{
    
}

void MainUi::onEnter()
{
    WrapperUILayer::onEnter();
    cocos2d::Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MAIN_TIPS, CC_CALLBACK_1(MainUi::onEventTips, this));
}
void MainUi::onExit()
{
    cocos2d::Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MAIN_TIPS);
    WrapperUILayer::onExit();
}
void MainUi::addEvents()
{
    //test
    
    cocos2d::ui::Button* testABtn = cocos2d::ui::Button::create("ui_frame_black.png");
//    testABtn->setScale9Enabled(true);
    if(!testABtn)
        return ;
    
    testABtn->setPosition(cocos2d::Vec2(SCREEN_WIDTH*0.3,SCREEN_HEIGHT*0.8));
    testABtn->addClickEventListener([this](Ref* ref)
                                    {
                                        PopupUILayerManager::getInstance()->openPopup(ePopupTest);
                                    });
    testABtn->setScale(SCREEN_SCALE);
   

    getRootLayout()->addChild(testABtn);

    RelativeLayoutParameter* rp_RightCenter = RelativeLayoutParameter::create();
    rp_RightCenter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_LEFT);
    testABtn->setLayoutParameter(rp_RightCenter);

    

    tipsLabel = cocos2d::Label::createWithSystemFont("", DEFAULT_FONT, 13);
    tipsLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    tipsLabel->setCameraMask((unsigned short)cocos2d::CameraFlag::USER1);
    tipsLabel->setScale(SCREEN_SCALE);
    addChild(tipsLabel);
    //test
}
void MainUi::onEventTips(cocos2d::EventCustom *sender)
{
    if (tipsLabel && tipsLabel->getString().empty()) {
        TipData* tipData = (TipData*)sender->getUserData();
        CCLOG("pos : %f, %f; tips: %s", tipData->m_pPt.x, tipData->m_pPt.y, tipData->m_pDes.c_str());
        tipsLabel->setPosition(tipData->m_pPt);
        tipsLabel->setString(tipData->m_pDes);
        cocos2d::CallFunc* fun1 = cocos2d::CallFunc::create([this](){
            tipsLabel->setString("");
        });
        tipsLabel->runAction(cocos2d::Sequence::createWithTwoActions(cocos2d::DelayTime::create(1.5f), fun1));
    }
    
}