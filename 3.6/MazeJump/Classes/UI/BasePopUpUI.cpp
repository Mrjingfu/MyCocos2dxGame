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

}
BasePopUpUI::~BasePopUpUI()
{
}


void BasePopUpUI::showPopUp(Popup_Show popupShow,const std::function<void()> &func)
{
    Size size = Director::getInstance()->getVisibleSize();
    m_popupShow = popupShow;
 
        if (m_popupShow==POPUP_HORIZONTAL) {
            
           setPosition(Vec2(size.width, 0));
            
            cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.5,Vec2::ZERO);
            cocos2d::EaseBackOut* inout = cocos2d::EaseBackOut::create(moveTo);
            if (func) {
                CallFunc* callFunc = CallFunc::create(func);
                runAction(Sequence::create(inout,callFunc, NULL));
            }else{
                runAction(inout);
            }
            
        }else if (m_popupShow==POPUP_VERTICAL)
        {
            setPosition(Vec2(0, size.height));
            cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.5,Vec2::ZERO);
            cocos2d::EaseBackOut* inout = cocos2d::EaseBackOut::create(moveTo);
            if (func) {
                CallFunc* callFunc = CallFunc::create(func);
                runAction(Sequence::create(moveTo,callFunc, NULL));
            }else{
                runAction(inout);
            }
        }

}
void BasePopUpUI::hidePopUp(const std::function<void()> &func )
{
     Size size = Director::getInstance()->getVisibleSize();

        
        if (m_popupShow == POPUP_VERTICAL ) {
            
            cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.5,Vec2(0,size.height));
            cocos2d::EaseBackIn* backIn = cocos2d::EaseBackIn::create(moveTo);
            CallFunc* callFunc1 = CallFunc::create(CC_CALLBACK_0(UIManager::removePopUp,UIManager::getInstance(),this));
            if (func) {
                CallFunc* callFunc2 = CallFunc::create(func);
                runAction(Sequence::create (backIn,callFunc1,callFunc2,NULL));
            }else
            {
                runAction(Sequence::create( backIn,callFunc1,NULL));
            }
        }else if (m_popupShow == POPUP_HORIZONTAL)
        {
            cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.5,Vec2(size.width,0));
            cocos2d::EaseBackIn* backIn = cocos2d::EaseBackIn::create(moveTo);
            CallFunc* callFunc1 = CallFunc::create(CC_CALLBACK_0(UIManager::removePopUp,UIManager::getInstance(),this));
            if (func) {
                CallFunc* callFunc2 = CallFunc::create(func);
                runAction(Sequence::create(backIn,callFunc1,callFunc2,NULL));
            }else
            {
                runAction(Sequence::create( backIn,callFunc1,NULL));
            }
        }

    
}

