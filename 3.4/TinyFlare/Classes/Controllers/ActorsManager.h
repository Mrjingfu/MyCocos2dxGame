//
//  ActorsManager.h
//  TinyFlare
//
//  Created by wang haibo on 15/3/12.
//
//

#ifndef __TinyFlare__ActorsManager__
#define __TinyFlare__ActorsManager__

#include "cocos2d.h"
#include "Bullet.h"
#include "Enemies.h"
#include "Explosion.h"
class ActorsManager : public cocos2d::Ref
{
    ActorsManager();
    virtual ~ActorsManager();
public:
    static ActorsManager* getInstance();
    
    static Bullet* spawnBullet(GameActor::ActorType type, const cocos2d::Vec2& pos, const cocos2d::Vec2& dir, float speed, const std::string& texName);
    
    static Enemy* spawnEnemy(Enemy::EnemyType enemyType, const cocos2d::Vec2& pos, const cocos2d::Vec2& dir, float speed);
    
    static Explosion* spawnExplosion(Explosion::ExplosionType explosionType, const cocos2d::Vec2& pos);
    
    bool init(cocos2d::Layer* actorLayer);
    void update(float delta);
    void destroy();
    
    void eraseBullet(Bullet* bullet);
    void eraseBullet(int i);
    
    void eraseEnemy(Enemy* enemy);
    void eraseEnemy(int i);
    
    void eraseExplosion(Explosion* explosion);
    void eraseExplosion(int i);
private:
    cocos2d::Vector<Bullet*>                m_Bullets;
    cocos2d::Vector<Enemy*>                 m_Enemies;
    cocos2d::Vector<Explosion*>             m_Explosions;
    cocos2d::Layer*                         m_pActorLayer;
};

#endif /* defined(__TinyFlare__ActorsManager__) */
