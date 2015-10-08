//
//  TestPlayer.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/8.
//
//

#include "TestPlayer.hpp"
USING_NS_CC;

TestPlayer* TestPlayer::create(const std::string& modelPath)
{
    auto player = new (std::nothrow) TestPlayer();
    if (player && player->initWithFile(modelPath))
    {
        player->_contentSize = player->getBoundingBox().size;
        player->setCameraMask((unsigned int)CameraFlag::USER1);
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}
TestPlayer::TestPlayer()
{
    m_curState  = PS_UNKNOWN;
    m_dir       = PD_FORWARD;
}
TestPlayer::~TestPlayer()
{
}
