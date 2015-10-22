//
//  StandardMonster.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#include "StandardMonster.hpp"
USING_NS_CC;

StandardMonster* StandardMonster::create(BaseMonster::MonsterType type)
{
    auto monster = new (std::nothrow) StandardMonster();
    if (monster && monster->initWithFile("16x16x16.c3b"))
    {
        monster->m_Type = type;
        monster->setCameraMask((unsigned int)CameraFlag::USER1);
        monster->setLightMask((unsigned int)LightFlag::LIGHT0);
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return nullptr;
}

StandardMonster::StandardMonster()
{
}
StandardMonster::~StandardMonster()
{
}