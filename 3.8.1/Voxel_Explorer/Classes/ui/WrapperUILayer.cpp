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
    m_pRootLayer = nullptr;
    m_pRootNode  = nullptr;
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
    
    ::gettimeofday(&m_actionTime, nullptr);
    
    m_actionRef = nullptr;
    m_pRootLayer = cocos2d::Layer::create();
    m_pRootLayer->setContentSize(cocos2d::Director::getInstance()->getVisibleSize());
    this->addChild(m_pRootLayer,1);
    
    
    //
    if(!initUi())
        return false;
    //setCameraMask 只能使node的当前所有子节点的cameraMask设置为mask 之后新添加的子节点则不会受影响 所以在初始化UI之后设置
    m_pRootLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    return true;
    
}
bool WrapperUILayer::load(const std::string gameUIFile,bool isSceneUi)
{
    bool ret =true;
    m_pRootNode = cocos2d::CSLoader::createNode(gameUIFile);
    if (!m_pRootNode) {
        ret = false;
    }
    if (m_pRootNode->getParent()) {
        ret = true;
    }
    
    if (isSceneUi) {
        m_pRootNode->setContentSize(cocos2d::Director::getInstance()->getVisibleSize());
    }else{
        m_pRootNode->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
        m_pRootNode->setPosition(cocos2d::Director::getInstance()->getVisibleSize()*0.5);
    }
    
    cocos2d::ui::Helper::doLayout(m_pRootNode);

//  m_pRootNode->setPosition(m_pRootNode->getPosition()+cocos2d::Director::getInstance()->getVisibleOrigin());
    
    this->addChild(m_pRootNode,1);
    m_pRootNode->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    if(!addEvents())
        ret = false;
    
    return ret;
}
void WrapperUILayer::schedulerPause()
{
    std::set<void*> _m_pBeforeTargetSets = cocos2d::Director::getInstance()->getScheduler()->pauseAllTargets();
    
    for(std::set<void*>::iterator it=_m_pBeforeTargetSets.begin();it!=_m_pBeforeTargetSets.end();it++)
    {
        cocos2d::Director::getInstance()->getScheduler()->pauseTarget(*it);
    }
}
void WrapperUILayer::schedulerResume()
{
    std::set<void*> _m_pBeforeTargetSets = cocos2d::Director::getInstance()->getScheduler()->pauseAllTargets();
    
    for(std::set<void*>::iterator it=_m_pBeforeTargetSets.begin();it!=_m_pBeforeTargetSets.end();it++)
    {
        cocos2d::Director::getInstance()->getScheduler()->resumeTarget(*it);
    }
}
bool WrapperUILayer::isForbiddenAction(cocos2d::Ref *sender)
{
    struct timeval now;
    ::gettimeofday(&now, NULL);
    
    unsigned long long used = (now.tv_sec - m_actionTime.tv_sec)*1000 + (now.tv_usec - m_actionTime.tv_usec)/1000;
    
    if( m_actionRef != sender && used < UI_ACTION_INTERVAL){
        CCLOG("SSSSSS");
        return true;
    }else if(m_actionRef == sender && used < UI_ACTION_INTERVAL){
         CCLOG("EEEEE");
        return true;
    }else{
         CCLOG("GGGGGG");
        ::gettimeofday(&m_actionTime, NULL);
        m_actionRef = sender;
        return false;
    }
}