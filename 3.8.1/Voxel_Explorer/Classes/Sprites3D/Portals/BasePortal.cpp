//
//  BasePortal.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/20.
//
//

#include "BasePortal.hpp"
#include "UtilityHelper.h"
USING_NS_CC;
const std::string PORTAL_NAMES[] = {
    
    "PTN_STANDARD",           ///标准传送门， 地图间传送
    "PTN_SMALL"               ///小传送门， 地图内传送
};
BasePortal::BasePortal()
{
    m_Type = PT_UNKNOWN;
    m_pCenterSprite = nullptr;
    m_bIsCanUse = false;
}
BasePortal::~BasePortal()
{
}
std::string BasePortal::getDesc()
{
    return UtilityHelper::getLocalString(PORTAL_NAMES[m_Type] + "_DESC");
}

void BasePortal::setVisited(bool visited)
{
    setVisible(visited);
    unsigned int lightmask = getLightMask();
    if (visited)
        lightmask = lightmask | (unsigned int)LightFlag::LIGHT1;
    else
        lightmask = lightmask &~ (unsigned int)LightFlag::LIGHT1;
    setLightMask(lightmask);
    if(m_pCenterSprite)
    {
        m_pCenterSprite->setVisible(visited);
        m_pCenterSprite->setLightMask(lightmask);
    }
}