//
//  MonsterPropLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#include "NpcPropLayer.hpp"

#include "UtilityHelper.h"
#include "PopupUILayerManager.h"
#include "Npc.hpp"
USING_NS_CC;
NpcPropLayer::NpcPropLayer()
{
   
}
NpcPropLayer::~NpcPropLayer()
{
    
}
bool NpcPropLayer::initUi()
{
    if (!load("monsterInfoLayer.csb",false))
        return false;
    setContentSize(m_pRootNode->getContentSize());
    m_pRootNode->setPosition(getContentSize()*0.5);
    return true;
}
bool NpcPropLayer::addEvents()
{
    
    if(!CharacterPropLayer::addEvents())
        return false;
    
    m_pCharacterHpBar->setDirection(cocos2d::ui::LoadingBar::Direction::RIGHT);
    m_pCharacterMpBar->setDirection(cocos2d::ui::LoadingBar::Direction::RIGHT);
    
    m_pCharacterCurHp->setString("??");
    m_pCharacterMaxHp->setString("/??");
    m_pCharacterCurMp->setString("??");
    m_pCharacterMaxMp->setString("/??");
    m_pCharacterLevel->setString("???");
    return true;
}

void NpcPropLayer::updateCharacterBuff()
{
    
}
void NpcPropLayer::setNpc(Npc *npc)
{
    
    std::string npcName = npc->getNpcName();
    m_pCharacterIcon->loadTexture(npc->getIconRes(),TextureResType::PLIST);
    m_pCharacterIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pCharacterName->setString(npcName);
}
void NpcPropLayer::updateCharacterProp()
{

}