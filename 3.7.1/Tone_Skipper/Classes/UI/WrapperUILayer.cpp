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
    
    
    m_pRootLayer = Layer::create();
    m_pRootLayer->setColor(cocos2d::Color3B::GREEN);
    
    this->addChild(m_pRootLayer,1);
    
    ::gettimeofday(&m_actionTime, nullptr);
    
    //暂时放在这
    addEvents();
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