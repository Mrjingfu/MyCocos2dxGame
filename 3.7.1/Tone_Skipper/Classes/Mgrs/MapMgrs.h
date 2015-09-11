//
//  MapMgrs.h
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/7.
//
//

#ifndef __Tone_Skipper__MapMgrs__
#define __Tone_Skipper__MapMgrs__

#include "ActorFactory.h"
class MapMgrs : public cocos2d::Ref
{
    MapMgrs();
    ~MapMgrs();
public:
    typedef enum {
        CF_NONE = 0,
        CF_LEFT = 1<<0,
        CF_RIGHT= 1<<1,
    }
    CollisionFlag;
    static MapMgrs* getInstance();
    bool init(cocos2d::Layer* pMainLayer);
    bool loadMap(const std::string& strFile);
    void unloadMap();
    void update(float delta);
    
    bool checkRayCast(const cocos2d::Rect& rect, cocos2d::Vec2& velocity, Actor::RAYCAST_TYPE& type,bool ignoreAdjust);
    bool checkCollision(const cocos2d::Rect& rect, cocos2d::Vec2& velocity, int& flag);
    bool checkTrigger(const cocos2d::Rect& rect, Actor::TRIGGER_TYPE& type);
    
    Player* getNilo() const { return m_pNilo; }
    
    void showDebug(bool debug);
private:
    bool initPlayer();
private:
    cocos2d::Layer*                         m_pMainLayer;
    cocos2d::experimental::TMXTiledMap*     m_pCurrentTiledMap;
    cocos2d::TMXObjectGroup*                m_pStarters;
    cocos2d::TMXObjectGroup*                m_pColliders;
    cocos2d::TMXObjectGroup*                m_pRayCasters;
    cocos2d::TMXObjectGroup*                m_pTriggers;
    cocos2d::TMXObjectGroup*                m_pMonsters;
    
    Player*                                 m_pNilo;
    
    cocos2d::DrawNode*                      m_pDebugDrawNode;
};

#endif /* defined(__Tone_Skipper__MapMgrs__) */
