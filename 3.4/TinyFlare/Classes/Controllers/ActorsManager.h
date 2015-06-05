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
#include "Item.h"
#include "Stardust.h"
class ActorsManager : public cocos2d::Ref
{
    ActorsManager();
    virtual ~ActorsManager();
public:
    static ActorsManager* getInstance();
    
    static Bullet* spawnBullet(GameActor::ActorType type, const cocos2d::Vec2& pos, const cocos2d::Vec2& dir, float speed, const std::string& texName, const cocos2d::Color3B& colormask = cocos2d::Color3B::WHITE, float scaleX = 1.0f, float scaleY = 1.0f);
    
    static Enemy* spawnEnemy(Enemy::EnemyType enemyType, const cocos2d::Vec2& pos, const cocos2d::Vec2& dir);
    
    static Laser* spawnLaser(const cocos2d::Vec2& start, const cocos2d::Vec2& end);
    
    static Item* spawnItem(Item::ItemType type, const cocos2d::Vec2& pos);
    
    static Stardust* spawnStardust(Stardust::StardustType type, const cocos2d::Vec2& pos);
    
    bool init(cocos2d::Layer* gameLayer);
    void update(float delta);
    void destroy();
    
    void eraseBullet(Bullet* bullet);
    void eraseBullet(int i);
    
    void eraseEnemy(Enemy* enemy);
    void eraseEnemy(int i);
    
    void eraseLaser(Laser* laser);
    void eraseLaser(int i);
    
    void eraseItem(Item* item);
    void eraseItem(int i);
    
    void eraseStardust(Stardust* stardust);
    void eraseStardust(int i);
    
    void setEnemyActorPause(bool pause);
    bool getEnemyActorPause() const;
    
    void reset();
private:
    cocos2d::Vector<Bullet*>                m_Bullets;
    cocos2d::Vector<Enemy*>                 m_Enemies;
    cocos2d::Vector<Laser*>                 m_Lasers;
    cocos2d::Vector<Item*>                  m_Items;
    cocos2d::Vector<Stardust*>              m_Stardusts;
    cocos2d::Layer*                         m_pActorLayer;
    cocos2d::Layer*                         m_pColorCircleLayer;
    cocos2d::Layer*                         m_pColorTriangleLayer;
    cocos2d::Layer*                         m_pColorDiamondLayer;
    cocos2d::Layer*                         m_pColorStarLayer;
    cocos2d::Layer*                         m_pColorHexagonLayer;
    cocos2d::Layer*                         m_pColorLaserLayer;
    
    bool                                    m_bEnemyActorPause;
};

#endif /* defined(__TinyFlare__ActorsManager__) */
