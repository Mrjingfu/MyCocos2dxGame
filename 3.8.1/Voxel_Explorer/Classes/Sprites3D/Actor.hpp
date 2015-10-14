//
//  Actor.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/14.
//
//

#ifndef Actor_hpp
#define Actor_hpp

#include "cocos2d.h"
class Actor : public cocos2d::Sprite3D
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
    ~Actor();
    virtual void rotateToLeft() { m_dir = AD_LEFT; };
    virtual void rotateToRight() { m_dir = AD_RIGHT; };
    virtual void rotateToForward() { m_dir = AD_FORWARD; };
    virtual void rotateToBack() { m_dir = AD_BACK; };
public:
    cocos2d::Vec2 getPosInMap();
    
    ActorDir getActorDir() const { return m_dir; }
    void setActorDir( ActorDir dir );
protected:
    ActorDir       m_dir;
};

#endif /* Actor_hpp */
