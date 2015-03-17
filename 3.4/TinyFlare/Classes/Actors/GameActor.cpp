//
//  GameActor.cpp
//  Geometry-Wars
//
//  Created by wang haibo on 15/2/5.
//
//

#include "GameActor.h"
USING_NS_CC;

GameActor::GameActor()
{
    m_type = AT_UNKNOWN;
    m_pModel = nullptr;
    m_Orientation = Vec2::UNIT_Y;
    m_Direction = Vec2::ZERO;
    m_Velocity = Vec2::ZERO;
    m_fAccel = 20.0f;
    m_fDecel = -5.0f;
    m_fRadius = 0.0f;
    m_fMaxSpeed = 1.0f;
    m_bBounce = false;
}
GameActor::~GameActor()
{
}
void GameActor::onEnter()
{
    Node::onEnter();
    scheduleUpdate();
}
void GameActor::onExit()
{
    unscheduleUpdate();
    Node::onExit();
}
void GameActor::loadModel(const std::string& texName)
{
    if(m_pModel)
    {
        removeChild(m_pModel);
        m_pModel = nullptr;
    }
    m_pModel = Sprite::create(texName);
    if(m_pModel == nullptr)
        CCLOGERROR("Load model %s failed!" , texName.c_str());
    m_pModel->setScale(0.5f);
    addChild(m_pModel);
    caculateRadius();
}
void GameActor::loadModel(const std::string& texName, const cocos2d::Rect& rect)
{
    if(m_pModel)
    {
        removeChild(m_pModel);
        m_pModel = nullptr;
    }
    m_pModel = Sprite::create(texName, rect);
    if(m_pModel == nullptr)
        CCLOGERROR("Load model %s failed!" , texName.c_str());
    addChild(m_pModel);
    caculateRadius();
}
void GameActor::setBounce(bool bounce)
{
    m_bBounce = bounce;
    if(m_bBounce)
    {
        
    }
}
void GameActor::caculateRadius()
{
    if (m_pModel) {
        Rect rect = m_pModel->getBoundingBox();
        Vec2 min = Vec2(rect.getMaxX(), rect.getMaxY());
        Vec2 max = Vec2(rect.getMinX(), rect.getMinY());
        m_fRadius = max.distance(min) * 0.5f;
        m_fRadius *= getScale();
    }
}