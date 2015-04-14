//
//  ParticleSystemHelper.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/3/18.
//
//

#include "ParticleSystemHelper.h"
#include "GameController.h"
USING_NS_CC;

ParticleSystemQuad* ParticleSystemHelper::spawnExplosion(ExplosionType explosionType, const cocos2d::Vec2& pos)
{
    if(!GameController::getInstance()->getGameLayer())
        return nullptr;
    
    ParticleSystemQuad* explosion = nullptr;
    switch (explosionType) {
        case ET_EXPLOSION_PLAYER:
            {
                explosion= ParticleSystemQuad::create("explosion.plist");
                if(!explosion)
                {
                    CCLOG("Load explosion particle system failed! file: explosion.plist");
                    return nullptr;
                }
                explosion->setStartColor(Color4F(0.0f, 224.0f/255.0f, 252.0f/255.0f, 1.0f));
                explosion->setDuration(0.4f);
                explosion->setEmitterMode(ParticleSystem::Mode::RADIUS);
                explosion->setStartRadius(50.0f);
                explosion->setStartRadiusVar(100.0f);
                explosion->setEndRadius(300.0f);
                explosion->setEndRadiusVar(400.0f);
                explosion->setPosition(pos);
                explosion->setAutoRemoveOnFinish(true);
                GameController::getInstance()->getGameLayer()->addChild(explosion);
                GameController::getInstance()->getGameLayer()->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ET_EXPLOSION_WHITE:
            {
                explosion= ParticleSystemQuad::create("explosion.plist");
                if(!explosion)
                {
                    CCLOG("Load explosion particle system failed! file: explosion.plist");
                    return nullptr;
                }
                explosion->setScale(0.4f);
                explosion->setStartColor(Color4F::WHITE);
                explosion->setEndColor(Color4F::WHITE);
                explosion->setLife(0.5f);
                explosion->setPosition(pos);
                explosion->setAutoRemoveOnFinish(true);
                GameController::getInstance()->getGameLayer()->addChild(explosion);
                GameController::getInstance()->getGameLayer()->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ET_EXPLOSION_YELLOW:
            {
                explosion= ParticleSystemQuad::create("explosion.plist");
                if(!explosion)
                {
                    CCLOG("Load explosion particle system failed! file: explosion.plist");
                    return nullptr;
                }
                explosion->setScale(0.4f);
                explosion->setStartColor(Color4F(253.0f/255.0f, 1.0f, 12.0f/255.0f, 1.0f));
                explosion->setEndColor(Color4F(253.0f/255.0f, 1.0f, 12.0f/255.0f, 1.0f));
                explosion->setLife(0.5f);
                explosion->setPosition(pos);
                explosion->setAutoRemoveOnFinish(true);
                GameController::getInstance()->getGameLayer()->addChild(explosion);
                GameController::getInstance()->getGameLayer()->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ET_EXPLOSION_GREEN:
            {
                explosion= ParticleSystemQuad::create("explosion.plist");
                if(!explosion)
                {
                    CCLOG("Load explosion particle system failed! file: explosion.plist");
                    return nullptr;
                }
                explosion->setScale(0.4f);
                explosion->setStartColor(Color4F(64.0f/255.0f, 1.0f, 1.0f/255.0f, 1.0f));
                explosion->setEndColor(Color4F(64.0f/255.0f, 1.0f, 1.0f/255.0f, 1.0f));
                explosion->setLife(0.5f);
                explosion->setPosition(pos);
                explosion->setAutoRemoveOnFinish(true);
                GameController::getInstance()->getGameLayer()->addChild(explosion);
                GameController::getInstance()->getGameLayer()->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ET_EXPLOSION_ORANGE:
            {
                explosion= ParticleSystemQuad::create("explosion.plist");
                if(!explosion)
                {
                    CCLOG("Load explosion particle system failed! file: explosion.plist");
                    return nullptr;
                }
                explosion->setScale(0.4f);
                explosion->setStartColor(Color4F(253.0f/255.0f, 153.0f/255.0f, 31.0f/255.0f, 1.0f));
                explosion->setEndColor(Color4F(253.0f/255.0f, 153.0f/255.0f, 31.0f/255.0f, 1.0f));
                explosion->setLife(0.5f);
                explosion->setPosition(pos);
                explosion->setAutoRemoveOnFinish(true);
                GameController::getInstance()->getGameLayer()->addChild(explosion);
                GameController::getInstance()->getGameLayer()->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
            case ET_EXPLOSION_BLUE:
            {
                explosion= ParticleSystemQuad::create("explosion.plist");
                if(!explosion)
                {
                    CCLOG("Load explosion particle system failed! file: explosion.plist");
                    return nullptr;
                }
                explosion->setScale(0.4f);
                explosion->setStartColor(Color4F(0.0f, 224.0f/255.0f, 252.0f/255.0f, 1.0f));
                explosion->setEndColor(Color4F(0.0f, 224.0f/255.0f, 252.0f/255.0f, 1.0f));
                explosion->setLife(0.5f);
                explosion->setPosition(pos);
                explosion->setAutoRemoveOnFinish(true);
                GameController::getInstance()->getGameLayer()->addChild(explosion);
                GameController::getInstance()->getGameLayer()->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ET_EXPLOSION_BULLET_COLLISION:
            {
                explosion= ParticleSystemQuad::create("collisionexplosion.plist");
                if(!explosion)
                {
                    CCLOG("Load collision explosion particle system failed! file: collisionexplosion.plist");
                    return nullptr;
                }
                explosion->setLife(0.25f);
                explosion->setPosition(pos);
                explosion->setAutoRemoveOnFinish(true);
                GameController::getInstance()->getGameLayer()->addChild(explosion);
                GameController::getInstance()->getGameLayer()->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ET_EXPLOSION_ACTOR_COLLISION:
            {
                explosion= ParticleSystemQuad::create("collision.plist");
                if(!explosion)
                {
                    CCLOG("Load collision particle system failed! file: collision.plist");
                    return nullptr;
                }
                explosion->setPosition(pos);
                explosion->setAutoRemoveOnFinish(true);
                GameController::getInstance()->getGameLayer()->addChild(explosion);
                GameController::getInstance()->getGameLayer()->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ET_EXPLOSION_ACTOR_RESPAWN:
            {
                explosion= ParticleSystemQuad::create("explosion.plist");
                if(!explosion)
                {
                    CCLOG("Load explosion particle system failed! file: explosion.plist");
                    return nullptr;
                }
                explosion->setScale(0.3f);
                explosion->setDuration(0.4f);
                explosion->setStartColor(Color4F(0.0f, 224.0f/255.0f, 252.0f/255.0f, 1.0f));
                explosion->setEmitterMode(ParticleSystem::Mode::RADIUS);
                explosion->setStartRadius(100.0f);
                explosion->setStartRadiusVar(600.0f);
                explosion->setEndRadius(0.0f);
                explosion->setEndRadiusVar(50.0f);
                explosion->setRotatePerSecond(90.0f);
                explosion->setRotatePerSecondVar(0.0f);
                explosion->setLife(0.4f);
                explosion->setLifeVar(0.4f);
                explosion->setEndSize(30.0f);
                explosion->setEndSizeVar(30.0f);
                explosion->setPosition(pos);
                explosion->setAutoRemoveOnFinish(true);
                GameController::getInstance()->getGameLayer()->addChild(explosion);
                GameController::getInstance()->getGameLayer()->setCameraMask((unsigned short)CameraFlag::USER1);

            }
            break;
        case ET_EXPLOSION_CLEAR:
            {
                explosion= ParticleSystemQuad::create("clearexplosion.plist");
                if(!explosion)
                {
                    CCLOG("Load explosion particle system failed! file: clearexplosion.plist");
                    return nullptr;
                }
                explosion->setPosition(pos);
                explosion->setAutoRemoveOnFinish(true);
                GameController::getInstance()->getGameLayer()->addChild(explosion);
                GameController::getInstance()->getGameLayer()->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ET_EXPLOSION_BLACK_HOLE:
            {
                explosion= ParticleSystemQuad::create("blackhole.plist");
                if(!explosion)
                {
                    CCLOG("Load explosion particle system failed! file: blackhole.plist");
                    return nullptr;
                }
                
                explosion->setPositionType(ParticleSystem::PositionType::GROUPED);
                explosion->setPosition(pos);
                explosion->setDuration(15.0f);
                explosion->setAutoRemoveOnFinish(true);
                GameController::getInstance()->getGameLayer()->addChild(explosion);
                GameController::getInstance()->getGameLayer()->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ET_EXPLOSION_STARFIELD:
            {
                explosion= ParticleSystemQuad::create("starfield.plist");
                if(!explosion)
                {
                    CCLOG("Load explosion particle system failed! file: starfield.plist");
                    return nullptr;
                }
                GameController::getInstance()->getGameLayer()->addChild(explosion);
                GameController::getInstance()->getGameLayer()->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ET_EXPLOSION_FLARE:
            {
                explosion= ParticleSystemQuad::create("flare.plist");
                if(!explosion)
                {
                    CCLOG("Load explosion particle system failed! file: flare.plist");
                    return nullptr;
                }
                explosion->setPosition(pos);
                explosion->setAutoRemoveOnFinish(true);
                GameController::getInstance()->getGameLayer()->addChild(explosion);
                GameController::getInstance()->getGameLayer()->setCameraMask((unsigned short)CameraFlag::USER1);
                CCLOG("Flare!!!!!");
            }
            break;
        default:
            break;
    }
    return explosion;
}

ParticleSystemQuad* ParticleSystemHelper::spawnActorWidget(ActorWidgetType actorWidgetType, const cocos2d::Vec2& pos, GameActor* actor)
{
    if(!actor)
        return nullptr;
    
    ParticleSystemQuad* widget = nullptr;
    switch (actorWidgetType) {
        case ActorWidgetType::AWT_FIRE_FLARE:
            {
                widget = ParticleSystemQuad::create("explosion.plist");
                if(!widget)
                {
                    CCLOG("Load player widget particle system failed! file: explosion.plist");
                    return nullptr;
                }
                widget->setEmitterMode(ParticleSystem::Mode::RADIUS);
                widget->setStartColor(Color4F(0.0f, 224.0f/255.0f, 252.0f/255.0f, 1.0f));
                widget->setTotalParticles(100);
                widget->setStartSize(1.0f);
                widget->setLife(0.1f);
                widget->setLifeVar(0.1f);
                widget->setPositionType(ParticleSystem::PositionType::RELATIVE);
                widget->setPosition(pos);
                widget->setAutoRemoveOnFinish(true);
                actor->addChild(widget);
                actor->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ActorWidgetType::AWT_FIRE_FLARE_MULTI:
            {
                widget = ParticleSystemQuad::create("explosion.plist");
                if(!widget)
                {
                    CCLOG("Load player widget particle system failed! file: explosion.plist");
                    return nullptr;
                }
                widget->setEmitterMode(ParticleSystem::Mode::RADIUS);
                widget->setStartColor(Color4F(174.0f/255.0f, 250.0f/255.0f, 27.0f/255.0f, 1.0f));
                widget->setEndColor(Color4F(174.0f/255.0f, 250.0f/255.0f, 27.0f/255.0f, 1.0f));
                widget->setTotalParticles(100);
                widget->setStartSize(1.0f);
                widget->setLife(0.1f);
                widget->setLifeVar(0.1f);
                widget->setPositionType(ParticleSystem::PositionType::RELATIVE);
                widget->setPosition(pos);
                widget->setAutoRemoveOnFinish(true);
                actor->addChild(widget);
                actor->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ActorWidgetType::AWT_PLAYER_TAIL:
            {
                widget = ParticleSystemQuad::create("tail.plist");
                if(!widget)
                {
                    CCLOG("Load player widget particle system failed! file: tail.plist");
                    return nullptr;
                }
                widget->setPositionType(ParticleSystem::PositionType::FREE);
                widget->setPosition(pos);
                widget->setStartSize(6.0f);
                widget->setStartSizeVar(1.0f);
                widget->setRotatePerSecond(30.0f);
                widget->setAutoRemoveOnFinish(true);
                actor->addChild(widget);
                actor->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ActorWidgetType::AWT_COLOR_CIRCLE_TAIL:
            {
                widget = ParticleSystemQuad::create("colorgeometry.plist");
                if(!widget)
                {
                    CCLOG("Load actor widget particle system failed! file: colorgeometry.plist");
                    return nullptr;
                }
                widget->setPositionType(ParticleSystem::PositionType::FREE);
                widget->setPosition(pos);
                widget->setTotalParticles(50);
                widget->setSpeed(0);
                widget->setSpeedVar(0);
                widget->setScale(0.5f);
                widget->setAutoRemoveOnFinish(true);
                actor->addChild(widget);
                actor->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ActorWidgetType::AWT_COLOR_TRIANGLE_TAIL:
            {
                widget = ParticleSystemQuad::create("colorgeometry.plist");
                if(!widget)
                {
                    CCLOG("Load actor widget particle system failed! file: colorgeometry.plist");
                    return nullptr;
                }
                widget->setPositionType(ParticleSystem::PositionType::FREE);
                widget->setPosition(pos);
                widget->setTotalParticles(50);
                widget->setSpeed(0);
                widget->setSpeedVar(0);
                widget->setScale(0.5f);
                Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("triangle.png");
                widget->setTexture(texture);
                widget->setAutoRemoveOnFinish(true);
                actor->addChild(widget);
                actor->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ActorWidgetType::AWT_COLOR_DIAMOND_TAIL:
            {
                widget = ParticleSystemQuad::create("colorgeometry.plist");
                if(!widget)
                {
                    CCLOG("Load actor widget particle system failed! file: colorgeometry.plist");
                    return nullptr;
                }
                widget->setPositionType(ParticleSystem::PositionType::FREE);
                widget->setPosition(pos);
                widget->setTotalParticles(50);
                widget->setSpeed(0);
                widget->setSpeedVar(0);
                widget->setScale(0.5f);
                Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("diamond.png");
                widget->setTexture(texture);
                widget->setAutoRemoveOnFinish(true);
                actor->addChild(widget);
                actor->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ActorWidgetType::AWT_COLOR_STAR_TAIL:
            {
                widget = ParticleSystemQuad::create("colorgeometry.plist");
                if(!widget)
                {
                    CCLOG("Load actor widget particle system failed! file: colorgeometry.plist");
                    return nullptr;
                }
                widget->setPositionType(ParticleSystem::PositionType::FREE);
                widget->setPosition(pos);
                widget->setTotalParticles(50);
                widget->setSpeed(0);
                widget->setSpeedVar(0);
                widget->setScale(0.5f);
                Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("star.png");
                widget->setTexture(texture);
                widget->setAutoRemoveOnFinish(true);
                actor->addChild(widget);
                actor->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case ActorWidgetType::AWT_COLOR_HEXAGON_TAIL:
            {
                widget = ParticleSystemQuad::create("colorgeometry.plist");
                if(!widget)
                {
                    CCLOG("Load actor widget particle system failed! file: colorgeometry.plist");
                    return nullptr;
                }
                widget->setPositionType(ParticleSystem::PositionType::RELATIVE);
                widget->setPosition(pos);
                widget->setScale(0.6f);
                Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("hexagon.png");
                widget->setTexture(texture);
                widget->setAutoRemoveOnFinish(true);
                actor->addChild(widget);
                actor->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        default:
            break;
    }
    return widget;
}