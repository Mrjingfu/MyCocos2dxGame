//
//  PopupUILayer.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/9/18.
//
//

#include "PopupUILayer.h"
#include "GameConfig.h"
#include "PopupUILayerManager.h"
USING_NS_CC;
PopupUILayer::PopupUILayer()
{
    m_pPopupType = ePopupInvalid;
    m_pActionType = eNone;
    m_pDarkLayer = nullptr;
    
    
}
PopupUILayer::~PopupUILayer()
{
    
}
bool PopupUILayer::init()
{
    if (!WrapperUILayer::init()) {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan =  CC_CALLBACK_2(PopupUILayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(PopupUILayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(PopupUILayer::onTouchEnded,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

    return true;
}
void PopupUILayer::onEnter()
{
    WrapperUILayer::onEnter();
}
void PopupUILayer::onExit()
{
    WrapperUILayer::onExit();
}
void PopupUILayer::enableDarkLayer(bool bEnable)
{
    if (bEnable)
    {
        if (m_pDarkLayer)
        {
            m_pDarkLayer->setVisible(true);
            m_pDarkLayer->setPosition(cocos2d::Vec2(-100,-100));
        }
        else
        {
            m_pDarkLayer = LayerColor::create(Color4B(0,0,0,150), SCREEN_WIDTH*2, SCREEN_HEIGHT*2);
            //有摄像机的情况需要设置对应的CameraMask
            m_pDarkLayer->setCameraMask((unsigned short)CameraFlag::USER3);
            this->addChild(m_pDarkLayer);
            this->setSwallowsTouches(true);
            m_pDarkLayer->setPosition(Vec2(-100,-100));
        }
    }else
    {
        if (m_pDarkLayer) {
            
            m_pDarkLayer->setVisible(false);
        }
    }
}
void PopupUILayer::openPopup()
{
    CCLOG("PopupUILayer::openPopup");
    //可以添加暂停监听
    enableDarkLayer(true);
    inAction();
}
void PopupUILayer::closePopup()
{
    CCLOG("PopupUILayer::closePopup");
    outAction();
}
void PopupUILayer::inAction()
{
    switch (m_pActionType) {
        case eNone:
            break;
        case eCenterScale:
            inActionCenterScale();
            break;
        case eDownCenter:
            inActionDownCenter();
            break;
        case eTopCenter:
            inActionTopCenter();
            break;
        case eLeftCenter:
            inActionLeftCenter();
            break;
        case eRightCenter:
            inActionRightCenter();
            break;
        default:
            break;
    }
}
void PopupUILayer::outAction()
{
    switch (m_pActionType) {
        case eNone:
            removeSelfCallFunc();
            break;
        case eCenterScale:
            outActionCenterScale();
            break;
        case eDownCenter:
            outActionDownCenter();
            break;
        case eTopCenter:
            outActionTopCenter();
            break;
        case eLeftCenter:
            outActionLeftCenter();
            break;
        case eRightCenter:
            outActionRightCenter();
            break;
        default:
            break;
    }
}
void PopupUILayer::inActionCenterScale()
{
    cocos2d::Layer* root = getRootLayer();
    

    if (root) {
        root->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
        //    root->setPosition(WINDOW_CENTER);
        root->setScale(0.001f);
        
        EaseIn* scale1 = EaseIn::create(ScaleTo::create(0.3f,1.1f *1),0.3f);
        
        ScaleTo* scale2 = ScaleTo::create(0.1f,1.0f * 1);
        CallFunc* callFunc =  CallFunc::create(CC_CALLBACK_0(PopupUILayer::inActionCallFunc, this));
        root->runAction(Sequence::create(scale1,scale2, callFunc,nullptr));
    }
}
void PopupUILayer::outActionCenterScale()
{
   cocos2d::Layer* root = getRootLayer();
    if (root) {
        ScaleTo* scale1 = ScaleTo::create(0.1f,1.1f * 1);
        EaseOut* scale2 = EaseOut::create(ScaleTo::create(0.4f,0.001f * 1),0.3f);
        CallFunc* callFunc =  CallFunc::create(CC_CALLBACK_0(PopupUILayer::removeSelfCallFunc, this));
        root->runAction(Sequence::create(scale1,scale2, callFunc,nullptr));
    }
}

void PopupUILayer::inActionDownCenter()
{
    cocos2d::Layer* root = getRootLayer();
    
    if (root)
    {
        root->setPosition(Vec2(0, -SCREEN_HEIGHT));
        cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.5,Vec2::ZERO);
        cocos2d::EaseBackOut* inout = cocos2d::EaseBackOut::create(moveTo);
        CallFunc* callFunc =  CallFunc::create(CC_CALLBACK_0(PopupUILayer::inActionCallFunc, this));
        root->runAction(Sequence::create(inout,callFunc, nullptr));
    }
}
void PopupUILayer::outActionDownCenter()
{
    cocos2d::Layer* root = getRootLayer();
    if (root)
    {
        cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.5,Vec2(0,-SCREEN_HEIGHT));
        cocos2d::EaseBackIn* inout = cocos2d::EaseBackIn::create(moveTo);
        CallFunc* callFunc =  CallFunc::create(CC_CALLBACK_0(PopupUILayer::removeSelfCallFunc, this));
        root->runAction(Sequence::create(inout,callFunc, nullptr));
    }
}

void PopupUILayer::inActionTopCenter()
{
    cocos2d::Layer* root = getRootLayer();
    if (root)
    {
        root->setPosition(Vec2(0, SCREEN_HEIGHT));
        cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.5,Vec2::ZERO);
        cocos2d::EaseBackOut* inout = cocos2d::EaseBackOut::create(moveTo);
        CallFunc* callFunc =  CallFunc::create(CC_CALLBACK_0(PopupUILayer::inActionCallFunc, this));
        root->runAction(Sequence::create(inout,callFunc, nullptr));
    }
}
void PopupUILayer::outActionTopCenter()
{
    cocos2d::Layer* root = getRootLayer();
    if (root)
    {
        cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.5,Vec2(0,SCREEN_HEIGHT));
        cocos2d::EaseBackIn* inout = cocos2d::EaseBackIn::create(moveTo);
        CallFunc* callFunc =  CallFunc::create(CC_CALLBACK_0(PopupUILayer::removeSelfCallFunc, this));
        root->runAction(Sequence::create(inout,callFunc, nullptr));

    }
}

void PopupUILayer::inActionLeftCenter()
{
   cocos2d::Layer* root = getRootLayer();
    if (root)
    {
        root->setPosition(Vec2(-SCREEN_WIDTH, 0));
        cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.5,Vec2::ZERO);
        cocos2d::EaseBackOut* inout = cocos2d::EaseBackOut::create(moveTo);
        CallFunc* callFunc =  CallFunc::create(CC_CALLBACK_0(PopupUILayer::inActionCallFunc, this));
        root->runAction(Sequence::create(inout,callFunc, nullptr));

    }
}
void PopupUILayer::outActionLeftCenter()
{
  cocos2d::Layer* root = getRootLayer();
    if (root)
    {
        cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.5,Vec2(-SCREEN_WIDTH,0));
        cocos2d::EaseBackIn* inout = cocos2d::EaseBackIn::create(moveTo);
        CallFunc* callFunc =  CallFunc::create(CC_CALLBACK_0(PopupUILayer::removeSelfCallFunc, this));
        root->runAction(Sequence::create(inout,callFunc, nullptr));
    }
}

void PopupUILayer::inActionRightCenter()
{
  cocos2d::Layer* root = getRootLayer();
    if (root)
    {
        root->setPosition(Vec2(SCREEN_WIDTH, 0));
        cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.5,Vec2::ZERO);
        cocos2d::EaseBackOut* inout = cocos2d::EaseBackOut::create(moveTo);
        CallFunc* callFunc =  CallFunc::create(CC_CALLBACK_0(PopupUILayer::inActionCallFunc, this));
        root->runAction(Sequence::create(inout,callFunc, nullptr));

    }
}
void PopupUILayer::outActionRightCenter()
{
  cocos2d::Layer* root = getRootLayer();
    if (root)
    {
        cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.5,Vec2(SCREEN_WIDTH,0));
        cocos2d::EaseBackIn* inout = cocos2d::EaseBackIn::create(moveTo);
        CallFunc* callFunc =  CallFunc::create(CC_CALLBACK_0(PopupUILayer::removeSelfCallFunc, this));
        root->runAction(Sequence::create(inout,callFunc, nullptr));

    }
}

void PopupUILayer::inActionCallFunc()
{
    CCLOG("inActionCallFunc");
}

void PopupUILayer::removeSelfCallFunc()
{
    CCLOG("removeSelfCallFunc");
    executeCloseBack();
    executeCloseBackO();
    executeCloseCallbackD();
    
    PopupUILayerManager::getInstance()->resetPopupType(m_pPopupType);
    
    //暂停事件恢复
    
    this->removeFromParent();
}
bool PopupUILayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}
void PopupUILayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return;
}
void PopupUILayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return;
}
void PopupUILayer::setDarkLayerVisble(bool visble)
{
    if (m_pDarkLayer) {
        m_pDarkLayer->setVisible(visble);
    }
}
void PopupUILayer::onKeyBackClick()
{
    closePopup();
}

