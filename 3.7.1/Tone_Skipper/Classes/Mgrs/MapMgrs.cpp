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
    
    m_pCurrentTiledMap = nullptr;
    m_pStarters = nullptr;
    m_pColliders = nullptr;
    m_pMonsters = nullptr;
    m_pAvalidObjects = nullptr;
    m_pItemObjects = nullptr;
    m_pTriggers = nullptr;
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
    
    if(!initPlayer())
        return false;
    
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
    m_pMonsters = nullptr;
    m_pAvalidObjects = nullptr;
    m_pItemObjects = nullptr;
    m_pTriggers = nullptr;
}
void MapMgrs::update(float delta)
{
    if(m_pNilo)
        m_pNilo->update(delta);
}
bool MapMgrs::checkCollision(const Rect& rect, int& flag, Actor::RAYCAST_TYPE& type)
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
            if(colliderRect.getMaxX() >= rect.getMinX()|| rect.getMaxX() >= colliderRect.getMinX())
            {
                if(colliderRect.getMaxY() >= rect.getMinY() || rect.getMaxY() >= colliderRect.getMinY())
                    flag |= CF_LAND;
            }
            type = (Actor::RAYCAST_TYPE)valuemap.at("type").asInt();
            ret = true;
            break;
        }
    }
    return ret;
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
    m_pNilo = ActorFactory::getInstance()->createPlayer(Player::PT_NILO);
    if(!m_pNilo)
        return false;
    m_pNilo->setPosition(Vec2(x, y));
    m_pNilo->setFlipX(flip_x);
    m_pMainLayer->addChild(m_pNilo);
    return true;
}