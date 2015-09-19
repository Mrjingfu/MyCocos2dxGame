//
//  WarpperLayer.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/9/18.
//
//

#include "WrapperUILayer.h"

#define UI_ACTION_INTERVAL  500 // 毫秒

WrapperUILayer::WrapperUILayer()
{
    
}
WrapperUILayer::~WrapperUILayer()
{
    
}
void WrapperUILayer::onEnter()
{
    Layer::onEnter();
}
void WrapperUILayer::onExit()
{
    Layer::onExit();
}
bool WrapperUILayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    m_actionRef = nullptr;
    
    cocos2d::Camera* uiCamera = cocos2d::Camera::create();
    uiCamera->setCameraFlag(cocos2d::CameraFlag::USER3);
    this->addChild(uiCamera);
    
    m_pRootLayout = cocos2d::ui::Layout::create();
    m_pRootLayout->setContentSize(cocos2d::Size(SCREEN_WIDTH,SCREEN_HEIGHT));
    m_pRootLayout->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    m_pRootLayout->setLayoutType(cocos2d::ui::Layout::Type::RELATIVE);
    m_pRootLayout->setPosition(WINDOW_CENTER);
    this->addChild(m_pRootLayout,1);
    
    m_pPopupLayer = cocos2d::Layer::create();
    this->addChild(m_pPopupLayer,2);
    ::gettimeofday(&m_actionTime, nullptr);
    
    //暂时放在这
    addEvents();
    //setCameraMask 只能使node的当前所有子节点的cameraMask设置为mask 之后新添加的子节点则不会受影响 所以在初始化UI之后设置
    m_pRootLayout->setCameraMask((unsigned short)cocos2d::CameraFlag::USER3);
    m_pPopupLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER3);
    return true;
    
}
bool WrapperUILayer::isForbiddenAction(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
    struct timeval now;
    ::gettimeofday(&now, NULL);
    
    unsigned long long used = (now.tv_sec - m_actionTime.tv_sec)*1000 + (now.tv_usec - m_actionTime.tv_usec)/1000;
    
    if( m_actionRef != sender && used < UI_ACTION_INTERVAL){
        CCLOG("SSSSSS");
        return true;
    }else if(m_actionRef == sender && used < UI_ACTION_INTERVAL && cocos2d::ui::Widget::TouchEventType::BEGAN == type){
         CCLOG("EEEEE");
        return true;
    }else{
         CCLOG("GGGGGG");
        ::gettimeofday(&m_actionTime, NULL);
        m_actionRef = sender;
        return false;
    }
}