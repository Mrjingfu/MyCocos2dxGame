//
//  Door.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "Door.h"
USING_NS_CC;

Door* Door::create()
{
    Door *pRet = new(std::nothrow) Door();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}


Door::Door()
{
    m_Type = DT_EMPTY;
}
Door::~Door()
{
}
bool Door::init()
{
    return true;
}

Door::DOOR_TYPE Door::getDoorType() const
{
    return m_Type;
}
void Door::setDoorType(Door::DOOR_TYPE type)
{
    m_Type = type;
}

Vec2 Door::getPos() const
{
    return m_Pos;
}
void Door::setPos(const cocos2d::Vec2& pos)
{
    if(m_Pos != pos)
        m_Pos = pos;
}