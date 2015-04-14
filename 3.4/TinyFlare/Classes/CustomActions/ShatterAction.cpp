//
//  ShatterAction.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/14.
//
//

#include "ShatterAction.h"
#include "ShatterSprite.h"
USING_NS_CC;

ShatterAction::ShatterAction()
{
    m_fTimeFoe = 0.0f;
    m_fTimeCur = 0.0f;
    m_fGrowSpeedOfTargetR = 5000;
}
ShatterAction::~ShatterAction()
{
}

ShatterAction* ShatterAction::create(float duration)
{
    ShatterAction *pRet = new(std::nothrow) ShatterAction();
    if (pRet && pRet->initWithDuration(duration))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}
void ShatterAction::stop()
{
    ShatterSprite* pSprite = static_cast<ShatterSprite*>(_target);
    if(pSprite)
        pSprite->m_pFragBatchNode->setVisible(true);
    CCActionInterval::stop();
}
void ShatterAction::startWithTarget(cocos2d::Node* target)
{
    ShatterSprite* pSprite = static_cast<ShatterSprite*>(target);
    if(pSprite)
    {
        pSprite->resetShatter();
        pSprite->m_pFragBatchNode->setVisible(true);
    }
    CCActionInterval::startWithTarget(target);
}
void ShatterAction::update(float delta)
{
    m_fTimeFoe = m_fTimeCur;
    float progressPercentage = delta;
    m_fTimeCur=progressPercentage*getDuration();
    ShatterSprite* pSprite = static_cast<ShatterSprite*>(_target);
    if(pSprite)
        pSprite->updateShatterAction(m_fTimeCur, m_fTimeCur - m_fTimeFoe, m_fGrowSpeedOfTargetR);
}
