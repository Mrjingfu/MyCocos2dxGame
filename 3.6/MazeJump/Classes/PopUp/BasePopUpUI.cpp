//
//  BasePopUpUI.cpp
//
//
//
//

#include "BasePopUpUI.h"
#include "GameConst.h"
#include "GameInfoUI.h"
#include "UIManager.h"
USING_NS_CC;


BasePopUpUI::BasePopUpUI()
{


    m_popupShow = POPUP_VERTICAL;
    m_isShowDialog = false;
    m_isPlayAn = true;
    m_pt = Vec2::ZERO;
    m_popupBgLayer = nullptr;
    m_maskLayer = nullptr;
    m_maskLayerBg = nullptr;
    m_dialogLayer = nullptr;
}
BasePopUpUI::~BasePopUpUI()
{
}
void BasePopUpUI::onEnter()
{
    Layer::onEnter();
    Size size = Director::getInstance()->getVisibleSize();
    m_maskLayer = cocos2d::Layer::create();
    addChild(m_maskLayer,LAYER_MASK);
    
    
    m_maskLayerBg = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 150));
    m_maskLayerBg->setContentSize(size);
    m_maskLayer->addChild(m_maskLayerBg);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan =  CC_CALLBACK_2(BasePopUpUI::onTouchBegan, this);
   
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,m_maskLayer);
    
    m_dialogLayer = cocos2d::Layer::create();
    addChild(m_dialogLayer,LAYER_DIALOG,LAYER_DIALOG);
    
}

bool BasePopUpUI::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (m_isShowDialog) {
        
        Point touchBegin = touch->getLocation();
        if (m_popupBgLayer && m_popupBgLayer->getBoundingBox().containsPoint(touchBegin)) {
            return true;
        }
        UIManager::getInstance()->hidePopUp();
        return true;
    }else{
        return false;
    }
}
void BasePopUpUI::onExit()
{
    Layer::onExit();
    
}

void BasePopUpUI::showPopUp(bool isPlayAn,cocos2d::Vec2 vc,Popup_Show popupShow,const std::function<void()> &endfunc)
{
    Size size = Director::getInstance()->getVisibleSize();
    m_isShowDialog =true;
    m_isPlayAn = isPlayAn;
    m_pt = vc;
    m_popupShow = popupShow;
   
    if (!m_isPlayAn) {
        m_dialogLayer->setPosition(vc);
        if ( endfunc)
        {
            CallFunc* endcallFunc = CallFunc::create(endfunc);
            m_dialogLayer->runAction(endcallFunc);
        }
        return;
    }

    if (m_popupShow==POPUP_HORIZONTAL) {
        
       m_dialogLayer->setPosition(Vec2(size.width, 0));
        
    }else if (m_popupShow==POPUP_VERTICAL)
    {
        m_dialogLayer->setPosition(Vec2(0, size.height));
        
    }
    cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.5,vc);
    cocos2d::EaseBackOut* inout = cocos2d::EaseBackOut::create(moveTo);
    if ( endfunc)
    {
        CallFunc* endcallFunc = CallFunc::create(endfunc);
        m_dialogLayer->runAction(Sequence::create(inout,endcallFunc, NULL));
    }else{
        m_dialogLayer->runAction(inout);
    }
}
void BasePopUpUI::hidePopUp(const std::function<void()> &endfunc )
{
     Size size = Director::getInstance()->getVisibleSize();
    if (!m_isPlayAn) {

        onHidePopUpEnd();
        UIManager::getInstance()->onGameInfoHidePopUp();
        UIManager::getInstance()->removePopUp(true,this);
        
        return;
    }
    
        cocos2d::MoveTo* moveTo = nullptr;
        if (m_popupShow == POPUP_VERTICAL ) {
            
            moveTo = cocos2d::MoveTo::create(0.5,Vec2(0,size.height));
            
        }else if (m_popupShow == POPUP_HORIZONTAL)
        {
             moveTo = cocos2d::MoveTo::create(0.5,Vec2(size.width,0));
        }
    cocos2d::EaseBackIn* backIn = cocos2d::EaseBackIn::create(moveTo);
    CallFunc* callFunc1 = CallFunc::create(CC_CALLBACK_0(BasePopUpUI::onHidePopUpEnd,this));
    CallFunc* callFunc2 = CallFunc::create(CC_CALLBACK_0(UIManager::removePopUp,UIManager::getInstance(),true,this));
     if (endfunc)
    {
        CallFunc* endcallFunc = CallFunc::create(endfunc);
        m_dialogLayer->runAction(Sequence::create (backIn,callFunc1,endcallFunc,callFunc2,NULL));
    }else
    {
        m_dialogLayer->runAction(Sequence::create( backIn,callFunc1,callFunc2,NULL));
    }
    
}
void BasePopUpUI::onHidePopUpEnd()
{
    m_isShowDialog=false;
    m_isPlayAn = true;
    if (m_dialogLayer)
    {
        m_dialogLayer->setPosition(m_pt);
 
    }

}
