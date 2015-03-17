//
//  Joystick.h
//  Geometry-Wars
//
//  Created by wang haibo on 15/2/9.
//
//

#ifndef __Geometry_Wars__Joystick__
#define __Geometry_Wars__Joystick__

#include "cocos2d.h"
typedef enum
{
    JT_ALWAYSSHOW,
    JT_TOUCHSHOW
} JoystickVisiableType;

class Joystick;
class JoystickListener
{
public:
    virtual void onJoystickUpdateDirection(Joystick* joystick, const cocos2d::Vec2& dir){};
    virtual void onJoystickPressed(Joystick* joystick, float pressedTime){};
    virtual void onJoystickReleased(Joystick* joystick, float pressedTime){};
};
class Joystick : public cocos2d::Layer
{
    Joystick();
    virtual ~Joystick();
public:
    static Joystick* create(const std::string& bgTex, const std::string& tex);
    virtual bool init(const std::string& bgTex, const std::string& tex);
    void setVisibleType(JoystickVisiableType type);
    cocos2d::Vec2 getJoystickPosition() const;
    void setJoystickPosition(const cocos2d::Vec2& pos);
    void show();
    void hide();
    void updateJoystick(cocos2d::Touch* touch);
    void setJoystickListener(JoystickListener* pJoystickListener);
protected:
    // 处理输入
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
private:
    cocos2d::Sprite*        m_pJoystickBg;
    cocos2d::Sprite*        m_pJoystick;
    cocos2d::Vec2           m_JoystickPos;
    cocos2d::Vec2           m_TouchBeganPos;
    JoystickVisiableType    m_VisiableType;
    JoystickListener*       m_pJoystickListener;
    float                   m_fScale;
    float                   m_fRadius;
    float                   m_fMinRadius;
    float                   m_fPressTime;
};

#endif /* defined(__Geometry_Wars__Joystick__) */
