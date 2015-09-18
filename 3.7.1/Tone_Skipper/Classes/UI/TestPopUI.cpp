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
using namespace cocos2d::ui;
TestPopUI::TestPopUI()
{
    m_pActionType = eNone;
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
//    PopupUILayer::addEvents();
    auto testColor = cocos2d::LayerColor::create(cocos2d::Color4B::BLUE, 100.0f*SCREEN_SCALE, 100.0f*SCREEN_SCALE);
    testColor->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    testColor->setPosition(WINDOW_CENTER);
    auto testColseBtn = cocos2d::ui::Button::create("a_normal.png", "a_clicked.png", "", cocos2d::ui::TextureResType::PLIST);
    testColseBtn->setScale(SCREEN_SCALE);
    testColseBtn->setPosition(cocos2d::Vec2(testColor->getContentSize().width/2,testColor->getContentSize().height/2));
    testColor->addChild(testColseBtn);
    testColseBtn->addTouchEventListener(CC_CALLBACK_2(TestPopUI::onCancel,this));
    m_pRootLayer->addChild(testColor);
}
void TestPopUI::onCancel(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
    CHECK_ACTION_WRAPPER(sender,type);
    closePopup();
}