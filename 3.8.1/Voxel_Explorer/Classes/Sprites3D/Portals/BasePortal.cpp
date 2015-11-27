//
//  BasePortal.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/20.
//
//

#include "BasePortal.hpp"
#include "UtilityHelper.h"
#include "FakeShadow.hpp"
#include "VoxelExplorer.h"
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
void BasePortal::onEnter()
{
    Actor::onEnter();
    scheduleUpdate();
}
void BasePortal::onExit()
{
    unscheduleUpdate();
    Actor::onExit();
}
void BasePortal::update(float delta)
{
    if(m_pFakeShadow)
        m_pFakeShadow->setPosition3D(Vec3(getPositionX(),-TerrainTile::CONTENT_SCALE*0.49f,getPositionZ()));
}
std::string BasePortal::getDesc()
{
    if(m_bIsCanUse)
        return UtilityHelper::getLocalString(PORTAL_NAMES[m_Type] + "_DESC");
    else
        return UtilityHelper::getLocalString(PORTAL_NAMES[m_Type] + "_LOCK");
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
bool BasePortal::createFakeShadow()
{
    m_pFakeShadow = FakeShadow::create();
    if(!m_pFakeShadow)
        return false;
    m_pFakeShadow->retain();
    m_pFakeShadow->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pFakeShadow->setLightMask((unsigned int)LightFlag::LIGHT0);
    VoxelExplorer::getInstance()->getFakeShadowLayer()->addChild(m_pFakeShadow);
    m_pFakeShadow->setScale(2);
    m_pFakeShadow->setPosition3D(Vec3(getPositionX(),-TerrainTile::CONTENT_SCALE*0.49f,getPositionZ()));
    return true;
}