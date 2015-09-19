//
//  TestPopUI.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/9/18.
//
//

#include "TestPopUI.h"
#include "GameConfig.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
TestPopUI::TestPopUI()
{
    m_pActionType = eCenterScale;
}
TestPopUI::~TestPopUI()
{
    
}
bool TestPopUI::init()
{
    return PopupUILayer::init();
}

void TestPopUI::addEvents()
{
    cocos2d::ui::Layout* testLayout = cocos2d::ui::Layout::create();
    testLayout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    testLayout->setBackGroundImage("ui_frame_black.png");
    testLayout->setBackGroundImageScale9Enabled(true);
    testLayout->setContentSize(cocos2d::Size(200,200));
    testLayout->setLayoutType(Layout::Type::RELATIVE);
    testLayout->setScale(SCREEN_SCALE);
    testLayout->setPosition(WINDOW_CENTER);
    getRootPopupLayer()->addChild(testLayout);
   
    auto testColseBtn = cocos2d::ui::Button::create("ui_frame_black.png");
    testColseBtn->setScale(SCREEN_SCALE);
    testLayout->addChild(testColseBtn);
    testColseBtn->addTouchEventListener(CC_CALLBACK_2(TestPopUI::onCancel,this));
    
    RelativeLayoutParameter* rp_RightCenter = RelativeLayoutParameter::create();
    rp_RightCenter->setAlign(RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
    testColseBtn->setLayoutParameter(rp_RightCenter);
}
void TestPopUI::onCancel(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
    CHECK_ACTION(sender,type);
    closePopup();
}