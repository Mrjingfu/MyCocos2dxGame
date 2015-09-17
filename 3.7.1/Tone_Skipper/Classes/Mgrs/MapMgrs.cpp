//
//  MapMgrs.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/7.
//
//

#include "MapMgrs.h"
#include "UtilityHelper.h"
USING_NS_CC;

MapMgrs* g_pMapMgrsInstance = nullptr;

MapMgrs* MapMgrs::getInstance()
{
    if( g_pMapMgrsInstance == nullptr )
        g_pMapMgrsInstance = new MapMgrs();
    
    return g_pMapMgrsInstance;
}
MapMgrs::MapMgrs()
{
    m_MaskColorType = MCT_NONE;
    m_pBackgroundColorMaskLayer = nullptr;
    m_pMainLayer = nullptr;
    m_pNilo = nullptr;
    m_pMainCamera = nullptr;
    
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
    
    Color3B maskColor = Color3B::BLACK;
    switch (m_MaskColorType) {
        case MCT_RED:
            maskColor = UtilityHelper::randomRedColor();
            break;
        case MCT_ORANGE:
            maskColor = UtilityHelper::randomOrangeColor();
            break;
        case MCT_YELLOW:
            maskColor = UtilityHelper::randomYellowColor();
            break;
        case MCT_GREEN:
            maskColor = UtilityHelper::randomGreenColor();
            break;
        case MCT_CYAN:
            maskColor = UtilityHelper::randomCyanColor();
            break;
        case MCT_BLUE:
            maskColor = UtilityHelper::randomBlueColor();
            break;
        case MCT_PURPLE:
            maskColor = UtilityHelper::randomPurpleColor();
            break;
        case MCT_RANDOM:
            maskColor = UtilityHelper::randomColor();
            break;
        default:
            break;
    }
    m_pBackgroundColorMaskLayer = LayerColor::create(Color4B(maskColor.r, maskColor.g, maskColor.b, 50));
    if(!m_pBackgroundColorMaskLayer)
        return false;
    m_pBackgroundColorMaskLayer->setBlendFunc(BlendFunc::ADDITIVE);
    m_pMainLayer->addChild(m_pBackgroundColorMaskLayer);
    
    if(!initCamera())
        return false;
    return true;
}
bool MapMgrs::loadMap(const std::string& strFile)
{
    unloadMap();
    
    m_pCurrentTiledMap = cocos2d::TMXTiledMap::create(strFile);
    if(!m_pCurrentTiledMap)
        return false;
    m_pCurrentTiledMap->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pMainLayer->addChild(m_pCurrentTiledMap);
    
    m_MaskColorType = (MaskColorType)(m_pCurrentTiledMap->getProperty("maskcolor_typ").asInt());
    
    cocos2d::Size mapSize = m_pCurrentTiledMap->getMapSize();
    cocos2d::Size tileSize = m_pCurrentTiledMap->getTileSize();
    
    CCLOG("ContentSize: %f, %f", mapSize.width,mapSize.height);
    m_pMapRect = cocos2d::Rect(0,0,mapSize.width*tileSize.width,mapSize.height*tileSize.height);
    
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
    
    if(!initColorMask())
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
    updatePlayers(delta);
    updateCamera(delta);
}
bool MapMgrs::checkRayCast(const cocos2d::Rect& rect, Vec2& velocity, Actor::RAYCAST_TYPE& type, bool ignoreAdjust)
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
        cocos2d::Rect colliderRect = cocos2d::Rect(x, y, width, height);
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
bool MapMgrs::checkCollision(const cocos2d::Rect& rect, Vec2& velocity, int& flag)
{
    bool ret = false;
    if(!ret)
    {
        if(rect.getMaxX() >= m_pMapRect.getMaxX() && velocity.x >= 0)
        {
            velocity.x = velocity.x + m_pMapRect.getMaxX() - rect.getMaxX();
            flag |= CF_BOUND;
            ret = true;
            return ret;
        }
        else if(m_pMapRect.getMinX() >= rect.getMinX() && velocity.x <= 0)
        {
            velocity.x = velocity.x + m_pMapRect.getMinX() - rect.getMinX();
            flag |= CF_BOUND;
            ret = true;
            return ret;
        }
    }
    ValueVector colliders = m_pColliders->getObjects();
    for (Value value : colliders) {
        ValueMap valuemap = value.asValueMap();
        if(valuemap.empty())
            continue;
        float x = valuemap.at("x").asFloat();
        float y = valuemap.at("y").asFloat();
        float width = valuemap.at("width").asFloat();
        float height = valuemap.at("height").asFloat();
        cocos2d::Rect colliderRect = cocos2d::Rect(x, y, width, height);
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
        cocos2d::Rect tiggerRect = cocos2d::Rect(x, y, width, height);
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
        m_pDebugDrawNode->setCameraMask((unsigned short)CameraFlag::USER1);
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
            cocos2d::Rect starterRect = cocos2d::Rect(x, y, width, height);
            
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
            cocos2d::Rect colliderRect = cocos2d::Rect(x, y, width, height);
            
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
            cocos2d::Rect colliderRect = cocos2d::Rect(x, y, width, height);
            
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
            cocos2d::Rect colliderRect = cocos2d::Rect(x, y, width, height);
            
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
bool MapMgrs::initCamera()
{
    if(!m_pMainLayer)
        return false;
    m_pMainCamera = Camera::create();
    if(!m_pMainCamera)
        return false;
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    m_pMainLayer->addChild(m_pMainCamera);
    return true;
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
    cocos2d::Rect colliderRect = cocos2d::Rect(x, y, width, height);
    m_pNilo = ActorFactory::getInstance()->createPlayer(Player::PT_NILO);
    if(!m_pNilo)
        return false;
    m_pNilo->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pNilo->setPosition(Vec2(colliderRect.getMidX(),y));
    m_pNilo->setFlipX(flip_x);
    m_pMainLayer->addChild(m_pNilo);
    
    
    m_pPudge = ActorFactory::getInstance()->createPlayer(Player::PT_PUDGE);
    if(!m_pPudge)
        return false;
    m_pPudge->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pPudge->setPosition(Vec2(m_pNilo->getPosition().x+15,m_pNilo->getPosition().y));
    m_pPudge->setFlipX(flip_x);
    m_pMainLayer->addChild(m_pPudge);
    m_pPudge->setVisible(false);
    
    
    return true;
}
bool MapMgrs::initColorMask()
{
    if(!m_pMainLayer || !m_pCurrentTiledMap)
        return false;
    Color3B maskColor = Color3B::BLACK;
    switch (m_MaskColorType) {
        case MCT_RED:
            maskColor = UtilityHelper::randomRedColor();
            break;
        case MCT_ORANGE:
            maskColor = UtilityHelper::randomOrangeColor();
            break;
        case MCT_YELLOW:
            maskColor = UtilityHelper::randomYellowColor();
            break;
        case MCT_GREEN:
            maskColor = UtilityHelper::randomGreenColor();
            break;
        case MCT_CYAN:
            maskColor = UtilityHelper::randomCyanColor();
            break;
        case MCT_BLUE:
            maskColor = UtilityHelper::randomBlueColor();
            break;
        case MCT_PURPLE:
            maskColor = UtilityHelper::randomPurpleColor();
            break;
        case MCT_RANDOM:
            maskColor = UtilityHelper::randomColor();
            break;
        default:
            break;
    }
    ValueVector colliders = m_pColliders->getObjects();
    for (Value value : colliders) {
        ValueMap valuemap = value.asValueMap();
        if(valuemap.empty())
            continue;
        float x = valuemap.at("x").asFloat();
        float y = valuemap.at("y").asFloat();
        float width = valuemap.at("width").asFloat();
        float height = valuemap.at("height").asFloat();
        cocos2d::Rect colliderRect = cocos2d::Rect(x, y, width, height);
        
        m_pCurrentTiledMap->getProperty("maskcolor_type").asInt();
        
        cocos2d::LayerColor* colorMaskLayer  = LayerColor::create(Color4B(maskColor.r,maskColor.g,maskColor.b,50), width, height);
        if(!colorMaskLayer)
            return false;
        colorMaskLayer->setPosition(Vec2(x,y));
        colorMaskLayer->setCameraMask((unsigned short)CameraFlag::USER1);
        colorMaskLayer->setBlendFunc(BlendFunc::ADDITIVE);
        m_pMainLayer->addChild(colorMaskLayer);
    }
    return true;
}
void MapMgrs::updatePlayers(float delta)
{
    if(!m_pNilo)
        return;
    m_pNilo->update(delta);
    
    if (!m_pPudge)
        return;
    m_pPudge->update(delta);
}
void MapMgrs::updateCamera(float delta)
{
    if(!m_pCurrentTiledMap || !m_pMainCamera || !m_pNilo)
        return;

    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();
    cocos2d::Rect mapRect = m_pCurrentTiledMap->getBoundingBox();

    Vec2 playerPos = m_pNilo->getPosition();
    if(playerPos.x > mapRect.getMinX() + winSize.width*0.5f && playerPos.x < mapRect.getMaxX() - winSize.width*0.5f)
    {
        float dist = playerPos.x - m_pMainCamera->getPositionX();
        if(fabs(dist)<=1)
            m_pMainCamera->setPositionX(m_pMainCamera->getPositionX() + dist*delta*2);
        else
            m_pMainCamera->setPositionX(m_pMainCamera->getPositionX() + dist*delta*20);
    }
    if(playerPos.y > mapRect.getMinY() + winSize.height*0.5f && playerPos.y < mapRect.getMaxY() - winSize.width*0.5f)
        m_pMainCamera->setPositionY(playerPos.y);
}