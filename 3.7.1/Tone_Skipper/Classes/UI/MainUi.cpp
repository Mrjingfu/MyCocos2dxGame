//
//  MainUi.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/9/19.
//
//

#include "MainUi.h"
#include "PopupUILayerManager.h"
#include "RegionSlider.h"
#include "MapMgrs.h"
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
    cocos2d::ui::Button* testABtn = cocos2d::ui::Button::create("ui_frame_black.png");
    
//    testABtn->setScale9Enabled(true);
    if(!testABtn)
        return ;
    testABtn->addClickEventListener([this](Ref* ref)
                                    {
                                       PopupUILayer* pop =  PopupUILayerManager::getInstance()->openPopup(ePopupBag);
                                        pop->setDarkLayerVisble(false);
                                    });
    testABtn->setPosition(Vec2(SCREEN_WIDTH*0.1, SCREEN_HEIGHT*0.9));
    testABtn->setScale(SCREEN_SCALE);
    m_pRootLayer->addChild(testABtn);

    tipsLabel = cocos2d::Label::createWithSystemFont("", DEFAULT_FONT, 13);
    tipsLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    tipsLabel->setCameraMask((unsigned short)cocos2d::CameraFlag::USER1);
    tipsLabel->setScale(SCREEN_SCALE);
    addChild(tipsLabel);
    
    
    RegionSlider* regionSlider = RegionSlider::create();
    regionSlider->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    regionSlider->setCapInsets(Rect(0, 0, 0, 0));
    regionSlider->setScale(SCREEN_SCALE);
    regionSlider->loadBarTexture("ui_frame_black.png");
    regionSlider->loadSlidBallTextureNormal("ui_frame_black.png");
    regionSlider->loadSlidBallTexturePressed("ui_frame_black.png");
    regionSlider->loadProgressBarTexture("slider_bar_active_9patch.png");
    regionSlider->setScale9Enabled(true);
    regionSlider->setContentSize(cocos2d::Size(150,24));
    regionSlider->setRotation(-90);
    regionSlider->addEventListener(CC_CALLBACK_2(MainUi::sliderPercentChanged, this));
    regionSlider->setPosition(Vec2(SCREEN_WIDTH*0.8, SCREEN_HEIGHT*0.65));
    m_pRootLayer->addChild(regionSlider);
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
void MainUi::sliderPercentChanged(cocos2d::Ref *sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        RegionSlider* slider = dynamic_cast<RegionSlider*>(sender);
        if (slider) {
            int percent = slider->getPercent();
            CCLOG("percent:%f",percent/100.0f);
            MapMgrs::getInstance()->getNilo()->setHue(percent/100.0f);
        }
        
       
    }
}