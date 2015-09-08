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
        CF_LAND = 1<<0,
        CF_LEFT = 1<<1,
        CF_RIGHT= 1<<2,
        CF_TOP  = 1<<3
    }
    CollisionFlag;
    static MapMgrs* getInstance();
    bool init(cocos2d::Layer* pMainLayer);
    bool loadMap(const std::string& strFile);
    void unloadMap();
    void update(float delta);
    
    bool checkCollision(const cocos2d::Rect& rect, int& flag, Actor::RAYCAST_TYPE& type);
    
    Player* getNilo() const { return m_pNilo; }
private:
    bool initPlayer();
private:
    cocos2d::Layer*                         m_pMainLayer;
    cocos2d::experimental::TMXTiledMap*     m_pCurrentTiledMap;
    cocos2d::TMXObjectGroup*                m_pStarters;
    cocos2d::TMXObjectGroup*                m_pColliders;
    cocos2d::TMXObjectGroup*                m_pMonsters;
    cocos2d::TMXObjectGroup*                m_pAvalidObjects;
    cocos2d::TMXObjectGroup*                m_pItemObjects;
    cocos2d::TMXObjectGroup*                m_pTriggers;
    
    Player*                                 m_pNilo;
};

#endif /* defined(__Tone_Skipper__MapMgrs__) */
