//
//  SewerLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/23.
//
//

#include "SewerLevel.hpp"
#include "GameFormula.hpp"
#include "RandomDungeon.hpp"
#include "StandardMonster.hpp"
#include "PickableItem.hpp"
#include "VoxelExplorer.h"
#include "UseableItem.hpp"
#include "AlisaMethod.h"
USING_NS_CC;

SewerLevel::SewerLevel()
{
}

bool SewerLevel::createMonsters()
{
    int monsterNum = calculateLevelMonsterCount();
    for (int i=0; i < monsterNum; i++) {
        BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_RAT, (int)BaseMonster::MT_SLIME);
        StandardMonster* monster = StandardMonster::create(type);
        if(!monster)
            return false;
        int tileIndex = -1;
        do {
             tileIndex = randomMonsterRespawnCell();
        } while (tileIndex == -1);
        
        monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
        monster->setVisited(m_Map[tileIndex].m_bVisited);
        monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
        VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
        monster->setState(BaseMonster::MS_SLEEPING);
    }
    return true;
}
bool SewerLevel::createUseableItems()
{
    for (PathGraphNode* node : m_Areas) {
        Area* area = static_cast<Area*>(node);
        if(area)
        {
            if(area->getAreaType() == Area::AT_STANDARD)
            {
                std::vector<int> edgeIndexList = area->getTilesOnEdge(this, 1);
                int itemCount = calculateLevelUseableItemCount(area->getRect().size);
                int retryCount = 10;
                for (int i = 0; i < itemCount; ++i) {
                    int index = cocos2d::random(0, (int)(edgeIndexList.size()-1));
                    int tileIndex = edgeIndexList[index];
                    if((m_Map[tileIndex].m_Type != TerrainTile::TT_STANDARD) || (m_Map[tileIndex].isPassable() == false))
                    {
                        i--;
                        continue;
                    }
                    std::vector<int> neighbours8 = this->getNeighbours8();
                    bool neighbourHasDoor = false;
                    int count = 0;
                    for (int j = 0; j<neighbours8.size(); ++j) {
                        if(m_Map[neighbours8[j] + tileIndex].m_Type >= TerrainTile::TT_ENTRANCE
                           && m_Map[neighbours8[j] + tileIndex].m_Type <= TerrainTile::TT_SECRET_DOOR)
                            neighbourHasDoor = true;
                        else if(m_Map[neighbours8[j] + tileIndex].m_Type == TerrainTile::TT_STANDARD || (m_Map[neighbours8[j] + tileIndex].m_Type >= TerrainTile::TT_TOXIC_TRAP && m_Map[neighbours8[j] + tileIndex].m_Type <= TerrainTile::TT_HIDE_WEAK_TRAP))
                            count++;
                    }
                    if(neighbourHasDoor)
                    {
                        i--;
                        continue;
                    }
                    if(count == 8)
                    {
                        retryCount--;
                        if(retryCount > 0)
                            i--;
                        continue;
                    }
                    UseableItem* item = UseableItem::create(GameFormula::generateUseItemType());
                    if(!item)
                        return false;
                    item->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
                    if(m_Map[tileIndex].m_nY == area->getRect().getMinY() + 1)
                        item->setActorDir(Actor::AD_FORWARD);
                    else if(m_Map[tileIndex].m_nY == area->getRect().getMaxY() - 1)
                        item->setActorDir(Actor::AD_BACK);
                    else if(m_Map[tileIndex].m_nX == area->getRect().getMaxX() - 1)
                        item->setActorDir(Actor::AD_LEFT);
                    else if(m_Map[tileIndex].m_nX == area->getRect().getMinX() + 1)
                        item->setActorDir(Actor::AD_RIGHT);
                    item->setVisited(m_Map[tileIndex].m_bVisited);
                    item->addTerrainTileFlag(TileInfo::USEABLE);
                    VoxelExplorer::getInstance()->getUseableItemsLayer()->addChild(item);
                    item->setState(UseableItem::UIS_IDLE);
                    edgeIndexList.erase(edgeIndexList.begin() + index);
                    CCLOG("Useable item pos = %d %d", (int)(item->getPosInMap().x), (int)(item->getPosInMap().y));
                }
            }
        }
    }
    return true;
}
bool SewerLevel::createPickableItems()
{
    ///创建房间钥匙
//    PickableItem* item = PickableItem::create(type);
//    if(item)
//    {
//        item->setPosition3D(Vec3(pos.x*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -pos.y*TerrainTile::CONTENT_SCALE));
//        item->setVisited(true);
//        VoxelExplorer::getInstance()->getPickableItemsLayer()->addChild(item);
//        item->setState(PickableItem::PIS_BEGIN_GENERATE);
//    }
    return true;
}
bool SewerLevel::createSummoningMonsters(const cocos2d::Vec2& mapPos)
{
    std::vector<int> neighbours4 = getNeighbours4();
    for (int i = 0; i < neighbours4.size(); i++) {
        int index = mapPos.x + mapPos.y * m_nWidth + neighbours4[i];
        if(isTerrainTilePassable(index))
        {
            BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_RAT, (int)BaseMonster::MT_SLIME);
            StandardMonster* monster = StandardMonster::create(type);
            if(!monster)
                return false;
            monster->setPosition3D(Vec3(m_Map[index].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[index].m_nY*TerrainTile::CONTENT_SCALE));
            monster->setVisited(m_Map[index].m_bVisited);
            monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
            VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
            monster->setState(BaseMonster::MS_SLEEPING);
        }
    }
    return true;
}
int SewerLevel::calculateLevelMonsterCount()
{
    int ret = m_nStandardAreaCount;
    if(m_Style == LS_STANDARD)
        ret = (int)(m_nStandardAreaCount*0.8f) + cocos2d::random(2, 5);
    else if (m_Style == LS_TUNNEL)
        ret = m_nStandardAreaCount + cocos2d::random(0, m_nStandardAreaCount);
    else if(m_Style == LS_PASSAGE)
        ret = (int)(m_nStandardAreaCount*0.5f) + m_nPassageAreaCount + cocos2d::random(2, 5);
    return ret;
}
int SewerLevel::calculateLevelUseableItemCount(const cocos2d::Size& areaSize)
{
    if(areaSize.width-1 < 4 || areaSize.height-1 < 4)
        return 0;
    int length = (areaSize.width-1) * (areaSize.height-1);
    if(length <= 15)
        return 0;
    else if(length < 25)
        return cocos2d::random(1, 2);
    else if(length < 36)
        return cocos2d::random(1, 3);
    else if(length < 49)
        return cocos2d::random(2, 4);
    return cocos2d::random(3, 5);
}