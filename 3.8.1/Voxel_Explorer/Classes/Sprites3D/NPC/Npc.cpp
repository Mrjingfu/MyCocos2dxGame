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
#include "VoxelExplorer.h"
#include "Player.hpp"
#include "OutlineEffect3D.h"
#include "StatisticsManager.hpp"
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
        
        OutlineEffect3D* outline = OutlineEffect3D::create();
        outline->setOutlineColor(Vec3(0.1f, 0.1f, 0.1f));
        outline->setOutlineWidth(0.05f);
        npc->addEffect(outline, 1);
        
        npc->autorelease();
        return npc;
    }
    CC_SAFE_DELETE(npc);
    return nullptr;

}
Npc::Npc()
{
    m_Type = NPC_UNKNOWN;
    m_State = NPCS_UNKNOWN;
}
Npc::~Npc()
{
}
std::string Npc::getIconRes()
{
    return LevelResourceManager::getInstance()->getItemIconRes(NPC_NAMES[m_Type]);
}
std::string Npc::getDesc()
{
    return UtilityHelper::getLocalString(NPC_NAMES[m_Type] + "_DESC");
}
std::string Npc::getNpcName()
{
    return UtilityHelper::getLocalString(NPC_NAMES[m_Type]);
}
std::string Npc::getNpcContent()
{
    return UtilityHelper::getLocalString(NPC_NAMES[m_Type]+"_CONTENT");
}
void Npc::setState(NPCState state)
{
    if(m_State == state && m_State != NPCS_ANSWER)
        return;
    ///处理上一个状态退出逻辑
    switch (m_State) {
        case Npc::NPCS_IDLE:
            onExitIdle();
            break;
        case Npc::NPCS_ANSWER:
            onExitAnswer();
            break;
        case Npc::NPCS_FADEOUT:
            onExitFadeOut();
            break;
        default:
            break;
    }
    m_State = state;
    ///处理下一个状态进入逻辑
    switch (m_State) {
        case Npc::NPCS_IDLE:
            onEnterIdle();
            break;
        case Npc::NPCS_ANSWER:
            onEnterAnswer();
            break;
        case Npc::NPCS_FADEOUT:
            onEnterFadeOut();
            break;
        default:
            break;
    }
}
void Npc::setActorDir( ActorDir dir )
{
    if(m_dir == dir)
    {
        DelayTime* delay = DelayTime::create(0.5f);
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Npc::doAnswer, this));
        Sequence* sequence = Sequence::create(delay, callback, nullptr);
        this->runAction(sequence);
        return;
    }
    m_dir = dir;
    EaseSineOut* rotateTo = nullptr;
    switch (m_dir) {
        case AD_FORWARD:
            rotateTo = EaseSineOut::create(RotateTo::create(0.5f, Vec3(0,180,0)));
            break;
        case AD_LEFT:
            rotateTo = EaseSineOut::create(RotateTo::create(0.5f, Vec3(0,-90,0)));
            break;
        case AD_RIGHT:
            rotateTo = EaseSineOut::create(RotateTo::create(0.5f, Vec3(0,90,0)));
            break;
        case AD_BACK:
            rotateTo = EaseSineOut::create(RotateTo::create(0.5f, Vec3(0,0,0)));
            break;
        default:
            break;
    }
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Npc::doAnswer, this));
    Sequence* sequence = Sequence::create(rotateTo, callback, nullptr);
    this->runAction(sequence);
}
void Npc::onEnterIdle()
{
    m_dir = AD_BACK;
    EaseSineOut*rotateTo = EaseSineOut::create(RotateTo::create(0.5f, Vec3(0,0,0)));
    this->runAction(rotateTo);
}
void Npc::onExitIdle()
{
}

void Npc::onEnterAnswer()
{
    Player* player = VoxelExplorer::getInstance()->getPlayer();
    if(player)
    {
        Vec2 playerPos = player->getPosInMap();
        if(playerPos.x > getPosInMap().x)
            setActorDir(AD_RIGHT);
        else if(playerPos.x < getPosInMap().x)
            setActorDir(AD_LEFT);
        else
        {
            if(playerPos.y > getPosInMap().y)
                setActorDir(AD_FORWARD);
            else if(playerPos.y < getPosInMap().y)
                setActorDir(AD_BACK);
        }
    }
}
void Npc::onExitAnswer()
{
}

void Npc::onEnterFadeOut()
{
    removeTerrainTileFlag(TileInfo::USEABLE);
    EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(0.5f));
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Npc::destroySelf, this));
    Sequence* sequence = Sequence::create(fadeOut, callback, nullptr);
    this->runAction(sequence);
}
void Npc::onExitFadeOut()
{
}
void Npc::destroySelf()
{
    this->removeFromParentAndCleanup(true);
}
void Npc::doAnswer()
{
    switch (m_Type) {
        case NPC_CHILD:
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_NPC_CHILD_ANSWER, this);
            break;
        case NPC_SHOPGIRL:
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_NPC_SHOPGIRL_ANSWER, this);
            break;
        case NPC_OLDLADY:
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_NPC_OLDLADY_ANSWER, this);
            break;
        case NPC_KNIGHT:
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_NPC_KNIGHT_ANSWER, this);
            break;
        case NPC_WEIRDO:
            StatisticsManager::getInstance()->addMeetThiefNum();
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_NPC_WEIRDO_ANSWER, this);
            break;
        case NPC_OLDMAN:
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_NPC_OLDMAN_ANSWER, this);
            break;
        case NPC_LITTLEWITCH:
            StatisticsManager::getInstance()->addMeetHagNum();
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_NPC_LITTLEWITCH_ANSWER, this);
            break;
        case NPC_NURSE:
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_NPC_NURSE_ANSWER, this);
            break;
        default:
            break;
    }
}
void Npc::endAnswer()
{
    switch (m_Type) {
        case NPC_SHOPGIRL:
        case NPC_OLDLADY:
        case NPC_KNIGHT:
            setState(NPCS_IDLE);
            break;
        case NPC_CHILD:
        case NPC_WEIRDO:
        case NPC_OLDMAN:
            setState(NPCS_FADEOUT);
            break;
        case NPC_LITTLEWITCH:
            {
                int rand = cocos2d::random(4, 4);
                if (rand == 0) {
                    PlayerProperty::getInstance()->addMoney(10000);
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_LITTLEWITCH_ADDMONEY);
                }
                else if(rand == 1)
                {
                    PickableItem::PickableItemType type = (PickableItem::PickableItemType)cocos2d::random((int)PickableItem::PIT_POTION_MINORHEALTH, (int)PickableItem::PIT_POTION_UNIVERSAL);
                    PlayerProperty::getInstance()->addItemToBag(type, 1);
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_LITTLEWITCH_ADDPOTION);
                }
                else if(rand == 2)
                {
                    PickableItem::PickableItemType type = (PickableItem::PickableItemType)cocos2d::random((int)PickableItem::PIT_SCROLL_INDENTIFY, (int)PickableItem::PIT_SCROLL_DESTINY);
                    PlayerProperty::getInstance()->addItemToBag(type, 1);
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_LITTLEWITCH_ADDSCROLL);
                }
                else if(rand == 3)
                {
                    if(VoxelExplorer::getInstance()->getCurrentLevel())
                    {
                        VoxelExplorer::getInstance()->getCurrentLevel()->createSiegeMonsters(getPosInMap());
                        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_LITTLEWITCH_SUMMONMONSTER);
                    }
                    
                }
                else if(rand == 4)
                {
                    if(VoxelExplorer::getInstance()->getPlayer())
                    {
                        VoxelExplorer::getInstance()->getPlayer()->addPlayerBuffer(PlayerBuffer::PB_WEAK);
                        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_LITTLEWITCH_WEAK);
                    }
                }
                setState(NPCS_FADEOUT);
            }
            break;
        case NPC_NURSE:
            {
                if(VoxelExplorer::getInstance()->getPlayer())
                    VoxelExplorer::getInstance()->getPlayer()->healedbyNurse();
                setState(NPCS_FADEOUT);
            }
            break;
        default:
            break;
    }
}
void Npc::setVisited(bool visited)
{
    setVisible(visited);
    unsigned int lightmask = getLightMask();
    if (visited)
    {
        lightmask = lightmask | (unsigned int)LightFlag::LIGHT1;
        lightmask = lightmask | (unsigned int)LightFlag::LIGHT2;
    }
    else
    {
        lightmask = lightmask &~ (unsigned int)LightFlag::LIGHT1;
        lightmask = lightmask &~ (unsigned int)LightFlag::LIGHT2;
    }
    setLightMask(lightmask);
}
