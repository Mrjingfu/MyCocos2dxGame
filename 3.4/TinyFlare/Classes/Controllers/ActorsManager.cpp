//
//  ActorsManager.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/3/12.
//
//

#include "ActorsManager.h"
#include "GameController.h"
USING_NS_CC;

ActorsManager* g_pActorsManagerInstance = nullptr;
ActorsManager* ActorsManager::getInstance()
{
    if( g_pActorsManagerInstance == nullptr )
        g_pActorsManagerInstance = new ActorsManager();
    
    return g_pActorsManagerInstance;
}
ActorsManager::ActorsManager()
{
    m_pActorLayer = nullptr;
}
ActorsManager::~ActorsManager()
{
}


Bullet* ActorsManager::spawnBullet(GameActor::ActorType type, const cocos2d::Vec2& pos, const cocos2d::Vec2& dir, float speed, const std::string& texName)
{
    if(!ActorsManager::getInstance()->m_pActorLayer)
        return nullptr;
    Bullet* bullet = new(std::nothrow) Bullet();
    if (bullet && bullet->init())
    {
        bullet->setScale(0.5f);
        bullet->loadTexture(texName);
        bullet->setType(type);
        bullet->setPosition(pos);
        bullet->setDirection(dir);
        bullet->setOrientation(dir);
        bullet->setMaxSpeed(speed);
        bullet->caculateRadius();
        ActorsManager::getInstance()->m_Bullets.pushBack(bullet);
        ActorsManager::getInstance()->m_pActorLayer->addChild(bullet);
        ActorsManager::getInstance()->m_pActorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
        bullet->autorelease();
        return bullet;
    }
    else
    {
        CC_SAFE_DELETE(bullet);
        return nullptr;
    }
}
Enemy* ActorsManager::spawnEnemy(Enemy::EnemyType enemyType, const Vec2& pos, const Vec2& dir, float speed)
{
    if(!ActorsManager::getInstance()->m_pActorLayer)
        return nullptr;
    Enemy* enemy = nullptr;
    switch (enemyType) {
        case Enemy::EnemyType::ET_BLUE:
        {
        }
            break;

        default:
            break;
    }
    return enemy;
}
Explosion* ActorsManager::spawnExplosion(Explosion::ExplosionType explosionType, const Vec2& pos)
{
    if(!ActorsManager::getInstance()->m_pActorLayer)
        return nullptr;

    Explosion*explosion = new(std::nothrow) Explosion();
    if (explosion && explosion->init())
    {
        switch (explosionType) {
            case Explosion::ET_BLUE:
            {
                explosion->loadParticleSystem("explosion.plist");
                explosion->setScale(0.4f);
                explosion->getParticleSystem()->setStartColor(Color4F(0.0f, 224.0f/255.0f, 252.0f/255.0f, 1.0f));
                explosion->getParticleSystem()->setPosition(pos);
                explosion->getParticleSystem()->setLife(0.3f);
                explosion->setLifeTime(explosion->getParticleSystem()->getLife() + explosion->getParticleSystem()->getLifeVar() );
            }
                break;
            default:
                break;
        }
        ActorsManager::getInstance()->m_Explosions.pushBack(explosion);
        ActorsManager::getInstance()->m_pActorLayer->addChild(explosion);
        ActorsManager::getInstance()->m_pActorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
        explosion->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(explosion);
        return nullptr;
    }
    return explosion;
}
bool ActorsManager::init(cocos2d::Layer* actorLayer)
{
    if(!actorLayer)
        return false;
    m_pActorLayer = actorLayer;
    return true;
}
void ActorsManager::update(float delta)
{
    CCLOG("Current bullets number %zd", m_Bullets.size());
    
    for (ssize_t i = 0; i<m_Explosions.size(); ++i) {
        Explosion* explosion = m_Explosions.at(i);
        if(explosion)
        {
            float lifeTime = explosion->getLifeTime();
            lifeTime -= delta;
            if(lifeTime <= 0)
            {
                eraseExplosion(explosion);
            }
            else
                explosion->setLifeTime(lifeTime);
        }
    }
    
    for (ssize_t i = 0; i<m_Bullets.size(); ++i) {
        Bullet* bullet = m_Bullets.at(i);
        if(bullet)
        {
            float radius = bullet->getRadius();
            Vec3 min = Vec3(-radius, -radius, -0.5f) + bullet->getPosition3D();
            Vec3 max = Vec3(radius, radius, 0.5f) + bullet->getPosition3D();
            AABB aabb = AABB(min, max);
            bool isVisible = GameController::getInstance()->getActorCamera()->isVisibleInFrustum(&aabb);
            if(!isVisible)
            {
                eraseBullet(bullet);
            }
        }
    }
}
void ActorsManager::destroy()
{
    m_pActorLayer = nullptr;
    m_Bullets.clear();
    m_Enemies.clear();
}
void ActorsManager::eraseBullet(Bullet* bullet)
{
    if(!bullet)
        return;
    m_Bullets.eraseObject(bullet);
    bullet->removeFromParentAndCleanup(true);
}
void ActorsManager::eraseBullet(int i)
{
    auto bullet = m_Bullets.at(i);
    m_Bullets.erase(i);
    bullet->removeFromParentAndCleanup(true);
}

void ActorsManager::eraseEnemy(Enemy* enemy)
{
    if(!enemy)
        return;
    m_Enemies.eraseObject(enemy);
    enemy->removeFromParentAndCleanup(true);
}
void ActorsManager::eraseEnemy(int i)
{
    auto enemy = m_Enemies.at(i);
    m_Enemies.erase(i);
    enemy->removeFromParentAndCleanup(true);
}

void ActorsManager::eraseExplosion(Explosion* explosion)
{
    if(!explosion)
        return;
    m_Explosions.eraseObject(explosion);
    explosion->removeFromParentAndCleanup(true);
}
void ActorsManager::eraseExplosion(int i)
{
    auto explosion = m_Explosions.at(i);
    m_Explosions.erase(i);
    explosion->removeFromParentAndCleanup(true);
}