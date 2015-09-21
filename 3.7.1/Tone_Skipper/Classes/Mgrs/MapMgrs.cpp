//
//  MapMgrs.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/7.
//
//

#include "MapMgrs.h"
#include "UtilityHelper.h"
#include "GameConfig.h"
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
    m_BackgroundMaskColorType = MCT_NONE;
    m_pBackgroundColorMaskLayer = nullptr;
    
    m_FrontgroundMaskColorType = MCT_NONE;
    m_pFrontgroundColorMaskLayer = nullptr;
    m_pMainLayer = nullptr;
    m_pShadowLayer = nullptr;
    m_pNilo = nullptr;
    m_pMainCamera = nullptr;
    
    m_pCurrentTiledMap  = nullptr;
    m_pCoverLayer       = nullptr;
    m_pCoverLayerVisable = true;
    
    m_pStarters         = nullptr;
    m_pColliders        = nullptr;
    m_pRayCasters       = nullptr;
    m_pTriggers         = nullptr;
    m_pItems            = nullptr;
    m_pMonsters         = nullptr;
    m_pShadows          = nullptr;
    m_pFrontgroundMaskObjects = nullptr;
    m_pDebugDrawNode = nullptr;
    
    m_strBornPointName  = "bornpoint1";
}
MapMgrs::~MapMgrs()
{
}
bool MapMgrs::init(cocos2d::Layer* pMainLayer)
{
    if(pMainLayer == nullptr)
        return false;
    m_pMainLayer = pMainLayer;
    
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
    
    if(!initBackgroundMask())
        return false;
    
    m_pCurrentTiledMap->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pCoverLayer = m_pCurrentTiledMap->getLayer("coverlayer");
    if(m_pCoverLayer)
        m_pCoverLayer->removeFromParent();
    
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
    
    m_pItems = m_pCurrentTiledMap->getObjectGroup("items");
    if(!m_pItems)
        return false;
    
    m_pMonsters = m_pCurrentTiledMap->getObjectGroup("monsters");
    if(!m_pMonsters)
        return false;
    
    m_pShadows = m_pCurrentTiledMap->getObjectGroup("shadows");
    if(!m_pShadows)
        return false;
    
    m_pFrontgroundMaskObjects = m_pCurrentTiledMap->getObjectGroup("frontgroundmask");
    if(!m_pFrontgroundMaskObjects)
        return false;
    
    if(!initShadows())
        return false;
    
    m_pMainLayer->addChild(m_pCurrentTiledMap);
    
    if(!initFrontgroundMask())
        return false;
    if(!initPlayer())
        return false;
    
    if(m_pCoverLayer)
    {
        m_pCoverLayer->setCameraMask((unsigned short)CameraFlag::USER1);
        m_pCoverLayer->setCascadeOpacityEnabled(true);
        m_pMainLayer->addChild(m_pCoverLayer);
    }
    
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
    if(rect.getMaxY() >= m_pMapRect.getMaxY() && velocity.y >=0)
    {
        velocity.y = 0;
        flag |= CF_TOP;
        ret = true;
        return ret;
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
                else if(rect.getMaxY() >= colliderRect.getMinY())
                {
                    velocity.y = 0;
                    flag |= CF_TOP;
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
        if (tiggerRect.getMaxX() - rect.size.width < rect.getMinX() || rect.getMaxX() < tiggerRect.getMinX() + rect.size.width ||
            tiggerRect.getMaxY() < rect.getMinY() || rect.getMaxY() < tiggerRect.getMinY()) {
            ret = false;
        }
        else
        {
            type = (Actor::TRIGGER_TYPE)(valuemap.at("type").asInt());
            switch (type) {
                case Actor::TT_TIPS:
                    {
                        std::string tips = valuemap.at("tips_id").asString();
                        showTips(tiggerRect.origin + Vec2(0,tiggerRect.size.height), tips);
                    }
                    break;
                default:
                    break;
            }
            ret = true;
            break;
        }
    }
    return ret;
}
bool MapMgrs::checkUsableItems(const cocos2d::Rect& rect, Actor::USABLE_ITEM_TYPE& type)
{
    bool ret = false;
    ValueVector items = m_pItems->getObjects();
    for (Value value : items) {
        ValueMap valuemap = value.asValueMap();
        if(valuemap.empty())
            continue;
        float x = valuemap.at("x").asFloat();
        float y = valuemap.at("y").asFloat();
        float width = valuemap.at("width").asFloat();
        float height = valuemap.at("height").asFloat();
        cocos2d::Rect itemRect = cocos2d::Rect(x, y, width, height);
        if (itemRect.getMaxX() < rect.getMinX() || rect.getMaxX() < itemRect.getMinX() ||
            itemRect.getMaxY() < rect.getMinY() || rect.getMaxY() < itemRect.getMinY()) {
            ret = false;
        }
        else
        {
            if(rect.getMidX() <= itemRect.getMaxX() && rect.getMidX() >= itemRect.getMinX())
            {
                type = (Actor::USABLE_ITEM_TYPE)(valuemap.at("type").asInt());
                switch (type) {
                    case Actor::UIT_LADDER:
                        break;
                    case Actor::UIT_QUESTIONBOX:
                        break;
                    default:
                        break;
                }
                ret = true;
                break;
            }
        }
    }
    return ret;
}
bool MapMgrs::checkInShadowRect(const cocos2d::Rect& rect, float& shadowHue)
{
    if(!m_pShadowLayer || !m_pShadows)
        return false;
    bool ret = false;
    ValueVector shadows = m_pShadows->getObjects();
    for (Value value : shadows) {
        ValueMap valuemap = value.asValueMap();
        if(valuemap.empty())
            continue;
        float x = valuemap.at("x").asFloat();
        float y = valuemap.at("y").asFloat();
        float width = valuemap.at("width").asFloat();
        float height = valuemap.at("height").asFloat();
        cocos2d::Rect shadowRect = cocos2d::Rect(x, y, width, height);
        if (shadowRect.getMaxX() - rect.size.width < rect.getMinX() || rect.getMaxX() < shadowRect.getMinX() + rect.size.width ||
            shadowRect.getMaxY() - rect.size.height < rect.getMinY() || rect.getMaxY() < shadowRect.getMinY() + rect.size.height) {
            ret = false;
        }
        else
        {
            std::string name = valuemap.at("name").asString();
            HueSprite* sprite = static_cast<HueSprite*>(m_pShadowLayer->getChildByName(name));
            if(sprite)
            {
                shadowHue = sprite->getHue()/(2*M_PI);
                ret = true;
                break;
            }
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
        ////items
        ValueVector items = m_pItems->getObjects();
        for (Value value : items) {
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
            m_pDebugDrawNode->drawPoly(vertices, 4, true, Color4F(149.0f/255.0f,0,243.0f/255.0f,1.0f));
        }
        ///
        ///Monsters
        ValueVector monsters = m_pMonsters->getObjects();
        for (Value value : monsters) {
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
            m_pDebugDrawNode->drawPoly(vertices, 4, true, Color4F(250.0f/255.0f,134.0f/255.0f,26.0f/255.0f,1.0f));
        }
        ///
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
void MapMgrs::hideCoverLayer()
{
    if(m_pCoverLayer && m_pCoverLayerVisable)
    {
        m_pCoverLayerVisable = false;
        auto size = m_pCurrentTiledMap->getMapSize();
        for (int i = 0; i < size.width; ++i) {
            for (int j = 0; j < size.height; j++) {
                Sprite* sprite = m_pCoverLayer->getTileAt(Vec2(i, j));
                if(sprite)
                {
                    EaseSineOut* fadeout = EaseSineOut::create(FadeOut::create(0.5f));
                    sprite->runAction(fadeout);
                }
            }
        }
    }
}
void MapMgrs::showCoverLayer()
{
    if(m_pCoverLayer && !m_pCoverLayerVisable)
    {
        m_pCoverLayerVisable = true;
        auto size = m_pCurrentTiledMap->getMapSize();
        for (int i = 0; i < size.width; ++i) {
            for (int j = 0; j < size.height; j++) {
                Sprite* sprite = m_pCoverLayer->getTileAt(Vec2(i, j));
                if(sprite)
                {
                    EaseSineOut* fadeIn = EaseSineOut::create(FadeIn::create(0.5f));
                    sprite->runAction(fadeIn);
                }
            }
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
    
    ValueMap start_born = m_pStarters->getObject(m_strBornPointName);
    if(start_born.empty())
        return false;
    Player::PLayerDirection direction = (Player::PLayerDirection)(start_born.at("player_direction").asInt());
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
    m_pNilo->setPlayerDirection(direction);
    m_pNilo->setHue(0.18);
    m_pMainLayer->addChild(m_pNilo);
    
    
    m_pPudge = ActorFactory::getInstance()->createPlayer(Player::PT_PUDGE);
    if(!m_pPudge)
        return false;
    m_pPudge->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pPudge->setPosition(Vec2(m_pNilo->getPosition().x+m_pCurrentTiledMap->getTileSize().width,m_pNilo->getPosition().y));
    m_pPudge->setPlayerDirection(direction);
    m_pMainLayer->addChild(m_pPudge);
    m_pPudge->setVisible(false);
    
    
    return true;
}
bool MapMgrs::initShadows()
{
    if(!m_pMainLayer || !m_pCurrentTiledMap)
        return false;
    m_pShadowLayer = Layer::create();
    if(!m_pShadowLayer)
        return false;
    ValueVector shadows = m_pShadows->getObjects();
    for (Value value : shadows) {
        ValueMap valuemap = value.asValueMap();
        if(valuemap.empty())
            continue;
        float x = valuemap.at("x").asFloat();
        float y = valuemap.at("y").asFloat();
        float width = valuemap.at("width").asFloat();
        float height = valuemap.at("height").asFloat();
        std::string name = valuemap.at("name").asString();
        float hueValue = valuemap.at("hue_value").asFloat();
        cocos2d::Rect shadowRect = cocos2d::Rect(x, y, width, height);
        HueSprite* shadow = HueSprite::create("shadow.png");
        if(!shadow)
            return false;
        shadow->setName(name);
        shadow->setHue(2*M_PI*hueValue);
        shadow->setPosition(Vec2(shadowRect.getMidX(), shadowRect.getMidY()));
        Texture2D::TexParams texRepeat = {GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT};
        shadow->getTexture()->setTexParameters(texRepeat);
        shadow->setTextureRect(shadowRect, true, Size(32,32));
        shadow->setOpacity(128);
        m_pShadowLayer->addChild(shadow);
    }
    m_pShadowLayer->setCascadeOpacityEnabled(true);
    m_pShadowLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pMainLayer->addChild(m_pShadowLayer);
    return true;
}
bool MapMgrs::initBackgroundMask()
{
    if(!m_pMainLayer || !m_pCurrentTiledMap)
        return false;
    m_BackgroundMaskColorType = (MaskColorType)(m_pCurrentTiledMap->getProperty("background_colortype").asInt());
    Color3B maskColor = Color3B::BLACK;
    switch (m_BackgroundMaskColorType) {
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
    m_pBackgroundColorMaskLayer = LayerColor::create(Color4B(maskColor.r, maskColor.g, maskColor.b, 60));
    if(!m_pBackgroundColorMaskLayer)
        return false;
    m_pBackgroundColorMaskLayer->setBlendFunc(BlendFunc::ADDITIVE);
    m_pMainLayer->addChild(m_pBackgroundColorMaskLayer);
    return true;
}

bool MapMgrs::initFrontgroundMask()
{
    if(!m_pMainLayer || !m_pCurrentTiledMap)
        return false;
    m_pFrontgroundColorMaskLayer = Layer::create();
    if(!m_pFrontgroundColorMaskLayer)
        return false;
    m_FrontgroundMaskColorType = (MaskColorType)(m_pCurrentTiledMap->getProperty("frontground_colortype").asInt());
    Color3B maskColor = Color3B::BLACK;
    switch (m_FrontgroundMaskColorType) {
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
    ValueVector maskObjects = m_pFrontgroundMaskObjects->getObjects();
    for (Value value : maskObjects) {
        ValueMap valuemap = value.asValueMap();
        if(valuemap.empty())
            continue;
        float x = valuemap.at("x").asFloat();
        float y = valuemap.at("y").asFloat();
        float width = valuemap.at("width").asFloat();
        float height = valuemap.at("height").asFloat();
        cocos2d::Rect colliderRect = cocos2d::Rect(x, y, width, height);
        
        cocos2d::LayerColor* colorMaskLayer  = LayerColor::create(Color4B(maskColor.r,maskColor.g,maskColor.b,80), width, height);
        if(!colorMaskLayer)
            return false;
        colorMaskLayer->setPosition(Vec2(x,y));
        colorMaskLayer->setBlendFunc(BlendFunc::ADDITIVE);
        m_pFrontgroundColorMaskLayer->addChild(colorMaskLayer);
    }
    m_pFrontgroundColorMaskLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pMainLayer->addChild(m_pFrontgroundColorMaskLayer);
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
    if(playerPos.y > mapRect.getMinY() + winSize.height*0.3f && playerPos.y < mapRect.getMaxY() - winSize.width*0.5f)
        m_pMainCamera->setPositionY(playerPos.y + winSize.height*0.2f);
}
void MapMgrs::showTips(const cocos2d::Vec2& pos, const std::string& tips)
{
    TipData tipData;
    tipData.m_pPt = pos;
    tipData.m_pDes = tips;
//    CCLOG("pos : %f, %f; ", getNilo()->getPosition().x, getNilo()->getPosition().y);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MAIN_TIPS,(void*)&tipData);
}