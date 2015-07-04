//
//  Player.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/3.
//
//

#include "Player.h"
USING_NS_CC;

Player* Player::create(PlayerType type)
{
    auto player = new (std::nothrow) Player();
    if (player && player->initWithFile("strength.obj"))
    {
        player->setTexture("IndexColor.png");
        player->setType(type);
        player->_contentSize = player->getBoundingBox().size;
        player->m_fRadius = player->_contentSize.width*0.5f;
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}
Player::Player()
{
}
void Player::setType(PlayerType type)
{
    m_Type = type;
}