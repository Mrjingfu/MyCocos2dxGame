//
//  BaseLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "BaseLevel.h"
#include "VoxelExplorer.h"
USING_NS_CC;

BaseLevel::BaseLevel()
{
    m_Type = LT_STANDARD;
    m_pMapDrawNode = nullptr;
    m_pDebugDrawNode = nullptr;
    m_nWidth = 32;
    m_nHeight = 48;
}
void BaseLevel::create()
{
    do
    {
        m_nLenght = m_nWidth*m_nHeight;
        m_Map.resize(m_nLenght);
    }
    while (!build());
    if(!createTerrain())
        CCLOGERROR("Create Terrain failed!");
    if(!createMonsters())
        CCLOGERROR("Create Monsters failed!");
    if(!createUseableItems())
        CCLOGERROR("Create Useable Items failed!");
}

BaseLevel::LEVEL_TYPE BaseLevel::getLevelType() const
{
    return m_Type;
}
void BaseLevel::setLevelType(BaseLevel::LEVEL_TYPE type)
{
    m_Type = type;
}

void BaseLevel::generateTerrainTiles(int x, int y , int width, int height, TerrainTile::TileType tileType, Area::AREA_TYPE areaType, Actor::ActorDir dir)
{
    int pos = y * m_nWidth + x;
    for (int i = y; i < y + height; i++, pos += m_nWidth) {
        for (int j = pos, k = x; j<(pos + width); j++, k++) {
            m_Map[j].m_Type = tileType;
            m_Map[j].m_AreaType = areaType;
            m_Map[j].m_Flag = assignTerrainTileFlag(tileType);
            m_Map[j].m_nX = k;
            m_Map[j].m_nY = i;
            m_Map[j].m_Dir = dir;
        }
    }
}
void BaseLevel::setTerrainTile(int x, int y, TerrainTile::TileType tileType, Area::AREA_TYPE areaType, Actor::ActorDir dir)
{
    int index = x + y * m_nWidth;
    m_Map[index].m_Type = tileType;
    m_Map[index].m_AreaType = areaType;
    m_Map[index].m_Flag = assignTerrainTileFlag(tileType);
    m_Map[index].m_nX = x;
    m_Map[index].m_nY = y;
    m_Map[index].m_Dir = dir;
}
int BaseLevel::getTerrainTileFlag(int x, int y)
{
    int index = x + y * m_nWidth;
    return m_Map[index].m_Flag;
}
void BaseLevel::setTerrainTileFlag(int x, int y, int flag )
{
    int index = x + y * m_nWidth;
    m_Map[index].m_Flag = flag;
}
void BaseLevel::wrapTerrainTiles(int x, int y , int width, int height, TerrainTile::TileType type, TerrainTile::TileType withType)
{
    int pos = y * m_nWidth + x;
    for (int i = y; i < y + height; i++, pos += m_nWidth) {
        for (int j = pos; j<(pos + width); j++) {
            if(m_Map[j].m_Type == type)
            {
                for (int n : getNeighbours8()) {
                    int cell = j + n;
                    if(m_Map[cell].m_Type == TerrainTile::TT_CHASM)
                    {
                        m_Map[cell].m_Type = withType;
                        m_Map[cell].m_Flag = assignTerrainTileFlag(withType);
                    }
                }
            }
        }
    }
}
bool BaseLevel::checkMovable(Actor* actor)
{
    if(!actor)
        return false;
    Vec2 pos = actor->getPosInMap();
    if(actor->getActorDir() == Actor::AD_LEFT)
        pos += Vec2(-1, 0);
    else if(actor->getActorDir() == Actor::AD_RIGHT)
        pos += Vec2(1, 0);
    else if(actor->getActorDir() == Actor::AD_FORWARD)
        pos += Vec2(0, 1);
    else if(actor->getActorDir() == Actor::AD_BACK)
        pos += Vec2(0, -1);
    int index = pos.x + pos.y*m_nWidth;
    TileInfo info = m_Map[index];
    if((info.m_Flag & TileInfo::INITIALISED) != 0)
    {
        ///发送跳崖事件
        return false;
    }
    if((info.m_Flag & TileInfo::LOS_BLOCKING) != 0)
    {
        if( info.m_Type == TerrainTile::TT_DOOR || info.m_Type == TerrainTile::TT_LOCKED_DOOR || info.m_Type == TerrainTile::TT_SECRET_DOOR )
            VoxelExplorer::getInstance()->handlDoor(pos);
        return false;
    }
    if((info.m_Flag & TileInfo::PASSABLE) != 0)
    {
        if(info.m_Type >= TerrainTile::TT_TOXIC_TRAP && info.m_Type <= TerrainTile::TT_HIDE_WEAK_TRAP)
        {
        }
        return true;
    }
    return false;
}
int BaseLevel::assignTerrainTileFlag(TerrainTile::TileType type)
{
    int flag = TileInfo::INITIALISED;
    switch (type) {
        case TerrainTile::TT_STANDARD:
        case TerrainTile::TT_TUNNEL:
            flag = TileInfo::PASSABLE;
            break;
        case TerrainTile::TT_DOOR:
        case TerrainTile::TT_LOCKED_DOOR:
        case TerrainTile::TT_SECRET_DOOR:
            flag = TileInfo::PASSABLE | TileInfo::LOS_BLOCKING;
            break;
        case TerrainTile::TT_OPENED_DOOR:
            flag = TileInfo::PASSABLE;
            break;
        default:
            break;
    }
    return flag;
}

void BaseLevel::load()
{
}
void BaseLevel::save()
{
}