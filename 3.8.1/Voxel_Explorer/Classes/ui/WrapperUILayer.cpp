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
    
//    cocos2d::Camera* uiCamera = cocos2d::Camera::create();
//    uiCamera->setCameraFlag(cocos2d::CameraFlag::USER3);
//    this->addChild(uiCamera);
    
    m_pRootLayer = cocos2d::Layer::create();
    this->addChild(m_pRootLayer,1);
    ::gettimeofday(&m_actionTime, nullptr);
    
    
    if(!initUi())
        return false;
    //setCameraMask 只能使node的当前所有子节点的cameraMask设置为mask 之后新添加的子节点则不会受影响 所以在初始化UI之后设置
    m_pRootLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    return true;
    
}
bool WrapperUILayer::load(const std::string gameUIFile)
{
    bool ret =true;
    m_pRootNode = cocos2d::CSLoader::createNode(gameUIFile);
    if (!m_pRootNode) {
        ret = false;
    }
    if (m_pRootNode->getParent()) {
        ret = true;
    }
    
    m_pRootNode->setContentSize(cocos2d::Director::getInstance()->getVisibleSize());
    cocos2d::ui::Helper::doLayout(m_pRootNode);
    m_pRootNode->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pRootNode->setPosition(m_pRootNode->getPosition()+cocos2d::Director::getInstance()->getVisibleOrigin());
    this->addChild(m_pRootNode,1);
    
    addEvents();
    
    return ret;
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