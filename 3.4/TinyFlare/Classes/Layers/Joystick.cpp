//
//  Joystick.cpp
//  Geometry-Wars
//
//  Created by wang haibo on 15/2/9.
//
//

#include "Joystick.h"
USING_NS_CC;

Joystick* Joystick::create(const std::string& bgTex, const std::string& tex)
{
    Joystick *pRet = new(std::nothrow) Joystick();
    if (pRet && pRet->init(bgTex, tex))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
Joystick::Joystick()
{
    m_VisiableType = JoystickVisiableType::JT_ALWAYSSHOW;
    m_JoystickPos = Vec2(120, 120);
    m_TouchBeganPos = m_JoystickPos;
    m_pJoystickListener = nullptr;
    m_fScale = 1.0f;
    m_fRadius = 80.0f;
    m_fMinRadius = 20.0f;
    m_fPressTime = 0.0f;
}
Joystick::~Joystick()
{
}
bool Joystick::init(const std::string& bgTex, const std::string& tex)
{
    if (!Layer::init())
        return false;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    m_fScale = visibleSize.height/640.0f;
    m_JoystickPos = m_JoystickPos*m_fScale;
    m_fRadius = m_fRadius*m_fScale;
    m_fMinRadius = m_fMinRadius*m_fScale;
    // joystick的背景
    m_pJoystickBg = Sprite::create(bgTex);
    if (m_pJoystickBg == nullptr)
        return false;
    m_pJoystickBg->setGlobalZOrder(10);
    m_pJoystickBg->setPosition(m_JoystickPos);
    m_pJoystickBg->setScale(m_fScale);
    m_pJoystickBg->setCascadeOpacityEnabled(true);
    m_pJoystickBg->setOpacity(200);
    addChild(m_pJoystickBg);
    
    m_pJoystick = Sprite::create(tex);
    if (m_pJoystick == nullptr)
        return false;
    m_pJoystick->setGlobalZOrder(10);
    m_pJoystick->setScale(m_fScale);
    m_pJoystick->setPosition(m_JoystickPos);
    m_pJoystick->setCascadeOpacityEnabled(true);
    m_pJoystick->setOpacity(200);
    addChild(m_pJoystick);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    if(touchListener == nullptr)
        return false;
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(Joystick::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Joystick::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Joystick::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}
void Joystick::setVisibleType(JoystickVisiableType type)
{
    if(m_VisiableType != type)
    {
        m_VisiableType = type;
        if(m_VisiableType == JoystickVisiableType::JT_TOUCHSHOW)
            hide();
    }
}
Vec2 Joystick::getJoystickPosition() const
{
    return m_JoystickPos;
}
void Joystick::setJoystickPosition(const cocos2d::Vec2& pos)
{
    CCASSERT(m_pJoystickBg && m_pJoystick, "");
    m_JoystickPos = pos;
    m_pJoystickBg->setPosition(m_JoystickPos);
    m_pJoystick->setPosition(m_JoystickPos);
}
void Joystick::show()
{
    CCASSERT(m_pJoystickBg && m_pJoystick, "");
    m_pJoystickBg->setVisible(true);
    m_pJoystick->setVisible(true);
}
void Joystick::hide()
{
    CCASSERT(m_pJoystickBg && m_pJoystick, "");
    m_pJoystickBg->setVisible(false);
    m_pJoystick->setVisible(false);
}
void Joystick::setJoystickListener(JoystickListener* pJoystickListener)
{
    m_pJoystickListener = pJoystickListener;
}
void Joystick::updateJoystick(Touch* touch)
{
    if(touch && m_pJoystick && m_pJoystickBg)
    {
        Vec2 hit = touch->getLocation();
        float distance = m_JoystickPos.getDistance(hit);
        Vec2 direction = (hit - m_JoystickPos).getNormalized();
    
        if(distance < m_fRadius)
        {
            m_pJoystick->setPosition(m_JoystickPos + (direction * distance));
        }
        else {
            m_pJoystick->setPosition(m_JoystickPos + (direction * m_fRadius));
        }
        if(m_pJoystickListener)
        {
            if(distance >= m_fMinRadius)
                m_pJoystickListener->onJoystickUpdateDirection(this, direction);
            m_pJoystickListener->onJoystickPressed(this, m_fPressTime);
        }
    }
}
// 处理输入
bool Joystick::onTouchBegan(Touch* touch, Event* unused_event)
{
    m_TouchBeganPos = touch->getLocation();
    if(m_VisiableType == JoystickVisiableType::JT_TOUCHSHOW)
    {
        setJoystickPosition(m_TouchBeganPos);
        show();
    }
    if (m_pJoystick->getBoundingBox().containsPoint(m_TouchBeganPos)) {
        updateJoystick(touch);
        return true;
    }
    return false;
}
void Joystick::onTouchMoved(Touch* touch, Event* unused_event)
{
    if (m_pJoystick->isVisible()) {
        updateJoystick(touch);
        m_fPressTime += Director::getInstance()->getDeltaTime();
    }
}
void Joystick::onTouchEnded(Touch* touch, Event* unused_event)
{
    if(m_VisiableType == JoystickVisiableType::JT_TOUCHSHOW)
        hide();
    setJoystickPosition(m_JoystickPos);
    if(m_pJoystickListener)
    {
        m_pJoystickListener->onJoystickUpdateDirection(this, Vec2::ZERO);
        m_pJoystickListener->onJoystickReleased(this, m_fPressTime);
        m_fPressTime = 0.0f;
    }
}