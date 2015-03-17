//
//  TwoJoysticks.h
//  TinyFlare
//
//  Created by wang haibo on 15/3/16.
//
//

#ifndef __TinyFlare__TwoJoysticks__
#define __TinyFlare__TwoJoysticks__

#include "cocos2d.h"

class TwoJoysticks;
class JoystickLeftListener
{
public:
    virtual void onJoystickUpdateDirection(TwoJoysticks* joystick, const cocos2d::Vec2& dir){};
};
class JoystickRightListener
{
public:
    virtual void onJoystickUpdateOrientation(TwoJoysticks* joystick, const cocos2d::Vec2& dir){};
    virtual void onJoystickPressed(TwoJoysticks* joystick, float pressedTime){};
    virtual void onJoystickReleased(TwoJoysticks* joystick, float pressedTime){};
};
class TwoJoysticks : public cocos2d::Layer
{
    TwoJoysticks();
    virtual ~TwoJoysticks();
public:
    static TwoJoysticks* create(const std::string& leftBgTex, const std::string& leftTex, const std::string& rightBgTex, const std::string& rightTex);
    virtual bool init(const std::string& leftBgTex, const std::string& leftTex, const std::string& rightBgTex, const std::string& rightTex);

    void updateJoystickLeft(cocos2d::Touch* touch);
    void updateJoystickRight(cocos2d::Touch* touch);
    void setJoystickLeftListener(JoystickLeftListener* pJoystickLeftListener);
    void setJoystickRightListener(JoystickRightListener* pJoystickRightListener);
protected:
    // 处理输入
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
private:
    cocos2d::Sprite*        m_pJoystickLeftBg;
    cocos2d::Sprite*        m_pJoystickLeft;
    cocos2d::Sprite*        m_pJoystickRightBg;
    cocos2d::Sprite*        m_pJoystickRight;
    cocos2d::Vec2           m_JoystickLeftPos;
    cocos2d::Vec2           m_JoystickRightPos;
    cocos2d::Vec2           m_TouchBeganPos;
    JoystickLeftListener*   m_pJoystickLeftListener;
    JoystickRightListener*  m_pJoystickRightListener;
    float                   m_fScale;
    float                   m_fRadius;
    float                   m_fMinRadius;
    float                   m_fPressTime;
};

#endif /* defined(__TinyFlare__TwoJoysticks__) */
