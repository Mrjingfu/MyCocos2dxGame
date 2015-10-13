//
//  BaseLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "BaseLevel.h"
USING_NS_CC;

BaseLevel::BaseLevel()
{
    m_Type = LT_STANDARD;
    m_FeelingType = LFT_NONE;
    m_pMapDrawNode = nullptr;
    m_pDebugDrawNode = nullptr;
    cocos2d::Size size = Director::getInstance()->getVisibleSize();
    m_nWidth = size.width/10;
    m_nHeight = size.height/10;
}
void BaseLevel::create()
{
    m_nLenght = m_nWidth*m_nHeight;
    m_Map.resize(m_nLenght);
    if(!build())
        CCLOG("Level build failed!");
    if(!createRenderObjs())
        CCLOG("Create RenderObj failed!");
}

BaseLevel::LEVEL_TYPE BaseLevel::getLevelType() const
{
    return m_Type;
}
void BaseLevel::setLevelType(BaseLevel::LEVEL_TYPE type)
{
    m_Type = type;
}
void BaseLevel::generateTerrainTiles(int x, int y , int width, int height, TerrainTile::TileType tileType, Area::AREA_TYPE areaType)
{
    int pos = y * m_nWidth + x;
    for (int i = y; i < y + height; i++, pos += m_nWidth) {
        for (int j = pos; j<(pos + width); j++) {
            m_Map[j].m_Type = tileType;
            m_Map[j].m_AreaType = areaType;
            m_Map[j].m_nX = x;
            m_Map[j].m_nY = y;
        }
    }
}