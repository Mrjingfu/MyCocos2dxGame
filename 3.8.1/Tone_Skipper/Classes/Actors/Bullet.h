//
//  Bullet.hpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/9.
//
//

#ifndef Bullet_hpp
#define Bullet_hpp
#include "Actor.h"
class Bullet:public Actor
{
public:
    typedef enum{
        BT_SIMPLE = 0
    } BulletType;
    typedef enum{
        ABT_ENEMY =0,
        ABT_PLAYER
    }ActorBulletType;
    
    Bullet();
    ~Bullet();
    virtual bool loadModel();
    virtual bool loadAnimations();
    virtual void onLand();
    virtual void update(float delta);
    cocos2d::Vec2 getDirection() const { return m_Direction; }
    void setDirection(const cocos2d::Vec2& dir) {
        m_Direction = dir;
        m_Direction.normalize();
    }
    void setBulletType(BulletType type){m_pBulletType = type;}
    BulletType getBulletType()const{ return m_pBulletType;}
    
    void setActorBulletType(ActorBulletType type){m_pActorBulletType = type;}
    ActorBulletType getActorBulletType() const{return m_pActorBulletType;}
     virtual cocos2d::Rect getBoundingBox() const override;
private:
    BulletType          m_pBulletType;
    ActorBulletType     m_pActorBulletType;
    cocos2d::Vec2       m_Direction;
    
};

#endif /* Bullet_hpp */
