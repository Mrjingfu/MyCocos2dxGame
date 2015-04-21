//
//  BufferContainer.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/20.
//
//

#include "BufferContainer.h"
USING_NS_CC;

BufferContainer* BufferContainer::create()
{
    BufferContainer *pRet = new(std::nothrow) BufferContainer();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

BufferContainer::BufferContainer()
{
    m_pAccelIcon        = nullptr;
    m_pMultiIcon        = nullptr;
    m_pProtectedIcon    = nullptr;
    m_pTimeIcon         = nullptr;
    m_nCurrentShowNum   = 0;
}
BufferContainer::~BufferContainer()
{
}
bool BufferContainer::init()
{
    m_pAccelIcon = Node::create();
    if(!m_pAccelIcon)
        return false;
    auto bound = ui::ImageView::create("bound.png");
    if(!bound)
        return false;
    auto accel = ui::ImageView::create("accel.png");
    if(!accel)
        return false;
    m_pAccelIcon->addChild(bound);
    m_pAccelIcon->addChild(accel);
    addChild(m_pAccelIcon);
    m_pAccelIcon->setPosition(Vec2::ZERO);
    m_pAccelIcon->setCascadeOpacityEnabled(true);
    m_pAccelIcon->setOpacity(0);
    m_pAccelIcon->setVisible(false);
    m_pAccelIcon->setTag(0);
    
    m_SizeBound = bound->getContentSize();
    
    m_pMultiIcon = Node::create();
    if(!m_pMultiIcon)
        return false;
    bound = ui::ImageView::create("bound.png");
    if(!bound)
        return false;
    auto multi = ui::ImageView::create("multi.png");
    if(!multi)
        return false;
    m_pMultiIcon->addChild(bound);
    m_pMultiIcon->addChild(multi);
    addChild(m_pMultiIcon);
    m_pMultiIcon->setPosition(m_pAccelIcon->getPosition() + Vec2(m_SizeBound.width, 0));
    m_pMultiIcon->setCascadeOpacityEnabled(true);
    m_pMultiIcon->setOpacity(0);
    m_pMultiIcon->setVisible(false);
    m_pMultiIcon->setTag(1);
    
    m_pProtectedIcon = Node::create();
    if(!m_pProtectedIcon)
        return false;
    bound = ui::ImageView::create("bound.png");
    if(!bound)
        return false;
    auto protect = ui::ImageView::create("protected.png");
    if(!protect)
        return false;
    m_pProtectedIcon->addChild(bound);
    m_pProtectedIcon->addChild(protect);
    addChild(m_pProtectedIcon);
    m_pProtectedIcon->setPosition(m_pMultiIcon->getPosition() + Vec2(m_SizeBound.width, 0));
    m_pProtectedIcon->setCascadeOpacityEnabled(true);
    m_pProtectedIcon->setOpacity(0);
    m_pProtectedIcon->setVisible(false);
    m_pProtectedIcon->setTag(2);
    
    m_pTimeIcon = Node::create();
    if(!m_pTimeIcon)
        return false;
    bound = ui::ImageView::create("bound.png");
    if(!bound)
        return false;
    auto time = ui::ImageView::create("time.png");
    if(!time)
        return false;
    m_pTimeIcon->addChild(bound);
    m_pTimeIcon->addChild(time);
    addChild(m_pTimeIcon);
    m_pTimeIcon->setPosition(m_pProtectedIcon->getPosition() + Vec2(m_SizeBound.width, 0));
    m_pTimeIcon->setCascadeOpacityEnabled(true);
    m_pTimeIcon->setOpacity(0);
    m_pTimeIcon->setVisible(false);
    m_pTimeIcon->setTag(3);
    
    return true;
}
void BufferContainer::showAccel(float time)
{
    if(m_pAccelIcon)
    {
        hideAccel();
        m_pAccelIcon->stopAllActions();
        m_pAccelIcon->setTag(m_nCurrentShowNum);
        Vec2 startPos = Vec2(m_SizeBound.width*5, m_pAccelIcon->getPosition().y);
        m_pAccelIcon->setPosition(startPos);
        Vec2 targetPos = Vec2(m_SizeBound.width*(m_nCurrentShowNum), m_pAccelIcon->getPosition().y);
        FadeIn* fadeIn = FadeIn::create(0.5f*_scheduler->getTimeScale());
        EaseSineOut* easeOut = EaseSineOut::create(fadeIn);
        MoveTo* moveTo = MoveTo::create(0.5f*_scheduler->getTimeScale(), targetPos);
        DelayTime* delay = DelayTime::create(time-5.0f);
        CallFunc* callfunc = CallFunc::create(CC_CALLBACK_0(BufferContainer::flashAccel, this));
        Sequence* sequence = Sequence::createWithTwoActions(delay, callfunc);
        Spawn* spawn = Spawn::create(easeOut, moveTo, sequence, NULL);
        m_pAccelIcon->runAction(spawn);
        if(!m_pAccelIcon->isVisible())
        {
            m_pAccelIcon->setVisible(true);
            m_nCurrentShowNum++;
        }
    }
}
void BufferContainer::flashAccel()
{
    if(m_pAccelIcon)
    {
        m_pAccelIcon->stopAllActions();
        EaseSineOut* easeOut1 = EaseSineOut::create(FadeIn::create(0.4f*_scheduler->getTimeScale()));
        EaseSineOut* easeOut2 = EaseSineOut::create(FadeOut::create(0.4f*_scheduler->getTimeScale()));
        DelayTime* delay = DelayTime::create(0.2f*_scheduler->getTimeScale());
        Sequence* sequence = Sequence::create(easeOut1, delay, easeOut2, NULL);
        RepeatForever* repeat = RepeatForever::create(sequence);
        m_pAccelIcon->runAction(repeat);
    }
}
void BufferContainer::hideAccel()
{
    if(m_pAccelIcon)
    {
        m_pAccelIcon->stopAllActions();
        if(m_pAccelIcon->isVisible())
        {
            m_pAccelIcon->setVisible(false);
            m_nCurrentShowNum--;
            if(m_pMultiIcon->isVisible() && m_pMultiIcon->getTag() > m_pAccelIcon->getTag() )
            {
                m_pMultiIcon->setPosition(m_pMultiIcon->getPosition() - Vec2(m_SizeBound.width, 0));
                m_pMultiIcon->setTag(m_pMultiIcon->getTag() -1);
            }
            if(m_pProtectedIcon->isVisible() && m_pProtectedIcon->getTag() > m_pAccelIcon->getTag() )
            {
                m_pProtectedIcon->setPosition(m_pProtectedIcon->getPosition() - Vec2(m_SizeBound.width, 0));
                m_pProtectedIcon->setTag(m_pProtectedIcon->getTag() - 1);
            }
            if(m_pTimeIcon->isVisible() && m_pTimeIcon->getTag() > m_pAccelIcon->getTag())
            {
                m_pTimeIcon->setPosition(m_pTimeIcon->getPosition() - Vec2(m_SizeBound.width, 0));
                m_pTimeIcon->setTag(m_pTimeIcon->getTag() - 1);
            }
        }
    }
}

void BufferContainer::showMulti(float time)
{
    if(m_pMultiIcon)
    {
        hideMulti();
        m_pMultiIcon->stopAllActions();
        m_pMultiIcon->setTag(m_nCurrentShowNum);
        Vec2 startPos = Vec2(m_SizeBound.width*5, m_pMultiIcon->getPosition().y);
        m_pMultiIcon->setPosition(startPos);
        Vec2 targetPos = Vec2(m_SizeBound.width*(m_nCurrentShowNum), m_pMultiIcon->getPosition().y);
        FadeIn* fadeIn = FadeIn::create(0.5f*_scheduler->getTimeScale());
        EaseSineOut* easeOut = EaseSineOut::create(fadeIn);
        MoveTo* moveTo = MoveTo::create(0.5f*_scheduler->getTimeScale(), targetPos);
        DelayTime* delay = DelayTime::create(time-5.0f);
        CallFunc* callfunc = CallFunc::create(CC_CALLBACK_0(BufferContainer::flashMulti, this));
        Sequence* sequence = Sequence::createWithTwoActions(delay, callfunc);
        Spawn* spawn = Spawn::create(easeOut, moveTo, sequence, NULL);
        m_pMultiIcon->runAction(spawn);
        if(!m_pMultiIcon->isVisible())
        {
            m_pMultiIcon->setVisible(true);
            m_nCurrentShowNum++;
        }
    }
}
void BufferContainer::flashMulti()
{
    if(m_pMultiIcon)
    {
        m_pMultiIcon->stopAllActions();
        EaseSineOut* easeOut1 = EaseSineOut::create(FadeIn::create(0.4f*_scheduler->getTimeScale()));
        EaseSineOut* easeOut2 = EaseSineOut::create(FadeOut::create(0.4f*_scheduler->getTimeScale()));
        DelayTime* delay = DelayTime::create(0.2f*_scheduler->getTimeScale());
        Sequence* sequence = Sequence::create(easeOut1, delay, easeOut2, NULL);
        RepeatForever* repeat = RepeatForever::create(sequence);
        m_pMultiIcon->runAction(repeat);
    }
}
void BufferContainer::hideMulti()
{
    if(m_pMultiIcon)
    {
        m_pMultiIcon->stopAllActions();
        if(m_pMultiIcon->isVisible())
        {
            m_pMultiIcon->setVisible(false);
            m_nCurrentShowNum--;
            if(m_pAccelIcon->isVisible() && m_pAccelIcon->getTag() > m_pMultiIcon->getTag())
            {
                m_pAccelIcon->setPosition(m_pAccelIcon->getPosition() - Vec2(m_SizeBound.width, 0));
                m_pAccelIcon->setTag(m_pAccelIcon->getTag() - 1);
            }
            if(m_pProtectedIcon->isVisible() && m_pProtectedIcon->getTag() > m_pMultiIcon->getTag())
            {
                m_pProtectedIcon->setPosition(m_pProtectedIcon->getPosition() - Vec2(m_SizeBound.width, 0));
                m_pProtectedIcon->setTag(m_pProtectedIcon->getTag() - 1);
            }
            if(m_pTimeIcon->isVisible() && m_pTimeIcon->getTag() > m_pMultiIcon->getTag())
            {
                m_pTimeIcon->setPosition(m_pTimeIcon->getPosition() - Vec2(m_SizeBound.width, 0));
                m_pTimeIcon->setTag(m_pTimeIcon->getTag() - 1);
            }
        }
    }
}

void BufferContainer::showProtected(float time)
{
    if(m_pProtectedIcon)
    {
        hideProtected();
        m_pProtectedIcon->stopAllActions();
        m_pProtectedIcon->setTag(m_nCurrentShowNum);
        Vec2 startPos = Vec2(m_SizeBound.width*5, m_pProtectedIcon->getPosition().y);
        m_pProtectedIcon->setPosition(startPos);
        Vec2 targetPos = Vec2(m_SizeBound.width*(m_nCurrentShowNum), m_pProtectedIcon->getPosition().y);
        FadeIn* fadeIn = FadeIn::create(0.5f*_scheduler->getTimeScale());
        EaseSineOut* easeOut = EaseSineOut::create(fadeIn);
        MoveTo* moveTo = MoveTo::create(0.5f*_scheduler->getTimeScale(), targetPos);
        DelayTime* delay = DelayTime::create(time-5.0f);
        CallFunc* callfunc = CallFunc::create(CC_CALLBACK_0(BufferContainer::flashProtected, this));
        Sequence* sequence = Sequence::createWithTwoActions(delay, callfunc);
        Spawn* spawn = Spawn::create(easeOut, moveTo, sequence, NULL);
        m_pProtectedIcon->runAction(spawn);
        if(!m_pProtectedIcon->isVisible())
        {
            m_pProtectedIcon->setVisible(true);
            m_nCurrentShowNum++;
        }
    }

}
void BufferContainer::flashProtected()
{
    if(m_pProtectedIcon)
    {
        m_pProtectedIcon->stopAllActions();
        EaseSineOut* easeOut1 = EaseSineOut::create(FadeIn::create(0.4f*_scheduler->getTimeScale()));
        EaseSineOut* easeOut2 = EaseSineOut::create(FadeOut::create(0.4f*_scheduler->getTimeScale()));
        DelayTime* delay = DelayTime::create(0.2f*_scheduler->getTimeScale());
        Sequence* sequence = Sequence::create(easeOut1, delay, easeOut2, NULL);
        RepeatForever* repeat = RepeatForever::create(sequence);
        m_pProtectedIcon->runAction(repeat);
    }

}
void BufferContainer::hideProtected()
{
    if(m_pProtectedIcon)
    {
        m_pProtectedIcon->stopAllActions();
        if(m_pProtectedIcon->isVisible())
        {
            m_pProtectedIcon->setVisible(false);
            m_nCurrentShowNum--;
            if(m_pAccelIcon->isVisible() && m_pAccelIcon->getTag() > m_pProtectedIcon->getTag())
            {
                m_pAccelIcon->setPosition(m_pAccelIcon->getPosition() - Vec2(m_SizeBound.width, 0));
                m_pAccelIcon->setTag(m_pAccelIcon->getTag() - 1);
            }
            if(m_pMultiIcon->isVisible() && m_pMultiIcon->getTag() > m_pProtectedIcon->getTag())
            {
                m_pMultiIcon->setPosition(m_pMultiIcon->getPosition() - Vec2(m_SizeBound.width, 0));
                m_pMultiIcon->setTag(m_pMultiIcon->getTag() - 1);
            }
            if(m_pTimeIcon->isVisible() && m_pTimeIcon->getTag() > m_pProtectedIcon->getTag())
            {
                m_pTimeIcon->setPosition(m_pTimeIcon->getPosition() - Vec2(m_SizeBound.width, 0));
                m_pTimeIcon->setTag(m_pTimeIcon->getTag() - 1);
            }
        }
    }
}

void BufferContainer::showTime(float time)
{
    if(m_pTimeIcon)
    {
        hideTime();
        m_pTimeIcon->stopAllActions();
        m_pTimeIcon->setTag(m_nCurrentShowNum);
        Vec2 startPos = Vec2(m_SizeBound.width*5, m_pTimeIcon->getPosition().y);
        m_pTimeIcon->setPosition(startPos);
        Vec2 targetPos = Vec2(m_SizeBound.width*(m_nCurrentShowNum), m_pTimeIcon->getPosition().y);
        FadeIn* fadeIn = FadeIn::create(0.5f*_scheduler->getTimeScale());
        EaseSineOut* easeOut = EaseSineOut::create(fadeIn);
        MoveTo* moveTo = MoveTo::create(0.5f*_scheduler->getTimeScale(), targetPos);
        DelayTime* delay = DelayTime::create(time-5.0f);
        CallFunc* callfunc = CallFunc::create(CC_CALLBACK_0(BufferContainer::flashTime, this));
        Sequence* sequence = Sequence::createWithTwoActions(delay, callfunc);
        Spawn* spawn = Spawn::create(easeOut, moveTo, sequence, NULL);
        m_pTimeIcon->runAction(spawn);
        if(!m_pTimeIcon->isVisible())
        {
            m_pTimeIcon->setVisible(true);
            m_nCurrentShowNum++;
        }
    }
}
void BufferContainer::flashTime()
{
    if(m_pTimeIcon)
    {
        m_pTimeIcon->stopAllActions();
        EaseSineOut* easeOut1 = EaseSineOut::create(FadeIn::create(0.4f*_scheduler->getTimeScale()));
        EaseSineOut* easeOut2 = EaseSineOut::create(FadeOut::create(0.4f*_scheduler->getTimeScale()));
        DelayTime* delay = DelayTime::create(0.2f*_scheduler->getTimeScale());
        Sequence* sequence = Sequence::create(easeOut1, delay, easeOut2, NULL);
        RepeatForever* repeat = RepeatForever::create(sequence);
        m_pTimeIcon->runAction(repeat);
    }

}
void BufferContainer::hideTime()
{
    if(m_pTimeIcon)
    {
        m_pTimeIcon->stopAllActions();
        if(m_pTimeIcon->isVisible())
        {
            m_pTimeIcon->setVisible(false);
            m_nCurrentShowNum--;
            if(m_pAccelIcon->isVisible() && m_pAccelIcon->getTag() > m_pTimeIcon->getTag())
            {
                m_pAccelIcon->setPosition(m_pAccelIcon->getPosition() - Vec2(m_SizeBound.width, 0));
                m_pAccelIcon->setTag(m_pAccelIcon->getTag() - 1);
            }
            if(m_pMultiIcon->isVisible() && m_pMultiIcon->getTag() > m_pTimeIcon->getTag())
            {
                m_pMultiIcon->setPosition(m_pMultiIcon->getPosition() - Vec2(m_SizeBound.width, 0));
                m_pMultiIcon->setTag(m_pMultiIcon->getTag() - 1);
            }
            if(m_pProtectedIcon->isVisible() && m_pProtectedIcon->getTag() > m_pTimeIcon->getTag())
            {
                m_pProtectedIcon->setPosition(m_pProtectedIcon->getPosition() - Vec2(m_SizeBound.width, 0));
                m_pProtectedIcon->setTag(m_pProtectedIcon->getTag() - 1);
            }
        }
    }
}