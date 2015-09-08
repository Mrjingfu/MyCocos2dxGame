//
//  JoyStick.h
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/27.
//
//

#ifndef __Tone_Skipper__JoyStick__
#define __Tone_Skipper__JoyStick__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class JoystickListener
{
public:
    virtual void onLeftBtnPressed(){};
    virtual void onLeftBtnReleased(){};
    
    virtual void onUpBtnPressed(){};
    virtual void onUpBtnReleased(){};
    
    virtual void onRightBtnPressed(){};
    virtual void onRightBtnReleased(){};
    
    virtual void onDownBtnPressed(){};
    virtual void onDownBtnReleased(){};
    
    virtual void onABtnPressed(){};
    virtual void onABtnReleased(){};
    
    virtual void onBBtnPressed(){};
    virtual void onBBtnReleased(){};
};

class JoyStick : public cocos2d::Layer
{
    JoyStick();
    virtual ~JoyStick();
public:
    static JoyStick* create();
    virtual bool init();
    void addJoystickListener(JoystickListener* listener);
    void removeJoyStickListener(JoystickListener* listener);
    void removeAllJoyStickListener();
    
    void leftBtnTouchEvent(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType touchType);
    void upBtnTouchEvent(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType touchType);
    void rightBtnTouchEvent(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType touchType);
    void downBtnTouchEvent(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType touchType);
    void aBtnTouchEvent(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType touchType);
    void bBtnTouchEvent(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType touchType);
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event);
private:
    cocos2d::ui::Button*       m_pLeftBtn;
    cocos2d::ui::Button*       m_pUpBtn;
    cocos2d::ui::Button*       m_pRightBtn;
    cocos2d::ui::Button*       m_pDownBtn;
    cocos2d::ui::Button*       m_pABtn;
    cocos2d::ui::Button*       m_pBBtn;
    
    std::vector<JoystickListener*>  m_Listeners;
};

#endif /* defined(__Tone_Skipper__JoyStick__) */
