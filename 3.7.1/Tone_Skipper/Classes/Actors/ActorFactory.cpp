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
            player = new(std::nothrow) Pudge();
            if(player && player->loadModel() && player->loadAnimations())
            {
                player->setPlayerState(Player::PS_IDLE);
                player->autorelease();
                player->setScale(0.6);
            }
            else
                CC_SAFE_RELEASE_NULL(player);
            break;
        case Player::PT_LEA:
            
            break;
        default:
            break;
    }
    return player;
}