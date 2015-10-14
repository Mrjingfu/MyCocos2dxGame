//
//  BaseDoor.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/14.
//
//

#include "BaseDoor.hpp"
USING_NS_CC;
BaseDoor::BaseDoor()
{
    m_DoorState = DS_CLOSED;
    m_pFakeDoor = 0;
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
    switch (state) {
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
    
    m_DoorState = state;
    ///处理下一个状态进入逻辑
    switch (m_DoorState) {
        case BaseDoor::DS_CLOSED:
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
void BaseDoor::onEnterClosed()
{
}
void BaseDoor::onExitClosed()
{
}

void BaseDoor::onEnterOpened()
{
}
void BaseDoor::onExitOpened()
{
}

void BaseDoor::onEnterLocked()
{
}
void BaseDoor::onExitLocked()
{
}
void BaseDoor::onEnterHide()
{
}
void BaseDoor::onExitHide()
{
}