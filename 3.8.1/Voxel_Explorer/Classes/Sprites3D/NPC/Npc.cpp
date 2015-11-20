//
//  Npc.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/17.
//
//

#include "Npc.hpp"
#include "LevelResourceManager.h"
#include "UtilityHelper.h"
USING_NS_CC;
const std::string NPC_NAMES[] = {
    "NPCN_CHILD",           ///小孩
    "NPCN_SHOPGIRL",        ///女售货员
    "NPCN_OLDLADY",         ///老太太
    "NPCN_KNIGHT",          ///小骑士
    "NPCN_WEIRDO",          ///怪蜀黍
    "NPCN_OLDMAN",          ///老头
    "NPCN_LITTLEWITCH",     ///小魔女
    "NPCN_NURSE"            ///小护士
};
Npc* Npc::create(NPC_TYPE type)
{
    std::string model = LevelResourceManager::getInstance()->getItemModelRes(NPC_NAMES[type]);
    auto npc = new (std::nothrow) Npc();
    if (npc && npc->initWithFile(model))
    {
        npc->m_Type = type;
        npc->setCameraMask((unsigned int)CameraFlag::USER1);
        npc->setLightMask((unsigned int)LightFlag::LIGHT0);
        npc->setCascadeOpacityEnabled(true);
        npc->autorelease();
        return npc;
    }
    CC_SAFE_DELETE(npc);
    return nullptr;

}
Npc::Npc()
{
    m_Type = NPC_UNKNOWN;
}
Npc::~Npc()
{
}
std::string Npc::getDesc()
{
    return UtilityHelper::getLocalString(NPC_NAMES[m_Type] + "_DESC");
}