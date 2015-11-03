//
//  BaseDoor.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/14.
//
//

#include "BaseDoor.hpp"
#include "BaseLevel.h"
USING_NS_CC;
const char* DOOR_MODEL_NAMES[] = {
    "DMN_STANDARD",
    "DMN_MAX"
};
BaseDoor::BaseDoor()
{
    m_DoorState = DS_UNKNOWN;
    m_DoorLastState = DS_UNKNOWN;
    m_pFakeDoor = 0;
    m_OpenType = DOT_STANDARD;
}
BaseDoor::~BaseDoor()
{
}

BaseDoor::DoorState BaseDoor::getDoorState() const
{
    return m_DoorState;
}
void BaseDoor::setDoorState(BaseDoor::DoorState state)
{
    if (m_DoorState == state)
        return;
    
    ///处理上一个状态退出逻辑
    switch (m_DoorState) {
        case BaseDoor::DS_CLOSED:
            onExitClosed();
            break;
        case BaseDoor::DS_OPENED:
            onExitOpened();
            break;
        case BaseDoor::DS_LOCKED:
            onExitLocked();
            break;
        case BaseDoor::DS_HIDE:
            onExitHide();
            break;
        default:
            break;
    }
    m_DoorLastState = m_DoorState;
    m_DoorState = state;
    ///处理下一个状态进入逻辑
    switch (m_DoorState) {
        case BaseDoor::DS_CLOSED:
            if(m_DoorLastState != BaseDoor::DS_HIDE)
                onEnterClosed();
            break;
        case BaseDoor::DS_OPENED:
            onEnterOpened();
            break;
        case BaseDoor::DS_LOCKED:
            onEnterLocked();
            break;
        case BaseDoor::DS_HIDE:
            onEnterHide();
            break;
        default:
            break;
    }
}
void BaseDoor::setActorDir( ActorDir dir )
{
    m_dir = dir;
    if(!m_pFakeDoor)
        return;
    switch (m_dir) {
        case AD_FORWARD:
            m_pFakeDoor->setRotation3D(Vec3(0,180,0));
            break;
        case AD_LEFT:
            m_pFakeDoor->setRotation3D(Vec3(0,-90,0));
            break;
        case AD_RIGHT:
            m_pFakeDoor->setRotation3D(Vec3(0,90,0));
            break;
        case AD_BACK:
            m_pFakeDoor->setRotation3D(Vec3(0,0,0));
            break;
        default:
            break;
    }
}
void BaseDoor::onEnterClosed()
{
    if(!m_pFakeDoor)
        return;
    if (m_dir == AD_FORWARD || m_dir == AD_BACK) {
        int flag = TileInfo::PASSABLE | TileInfo::USEABLE;
        if(m_DoorLastState == BaseDoor::DS_UNKNOWN || m_DoorLastState == BaseDoor::DS_LOCKED)
        {
            m_pFakeDoor->setVisible(true);
            updateTerrainTileFlag(flag);
        }
        else
        {
            EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(0.5f, Vec3(getPositionX()+TerrainTile::CONTENT_SCALE, getPositionY(), getPositionZ())));
            CallFunc* callback1 = CallFunc::create(CC_CALLBACK_0(BaseDoor::setVisible,m_pFakeDoor, true));
            CallFunc* callback2 = CallFunc::create(CC_CALLBACK_0(BaseDoor::updateTerrainTileFlag,this, flag));
            Sequence* sequence = Sequence::create(moveTo, callback1, callback2, NULL);
            m_pFakeDoor->runAction(sequence);
        }
    }
    else if(m_dir == AD_LEFT || m_dir == AD_RIGHT)
    {
        int flag = TileInfo::PASSABLE | TileInfo::USEABLE;
        if(m_DoorLastState == BaseDoor::DS_UNKNOWN || m_DoorLastState == BaseDoor::DS_LOCKED)
        {
            m_pFakeDoor->setVisible(true);
            updateTerrainTileFlag(flag);
        }
        else
        {
            EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(0.5f, Vec3(getPositionX(),getPositionY(), getPositionZ()+TerrainTile::CONTENT_SCALE)));
            CallFunc* callback1 = CallFunc::create(CC_CALLBACK_0(BaseDoor::setVisible,m_pFakeDoor, true));
            CallFunc* callback2 = CallFunc::create(CC_CALLBACK_0(BaseDoor::updateTerrainTileFlag,this, flag));
            Sequence* sequence = Sequence::create(moveTo, callback1, callback2, NULL);
            m_pFakeDoor->runAction(sequence);
        }
    }
}
void BaseDoor::onExitClosed()
{
}

void BaseDoor::onEnterOpened()
{
    if(!m_pFakeDoor)
        return;
    if (m_dir == AD_FORWARD || m_dir == AD_BACK) {
        int flag = TileInfo::PASSABLE;
        if(m_DoorLastState == BaseDoor::DS_UNKNOWN)
        {
            m_pFakeDoor->setVisible(false);
            updateTerrainTileFlag(flag);
        }
        else
        {
            EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(0.5f, Vec3(m_pFakeDoor->getPositionX()-TerrainTile::CONTENT_SCALE, m_pFakeDoor->getPositionY(), m_pFakeDoor->getPositionZ())));
            CallFunc* callback1 = CallFunc::create(CC_CALLBACK_0(BaseDoor::setVisible,m_pFakeDoor, false));
            CallFunc* callback2 = CallFunc::create(CC_CALLBACK_0(BaseDoor::updateTerrainTileFlag,this, flag));
            Sequence* sequence = Sequence::create(moveTo, callback1, callback2, NULL);
            m_pFakeDoor->runAction(sequence);
        }
    }
    else if(m_dir == AD_LEFT || m_dir == AD_RIGHT)
    {
        int flag = TileInfo::PASSABLE;
        if(m_DoorLastState == BaseDoor::DS_UNKNOWN)
        {
            m_pFakeDoor->setVisible(false);
            updateTerrainTileFlag(flag);
        }
        else
        {
            EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(0.5f, Vec3(m_pFakeDoor->getPositionX(),m_pFakeDoor->getPositionY(), m_pFakeDoor->getPositionZ()+TerrainTile::CONTENT_SCALE)));
            CallFunc* callback1 = CallFunc::create(CC_CALLBACK_0(BaseDoor::setVisible,m_pFakeDoor, false));
            CallFunc* callback2 = CallFunc::create(CC_CALLBACK_0(BaseDoor::updateTerrainTileFlag,this, flag));
            Sequence* sequence = Sequence::create(moveTo, callback1, callback2, NULL);
            m_pFakeDoor->runAction(sequence);
        }
    }
}
void BaseDoor::onExitOpened()
{
}

void BaseDoor::onEnterLocked()
{
    if(m_pFakeDoor)
    {
        if(m_DoorLastState == BaseDoor::DS_UNKNOWN)
            m_pFakeDoor->setColor(Color3B::ORANGE);
        else
        {
            EaseSineOut* fadeIn = EaseSineOut::create(TintTo::create(0.5f, Color3B::ORANGE));
            m_pFakeDoor->runAction(fadeIn);
        }
    }
}
void BaseDoor::onExitLocked()
{
    if(m_pFakeDoor)
    {
        EaseSineOut* fadeOut = EaseSineOut::create(TintTo::create(0.5f, Color3B::WHITE));
        m_pFakeDoor->runAction(fadeOut);
    }
}
void BaseDoor::onEnterHide()
{
    EaseSineOut* fadeIn = EaseSineOut::create(FadeIn::create(0.5f));
    this->runAction(fadeIn);
}
void BaseDoor::onExitHide()
{
    EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(0.5f));
    this->runAction(fadeOut);
}
void BaseDoor::setVisited(bool visited)
{
    unsigned int lightmask = getLightMask();
    if (visited)
        lightmask = lightmask | (unsigned int)LightFlag::LIGHT1;
    else
        lightmask = lightmask &~ (unsigned int)LightFlag::LIGHT1;
    setLightMask(lightmask);
    if(m_pFakeDoor)
        m_pFakeDoor->setLightMask(lightmask);
}