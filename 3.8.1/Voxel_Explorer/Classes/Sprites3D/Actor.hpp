//
//  Actor.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/14.
//
//

#ifndef Actor_hpp
#define Actor_hpp

#include "EffectSprite3D.h"
class Actor : public EffectSprite3D
{
public:
    typedef enum {
        AD_FORWARD = 0,
        AD_LEFT,
        AD_RIGHT,
        AD_BACK,
        AD_UNKNOWN
    } ActorDir;
protected:
    Actor();
    virtual ~Actor();
    virtual void rotateToLeft() { m_dir = AD_LEFT; };
    virtual void rotateToRight() { m_dir = AD_RIGHT; };
    virtual void rotateToForward() { m_dir = AD_FORWARD; };
    virtual void rotateToBack() { m_dir = AD_BACK; };
public:
    cocos2d::Vec2 getPosInMap();
    
    ActorDir getActorDir() const { return m_dir; }
    virtual void setActorDir( ActorDir dir );
    
    virtual void addTerrainTileFlag(int flag);
    virtual void addTerrainTileFlagByPos(int flag, const cocos2d::Vec2& pos);
    
    virtual void removeTerrainTileFlag(int flag);
    virtual void removeTerrainTileFlagByPos(int flag, const cocos2d::Vec2& pos);
    
    virtual void setVisited(bool visited);
    
    virtual std::string getDesc() = 0;
protected:
    ActorDir       m_dir;
};

#endif /* Actor_hpp */
