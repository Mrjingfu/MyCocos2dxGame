//
//  PlayerProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/19.
//
//

#include "PlayerProperty.hpp"
USING_NS_CC;

PlayerProperty* g_pPlayerPropertyInstance = nullptr;
PlayerProperty* PlayerProperty::getInstance()
{
    if( g_pPlayerPropertyInstance == nullptr )
        g_pPlayerPropertyInstance = new PlayerProperty();
    
    return g_pPlayerPropertyInstance;
}
PlayerProperty::PlayerProperty()
{
}
PlayerProperty::~PlayerProperty()
{
}


void PlayerProperty::setExp(CChaosNumber exp)
{
}
void PlayerProperty::setCurrentHP(CChaosNumber hp)
{
}
void PlayerProperty::setCurrentMP(CChaosNumber mp)
{
}
void PlayerProperty::EquipWeapon(CChaosNumber id)
{
}
void PlayerProperty::EquipArmor(CChaosNumber id)
{
}
void PlayerProperty::EquipOrnaments(CChaosNumber id)
{
}