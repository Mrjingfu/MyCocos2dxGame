//
//  ActorFactory.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/7.
//
//

#include "ActorFactory.h"
#include "Nilo.h"
#include "Pudge.h"
#include "QuestionMark.h"
#include "ExcalmationMark.h"
USING_NS_CC;

ActorFactory* g_pActorFactoryInstance = nullptr;
ActorFactory* ActorFactory::getInstance()
{
    if( g_pActorFactoryInstance == nullptr )
        g_pActorFactoryInstance = new ActorFactory();
    
    return g_pActorFactoryInstance;
}
ActorFactory::ActorFactory()
{
    
}
ActorFactory::~ActorFactory()
{
}
Player* ActorFactory::createPlayer(Player::PlayerType type)
{
    Player* player = nullptr;
    switch (type) {
        case Player::PT_NILO:
        {
            player = new(std::nothrow) Nilo();
            if(player && player->loadModel() && player->loadAnimations())
            {
                player->setPlayerState(Player::PS_IDLE);
                player->autorelease();
            }
            else
                CC_SAFE_RELEASE_NULL(player);
        }
            break;
        case Player::PT_PUDGE:
        {
            player = new(std::nothrow) Pudge();
            if(player && player->loadModel() && player->loadAnimations())
            {
                player->setPlayerState(Player::PS_IDLE);
                player->autorelease();
                player->setScale(0.6);
            }
            else
                CC_SAFE_RELEASE_NULL(player);
        }
            break;
            
        case Player::PT_LEA:
            
            break;
        default:
            break;
    }
    return player;
}
UsableItem* ActorFactory::createUsableItem(UsableItem::USABLE_ITEM_TYPE type)
{
    UsableItem* item = nullptr;
    switch (type) {
        case UsableItem::UIT_QUESTION_MARK:
            {
                item = new(std::nothrow) QuestionMark();
                if(item && item->loadModel())
                {
                    item->setAnchorPoint(Vec2(0.5,0));
                    item->setScale(0.5f);
                    item->autorelease();
                }
                else
                    CC_SAFE_RELEASE_NULL(item);
            }
            break;
        default:
            break;
    }
    return item;
}
SceneItem* ActorFactory::createSceneItem(SceneItem::SCENE_ITEM_TYPE type)
{
    SceneItem* item = nullptr;
    switch (type) {
        case SceneItem::SIT_EXCALMATION_MARK:
        {
            item = new(std::nothrow) ExcalmationMark();
            if(item && item->loadModel())
            {
                item->setAnchorPoint(Vec2(0.5,0));
                item->setScale(0.5f);
                item->autorelease();
            }
            else
                CC_SAFE_RELEASE_NULL(item);
        }
            break;
        default:
            break;
    }
    return item;
}