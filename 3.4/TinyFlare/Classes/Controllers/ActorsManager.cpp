//
//  ActorsManager.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/3/12.
//
//

#include "ActorsManager.h"
#include "GameController.h"
#include "ParticleSystemHelper.h"
#include "UtilityHelper.h"
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


Bullet* ActorsManager::spawnBullet(GameActor::ActorType type, const cocos2d::Vec2& pos, const cocos2d::Vec2& dir, float speed, const std::string& texName, const cocos2d::Color3B& colormask, float scaleX, float scaleY)
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
        bullet->setColorMask(colormask);
        bullet->getModel()->setScale(scaleX,scaleY);
        bullet->caculateRadius();
        bullet->updateOrientation();
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
Enemy* ActorsManager::spawnEnemy(Enemy::EnemyType enemyType, const Vec2& pos, const Vec2& dir)
{
    if(!ActorsManager::getInstance()->m_pActorLayer)
        return nullptr;
    Enemy* enemy = nullptr;
    switch (enemyType) {
        case Enemy::EnemyType::ET_CIRCLE:
            {
                enemy = new(std::nothrow) Circle();
                if (enemy && enemy->init()) {
                    enemy->loadModel("circle.png");
                    enemy->setPosition(pos);
                    enemy->setDirection(dir);
                    enemy->setOrientation(dir);
                    enemy->setCascadeOpacityEnabled(true);
                    enemy->setOpacity(0);
                    enemy->setScale(0.2f);
                    enemy->setActorState(ActorState::AS_UNDERCONTROL);
                    enemy->caculateRadius();
                    ActorsManager::getInstance()->m_Enemies.pushBack(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->addChild(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
                    
                    EaseSineOut* easeOut1 = EaseSineOut::create(ScaleTo::create(1.5f, 0.8f));
                    EaseSineOut* easeOut2 = EaseSineOut::create(FadeIn::create(1.5f));
                    
                    DelayTime* delay = DelayTime::create(0.2f);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Enemy::beginTrack,enemy));
                    Sequence* sequence = Sequence::createWithTwoActions(delay, callFunc);
                    
                    Spawn* spawn = Spawn::create(easeOut1, easeOut2, sequence, NULL);
                    enemy->runAction(spawn);
                    enemy->autorelease();
                }
                else
                    CC_SAFE_DELETE(enemy);
            }
            break;
        case Enemy::EnemyType::ET_CIRCLE_COLORED:
            {
                enemy = new(std::nothrow) ColorCircle();
                if (enemy && enemy->init()) {
                    enemy->loadModel("circle.png");
                    //enemy->getModel()->setVisible(false);
                    enemy->setPosition(pos);
                    enemy->setDirection(dir);
                    enemy->setOrientation(dir);
                    enemy->setCascadeOpacityEnabled(true);
                    enemy->setOpacity(0);
                    enemy->setScale(0.2f);
                    enemy->setActorState(ActorState::AS_UNDERCONTROL);
                    enemy->caculateRadius();
                    ActorsManager::getInstance()->m_Enemies.pushBack(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->addChild(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
                    
                    ParticleSystemHelper::spawnActorWidget(ActorWidgetType::AWT_COLOR_CIRCLE_TAIL, Vec2::ZERO, enemy);
                    
                    EaseSineOut* easeOut1 = EaseSineOut::create(ScaleTo::create(1.5f, 0.8f));
                    EaseSineOut* easeOut2 = EaseSineOut::create(FadeIn::create(1.5f));
                    Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
                    
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Enemy::beginTrack,enemy));
                    Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
                    enemy->runAction(sequence);
                    enemy->autorelease();
                }
                else
                    CC_SAFE_DELETE(enemy);
            }
            break;
        case Enemy::EnemyType::ET_TRIANGLE:
            {
                enemy = new(std::nothrow) Triangle();
                if (enemy && enemy->init()) {
                    enemy->loadModel("triangle.png");
                    enemy->setPosition(pos);
                    enemy->setDirection(dir);
                    enemy->setOrientation(dir);
                    enemy->setCascadeOpacityEnabled(true);
                    enemy->setOpacity(0);
                    enemy->setScale(0.2f);
                    enemy->setActorState(ActorState::AS_UNDERCONTROL);
                    enemy->setColor(Color3B(253,255,12));
                    enemy->caculateRadius();
                    ActorsManager::getInstance()->m_Enemies.pushBack(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->addChild(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
                
                
                    EaseSineOut* easeOut1 = EaseSineOut::create(ScaleTo::create(1.5f, 1.0f));
                    EaseSineOut* easeOut2 = EaseSineOut::create(FadeIn::create(1.5f));
                    Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
                
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Enemy::beginTrack,enemy));
                    Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
                    enemy->runAction(sequence);
                    enemy->autorelease();
                }
                else
                    CC_SAFE_DELETE(enemy);
            }
            break;
        case Enemy::EnemyType::ET_TRIANGLE_COLORED:
            {
                enemy = new(std::nothrow) ColorTriangle();
                if (enemy && enemy->init()) {
                    enemy->loadModel("triangle.png");
                    enemy->setPosition(pos);
                    enemy->setDirection(dir);
                    enemy->setOrientation(dir);
                    enemy->setCascadeOpacityEnabled(true);
                    enemy->setOpacity(0);
                    enemy->setScale(0.2f);
                    enemy->setActorState(ActorState::AS_UNDERCONTROL);
                    enemy->setColor(Color3B(253,255,12));
                    enemy->caculateRadius();
                    ActorsManager::getInstance()->m_Enemies.pushBack(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->addChild(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
                
                    ParticleSystemHelper::spawnActorWidget(ActorWidgetType::AWT_COLOR_TRIANGLE_TAIL, Vec2::ZERO, enemy);
                
                    EaseSineOut* easeOut1 = EaseSineOut::create(ScaleTo::create(1.5f, 1.0f));
                    EaseSineOut* easeOut2 = EaseSineOut::create(FadeIn::create(1.5f));
                    Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
                
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Enemy::beginTrack,enemy));
                    Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
                    enemy->runAction(sequence);
                    enemy->autorelease();
                }
                else
                    CC_SAFE_DELETE(enemy);
            }
            break;
        case Enemy::EnemyType::ET_DIAMOND:
            {
                enemy = new(std::nothrow) Diamond();
                if (enemy && enemy->init()) {
                    enemy->loadModel("diamond.png");
                    enemy->setPosition(pos);
                    enemy->setDirection(dir);
                    enemy->setOrientation(dir);
                    enemy->setCascadeOpacityEnabled(true);
                    enemy->setOpacity(0);
                    enemy->setScale(0.2f);
                    enemy->setActorState(ActorState::AS_UNDERCONTROL);
                    enemy->setColor(Color3B(64,255,1));
                    enemy->caculateRadius();
                    ActorsManager::getInstance()->m_Enemies.pushBack(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->addChild(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
                
                    EaseSineOut* easeOut1 = EaseSineOut::create(ScaleTo::create(1.5f, 1.0f));
                    EaseSineOut* easeOut2 = EaseSineOut::create(FadeIn::create(1.5f));
                    Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
                
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Enemy::beginTrack, enemy));
                    Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
                    enemy->runAction(sequence);
                    enemy->autorelease();
                }
                else
                    CC_SAFE_DELETE(enemy);
            }
            break;
        case Enemy::EnemyType::ET_DIAMOND_COLORED:
            {
                enemy = new(std::nothrow) ColorDiamond();
                if (enemy && enemy->init()) {
                    enemy->loadModel("diamond.png");
                    enemy->setPosition(pos);
                    enemy->setDirection(dir);
                    enemy->setOrientation(dir);
                    enemy->setCascadeOpacityEnabled(true);
                    enemy->setOpacity(0);
                    enemy->setScale(0.2f);
                    enemy->setActorState(ActorState::AS_UNDERCONTROL);
                    enemy->setColor(Color3B(64,255,1));
                    enemy->caculateRadius();
                    ActorsManager::getInstance()->m_Enemies.pushBack(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->addChild(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
                
                    ParticleSystemHelper::spawnActorWidget(ActorWidgetType::AWT_COLOR_DIAMOND_TAIL, Vec2::ZERO, enemy);
                
                    EaseSineOut* easeOut1 = EaseSineOut::create(ScaleTo::create(1.5f, 1.0f));
                    EaseSineOut* easeOut2 = EaseSineOut::create(FadeIn::create(1.5f));
                    Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
                
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Enemy::beginTrack,enemy));
                    Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
                    enemy->runAction(sequence);
                    enemy->autorelease();
                }
                else
                    CC_SAFE_DELETE(enemy);
            }
            break;
        case Enemy::EnemyType::ET_STAR:
            {
                enemy = new(std::nothrow) Star();
                if (enemy && enemy->init()) {
                    enemy->loadModel("star.png");
                    enemy->setPosition(pos);
                    enemy->setDirection(dir);
                    //enemy->setOrientation(dir);
                    enemy->setCascadeOpacityEnabled(true);
                    enemy->setOpacity(0);
                    enemy->setScale(0.3f);
                    enemy->setActorState(ActorState::AS_UNDERCONTROL);
                    //enemy->setColor(Color3B(254,64,64));
                    enemy->setColor(Color3B(0,224,252));
                    enemy->caculateRadius();
                    ActorsManager::getInstance()->m_Enemies.pushBack(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->addChild(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
                
                    EaseSineOut* easeOut1 = EaseSineOut::create(ScaleTo::create(1.5f, 1.0f));
                    EaseSineOut* easeOut2 = EaseSineOut::create(FadeIn::create(1.5f));
                
                    DelayTime* delay = DelayTime::create(0.2f);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Enemy::beginTrack,enemy));
                    Sequence* sequence = Sequence::createWithTwoActions(delay, callFunc);
                
                    Spawn* spawn = Spawn::create(easeOut1, easeOut2, sequence, NULL);
                    enemy->runAction(spawn);
                    enemy->autorelease();
                }
                else
                    CC_SAFE_DELETE(enemy);
            }
            break;
        case Enemy::EnemyType::ET_STAR_COLORED:
            {
                enemy = new(std::nothrow) ColorStar();
                if (enemy && enemy->init()) {
                    enemy->loadModel("star.png");
                    enemy->setPosition(pos);
                    enemy->setDirection(dir);
                    //enemy->setOrientation(dir);
                    enemy->setCascadeOpacityEnabled(true);
                    enemy->setOpacity(0);
                    enemy->setScale(0.3f);
                    enemy->initFirePos();
                    enemy->setActorState(ActorState::AS_UNDERCONTROL);
                    //enemy->setColor(Color3B(254,64,64));
                    enemy->setColor(Color3B(0,224,252));
                    enemy->caculateRadius();
                    ActorsManager::getInstance()->m_Enemies.pushBack(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->addChild(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
                    
                    ParticleSystemHelper::spawnActorWidget(ActorWidgetType::AWT_COLOR_STAR_TAIL, Vec2::ZERO, enemy);
                
                    EaseSineOut* easeOut1 = EaseSineOut::create(ScaleTo::create(1.5f, 1.0f));
                    EaseSineOut* easeOut2 = EaseSineOut::create(FadeIn::create(1.5f));
                
                    DelayTime* delay = DelayTime::create(0.2f);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Enemy::beginTrack,enemy));
                    Sequence* sequence = Sequence::createWithTwoActions(delay, callFunc);
                
                    Spawn* spawn = Spawn::create(easeOut1, easeOut2, sequence, NULL);
                    enemy->runAction(spawn);
                    enemy->autorelease();
                }
                else
                    CC_SAFE_DELETE(enemy);
            }
            break;
        case Enemy::EnemyType::ET_HEXAGON:
            {
                enemy = new(std::nothrow) Hexagon();
                if (enemy && enemy->init()) {
                    enemy->loadModel("hexagon.png");
                    enemy->setPosition(pos);
                    enemy->setDirection(dir);
                    //enemy->setOrientation(dir);
                    enemy->setCascadeOpacityEnabled(true);
                    enemy->setOpacity(0);
                    enemy->setScale(0.3f);
                    enemy->setActorState(ActorState::AS_UNDERCONTROL);
                    enemy->setColor(Color3B(253,153,31));
                    enemy->caculateRadius();
                    ActorsManager::getInstance()->m_Enemies.pushBack(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->addChild(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
                
                    EaseSineOut* easeOut1 = EaseSineOut::create(ScaleTo::create(1.5f, 1.0f));
                    EaseSineOut* easeOut2 = EaseSineOut::create(FadeIn::create(1.5f));
                
                    DelayTime* delay = DelayTime::create(0.2f);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Enemy::beginTrack,enemy));
                    Sequence* sequence = Sequence::createWithTwoActions(delay, callFunc);
                
                    Spawn* spawn = Spawn::create(easeOut1, easeOut2, sequence, NULL);
                    enemy->runAction(spawn);
                    enemy->autorelease();
                }
                else
                    CC_SAFE_DELETE(enemy);
            }
            break;
        case Enemy::EnemyType::ET_HEXAGON_COLORED:
            {
                enemy = new(std::nothrow) ColorHexagon();
                if (enemy && enemy->init()) {
                    enemy->loadModel("hexagon.png");
                    enemy->getModel()->setVisible(false);
                    enemy->setPosition(pos);
                    enemy->setDirection(dir);
                    //enemy->setOrientation(dir);
                    enemy->setCascadeOpacityEnabled(true);
                    enemy->setOpacity(0);
                    enemy->setScale(0.3f);
                    enemy->setActorState(ActorState::AS_UNDERCONTROL);
                    enemy->setColor(Color3B(253,153,31));
                    enemy->caculateRadius();
                    ActorsManager::getInstance()->m_Enemies.pushBack(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->addChild(enemy);
                    ActorsManager::getInstance()->m_pActorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
                    
                    ParticleSystemHelper::spawnActorWidget(ActorWidgetType::AWT_COLOR_HEXAGON_TAIL, Vec2::ZERO, enemy);
                
                    EaseSineOut* easeOut1 = EaseSineOut::create(ScaleTo::create(1.5f, 1.0f));
                    EaseSineOut* easeOut2 = EaseSineOut::create(FadeIn::create(1.5f));
                
                    DelayTime* delay = DelayTime::create(0.2f);
                    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Enemy::beginTrack,enemy));
                    Sequence* sequence = Sequence::createWithTwoActions(delay, callFunc);
                
                    Spawn* spawn = Spawn::create(easeOut1, easeOut2, sequence, NULL);
                    enemy->runAction(spawn);
                    enemy->autorelease();
                }
                else
                    CC_SAFE_DELETE(enemy);
            }
            break;
        default:
            break;
    }
    return enemy;
}
Laser* ActorsManager::spawnLaser(const cocos2d::Vec2& start, const cocos2d::Vec2& end)
{
    if(!ActorsManager::getInstance()->m_pActorLayer)
        return nullptr;
    Laser* laser = new(std::nothrow) Laser();
    if(laser)
    {
        laser->initLaser();
        laser->setStart(start);
        laser->setEnd(end);
        laser->setActorState(ActorState::AS_IDLE);
        ActorsManager::getInstance()->m_Lasers.pushBack(laser);
        ActorsManager::getInstance()->m_pActorLayer->addChild(laser);
        ActorsManager::getInstance()->m_pActorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
        laser->autorelease();
    }
    else
        CC_SAFE_DELETE(laser);
    return laser;
}
Item* ActorsManager::spawnItem(Item::ItemType type, const Vec2& pos)
{
    if(!ActorsManager::getInstance()->m_pActorLayer)
        return nullptr;
    Item* item = new(std::nothrow) Item();
    if (item) {
        switch (type) {
            case Item::IT_ACCEL:
                item->loadTexture("accel.png");
                break;
            case Item::IT_BOOM:
                item->loadTexture("boom.png");
                break;
            case Item::IT_MULTI:
                item->loadTexture("multi.png");
                break;
            case Item::IT_PROTETED:
                item->loadTexture("protected.png");
                break;
            case Item::IT_TIME:
                item->loadTexture("time.png");
                break;
            default:
                break;
        }
        item->setCascadeOpacityEnabled(true);
        item->setItemType(type);
        item->setPosition(pos);
        item->setActorState(ActorState::AS_IDLE);
        ActorsManager::getInstance()->m_Items.pushBack(item);
        ActorsManager::getInstance()->m_pActorLayer->addChild(item);
        ActorsManager::getInstance()->m_pActorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
        item->autorelease();
    }
    else
        CC_SAFE_DELETE(item);
    return item;
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
    Size boundSize =  GameController::getInstance()->getBoundSize();
    Vec2 playerPos = GameController::getInstance()->getPlayerPos();
    float playerRadius = GameController::getInstance()->getPlayer()->getRadius();
    
    //CCLOG("Current bullets number %zd", m_Bullets.size());
    for (ssize_t i = 0; i<m_Bullets.size(); ++i) {
        Bullet* bullet = m_Bullets.at(i);
        if(bullet)
        {
            float bulletRadius = bullet->getRadius();
            Vec2 bulletPos = bullet->getPosition();
            
            Vec3 min = Vec3(-bulletRadius, -bulletRadius, -0.5f) + bullet->getPosition3D();
            Vec3 max = Vec3(bulletRadius, bulletRadius, 0.5f) + bullet->getPosition3D();
            AABB aabb = AABB(min, max);
            bool isVisible = GameController::getInstance()->getActorCamera()->isVisibleInFrustum(&aabb);
            if(!isVisible)
            {
                eraseBullet(bullet);
                continue;
            }
            
            float minX = bulletPos.x - bullet->getRadius();
            float maxX = bulletPos.x + bullet->getRadius();
            float minY = bulletPos.y - bullet->getRadius();
            float maxY = bulletPos.y + bullet->getRadius();
            float boundX = boundSize.width*0.5f;
            float boundY = boundSize.height*0.5f;
            if (minY <= -boundY + bullet->getMaxSpeed() || maxY >= boundY - bullet->getMaxSpeed()){
                ParticleSystemQuad* collision = ParticleSystemHelper::spawnExplosion(ExplosionType::ET_EXPLOSION_BULLET_COLLISION, bulletPos);
                if(collision)
                {
                    Vec2 orient = bullet->getOrientation();
                    float rotationZ = CC_RADIANS_TO_DEGREES(cocos2d::Vec2::angle(orient, cocos2d::Vec2::UNIT_Y));
                    if (orient.x > 0)
                        rotationZ = -rotationZ;
                    collision->setRotation(rotationZ);
                }
                eraseBullet(bullet);
                continue;
            }
            
            if (minX <= -boundX + bullet->getMaxSpeed() || maxX >= boundX - bullet->getMaxSpeed()) {
                ParticleSystemQuad* collision = ParticleSystemHelper::spawnExplosion(ExplosionType::ET_EXPLOSION_BULLET_COLLISION, bulletPos);
                if(collision)
                {
                    Vec2 orient = bullet->getOrientation();
                    float rotationZ = CC_RADIANS_TO_DEGREES(cocos2d::Vec2::angle(orient, cocos2d::Vec2::UNIT_Y));
                    if (orient.x > 0)
                        rotationZ = 180.0f - rotationZ;
                    else
                        rotationZ = 180.0f + rotationZ;
                    collision->setRotation(rotationZ);
                }
                eraseBullet(bullet);
                continue;
            }
            
            if (bullet->getType() == GameActor::AT_PLAYER_BULLET) {
                for (ssize_t i = 0; i<m_Enemies.size(); ++i) {
                    Enemy* enemy = m_Enemies.at(i);
                    if(enemy)
                    {
                        float enemyRadius = enemy->getRadius();
                        float dist = enemy->getPosition().distance(bulletPos);
                        if (dist <= enemyRadius) {
                            enemy->setActorState(ActorState::AS_DEAD);
                            eraseEnemy(enemy);
                            eraseBullet(bullet);
                            break;
                        }
                    }
                }
            }
            else if(bullet->getType() == GameActor::AT_ENEMY_BULLET)
            {
                if(GameController::getInstance()->getPlayer()->getActorState() != ActorState::AS_DEAD)
                {
                    float dist = playerPos.distance(bulletPos);
                    if(dist <= playerRadius)
                    {
                        GameController::getInstance()->getPlayer()->setActorState(ActorState::AS_DEAD);
                        eraseBullet(bullet);
                        break;
                    }
                }
            }
        }
    }
    
    //CCLOG("Current Enemies number %zd", m_Enemies.size());
    for (ssize_t i = 0; i<m_Enemies.size(); ++i) {
        Enemy* enemy = m_Enemies.at(i);
        if(enemy)
        {
            if(GameController::getInstance()->getPlayer()->getActorState() != ActorState::AS_DEAD)
            {
                float dist = enemy->getPosition().distance(playerPos);
                if (dist <= playerRadius) {
                    GameController::getInstance()->getPlayer()->setActorState(ActorState::AS_DEAD);
                    enemy->setActorState(ActorState::AS_DEAD);
                    eraseEnemy(enemy);
                    continue;
                }
            }
            GameController::getInstance()->checkBounce(enemy);
        }
    }
    
    //CCLOG("Current Lasers number %zd", m_Lasers.size());
    for (ssize_t i = 0; i<m_Lasers.size(); ++i) {
        Laser* laser = m_Lasers.at(i);
        if(laser)
        {
            if(laser->getActorState() == ActorState::AS_DEAD)
            {
                eraseLaser(laser);
                continue;
            }
            if(GameController::getInstance()->getPlayer()->getActorState() != ActorState::AS_DEAD)
            {
                Vec2 start = laser->getStart();
                Vec2 end = laser->getEnd();
                bool intersect = UtilityHelper::checkCircleIntersectWithSegment(playerPos, playerRadius*0.3f, start, end);
                if (intersect) {
                    GameController::getInstance()->getPlayer()->setActorState(ActorState::AS_DEAD);
                    continue;
                }
            }
        }
    }
    //CCLOG("Current Items number %zd", m_Items.size());
    for (ssize_t i = 0; i<m_Items.size(); ++i) {
        Item* item = m_Items.at(i);
        if(item)
        {
            if(item->getActorState() == ActorState::AS_DEAD)
            {
                eraseItem(item);
                continue;
            }
            if(GameController::getInstance()->getPlayer()->getActorState() != ActorState::AS_DEAD)
            {
                float dist = item->getPosition().distance(playerPos);
                if (dist <= playerRadius) {
                    Item::ItemType iType = item->getItemType();
                    if(iType == Item::IT_ACCEL)
                        GameController::getInstance()->getPlayer()->addBuffer(Player::BT_ACCEL);
                    else if(iType == Item::IT_BOOM)
                        GameController::getInstance()->getPlayer()->addBuffer(Player::BT_BOOM);
                    else if(iType == Item::IT_MULTI)
                        GameController::getInstance()->getPlayer()->addBuffer(Player::BT_MULTI);
                    else if(iType == Item::IT_PROTETED)
                        GameController::getInstance()->getPlayer()->addBuffer(Player::BT_PROTECTED);
                    else if(iType == Item::IT_TIME)
                        GameController::getInstance()->getPlayer()->addBuffer(Player::BT_TIME);
                    item->setActorState(ActorState::AS_DEAD);
                    eraseItem(item);
                    continue;
                }
            }
        }
    }

}
void ActorsManager::destroy()
{
    m_pActorLayer = nullptr;
    m_Bullets.clear();
    m_Enemies.clear();
    m_Lasers.clear();
    m_Items.clear();
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
void ActorsManager::eraseLaser(Laser* laser)
{
    if(!laser)
        return;
    m_Lasers.eraseObject(laser);
    laser->removeFromParentAndCleanup(true);
}
void ActorsManager::eraseLaser(int i)
{
    auto laser = m_Lasers.at(i);
    m_Lasers.erase(i);
    laser->removeFromParentAndCleanup(true);
}
void ActorsManager::eraseItem(Item* item)
{
    if(!item)
        return;
    m_Items.eraseObject(item);
    item->removeFromParentAndCleanup(true);
}
void ActorsManager::eraseItem(int i)
{
    auto item = m_Items.at(i);
    m_Items.erase(i);
    item->removeFromParentAndCleanup(true);
}
void ActorsManager::reset()
{
    for (ssize_t i = 0; i<m_Bullets.size(); ++i) {
        Bullet* bullet = m_Bullets.at(i);
        if(bullet)
        {
            eraseBullet(bullet);
        }
    }
    for (ssize_t i = 0; i<m_Enemies.size(); ++i) {
        Enemy* enemy = m_Enemies.at(i);
        if(enemy)
        {
            enemy->setActorState(ActorState::AS_DEAD);
            eraseEnemy(enemy);
        }
    }
    for (ssize_t i = 0; i<m_Lasers.size(); ++i) {
        Laser* laser = m_Lasers.at(i);
        if(laser)
        {
            laser->setActorState(ActorState::AS_DEAD);
            eraseLaser(laser);
        }
    }
    for (ssize_t i = 0; i<m_Items.size(); ++i) {
        Item* item = m_Items.at(i);
        if(item)
        {
            item->setActorState(ActorState::AS_DEAD);
            eraseItem(item);
        }
    }
}