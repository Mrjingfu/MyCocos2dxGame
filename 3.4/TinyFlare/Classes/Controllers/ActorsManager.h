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
#include "Laser.h"
class ActorsManager : public cocos2d::Ref
{
    ActorsManager();
    virtual ~ActorsManager();
public:
    static ActorsManager* getInstance();
    
    static Bullet* spawnBullet(GameActor::ActorType type, const cocos2d::Vec2& pos, const cocos2d::Vec2& dir, float speed, const std::string& texName, const cocos2d::Color3B& colormask = cocos2d::Color3B::WHITE, float scaleX = 1.0f, float scaleY = 1.0f);
    
    static Enemy* spawnEnemy(Enemy::EnemyType enemyType, const cocos2d::Vec2& pos, const cocos2d::Vec2& dir);
    
    static Laser* spawnLaser(const cocos2d::Vec2& start, const cocos2d::Vec2& end);
    
    bool init(cocos2d::Layer* actorLayer);
    void update(float delta);
    void destroy();
    
    void eraseBullet(Bullet* bullet);
    void eraseBullet(int i);
    
    void eraseEnemy(Enemy* enemy);
    void eraseEnemy(int i);
    
    void eraseLaser(Laser* laser);
    void eraseLaser(int i);
    
    void reset();
private:
    cocos2d::Vector<Bullet*>                m_Bullets;
    cocos2d::Vector<Enemy*>                 m_Enemies;
    cocos2d::Vector<Laser*>                 m_Lasers;
    cocos2d::Layer*                         m_pActorLayer;
};

#endif /* defined(__TinyFlare__ActorsManager__) */
