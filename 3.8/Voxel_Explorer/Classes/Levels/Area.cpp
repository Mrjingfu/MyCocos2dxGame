//
//  Area.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "Area.h"
#include "BaseLevel.h"
USING_NS_CC;

Area::AREA_TYPE AT_SpecialTypes[] = { Area::AREA_TYPE::AT_SPECIAL_SECRET, Area::AREA_TYPE::AT_SPECIAL_WEAKFLOOR };
std::vector<Area::AREA_TYPE> Area::SPECIALS(AT_SpecialTypes, AT_SpecialTypes+ sizeof(AT_SpecialTypes)/sizeof(Area::AREA_TYPE));
Area* Area::create()
{
    Area *pRet = new(std::nothrow) Area();
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
Area::Area()
{
    m_Type = AT_UNKNOWN;
    m_nWeight = 1;
}
bool Area::init()
{
    return true;
}

void Area::addNeigbourArea( Area* other )
{
    if(!other)
        return;
    cocos2d::Rect rect = getIntersectRect(other);
    if((rect.size.width == 0 && rect.size.height>=3) || (rect.size.height == 0 && rect.size.width >= 3))
    {
        m_Neigbours.push_back(other);
        other->m_Neigbours.push_back(this);
    }
}
void Area::connectArea(Area* other)
{
    if(!other)
        return;
    if (m_ConnectedAreas.find(other) == m_ConnectedAreas.end()) {
        m_ConnectedAreas[other] = nullptr;
        other->m_ConnectedAreas[this] = nullptr;
    }
}
Door* Area::getEntrance()
{
    if(m_ConnectedAreas.empty())
        return nullptr;
    return (*m_ConnectedAreas.begin()).second;
}

bool Area::checkInside(int p)
{
    int x = p % BaseLevel::WIDTH;
    int y = p / BaseLevel::HEIGHT;
    return  x > m_Rect.getMinX() && x < m_Rect.getMaxX() && y > m_Rect.getMinY() && y < m_Rect.getMaxY();
}
cocos2d::Vec2 Area::getPos()
{
    return Vec2(m_Rect.getMidX(), m_Rect.getMidY());
}

Area::AREA_TYPE Area::getAreaType() const
{
    return m_Type;
}
void Area::setAreaType(Area::AREA_TYPE type)
{
    if(m_Type != type)
        m_Type = type;
}

cocos2d::Rect Area::getRect() const
{
    return m_Rect;
}
void Area::setRect(const cocos2d::Rect& rect)
{
    m_Rect = rect;
}
cocos2d::Rect Area::getIntersectRect(Area* other)
{
    CCASSERT(other != nullptr, "Other area must not be null!");
    cocos2d::Rect rect;
    int minX = std::max(m_Rect.getMinX(), other->getRect().getMinX());
    int minY = std::max(m_Rect.getMinY(), other->getRect().getMinY());
    int maxX = std::min(m_Rect.getMaxX(), other->getRect().getMaxX());
    int maxY = std::min(m_Rect.getMaxY(), other->getRect().getMaxY());
    rect.origin.x = minX;
    rect.origin.y = minY;
    rect.size.width = maxX - minX;
    rect.size.height = maxY - minY;
    return rect;
}