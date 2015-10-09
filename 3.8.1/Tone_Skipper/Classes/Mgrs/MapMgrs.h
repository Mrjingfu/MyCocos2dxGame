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
        CF_NONE     = 0,
        CF_LEFT     = 1<<0,
        CF_RIGHT    = 1<<1,
        CF_TOP      = 1<<2,
        CF_BOUND    = 1<<3
    }
    CollisionFlag;
    typedef enum {
        MCT_NONE = 0,
        MCT_RED,
        MCT_ORANGE,
        MCT_YELLOW,
        MCT_GREEN,
        MCT_CYAN,
        MCT_BLUE,
        MCT_PURPLE,
        MCT_RANDOM
    }
    MaskColorType;
    static MapMgrs* getInstance();
    bool init(cocos2d::Layer* pMainLayer);
    bool loadMap(const std::string& strFile);
    void unloadMap();
    void update(float delta);
    
    bool checkRayCast(const cocos2d::Rect& rect, cocos2d::Vec2& velocity, Actor::RAYCAST_TYPE& type,bool ignoreAdjust);
    bool checkCollision(const cocos2d::Rect& rect, cocos2d::Vec2& velocity, int& flag);
    bool checkTrigger(const cocos2d::Rect& rect, Actor::TRIGGER_TYPE& type);
    bool checkUsableItems(const cocos2d::Rect& rect, UsableItem::USABLE_ITEM_TYPE& type);
    bool checkInShadowRect(const cocos2d::Rect& rect, float& shadowHue);
    
    Player* getNilo() const { return m_pNilo; }
    Player* getPudge() const {return m_pPudge;}
    void showDebug(bool debug);
    
    void hideCoverLayer();
    void showCoverLayer();
    
    Bullet* createBullet(Bullet::BulletType btype,Bullet::ActorBulletType atype,cocos2d::Vec2 pt,cocos2d::Vec2 direction);
    
    void eraseBullet(Bullet* bullet);
    void eraseBullet(int i);
    
    void eraseEnemy(Enemy* enemy);
    void eraseEnemy(int i);
    
private:
    bool initCamera();
    bool initPlayer();
    bool initShadows();
    bool initBackgroundMask();
    bool initFrontgroundMask();
    bool initUsableItems();
    bool initSceneItems();
    bool initMosters();

    void updatePlayers(float delta);
    void updateCamera(float delta);
    void updateMonster(float delta);
    void updateBullet(float delta);
    
    void showTips(const cocos2d::Vec2& pos, const std::string& tips);
private:
    MaskColorType                           m_BackgroundMaskColorType;
    cocos2d::LayerColor*                    m_pBackgroundColorMaskLayer;
    
    MaskColorType                           m_FrontgroundMaskColorType;
    cocos2d::Layer*                         m_pFrontgroundColorMaskLayer;
    
    cocos2d::Layer*                         m_pMainLayer;
    cocos2d::Layer*                         m_pShadowLayer;
    cocos2d::TMXTiledMap*                   m_pCurrentTiledMap;
    cocos2d::Layer*                         m_pSceneItemLayer;
    cocos2d::Layer*                         m_pUsableItemLayer;
    cocos2d::Layer*                         m_pMonsterLayer;
    cocos2d::Layer*                         m_pPlayerLayer;
    cocos2d::Layer*                         m_pBulletLayer;
    cocos2d::TMXLayer*                      m_pCoverLayer;
    bool                                    m_pCoverLayerVisable;
    
    cocos2d::TMXObjectGroup*                m_pStarters;
    cocos2d::TMXObjectGroup*                m_pColliders;
    cocos2d::TMXObjectGroup*                m_pRayCasters;
    cocos2d::TMXObjectGroup*                m_pTriggers;
    cocos2d::TMXObjectGroup*                m_pUsableItems;
    cocos2d::TMXObjectGroup*                m_pMonsters;
    cocos2d::TMXObjectGroup*                m_pShadows;
    cocos2d::TMXObjectGroup*                m_pFrontgroundMaskObjects;
    
    cocos2d::Rect                           m_pMapRect;
    
    cocos2d::Camera*                        m_pMainCamera;
    Player*                                 m_pNilo;
    Player*                                 m_pPudge;
    cocos2d::DrawNode*                      m_pDebugDrawNode;
    cocos2d::Vector<Enemy*>                 m_pMonsterList;
    cocos2d::Vector<Bullet*>                m_pBulletList;
    std::string                             m_strBornPointName;
};

#endif /* defined(__Tone_Skipper__MapMgrs__) */
