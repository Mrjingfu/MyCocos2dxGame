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
USING_NS_CC;

StandardLevel::StandardLevel()
{
    m_Type = LT_STANDARD;
    m_nMinAreaSize  = 7;
    m_nMaxAreaSize  = 9;
    m_nStandardAreaCount = 0;
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
bool StandardLevel::decorate()
{
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
    int specialRooms = 0;
    
    for (PathGraphNode* node : m_Areas) {
        Area* area = static_cast<Area*>(node);
        if(area)
        {
            if(area->getAreaType() == Area::AT_UNKNOWN && area->getConnectedAreas().size() == 1)
            {
                if(m_SpecailAreas.size() > 0 && area->getRect().size.width > 3 && area->getRect().size.height > 3 && cocos2d::random(0, specialRooms*specialRooms + 1) == 0)
                {
                    area->setAreaType(Area::AT_SHOP);
                    specialRooms++;
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
    int rand = cocos2d::random(0, 2);
    m_nStandardAreaCount = 0;
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
                    switch (rand) {
                        case 0:
                            area->setAreaType(Area::AT_TUNNEL);
                            break;
                        case 1:
                            area->setAreaType(Area::AT_STANDARD);
                            m_nStandardAreaCount++;
                            break;
                        case 2:
                            area->setAreaType(Area::AT_PASSAGE);
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
        if (area != nullptr && area->getAreaType() == Area::AT_TUNNEL) {
            area->setAreaType(Area::AT_STANDARD);
            m_nStandardAreaCount++;
        }
    }
    
//    ///替换隧道为通道
//    for (PathGraphNode* node : m_Areas) {
//        Area* area = static_cast<Area*>(node);
//        if(area && area->getAreaType() == Area::AT_TUNNEL)
//            area->setAreaType(Area::AT_PASSAGE);
//    }
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

void StandardLevel::showMap(bool show)
{
    if(!show)
        return;
    if (VoxelExplorer::getInstance()->getMainLayer() == nullptr)
        return;
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
            m_pMapDrawNode->setScale(winSize.width/32);
        }
        m_pMapDrawNode->clear();
        
        for (int i = 0; i<m_nHeight; i++) {
            for (int j = 0; j<m_nWidth; j++) {
                int index = i*m_nWidth+j;
                TileInfo info = m_Map[index];
                cocos2d::Rect rect(j,i,1,1);
                Vec2 vertices[4] = {
                    Vec2( rect.getMinX(), rect.getMinY() ),
                    Vec2( rect.getMaxX(), rect.getMinY() ),
                    Vec2( rect.getMaxX(), rect.getMaxY() ),
                    Vec2( rect.getMinX(), rect.getMaxY() ),
                };
                
                switch (info.m_Type) {
                    case TerrainTile::TT_STANDARD:
                        if(info.m_AreaType == Area::AT_SHOP)
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
                    case TerrainTile::TT_TOXIC_TRAP:
                    case TerrainTile::TT_FIRE_TRAP:
                    case TerrainTile::TT_PARALYTIC_TRAP:
                    case TerrainTile::TT_GRIPPING_TRAP:
                    case TerrainTile::TT_SUMMONING_TRAP:
                    case TerrainTile::TT_WEAK_TRAP:
                        m_pMapDrawNode->drawPolygon(vertices, 4, Color4F::WHITE, 0, Color4F(0,0,0,0));
                        break;
                    default:
                        break;
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
bool StandardLevel::mergeSmallIntersectArea(Area* area, Area* other)
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
        
        rect.origin.x += 0;
        rect.origin.y += 1;
        rect.size.width += 1;
        rect.size.height -=1;
       
        generateTerrainTiles( rect.origin.x, rect.origin.y, 1, rect.size.height, TerrainTile::TT_STANDARD, area->getAreaType() );
        
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
        
        rect.origin.x += 1;
        rect.origin.y += 0;
        rect.size.width -= 1;
        rect.size.height +=1;
        
        generateTerrainTiles( rect.origin.x, rect.origin.y, rect.size.width, 1, TerrainTile::TT_STANDARD, area->getAreaType());
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
        nTraps = m_Areas.size() + RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nNodeDepth.GetLongValue() + RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth.GetLongValue();
    }
    else
    {
        if(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth > 1)
        {
            nTraps = m_Areas.size() + RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth.GetLongValue();
        }
    }
    
    for (int i = 0; i<nTraps; i++) {
        int pos = cocos2d::random(0, (int)m_Map.size());
        if(m_Map[pos].m_AreaType == Area::AT_ENTRANCE || m_Map[pos].m_AreaType == Area::AT_EXIT)
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
int StandardLevel::randomRespawnCell()
{
    int count = 0;
    int tileIndex = -1;
    
    while (true) {
        if (++count > 10) {
            return -1;
        }
        int rand = cocos2d::random(0, (int)(m_Areas.size())-1);
        Area* area = static_cast<Area*>(m_Areas[rand]);
        if (area == nullptr || area->getAreaType() != Area::AT_STANDARD)
            continue;
        CCASSERT(area->getAreaType() != Area::AT_ENTRANCE, "fuck");
        tileIndex = area->getRandomTile(this);
        if((m_Map[tileIndex].m_Flag & TileInfo::LOS_BLOCKING) != 0)
            continue;
        if ((m_Map[tileIndex].m_Flag & TileInfo::PASSABLE) != 0 ) {
            return tileIndex;
        }
    }
}