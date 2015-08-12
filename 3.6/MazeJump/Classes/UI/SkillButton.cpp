//
//  SkillButton.cpp
//  MazeJump
//
//  Created by wang haibo on 15/8/12.
//
//

#include "SkillButton.h"
#include "GameConst.h"
#include "RunController.h"
USING_NS_CC;


SkillButton* SkillButton::create(const std::string& btnTex, const std::string& maskTex)
{
    SkillButton *pRet = new(std::nothrow) SkillButton();
    if (pRet && pRet->init(btnTex, maskTex))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

SkillButton::SkillButton()
{
    m_pBtnSprite = nullptr;
    m_pMaskSprite = nullptr;
    m_pProgressTimer = nullptr;
    m_nCurrentRainbowValue = 100;
    m_bTouchEnable = false;
}



bool SkillButton::init(const std::string& btnTex, const std::string& maskTex)
{
    m_pBtnSprite = Sprite::create(btnTex);
    if(!m_pBtnSprite)
        return false;
    addChild(m_pBtnSprite);
    
    m_pMaskSprite = Sprite::create(maskTex);
    if(!m_pMaskSprite)
        return false;
    
    m_pProgressTimer = ProgressTimer::create(m_pMaskSprite);
    if(!m_pProgressTimer)
        return false;
    m_pProgressTimer->setReverseProgress(true);
    m_pProgressTimer->setPercentage(m_nCurrentRainbowValue);
    addChild(m_pProgressTimer);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    if(touchListener == nullptr)
        return false;
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(SkillButton::onTouchBegan, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void SkillButton::onEnter()
{
    Node::onEnter();
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_RAINBOW_VALUE_CHANGE, std::bind(&SkillButton::onRainbowValueChange, this, std::placeholders::_1));
}
void SkillButton::onExit()
{
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_RAINBOW_VALUE_CHANGE);
    Node::onExit();
}
void SkillButton::onRainbowValueChange(cocos2d::EventCustom* sender)
{
    if(sender && m_pProgressTimer)
    {
        m_nCurrentRainbowValue -=1;
        m_pProgressTimer->setPercentage(m_nCurrentRainbowValue);
        if(m_nCurrentRainbowValue <= 0)
            m_bTouchEnable = true;
    }
}
bool SkillButton::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!touch)
        return false;
    
    Vec2 touchPoint = m_pBtnSprite->convertTouchToNodeSpaceAR(touch);
    Rect bbox = m_pBtnSprite->getBoundingBox();
    if(!bbox.containsPoint(touchPoint))
        return false;
    
    if(m_bTouchEnable)
    {
        m_nCurrentRainbowValue = 100;
        m_pProgressTimer->setPercentage(m_nCurrentRainbowValue);
        m_bTouchEnable = false;
        RunController::getInstance()->showRainbow();
    }
    return true;
}