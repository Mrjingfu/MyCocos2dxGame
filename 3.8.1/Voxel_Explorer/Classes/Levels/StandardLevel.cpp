//
//  StandardLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "StandardLevel.h"
#include "Graph.h"
#include "VoxelExplorer.h"
#include "TerrainTile.hpp"
#include "StandardDoor.hpp"
#include "RandomDungeon.hpp"
#include "AlisaMethod.h"
#include "PickableItem.hpp"
#include "GameFormula.hpp"
USING_NS_CC;

StandardLevel::StandardLevel()
{
    m_Type = LT_STANDARD;
    m_nMinAreaSize  = 7;
    m_nMaxAreaSize  = 9;
    m_nStandardAreaCount = 0;
    m_nSpecialAreaCount = 0;
    m_nTunnelAreaCount = 0;
    m_nPassageAreaCount = 0;
    
    m_Style = LS_UNKNOWN;
}
bool StandardLevel::build()
{
    if(!initAreas())
        return false;
    int distance = 0;
    int retry = 0;
    int minDistance = (int)sqrt(m_Areas.size());
    do
    {
        do
        {
            int rand = cocos2d::random(0, (int)(m_Areas.size())-1);
            m_AreaEntrance = static_cast<Area*>(m_Areas[rand]);
        } while (m_AreaEntrance->getRect().size.width < 4 || m_AreaEntrance->getRect().size.height <4);
        do
        {
            int rand = cocos2d::random(0, (int)(m_Areas.size())-1);
            m_AreaExit = static_cast<Area*>(m_Areas[rand]);
        } while (m_AreaExit == m_AreaEntrance || m_AreaExit->getRect().size.width < 4 || m_AreaExit->getRect().size.height < 4);
        
        PathGraph::buildDistanceMap(m_Areas, m_AreaExit);
        
        distance = m_AreaEntrance->getDistance();
        
        if (retry++ > 10) {
            return false;
        }
    }
    while (distance < minDistance);
    
    m_AreaEntrance->setAreaType(Area::AT_ENTRANCE);
    m_AreaExit->setAreaType(Area::AT_EXIT);
    
    std::vector<Area*> connected;
    connected.push_back(m_AreaEntrance);
    
    PathGraph::buildDistanceMap( m_Areas, m_AreaExit );
    
    std::list<PathGraphNode*> path = PathGraph::buildPath( m_Areas, m_AreaEntrance, m_AreaExit );
    Area* startArea = m_AreaEntrance;
    for (PathGraphNode* node : path) {
        Area* next = static_cast<Area*>(node);
        if(next)
        {
            startArea->connectArea(next);
            startArea = next;
            connected.push_back(startArea);
        }
    }
    PathGraph::setWeight(path, m_AreaEntrance->getDistance());
    
    PathGraph::buildDistanceMap( m_Areas, m_AreaExit );
    path = PathGraph::buildPath( m_Areas, m_AreaEntrance, m_AreaExit );
    
    startArea = m_AreaEntrance;
    for (PathGraphNode* node : path) {
        Area* next = static_cast<Area*>(node);
        if(next)
        {
            startArea->connectArea(next);
            startArea = next;
            connected.push_back(startArea);
        }
    }
    
    int nConnected = (int)(m_Areas.size() * cocos2d::random( 0.5f, 0.7f ));
    while (connected.size() < nConnected) {
        int rand = cocos2d::random(0, (int)(connected.size())-1);
        Area* ca = static_cast<Area*>(connected[rand]);
        rand = cocos2d::random(0, (int)(ca->getNeigbours().size())-1);
        Area* oa = static_cast<Area*>(ca->getNeigbours()[rand]);
        if (std::find(connected.begin(), connected.end(), oa) == connected.end()) {
            ca->connectArea(oa);
            connected.push_back(oa);
        }
    }
    ///如果地图上有商店
    ///处理
    m_SpecailAreas = Area::SPECIALS;
//    if (Dungeon.bossLevel( Dungeon.depth + 1 )) {
//        specials.remove( Room.Type.WEAK_FLOOR );
//    }
    assignAreasType();
    generate();
    
#if COCOS2D_DEBUG
    showMap(false);
#endif
    return true;
}
bool StandardLevel::createTerrain()
{
    if(!VoxelExplorer::getInstance()->getTerrainTilesLayer())
        return false;
    for (int i = 0; i<m_nHeight; i++) {
        for (int j = 0; j<m_nWidth; j++) {
            int index = i*m_nWidth+j;
            TileInfo info = m_Map[index];
            if(info.m_Type == TerrainTile::TT_CHASM)
                continue;
            TerrainTile* tile = TerrainTile::create(info.m_Type);
            if(!tile)
                return false;
            tile->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, -TerrainTile::CONTENT_SCALE, -i*TerrainTile::CONTENT_SCALE));
            tile->setVisited(info.m_bVisited);
            VoxelExplorer::getInstance()->getTerrainTilesLayer()->addChild(tile);
            
            switch (info.m_Type) {
                case TerrainTile::TT_WALL:
                    {
                        tile->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, -TerrainTile::CONTENT_SCALE*0.5f, -i*TerrainTile::CONTENT_SCALE));
                    }
                    break;
                case TerrainTile::TT_DOOR:
                    {
                        StandardDoor* door = StandardDoor::create(false);
                        if(!door)
                            return false;
                        door->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, -TerrainTile::CONTENT_SCALE*0.5f, -i*TerrainTile::CONTENT_SCALE));
                        VoxelExplorer::getInstance()->getTerrainDoorsLayer()->addChild(door);
                        if(!door->createFakeDoor())
                            return false;
                        door->setVisited(info.m_bVisited);
                        door->setActorDir(info.m_Dir);
                        door->setDoorState(BaseDoor::DS_CLOSED);
                    }
                    break;
                case TerrainTile::TT_OPENED_DOOR:
                    {
                        StandardDoor* door = StandardDoor::create(false);
                        if(!door)
                            return false;
                        door->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, -TerrainTile::CONTENT_SCALE*0.5f, -i*TerrainTile::CONTENT_SCALE));
                        VoxelExplorer::getInstance()->getTerrainDoorsLayer()->addChild(door);
                        if(!door->createFakeDoor())
                            return false;
                        door->setVisited(info.m_bVisited);
                        door->setActorDir(info.m_Dir);
                        door->setDoorState(BaseDoor::DS_OPENED);
                    }
                    break;
                case TerrainTile::TT_LOCKED_DOOR:
                    {
                        StandardDoor* door = StandardDoor::create(false);
                        if(!door)
                            return false;
                        door->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, -TerrainTile::CONTENT_SCALE*0.5f, -i*TerrainTile::CONTENT_SCALE));
                        VoxelExplorer::getInstance()->getTerrainDoorsLayer()->addChild(door);
                        if(!door->createFakeDoor())
                            return false;
                        door->setVisited(info.m_bVisited);
                        door->setActorDir(info.m_Dir);
                        door->setDoorState(BaseDoor::DS_LOCKED);
                    }
                    break;
                case TerrainTile::TT_SECRET_DOOR:
                    {
                        StandardDoor* door = StandardDoor::create(true);
                        if(!door)
                            return false;
                        door->setPosition3D(Vec3(j*TerrainTile::CONTENT_SCALE, -TerrainTile::CONTENT_SCALE*0.5f, -i*TerrainTile::CONTENT_SCALE));
                        VoxelExplorer::getInstance()->getTerrainDoorsLayer()->addChild(door);
                        if(!door->createFakeDoor())
                            return false;
                        door->setVisited(info.m_bVisited);
                        door->setActorDir(info.m_Dir);
                        door->setDoorState(BaseDoor::DS_HIDE);
                    }
                    break;
                default:
                    break;
            }

        }
    }
    return true;
}
bool StandardLevel::decorateAreas()
{
    for (PathGraphNode* node : m_Areas) {
        Area* area = static_cast<Area*>(node);
        if(area)
        {
            if(area->getAreaType() == Area::AT_STANDARD)
            {
                if(!createUseableItems(area))
                {
                    CCLOGERROR("Create Useable Items failed!");
                    return false;
                }
            }
            else if(area->getAreaType() >= Area::AT_STANDARD)
            {
                if(!createNPCs(area))
                {
                    CCLOGERROR("Create NPCs failed!");
                    return false;
                }
            }
        }
    }
    return true;
}
bool StandardLevel::initAreas()
{
    m_Areas.clear();
    splitArea( cocos2d::Rect( 0, 0, m_nWidth - 1, m_nHeight - 1 ) );
    
    if (m_Areas.size() < 8) {
        return false;
    }
    for (int i = 0; i<m_Areas.size()-1; i++) {
        for (int j = i+1; j<m_Areas.size(); j++) {
            Area* area1 = static_cast<Area*>(m_Areas[i]);
            Area* area2 = static_cast<Area*>(m_Areas[j]);
            if(area1 && area2)
                area1->addNeigbourArea(area2);
        }
    }
    return true;
}
void StandardLevel::splitArea(const cocos2d::Rect& rect)
{
    int w = rect.size.width;
    int h = rect.size.height;
    
    if (w > m_nMaxAreaSize && h < m_nMinAreaSize) {
        int vw = cocos2d::random((int)(rect.getMinX()) + 3, (int)(rect.getMaxX()) - 3);
        splitArea( cocos2d::Rect( rect.getMinX(), rect.getMinY(), vw-rect.getMinX(), rect.size.height ) );
        splitArea( cocos2d::Rect( vw, rect.getMinY(), rect.getMaxX()-vw, rect.size.height ) );
        
    }
    else if (h > m_nMaxAreaSize && w < m_nMinAreaSize)
    {
        int vh = cocos2d::random( (int)(rect.getMinY()) + 3, (int)(rect.getMaxY()) - 3 );
        splitArea( cocos2d::Rect( rect.getMinX(), rect.getMinY(), rect.size.width, vh-rect.getMinY() ) );
        splitArea( cocos2d::Rect( rect.getMinX(), vh, rect.size.width, rect.getMaxY()-vh ) );
            
    }
    else if ((cocos2d::rand_0_1() <= ((float)(m_nMinAreaSize * m_nMinAreaSize) / (rect.size.width*rect.size.height)) && w <= m_nMaxAreaSize && h <= m_nMaxAreaSize) || w < m_nMinAreaSize || h < m_nMinAreaSize)
    {
                
        Area* area = Area::create();
        if(area)
        {
            area->setRect(rect);
            area->retain();
            m_Areas.push_back(area);
        }
    }
    else
    {
                
        if (cocos2d::rand_0_1() < (float)(w - 2) / (w + h - 4))
        {
            int vw = cocos2d::random( (int)(rect.getMinX()) + 3, (int)(rect.getMaxX()) - 3 );
            splitArea( cocos2d::Rect( rect.getMinX(), rect.getMinY(), vw-rect.getMinX(), rect.size.height ) );
            splitArea( cocos2d::Rect( vw, rect.getMinY(), rect.getMaxX()-vw, rect.size.height ) );
        }
        else
        {
            int vh = cocos2d::random( (int)(rect.getMinY()) + 3, (int)(rect.getMaxY()) - 3 );
            splitArea( cocos2d::Rect( rect.getMinX(), rect.getMinY(), rect.size.width, vh-rect.getMinY() ) );
            splitArea( cocos2d::Rect( rect.getMinX(), vh, rect.size.width, rect.getMaxY()-vh) );
        }
                
    }
}
void StandardLevel::assignAreasType()
{
    m_nSpecialAreaCount = 0;
    
    for (PathGraphNode* node : m_Areas) {
        Area* area = static_cast<Area*>(node);
        if(area)
        {
            if(area->getAreaType() == Area::AT_UNKNOWN && area->getConnectedAreas().size() == 1)
            {
                if(m_SpecailAreas.size() > 0 && area->getRect().size.width > 3 && area->getRect().size.height > 3 && cocos2d::random(0, m_nSpecialAreaCount*m_nSpecialAreaCount + 1) == 0)
                {
                    area->setAreaType(Area::AT_SPECIAL_SHOP);
                    m_nSpecialAreaCount++;
                }
                else if(cocos2d::random(0, 1) == 0)
                {
                    std::vector<PathGraphNode*> neigbours;
                    for (PathGraphNode* n : area->getNeigbours()) {
                        Area* areaNeigbour = static_cast<Area*>(n);
                        if(areaNeigbour)
                        {
                            if(areaNeigbour->getAreaType() != Area::AT_SPECIAL_PIT && (areaNeigbour->getConnectedAreas().find(areaNeigbour) == areaNeigbour->getConnectedAreas().end()) && (std::find(Area::SPECIALS.begin(), Area::SPECIALS.end(), areaNeigbour->getAreaType()) != Area::SPECIALS.end()))
                            {
                                neigbours.push_back(areaNeigbour);
                            }
                        }
                    }
                    if (neigbours.size() > 1) {
                        int rand = cocos2d::random(0, (int)(neigbours.size())-1);
                        area->connectArea(static_cast<Area*>(neigbours[rand]));
                    }
                }
            }
        }
    }
    ///生成通道
    //m_Style = cocos2d::random(LS_STANDARD, LS_PASSAGE);
    
    float percentStandard = 0.6f;
    float percentTunnel = 0.05f;
    float percentPassage = 1.0 - percentStandard - percentTunnel;
    AlisaMethod* am = AlisaMethod::create(percentStandard,percentTunnel,percentPassage,-1.0, NULL);
    if(am)
        m_Style = (LevelStyle)am->getRandomIndex();
    
    m_nStandardAreaCount = 0;
    m_nTunnelAreaCount = 0;
    m_nPassageAreaCount = 0;
    for (PathGraphNode* node : m_Areas) {
        Area* area = static_cast<Area*>(node);
        if(area)
        {
            if (area->getAreaType() == Area::AT_UNKNOWN) {
                int connections = area->getConnectedAreas().size();
                if ( connections == 0) {
                    CCASSERT(connections == 0, "Error: connections == 0");
                } else if (cocos2d::random(0, connections * connections-1) == 0) {
                    area->setAreaType(Area::AT_STANDARD);
                    m_nStandardAreaCount++;
                } else {
                    switch (m_Style) {
                        case LS_STANDARD:
                            area->setAreaType(Area::AT_STANDARD);
                            m_nStandardAreaCount++;
                            break;
                        case LS_TUNNEL:
                            area->setAreaType(Area::AT_TUNNEL);
                            m_nTunnelAreaCount++;
                            break;
                        case LS_PASSAGE:
                            area->setAreaType(Area::AT_PASSAGE);
                            m_nPassageAreaCount++;
                            break;
                        default:
                            break;
                    }
                    
                }
            }

        }
    }
    
    ///保证标准区域至少4个
    while (m_nStandardAreaCount < 4) {
        int rand = cocos2d::random(0, (int)(m_Areas.size())-1);
        Area* area = static_cast<Area*>(m_Areas[rand]);
        if (area != nullptr) {
            if(area->getAreaType() == Area::AT_TUNNEL)
            {
                area->setAreaType(Area::AT_STANDARD);
                m_nTunnelAreaCount--;
                m_nStandardAreaCount++;
            }
            else if(area->getAreaType() == Area::AT_PASSAGE)
            {
                area->setAreaType(Area::AT_STANDARD);
                m_nPassageAreaCount--;
                m_nStandardAreaCount++;
            }
        }
    }
    
    ////设置开始区域为探索区域
    m_AreaEntrance->updateAreaFogOfWar(this, true);

}
void StandardLevel::generate()
{
    for (PathGraphNode* node : m_Areas) {
        Area* area = static_cast<Area*>(node);
        if(area)
        {
            if(area->getAreaType() != Area::AT_UNKNOWN)
            {
                placeDoors(area);
                area->generate(this);
            }
            else
            {
                ///不绘制，以后有需要可以对UNKNOWN类型进行填充
            }
        }
    }
    for (PathGraphNode* node : m_Areas) {
        Area* area = static_cast<Area*>(node);
        if(area)
            generateDoors(area);
    }
    placeTraps();           ///放置陷阱
    generateSpawnPoint();   ///生成出生点
}
bool StandardLevel::createUseableItems(Area* area)
{
    if(!area)
        return false;
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
                if(m_Map[neighbours8[j] + tileIndex].m_Type >= TerrainTile::TT_ENTRANCE && m_Map[neighbours8[j] + tileIndex].m_Type <= TerrainTile::TT_SECRET_DOOR)
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
    return true;
}
bool StandardLevel::createNPCs(Area* area)
{
    if(!area)
        return false;
    return true;
}
bool StandardLevel::createPickableItems()
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
void StandardLevel::showMap(bool show)
{
    if (VoxelExplorer::getInstance()->getMainLayer() == nullptr)
        return;
    
    m_bShowMap = show;
    
    if(!show)
    {
        if(m_pMapDrawNode)
        {
            m_pMapDrawNode->clear();
            m_pMapDrawNode->removeFromParentAndCleanup(true);
            m_pMapDrawNode = nullptr;
        }
    }
    else
    {
        if(!m_pMapDrawNode)
        {
            m_pMapDrawNode = DrawNode::create();
            VoxelExplorer::getInstance()->getMainLayer()->addChild(m_pMapDrawNode);
            m_pMapDrawNode->setCameraMask((unsigned int)CameraFlag::USER2);
            auto winSize = Director::getInstance()->getVisibleSize();
            m_pMapDrawNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            m_pMapDrawNode->setPosition(Vec2(winSize.width*0.15, winSize.height*0.15));
            m_pMapDrawNode->setScale(winSize.width/48);
        }
        m_pMapDrawNode->clear();
        
        for (int i = 0; i<m_nHeight; i++) {
            for (int j = 0; j<m_nWidth; j++) {
                int index = i*m_nWidth+j;
                TileInfo info = m_Map[index];
                if(!info.m_bVisited)
                    continue;
                cocos2d::Rect rect(j,i,1,1);
                Vec2 vertices[4] = {
                    Vec2( rect.getMinX(), rect.getMinY() ),
                    Vec2( rect.getMaxX(), rect.getMinY() ),
                    Vec2( rect.getMaxX(), rect.getMaxY() ),
                    Vec2( rect.getMinX(), rect.getMaxY() ),
                };
                
                switch (info.m_Type) {
                    case TerrainTile::TT_STANDARD:
                        if(info.m_AreaType >= Area::AT_SPECIAL_SHOP)
                            m_pMapDrawNode->drawPolygon(vertices, 4, Color4F::MAGENTA, 0, Color4F(0,0,0,0));
                        else
                            m_pMapDrawNode->drawPolygon(vertices, 4, Color4F::WHITE, 0, Color4F(0,0,0,0));
                        break;
                    case TerrainTile::TT_WALL:
                        m_pMapDrawNode->drawPolygon(vertices, 4, Color4F::GRAY, 0, Color4F(0,0,0,0));
                        break;
                    case TerrainTile::TT_ENTRANCE:
                        m_pMapDrawNode->drawPolygon(vertices, 4, Color4F::YELLOW, 0, Color4F(0,0,0,0));
                        break;
                    case TerrainTile::TT_EXIT:
                        m_pMapDrawNode->drawPolygon(vertices, 4, Color4F::GREEN, 0, Color4F(0,0,0,0));
                        break;
                    case TerrainTile::TT_TUNNEL:
                        m_pMapDrawNode->drawPolygon(vertices, 4, Color4F::ORANGE, 0, Color4F(0,0,0,0));
                        break;
                    case TerrainTile::TT_DOOR:
                        m_pMapDrawNode->drawPolygon(vertices, 4, Color4F::BLUE, 0, Color4F(0,0,0,0));
                        break;
                    case TerrainTile::TT_LOCKED_DOOR:
                        m_pMapDrawNode->drawPolygon(vertices, 4, Color4F::RED, 0, Color4F(0,0,0,0));
                        break;
                    case TerrainTile::TT_HIDE_TOXIC_TRAP:
                    case TerrainTile::TT_HIDE_FIRE_TRAP:
                    case TerrainTile::TT_HIDE_PARALYTIC_TRAP:
                    case TerrainTile::TT_HIDE_GRIPPING_TRAP:
                    case TerrainTile::TT_HIDE_SUMMONING_TRAP:
                    case TerrainTile::TT_HIDE_WEAK_TRAP:
                        m_pMapDrawNode->drawPolygon(vertices, 4, Color4F::WHITE, 0, Color4F(0,0,0,0));
                        break;
                    case TerrainTile::TT_TOXIC_TRAP:
                        m_pMapDrawNode->drawPolygon(vertices, 4, Color4F(27.0f/255.0f, 186.0f/255.0f, 52.0f/255.0f, 1.0f), 0, Color4F(0,0,0,0));
                        break;
                    case TerrainTile::TT_FIRE_TRAP:
                        m_pMapDrawNode->drawPolygon(vertices, 4, Color4F(1.0f, 131.0f/255.0f, 41.0f/255.0f, 1.0f), 0, Color4F(0,0,0,0));
                        break;
                    case TerrainTile::TT_PARALYTIC_TRAP:
                        m_pMapDrawNode->drawPolygon(vertices, 4, Color4F(100.0f/255.0f, 201.0f/255.0f, 250.0f/255.0f, 1.0f), 0, Color4F(0,0,0,0));
                        break;
                    case TerrainTile::TT_GRIPPING_TRAP:
                        m_pMapDrawNode->drawPolygon(vertices, 4, Color4F(174.0f/255.0f, 230.0f/255.0f, 1.0f, 1.0f), 0, Color4F(0,0,0,0));
                        break;
                    case TerrainTile::TT_SUMMONING_TRAP:
                        m_pMapDrawNode->drawPolygon(vertices, 4, Color4F(178.0f/255.0f, 84.0f/255.0f, 242.0f/255.0f, 1.0f), 0, Color4F(0,0,0,0));
                        break;
                    case TerrainTile::TT_WEAK_TRAP:
                        m_pMapDrawNode->drawPolygon(vertices, 4, Color4F(234.0f/255.0f, 196.0f/255.0f, 96.0f/255.0f, 1.0f), 0, Color4F(0,0,0,0));
                        break;
                    default:
                        break;
                }
                
            }
        }
    }
}
void StandardLevel::updateAreaFogOfWarByPos(const cocos2d::Vec2& pos)
{
    for (PathGraphNode* node : m_Areas) {
        Area* area = static_cast<Area*>(node);
        if(area && area->checkInside(pos))
        {
            ///更新地图tile
            for (auto iter = area->getConnectedAreas().begin(); iter != area->getConnectedAreas().end(); iter++) {
                Area* areaOri = iter->first;
                Door* door = iter->second;
                if(areaOri)
                {
                    if(area->getAreaType() == Area::AT_TUNNEL )
                    {
                        if( areaOri->getAreaType() == Area::AT_TUNNEL)
                        {
                            areaOri->updateAreaFogOfWar(this, true);
                            ///更新场景、怪物和物品状态
                            VoxelExplorer::getInstance()->updateFogOfWar(areaOri->getRect(), true);
                        }
                    }
                    else
                    {
                        if(mergeSmallIntersectArea(area, areaOri))
                        {
                            areaOri->updateAreaFogOfWar(this, true);
                            ///更新场景、怪物和物品状态
                            VoxelExplorer::getInstance()->updateFogOfWar(areaOri->getRect(), true);
                        }
                    }
                    if(door && door->getPos() == pos)
                    {
                        area->updateAreaFogOfWar(this, true);
                        areaOri->updateAreaFogOfWar(this, true);
                        ///更新场景、怪物和物品状态
                        VoxelExplorer::getInstance()->updateFogOfWar(areaOri->getRect(), true);
                        VoxelExplorer::getInstance()->updateFogOfWar(area->getRect(), true);
                        
                        for (auto iter2 = areaOri->getConnectedAreas().begin(); iter2 != areaOri->getConnectedAreas().end(); iter2++) {
                            Area* areaOriOri = iter2->first;
                            if(areaOriOri)
                            {
                                if(mergeSmallIntersectArea(areaOri, areaOriOri))
                                {
                                    areaOri->updateAreaFogOfWar(this, true);
                                    areaOriOri->updateAreaFogOfWar(this, true);
                                    ///更新场景、怪物和物品状态
                                    VoxelExplorer::getInstance()->updateFogOfWar(areaOriOri->getRect(), true);
                                }
                            }
                        }
                        return;
                    }
                }
            }
        }
    }
    
}
void StandardLevel::placeDoors(Area* area)
{
    if(!area)
        return;
    for (auto iter = area->getConnectedAreas().begin(); iter != area->getConnectedAreas().end(); iter++) {
        Area* areaOri = iter->first;
        Door* door = iter->second;
        if(areaOri)
        {
            if(door == nullptr)
            {
                door = Door::create();
                if(door)
                {
                    cocos2d::Rect rect = area->getIntersectRect(areaOri);
                    if(rect.size.width == 0)
                        door->setPos(Vec2(rect.getMinX(),cocos2d::random((int)rect.getMinY()+1,(int)rect.getMaxY()-1)));
                    else
                        door->setPos(Vec2(cocos2d::random((int)rect.getMinX()+1, (int)rect.getMaxX()-1),rect.getMinY()));
                    door->retain();
                    area->getConnectedAreas()[areaOri] = door;
                    areaOri->getConnectedAreas()[area] = door;
                }
            }
        }
    }
}
void StandardLevel::generateDoors(Area* area)
{
    if(!area)
        return;
    for (auto iter = area->getConnectedAreas().begin(); iter != area->getConnectedAreas().end(); iter++) {
        Area* areaOri = iter->first;
        if(mergeSmallIntersectArea(area, areaOri))
            continue;
        Door* door = iter->second;
        if(door)
        {
            Actor::ActorDir dir = Actor::AD_UNKNOWN;
            if(door->getPos().x == area->getRect().getMinX())
                dir = Actor::AD_LEFT;
            else if(door->getPos().x == area->getRect().getMaxX())
                dir = Actor::AD_RIGHT;
            else
            {
                if(door->getPos().y == area->getRect().getMinY())
                    dir = Actor::AD_BACK;
                else if(door->getPos().y == area->getRect().getMaxY())
                    dir = Actor::AD_FORWARD;
            }
            switch (door->getDoorType()) {
                case Door::DT_EMPTY:
                case Door::DT_PASSAGE:
                    setTerrainTile(door->getPos().x, door->getPos().y, TerrainTile::TT_STANDARD, area->getAreaType(),dir);
                    break;
                case Door::DT_TUNNEL:
                    setTerrainTile(door->getPos().x, door->getPos().y, TerrainTile::TT_TUNNEL, area->getAreaType(),dir);
                    break;
                case Door::DT_STANDARD:
                    setTerrainTile(door->getPos().x, door->getPos().y, TerrainTile::TT_DOOR, area->getAreaType(),dir);
                    break;
                case Door::DT_UNLOCKED:
                    setTerrainTile(door->getPos().x, door->getPos().y, TerrainTile::TT_DOOR, area->getAreaType(),dir);
                    break;
                case Door::DT_HIDDEN:
                    setTerrainTile(door->getPos().x, door->getPos().y, TerrainTile::TT_SECRET_DOOR, area->getAreaType(), dir);
                    break;
                case Door::DT_BARRICADE:
                case Door::DT_LOCKED:
                    setTerrainTile(door->getPos().x, door->getPos().y, TerrainTile::TT_LOCKED_DOOR, area->getAreaType(), dir);
                    break;
                default:
                    break;
            }
        }
    }
}
bool StandardLevel::mergeSmallIntersectArea(Area* area, Area* other, bool generate)
{
    if(!area || !other)
        return false;
    if (area->getAreaType() != Area::AT_STANDARD || other->getAreaType() != Area::AT_STANDARD)
        return false;
    
    cocos2d::Rect rect = area->getIntersectRect( other );
    if (rect.getMinX() == rect.getMaxX()) {
        
        if (rect.getMaxY() - rect.getMinY() < 3) {
            return false;
        }
        
        if (rect.size.height == MAX(area->getRect().size.height, other->getRect().size.height)){
            return false;
        }
        
        if (area->getRect().size.width + other->getRect().size.width > m_nMaxAreaSize) {
            return false;
        }
        
        if(generate)
        {
            rect.origin.x += 0;
            rect.origin.y += 1;
            rect.size.width += 1;
            rect.size.height -=1;
       
            generateTerrainTiles( rect.origin.x, rect.origin.y, 1, rect.size.height, TerrainTile::TT_STANDARD, area->getAreaType() );
        }
        
    } else {
        
        if (rect.getMaxY() - rect.getMinY() < 3) {
            return false;
        }
        
        if (rect.size.width == MAX(area->getRect().size.width, other->getRect().size.width)) {
            return false;
        }
        
        if (area->getRect().size.height + other->getRect().size.height > m_nMaxAreaSize) {
            return false;
        }
        
        if(generate)
        {
            rect.origin.x += 1;
            rect.origin.y += 0;
            rect.size.width -= 1;
            rect.size.height +=1;
        
            generateTerrainTiles( rect.origin.x, rect.origin.y, rect.size.width, 1, TerrainTile::TT_STANDARD, area->getAreaType());
        }
    }
    
    return true;
}
void StandardLevel::placeTraps()  ///放置陷阱
{
    if(!RandomDungeon::getInstance()->getCurrentDungeonNode())
        return;
    int nTraps = 0;

    if(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nNodeDepth > 1)
    {
        nTraps = m_Areas.size()*0.4f + RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nNodeDepth.GetLongValue() + RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth.GetLongValue();
    }
    else
    {
        if(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth >= 1)
        {
            nTraps = m_Areas.size()*0.2f + RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth.GetLongValue();
        }
    }
    
    for (int i = 0; i<nTraps; i++) {
        int pos = cocos2d::random(0, (int)m_Map.size()-1);
        if(m_Map[pos].m_AreaType == Area::AT_ENTRANCE
           || m_Map[pos].m_AreaType == Area::AT_EXIT
           || m_Map[pos].m_AreaType >= Area::AT_SPECIAL_SHOP)
        {
            i--;
            continue;
        }
        if(m_Map[pos].m_Type == TerrainTile::TT_STANDARD)
        {
            int randType = cocos2d::random(0, 5);
            switch (randType) {
                case 0:
                    m_Map[pos].m_Type = TerrainTile::TT_HIDE_TOXIC_TRAP;
                    break;
                case 1:
                    m_Map[pos].m_Type = TerrainTile::TT_HIDE_FIRE_TRAP;
                    break;
                case 2:
                    m_Map[pos].m_Type = TerrainTile::TT_HIDE_PARALYTIC_TRAP;
                    break;
                case 3:
                    m_Map[pos].m_Type = TerrainTile::TT_HIDE_GRIPPING_TRAP;
                    break;
                case 4:
                    m_Map[pos].m_Type = TerrainTile::TT_HIDE_SUMMONING_TRAP;
                    break;
                case 5:
                    m_Map[pos].m_Type = TerrainTile::TT_HIDE_WEAK_TRAP;
                    break;
                default:
                    break;
            }
        }
    }
}
void StandardLevel::generateSpawnPoint()
{
    for (int i = 0; i<m_Map.size()-1; i++) {
        if(m_Map[i].m_Type == TerrainTile::TT_ENTRANCE)
            m_spawnPoint = Vec2((m_Map[i].m_nX+1)*TerrainTile::CONTENT_SCALE,(m_Map[i].m_nY)*TerrainTile::CONTENT_SCALE);
    }
}
int StandardLevel::randomMonsterRespawnCell()
{
    int count = 0;
    int tileIndex = -1;
    
    while (true) {
        if (++count > 10) {
            return -1;
        }
        int rand = cocos2d::random(0, (int)(m_Areas.size())-1);
        Area* area = static_cast<Area*>(m_Areas[rand]);
        if (area == nullptr)
            continue;
        if(m_Style == LS_PASSAGE)
        {
            if(area->getAreaType() != Area::AT_STANDARD)
                if(area->getAreaType() != Area::AT_PASSAGE)
                    continue;
        }
        else
        {
            if(area->getAreaType() != Area::AT_STANDARD)
                continue;
        }
        tileIndex = area->getRandomTile(this);
        if((m_Map[tileIndex].m_Flag & TileInfo::USEABLE) != 0 || (m_Map[tileIndex].m_Flag & TileInfo::ATTACKABLE) != 0 || (m_Map[tileIndex].m_Flag & TileInfo::STOPPABLE) != 0)
            continue;
        if ((m_Map[tileIndex].m_Flag & TileInfo::PASSABLE) != 0 ) {
            return tileIndex;
        }
    }
}
int StandardLevel::randomPickableRespawnCell()
{
    int count = 0;
    int tileIndex = -1;
    
    while (true) {
        if (++count > 10) {
            return -1;
        }
        int rand = cocos2d::random(0, (int)(m_Areas.size())-1);
        Area* area = static_cast<Area*>(m_Areas[rand]);
        if (area == nullptr)
            continue;
        if(area->getAreaType() != Area::AT_STANDARD)
            continue;

        tileIndex = area->getRandomTile(this);
        if((m_Map[tileIndex].m_Flag & TileInfo::USEABLE) != 0 || (m_Map[tileIndex].m_Flag & TileInfo::ATTACKABLE) != 0 || (m_Map[tileIndex].m_Flag & TileInfo::STOPPABLE) != 0)
            continue;
        if ((m_Map[tileIndex].m_Flag & TileInfo::PASSABLE) != 0 || (m_Map[tileIndex].m_Flag & TileInfo::PICKABLE) == 0) {
            return tileIndex;
        }
    }}