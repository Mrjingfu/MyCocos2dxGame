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
        case ET_EXPLOSION_BLUE:
            {
                explosion= ParticleSystemQuad::create("explosion.plist");
                if(!explosion)
                {
                    CCLOG("Load explosion particle system failed! file: explosion.plist");
                    return nullptr;
                }
                explosion->setScale(0.8f);
                explosion->setStartColor(Color4F(0.0f, 224.0f/255.0f, 252.0f/255.0f, 1.0f));
                explosion->setLife(1.0f);
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
                explosion->setLife(0.5f);
                explosion->setPosition(pos);
                explosion->setAutoRemoveOnFinish(true);
                GameController::getInstance()->getGameLayer()->addChild(explosion);
                GameController::getInstance()->getGameLayer()->setCameraMask((unsigned short)CameraFlag::USER1);
            }
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
        default:
            break;
    }
    return explosion;
}

ParticleSystemQuad* ParticleSystemHelper::spawnPlayerWidget(PlayerWidgetType playerWidgetType, const cocos2d::Vec2& pos)
{
    if(!GameController::getInstance()->getPlayer())
        return nullptr;
    
    ParticleSystemQuad* widget = nullptr;
    switch (playerWidgetType) {
        case PlayerWidgetType::PWT_FIRE_FLARE:
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
                GameController::getInstance()->getPlayer()->addChild(widget);
                GameController::getInstance()->getPlayer()->setCameraMask((unsigned short)CameraFlag::USER1);
            }
            break;
        case PlayerWidgetType::PWT_TAIL:
            {
                widget = ParticleSystemQuad::create("tail.plist");
                if(!widget)
                {
                    CCLOG("Load player widget particle system failed! file: tail.plist");
                    return nullptr;
                }
                widget->setPositionType(ParticleSystem::PositionType::FREE);
                widget->setPosition(pos);
                widget->setStartSize(8.0f);
                widget->setStartSizeVar(1.0f);
                widget->setAutoRemoveOnFinish(true);
                GameController::getInstance()->getPlayer()->addChild(widget);
                GameController::getInstance()->getPlayer()->setCameraMask((unsigned short)CameraFlag::USER1);
            }
        default:
            break;
    }
    return widget;
}