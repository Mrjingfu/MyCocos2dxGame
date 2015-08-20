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
#include "storage/local-storage/LocalStorage.h"
#include "AudioEngine.h"
#include "SdkBoxManager.h"
USING_NS_CC;
using namespace experimental;

SkillButton* SkillButton::create(const std::string& btnTex, const std::string& maskTex,  const std::string& colorTex)
{
    SkillButton *pRet = new(std::nothrow) SkillButton();
    if (pRet && pRet->init(btnTex, maskTex, colorTex))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

SkillButton::SkillButton()
{
    m_pRootNode = nullptr;
    m_pBtnSprite = nullptr;
    m_pMaskSprite = nullptr;
    m_pColorSprite = nullptr;
    m_pStepSprite = nullptr;
    m_pProgressTimer = nullptr;
    int maxLevel = Value(localStorageGetItem(USER_MAX_LEVEL)).asInt();
    if(maxLevel == 0)
        m_fCurrentRainbowValue = 75.0f;
    else
        m_fCurrentRainbowValue = 100.0f;
    m_bTouchEnable = false;
}



bool SkillButton::init(const std::string& btnTex, const std::string& maskTex,  const std::string& colorTex)
{
    m_pRootNode = Node::create();
    if(!m_pRootNode)
        return false;
    addChild(m_pRootNode);
    m_pBtnSprite = HueSprite::create(btnTex);
    if(!m_pBtnSprite)
        return false;
    //m_pBtnSprite->setHue(M_PI);
    m_pBtnSprite->setAnchorPoint(Vec2(0,0));
    m_pRootNode->addChild(m_pBtnSprite);
    
    m_pColorSprite = Sprite::create(colorTex);
    if(!m_pColorSprite)
        return false;
    m_pRootNode->addChild(m_pColorSprite);
    m_pColorSprite->setOpacity(200);
    RepeatForever* repeat = RepeatForever::create(RotateBy::create(1.0f, 180));
    m_pColorSprite->runAction(repeat);
    
    m_pStepSprite = Sprite::create(colorTex);
    if(!m_pStepSprite)
        return false;
    m_pStepSprite->setColor(Color3B::BLACK);
    m_pProgressTimer = ProgressTimer::create(m_pStepSprite);
    if(!m_pProgressTimer)
        return false;
    m_pProgressTimer->setReverseProgress(true);
    m_pProgressTimer->setPercentage(m_fCurrentRainbowValue);
    m_pRootNode->addChild(m_pProgressTimer);
    
    m_pMaskSprite = Sprite::create(maskTex);
    if(!m_pMaskSprite)
        return false;
    m_pMaskSprite->setAnchorPoint(Vec2(0,0));
    m_pRootNode->addChild(m_pMaskSprite);
    m_pRootNode->setScale(0.3f);
    
    m_pRootNode->runAction(EaseBackInOut::create(ScaleTo::create(0.5f, 0.7f)));
    
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
        m_fCurrentRainbowValue -=0.5f;
        m_pProgressTimer->setPercentage(m_fCurrentRainbowValue);
        if(m_fCurrentRainbowValue <= 75.0f)
        {
            if(!m_bTouchEnable)
            {
                m_bTouchEnable = true;
                m_pRootNode->runAction(EaseBackInOut::create(ScaleTo::create(0.5f, 1.0f)));
                m_pMaskSprite->runAction(EaseSineOut::create(FadeOut::create(0.5f)));
                AudioEngine::play2d("rainbowmodeok.wav", false, 0.5f);
            }
        }
    }
}
bool SkillButton::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!touch)
        return false;
    
    Vec2 touchPoint = m_pBtnSprite->convertTouchToNodeSpaceAR(touch);
    cocos2d::Rect bbox = m_pBtnSprite->getBoundingBox();
    if(!bbox.containsPoint(touchPoint))
        return false;
    
    if(m_bTouchEnable)
    {
        m_fCurrentRainbowValue = 100.0f;
        m_pProgressTimer->setPercentage(m_fCurrentRainbowValue);
        m_bTouchEnable = false;
        m_pRootNode->runAction(EaseBackInOut::create(ScaleTo::create(0.5f, 0.7f)));
        m_pMaskSprite->runAction(EaseSineOut::create(FadeIn::create(0.5f)));
        RunController::getInstance()->showRainbow();
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
        SdkBoxManager::getInstance()->logEvent("Run Game", "In Game", "Show Rainbow", 1);
#endif
    }
    return true;
}