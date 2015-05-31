//
//  TwoJoysticks.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/3/16.
//
//

#include "TwoJoysticks.h"
USING_NS_CC;

TwoJoysticks* TwoJoysticks::create(const std::string& leftBgTex, const std::string& leftTex, const std::string& rightBgTex, const std::string& rightTex)
{
    TwoJoysticks *pRet = new(std::nothrow) TwoJoysticks();
    if (pRet && pRet->init(leftBgTex, leftTex, rightBgTex, rightTex))
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
TwoJoysticks::TwoJoysticks()
{
    m_JoystickLeftPos = Vec2(120, 120);
    m_pJoystickLeftListener = nullptr;
    m_pJoystickRightListener = nullptr;
    m_fScale = 1.0f;
    m_fRadius = 80.0f;
    m_fMinRadius = 20.0f;
    m_fPressTime = 0.0f;
}
TwoJoysticks::~TwoJoysticks()
{
}
bool TwoJoysticks::init(const std::string& leftBgTex, const std::string& leftTex, const std::string& rightBgTex, const std::string& rightTex)
{
    if (!Layer::init())
        return false;
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    m_fScale = visibleSize.height/640.0f;
    m_JoystickLeftPos = m_JoystickLeftPos*m_fScale;
    m_JoystickRightPos = Vec2(visibleSize.width - m_JoystickLeftPos.x, m_JoystickLeftPos.y);
    
    m_fRadius = m_fRadius*m_fScale;
    m_fMinRadius = m_fMinRadius*m_fScale;
    // joystickLeft的背景
    m_pJoystickLeftBg = Sprite::createWithSpriteFrameName(leftBgTex);
    if (m_pJoystickLeftBg == nullptr)
        return false;
    m_pJoystickLeftBg->setGlobalZOrder(10);
    m_pJoystickLeftBg->setPosition(m_JoystickLeftPos);
    m_pJoystickLeftBg->setScale(m_fScale);
    m_pJoystickLeftBg->setCascadeOpacityEnabled(true);
    m_pJoystickLeftBg->setOpacity(200);
    addChild(m_pJoystickLeftBg);
    
    m_pJoystickLeft = Sprite::createWithSpriteFrameName(leftTex);
    if (m_pJoystickLeft == nullptr)
        return false;
    m_pJoystickLeft->setGlobalZOrder(10);
    m_pJoystickLeft->setScale(m_fScale);
    m_pJoystickLeft->setPosition(m_JoystickLeftPos);
    m_pJoystickLeft->setCascadeOpacityEnabled(true);
    m_pJoystickLeft->setOpacity(200);
    addChild(m_pJoystickLeft);
    
    // joystickRight的背景
    m_pJoystickRightBg = Sprite::createWithSpriteFrameName(rightBgTex);
    if (m_pJoystickRightBg == nullptr)
        return false;
    m_pJoystickRightBg->setGlobalZOrder(10);
    m_pJoystickRightBg->setPosition(m_JoystickRightPos);
    m_pJoystickRightBg->setScale(m_fScale);
    m_pJoystickRightBg->setCascadeOpacityEnabled(true);
    m_pJoystickRightBg->setOpacity(200);
    addChild(m_pJoystickRightBg);
    
    m_pJoystickRight = Sprite::createWithSpriteFrameName(rightTex);
    if (m_pJoystickRight == nullptr)
        return false;
    m_pJoystickRight->setGlobalZOrder(10);
    m_pJoystickRight->setScale(m_fScale);
    m_pJoystickRight->setPosition(m_JoystickRightPos);
    m_pJoystickRight->setCascadeOpacityEnabled(true);
    m_pJoystickRight->setOpacity(200);
    addChild(m_pJoystickRight);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchAllAtOnce::create();
    if(touchListener == nullptr)
        return false;
    touchListener->onTouchesBegan = CC_CALLBACK_2(TwoJoysticks::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(TwoJoysticks::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(TwoJoysticks::onTouchesEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}
void TwoJoysticks::setJoystickLeftListener(JoystickLeftListener* pJoystickLeftListener)
{
    m_pJoystickLeftListener = pJoystickLeftListener;
}
void TwoJoysticks::setJoystickRightListener(JoystickRightListener* pJoystickRightListener)
{
    m_pJoystickRightListener = pJoystickRightListener;
}
void TwoJoysticks::updateJoystickLeft(cocos2d::Touch* touch)
{
    if(touch && m_pJoystickLeft && m_pJoystickLeftBg)
    {
        Vec2 hit = touch->getLocation();
        float distance = m_JoystickLeftPos.getDistance(hit);
        Vec2 direction = (hit - m_JoystickLeftPos).getNormalized();
        
        if(distance < m_fRadius)
        {
            m_pJoystickLeft->setPosition(m_JoystickLeftPos + (direction * distance));
        }
        else {
            m_pJoystickLeft->setPosition(m_JoystickLeftPos + (direction * m_fRadius));
        }
        if(m_pJoystickLeftListener)
        {
            if(distance >= m_fMinRadius)
                m_pJoystickLeftListener->onJoystickUpdateDirection(this, direction);
        }
    }

}
void TwoJoysticks::updateJoystickRight(cocos2d::Touch* touch)
{
    if(touch && m_pJoystickRight && m_pJoystickRightBg)
    {
        Vec2 hit = touch->getLocation();
        float distance = m_JoystickRightPos.getDistance(hit);
        Vec2 direction = (hit - m_JoystickRightPos).getNormalized();
        
        if(distance < m_fRadius)
        {
            m_pJoystickRight->setPosition(m_JoystickRightPos + (direction * distance));
        }
        else {
            m_pJoystickRight->setPosition(m_JoystickRightPos + (direction * m_fRadius));
        }
        if(m_pJoystickRightListener)
        {
            if(distance >= m_fMinRadius)
                m_pJoystickRightListener->onJoystickUpdateOrientation(this, direction);
            m_fPressTime += Director::getInstance()->getDeltaTime();
            m_pJoystickRightListener->onJoystickPressed(this, m_fPressTime);
        }
    }

}

void TwoJoysticks::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
    for (int i = 0; i < touches.size(); ++i) {
        if (m_pJoystickLeft->getBoundingBox().containsPoint(touches[i]->getLocation())) {
            updateJoystickLeft(touches[i]);
        }else if (m_pJoystickRight->getBoundingBox().containsPoint(touches[i]->getLocation())) {
            updateJoystickRight(touches[i]);
        }
    }
}
void TwoJoysticks::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
    auto size = Director::getInstance()->getWinSize();
    for (int i = 0; i < touches.size(); ++i) {
        Vec2 touchPos = touches[i]->getLocation();
        if(touchPos.x < size.width*0.5f)
            updateJoystickLeft(touches[i]);
        else
            updateJoystickRight(touches[i]);
    }
}
void TwoJoysticks::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
    auto size = Director::getInstance()->getWinSize();
    for (int i = 0; i < touches.size(); ++i) {
        
        Vec2 touchPos = touches[i]->getLocation();
        if(touchPos.x < size.width*0.5f)
            m_pJoystickLeft->setPosition(m_JoystickLeftPos);
        else
            m_pJoystickRight->setPosition(m_JoystickRightPos);
        
        if(m_pJoystickLeftListener)
        {
            m_pJoystickLeftListener->onJoystickUpdateDirection(this, Vec2::ZERO);
        }
        if(m_pJoystickRightListener)
        {
            m_pJoystickRightListener->onJoystickUpdateOrientation(this, Vec2::ZERO);
            m_pJoystickRightListener->onJoystickReleased(this, m_fPressTime);
            m_fPressTime = 0.0f;
        }
    }
}