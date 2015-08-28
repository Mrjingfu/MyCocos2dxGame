//
//  ActorMgr.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/26.
//
//

#include "ActorMgr.h"
#include "Nilo.h"
USING_NS_CC;

ActorMgr* g_pActorMgrInstance = nullptr;
ActorMgr* ActorMgr::getInstance()
{
    if( g_pActorMgrInstance == nullptr )
        g_pActorMgrInstance = new ActorMgr();
    
    return g_pActorMgrInstance;
}
ActorMgr::ActorMgr()
{

}
ActorMgr::~ActorMgr()
{
}
Player* ActorMgr::createPlayer(Player::PlayerType type)
{
    Player* player = nullptr;
    switch (type) {
        case Player::PT_NILO:
            {
                player = new(std::nothrow) Nilo();
                if(player && player->loadModel() && player->loadAnimations())
                {
                    player->setPlayerState(Player::PS_IDLE);
                    player->setScale(4);
                    player->autorelease();
                }
                else
                    CC_SAFE_RELEASE_NULL(player);
            }
            break;
        case Player::PT_PUDGE:
            break;
        case Player::PT_LEA:
            
            break;
        default:
            break;
    }
    return player;
}