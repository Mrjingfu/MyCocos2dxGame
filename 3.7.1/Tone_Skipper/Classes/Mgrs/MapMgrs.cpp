//
//  MapMgrs.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/7.
//
//

#include "MapMgrs.h"
USING_NS_CC;
using namespace experimental;

MapMgrs* g_pMapMgrsInstance = nullptr;

MapMgrs* MapMgrs::getInstance()
{
    if( g_pMapMgrsInstance == nullptr )
        g_pMapMgrsInstance = new MapMgrs();
    
    return g_pMapMgrsInstance;
}
MapMgrs::MapMgrs()
{
    m_pMainLayer = nullptr;
    m_pNilo = nullptr;
    
    m_pCurrentTiledMap  = nullptr;
    m_pStarters         = nullptr;
    m_pColliders        = nullptr;
    m_pRayCasters       = nullptr;
    m_pTriggers         = nullptr;
    m_pMonsters         = nullptr;
    m_pDebugDrawNode = nullptr;
}
MapMgrs::~MapMgrs()
{
}
bool MapMgrs::init(cocos2d::Layer* pMainLayer)
{
    if(pMainLayer == nullptr)
        return false;
    m_pMainLayer = pMainLayer;
    return true;
}
bool MapMgrs::loadMap(const std::string& strFile)
{
    unloadMap();
    
    m_pCurrentTiledMap = cocos2d::experimental::TMXTiledMap::create(strFile);
    if(!m_pCurrentTiledMap)
        return false;
    m_pMainLayer->addChild(m_pCurrentTiledMap);
    
    cocos2d::Size mapSize = m_pCurrentTiledMap->getContentSize();
    CCLOG("ContentSize: %f, %f", mapSize.width,mapSize.height);
    
    m_pStarters = m_pCurrentTiledMap->getObjectGroup("starters");
    if(!m_pStarters)
        return false;
    
    m_pColliders = m_pCurrentTiledMap->getObjectGroup("colliders");
    if(!m_pColliders)
        return false;
    
    m_pRayCasters = m_pCurrentTiledMap->getObjectGroup("raycasters");
    if(!m_pRayCasters)
        return false;
    
    m_pTriggers = m_pCurrentTiledMap->getObjectGroup("triggers");
    if(!m_pTriggers)
        return false;
    
    m_pMonsters = m_pCurrentTiledMap->getObjectGroup("monsters");
    if(!m_pMonsters)
        return false;
    
    if(!initPlayer())
        return false;
    
#if COCOS2D_DEBUG
    showDebug(true);
#endif
    
    return true;
}
void MapMgrs::unloadMap()
{
    if(m_pCurrentTiledMap)
    {
        m_pCurrentTiledMap->removeFromParentAndCleanup(true);
        m_pCurrentTiledMap = nullptr;
    }
    m_pCurrentTiledMap = nullptr;
    m_pStarters = nullptr;
    m_pColliders = nullptr;
    m_pRayCasters = nullptr;
    m_pTriggers = nullptr;
    m_pMonsters = nullptr;
}
void MapMgrs::update(float delta)
{
    if(m_pNilo)
        m_pNilo->update(delta);
}
bool MapMgrs::checkRayCast(const Rect& rect, Vec2& velocity, Actor::RAYCAST_TYPE& type, bool ignoreAdjust)
{
    bool ret = false;
    ValueVector colliders = m_pColliders->getObjects();
    for (Value value : colliders) {
        ValueMap valuemap = value.asValueMap();
        if(valuemap.empty())
            continue;
        float x = valuemap.at("x").asFloat();
        float y = valuemap.at("y").asFloat();
        float width = valuemap.at("width").asFloat();
        float height = valuemap.at("height").asFloat();
        Rect colliderRect = Rect(x, y, width, height);
        if (colliderRect.getMaxX() < rect.getMinX() || rect.getMaxX() < colliderRect.getMinX() ||
            colliderRect.getMaxY() < rect.getMinY() || rect.getMaxY() < colliderRect.getMinY()) {
            ret = false;
        }
        else
        {
            if(colliderRect.getMaxX() - rect.getMinX() >= 1 && rect.getMaxX() - colliderRect.getMinX() >= 1)
            {
            if(colliderRect.getMaxY() >= rect.getMinY() && colliderRect.getMaxY() < rect.getMaxY() && velocity.y <= 0)
            {
                if(!ignoreAdjust)
                    velocity.y = velocity.y + colliderRect.getMaxY() - rect.getMinY();
                type = Actor::RT_GROUND;
                ret = true;
                break;
            }
            }
        }
    }
    return ret;
}
bool MapMgrs::checkCollision(const Rect& rect, Vec2& velocity, int& flag)
{
    bool ret = false;
    ValueVector colliders = m_pColliders->getObjects();
    for (Value value : colliders) {
        ValueMap valuemap = value.asValueMap();
        if(valuemap.empty())
            continue;
        float x = valuemap.at("x").asFloat();
        float y = valuemap.at("y").asFloat();
        float width = valuemap.at("width").asFloat();
        float height = valuemap.at("height").asFloat();
        Rect colliderRect = Rect(x, y, width, height);
        if (colliderRect.getMaxX() < rect.getMinX() || rect.getMaxX() < colliderRect.getMinX() ||
            colliderRect.getMaxY() < rect.getMinY() || rect.getMaxY() < colliderRect.getMinY()) {
            continue;
        }
        else
        {
            if(colliderRect.getMaxY() > rect.getMinY())
            {
                if(rect.getMaxX() >= colliderRect.getMinX() && rect.getMinX() < colliderRect.getMinX() && velocity.x >= 0)
                {
                    velocity.x = velocity.x + colliderRect.getMinX() - rect.getMaxX();
                    flag |= CF_RIGHT;
                }
                else if(colliderRect.getMaxX() >= rect.getMinX() && colliderRect.getMaxX() < rect.getMaxX() && velocity.x <= 0)
                {
                    velocity.x = velocity.x + colliderRect.getMaxX() - rect.getMinX();
                    flag |= CF_LEFT;
                }
                ret = true;
                break;
            }
        }
    }
    return ret;
}
bool MapMgrs::checkTrigger(const cocos2d::Rect& rect, Actor::TRIGGER_TYPE& type)
{
    bool ret = false;
    ValueVector triggers = m_pTriggers->getObjects();
    for (Value value : triggers) {
        ValueMap valuemap = value.asValueMap();
        if(valuemap.empty())
            continue;
        float x = valuemap.at("x").asFloat();
        float y = valuemap.at("y").asFloat();
        float width = valuemap.at("width").asFloat();
        float height = valuemap.at("height").asFloat();
        Rect tiggerRect = Rect(x, y, width, height);
        if (tiggerRect.getMaxX() < rect.getMinX() || rect.getMaxX() < tiggerRect.getMinX() ||
            tiggerRect.getMaxY() < rect.getMinY() || rect.getMaxY() < tiggerRect.getMinY()) {
            ret = false;
        }
        else
        {
            type = (Actor::TRIGGER_TYPE)(valuemap.at("type").asInt());
            ret = true;
            break;
        }
    }
    return ret;
}
void MapMgrs::showDebug(bool debug)
{
    if(!m_pMainLayer)
        return;
    if(debug)
    {
        m_pDebugDrawNode = DrawNode::create();
        m_pMainLayer->addChild(m_pDebugDrawNode);
        m_pDebugDrawNode->clear();
        
        ///Starter
        ValueVector starters = m_pStarters->getObjects();
        for (Value value : starters) {
            ValueMap valuemap = value.asValueMap();
            if(valuemap.empty())
                continue;
            float x = valuemap.at("x").asFloat();
            float y = valuemap.at("y").asFloat();
            float width = valuemap.at("width").asFloat();
            float height = valuemap.at("height").asFloat();
            Rect starterRect = Rect(x, y, width, height);
            
            Vec2 vertices[4] = {
                Vec2( starterRect.getMinX(), starterRect.getMinY() ),
                Vec2( starterRect.getMaxX(), starterRect.getMinY() ),
                Vec2( starterRect.getMaxX(), starterRect.getMaxY() ),
                Vec2( starterRect.getMinX(), starterRect.getMaxY() ),
            };
            m_pDebugDrawNode->drawPoly(vertices, 4, true, Color4F::GREEN);
        }
        ///
        ///Collider
        ValueVector colliders = m_pColliders->getObjects();
        for (Value value : colliders) {
            ValueMap valuemap = value.asValueMap();
            if(valuemap.empty())
                continue;
            float x = valuemap.at("x").asFloat();
            float y = valuemap.at("y").asFloat();
            float width = valuemap.at("width").asFloat();
            float height = valuemap.at("height").asFloat();
            Rect colliderRect = Rect(x, y, width, height);
            
            Vec2 vertices[4] = {
                Vec2( colliderRect.getMinX(), colliderRect.getMinY() ),
                Vec2( colliderRect.getMaxX(), colliderRect.getMinY() ),
                Vec2( colliderRect.getMaxX(), colliderRect.getMaxY() ),
                Vec2( colliderRect.getMinX(), colliderRect.getMaxY() ),
            };
            m_pDebugDrawNode->drawPoly(vertices, 4, true, Color4F::RED);
        }
        ////
        ////RayCaster
        ValueVector raycasters = m_pRayCasters->getObjects();
        for (Value value : raycasters) {
            ValueMap valuemap = value.asValueMap();
            if(valuemap.empty())
                continue;
            float x = valuemap.at("x").asFloat();
            float y = valuemap.at("y").asFloat();
            float width = valuemap.at("width").asFloat();
            float height = valuemap.at("height").asFloat();
            Rect colliderRect = Rect(x, y, width, height);
            
            Vec2 vertices[4] = {
                Vec2( colliderRect.getMinX(), colliderRect.getMinY() ),
                Vec2( colliderRect.getMaxX(), colliderRect.getMinY() ),
                Vec2( colliderRect.getMaxX(), colliderRect.getMaxY() ),
                Vec2( colliderRect.getMinX(), colliderRect.getMaxY() ),
            };
            m_pDebugDrawNode->drawPoly(vertices, 4, true, Color4F::BLUE);
        }
        ////
        
        ////trigger
        ValueVector triggers = m_pTriggers->getObjects();
        for (Value value : triggers) {
            ValueMap valuemap = value.asValueMap();
            if(valuemap.empty())
                continue;
            float x = valuemap.at("x").asFloat();
            float y = valuemap.at("y").asFloat();
            float width = valuemap.at("width").asFloat();
            float height = valuemap.at("height").asFloat();
            Rect colliderRect = Rect(x, y, width, height);
            
            Vec2 vertices[4] = {
                Vec2( colliderRect.getMinX(), colliderRect.getMinY() ),
                Vec2( colliderRect.getMaxX(), colliderRect.getMinY() ),
                Vec2( colliderRect.getMaxX(), colliderRect.getMaxY() ),
                Vec2( colliderRect.getMinX(), colliderRect.getMaxY() ),
            };
            m_pDebugDrawNode->drawPoly(vertices, 4, true, Color4F::YELLOW);
        }
        ////
    }
    else
    {
        if(m_pDebugDrawNode)
        {
            m_pDebugDrawNode->clear();
            m_pDebugDrawNode->removeFromParentAndCleanup(true);
            m_pDebugDrawNode = nullptr;
        }
    }
}
bool MapMgrs::initPlayer()
{
    if(!m_pMainLayer || !m_pStarters)
        return false;
    
    ValueMap start_born = m_pStarters->getObject("start_born");
    if(start_born.empty())
        return false;
    bool flip_x = start_born.at("flip_x").asBool();
    float x = start_born.at("x").asFloat();
    float y = start_born.at("y").asFloat();
    float width = start_born.at("width").asFloat();
    float height = start_born.at("height").asFloat();
    Rect colliderRect = Rect(x, y, width, height);
    m_pNilo = ActorFactory::getInstance()->createPlayer(Player::PT_NILO);
    if(!m_pNilo)
        return false;
    m_pNilo->setPosition(Vec2(colliderRect.getMidX(),y));
    m_pNilo->setFlipX(flip_x);
    m_pMainLayer->addChild(m_pNilo);
    return true;
}