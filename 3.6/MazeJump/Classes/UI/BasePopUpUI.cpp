//
//  BasePopUpUI.cpp
//
//
//
//

#include "BasePopUpUI.h"
#include "GameConst.h"
USING_NS_CC;


BasePopUpUI::BasePopUpUI()
{

    m_maskLayer = nullptr;
    m_dialogLayer = nullptr;
    m_isShowDialog = false;
    m_Listener = nullptr;
}
BasePopUpUI::~BasePopUpUI()
{
}
void BasePopUpUI::onEnter()
{
    Layout::onEnter();
    auto size = Director::getInstance()->getVisibleSize();
    
    
    m_maskLayer = cocos2d::Layer::create();
    m_maskLayer->setName(LAYER_NAME_MASK);
    addChild(m_maskLayer,LAYER_MASK,LAYER_MASK);
    
    
    auto maskLayer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 150));
    maskLayer->setContentSize(size);
    m_maskLayer->addChild(maskLayer);
    m_maskLayer->setVisible(false);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan =  [this](Touch * ,Event *)
    {
        if (m_isShowDialog) {
            return true;
        }else{
            return false;
        }
        
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,m_maskLayer);
   
    m_dialogLayer = cocos2d::Layer::create();
    m_dialogLayer->setName(LAYER_NAME_DIALOG);
    addChild(m_dialogLayer,LAYER_DIALOG,LAYER_DIALOG);
    m_dialogLayer->setVisible(false);
}

void BasePopUpUI::showPopUp(cocos2d::Node* node,PopUpAnimCustomListener* listener,const std::function<void()> &func)
{
    Size size = Director::getInstance()->getVisibleSize();
    m_parent = node;
    m_Listener = listener;
    m_parent->addChild(this);
    m_maskLayer->setVisible(true);
    m_dialogLayer->setVisible(true);
    m_isShowDialog = true;
    
    if (m_Listener) {
        m_Listener->onShowCustoom();
    }else{
        m_dialogLayer->setPosition(Vec2(0, size.height));
        cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.2,Vec2::ZERO);
        cocos2d::JumpBy* jumpBy =cocos2d::JumpBy::create(0.2,Point::ZERO, 50, 1);
        if (func) {
            CallFunc* callFunc = CallFunc::create(func);
            m_dialogLayer->runAction(Sequence::create(moveTo, jumpBy,callFunc, NULL));
        }else{
            m_dialogLayer->runAction(Sequence::createWithTwoActions(moveTo, jumpBy));
        }
        
        
    }

}
void BasePopUpUI::hidePopUp(const std::function<void()> &func )
{
     Size size = Director::getInstance()->getVisibleSize();
    if (m_Listener) {
        m_Listener->onHideCustoom();
    }else
    {
        cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.2,Vec2(0,size.height));
        cocos2d::MoveBy* moveBy = cocos2d::MoveBy::create(0.3, Vec2(0,-50));
        CallFunc* callFunc1 = CallFunc::create(CC_CALLBACK_0(BasePopUpUI::removePopUp,this));
        if (func) {
            CallFunc* callFunc2 = CallFunc::create(func);
            m_dialogLayer->runAction(Sequence::create(moveBy, moveTo,callFunc1,callFunc2,NULL));
        }else
        {
           m_dialogLayer->runAction(Sequence::create(moveBy, moveTo,callFunc1,NULL));
        }
       
       
    }
    
}
void BasePopUpUI::setPopUpPosition(cocos2d::Vec2 pt)
{
    if(m_dialogLayer)
    {
        m_dialogLayer->setPosition(pt);
    }
}

void BasePopUpUI::onExit()
{
    Layout::onExit();
}

void BasePopUpUI::removePopUp()
{
    m_maskLayer->setVisible(false);
    m_dialogLayer->setVisible(false);
    m_isShowDialog = false;
    m_parent->removeChild(this);
    m_Listener = nullptr;
}
