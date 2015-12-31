//
//  ScreenShake.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/29.
//
//

#include "CircleMoveAct.hpp"
USING_NS_CC;
CircleMoveAct* CircleMoveAct::create(float duration, const cocos2d::Vec2 &center, float scale, float angle)
{
    CircleMoveAct* pRet = new CircleMoveAct();
    pRet->initWithDuration( duration, center,  scale,  angle);
    pRet->autorelease();
    return pRet;
}

bool CircleMoveAct::initWithDuration(float duration, const cocos2d::Vec2 &center, float scaleDiff, float angle)
{
    if (ActionInterval::initWithDuration(duration)) {
        this->m_duration = duration;
        this->m_center = center;
        this->m_scaleDiff = scaleDiff;
        this->m_currScale = 1.0f;
        this->m_angle = angle;
        //计算每次update调用时需要转动的弧度
        this->m_anglePreFrame = angle / duration * Director::getInstance()->getAnimationInterval() / (180 / M_PI);
        this->m_frameCnts = 0;
        return true;
    }
    return false;
}
CircleMoveAct* CircleMoveAct::clone() const
{
    auto pRet = new CircleMoveAct();
    pRet->initWithDuration(m_duration, m_center, m_scaleDiff, m_angle);
    pRet->autorelease();
    return pRet;
}
CircleMoveAct* CircleMoveAct::reverse() const
{
    return  CircleMoveAct::create(m_duration, m_center, m_scaleDiff, -m_angle);
}

void CircleMoveAct::startWithTarget(cocos2d::Node *target)
{
    ActionInterval::startWithTarget(target);
    m_initPos = target->getPosition();
}
void CircleMoveAct::stop(void)
{
    
    ActionInterval::stop();

}
void CircleMoveAct::update(float time)
{
    m_frameCnts++;
    m_currScale += m_scaleDiff;
    
    cocos2d::Vec2 newPos =  m_initPos.rotateByAngle (m_center, m_frameCnts * m_anglePreFrame);
    Vec2 diff = newPos - m_center;
    newPos = diff * m_currScale + m_center;
    _target->setPosition(newPos);
    //debug
//#if 0
    DrawNode *node = DrawNode::create();
    node->clear();
    node->setCameraMask((unsigned int)CameraFlag::USER2);
    node->drawDot(newPos,3,Color4F(128,128,128,128));
    _target->getParent()->addChild(node);
//#endif

}
