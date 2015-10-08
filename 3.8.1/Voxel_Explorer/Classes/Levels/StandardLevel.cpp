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
USING_NS_CC;

StandardLevel::StandardLevel()
{
    m_Type = LT_STANDARD;
    m_nMinAreaSize  = 7;
    m_nMaxAreaSize  = 9;
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
        
        if (retry++ > 20) {
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
    generateTerrain();  ///生成地表
//    paintWater();
//    paintGrass();
//    
//    placeTraps();
    
    generateSpawnPoint(); ///生成出生点
#if COCOS2D_DEBUG
    showDebug(true);
#endif
    return true;
}
void StandardLevel::decorate()
{
}
void StandardLevel::createMobs()
{
}
void StandardLevel::createItems()
{
}

bool StandardLevel::initAreas()
{
    splitArea( cocos2d::Rect( 0, 0, WIDTH - 1, HEIGHT - 1 ) );
    
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
                    area->setAreaType(Area::AT_SPECIAL_SECRET);
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
    ///生成隧道
    int count = 0;
    for (PathGraphNode* node : m_Areas) {
        Area* area = static_cast<Area*>(node);
        if(area)
        {
            if (area->getAreaType() == Area::AT_UNKNOWN) {
                int connections = area->getConnectedAreas().size();
                if ( connections == 0) {
                    
                } else if (cocos2d::random(0, connections * connections-1) == 0) {
                    area->setAreaType(Area::AT_STANDARD);
                    count++;
                } else {
                    area->setAreaType(Area::AT_TUNNEL);
                }
            }

        }
    }
    
    ///保证隧道至少4条
    while (count < 4) {
        int rand = cocos2d::random(0, (int)(m_Areas.size())-1);
        Area* area = static_cast<Area*>(m_Areas[rand]);
        if (area != nullptr) {
            area->setAreaType(Area::AT_TUNNEL);
            count++;
        }
    }
}
void StandardLevel::generateTerrain()
{
    for (PathGraphNode* node : m_Areas) {
        Area* area = static_cast<Area*>(node);
        if(area)
        {
            if(area->getAreaType() != Area::AT_UNKNOWN)
            {
                placeDoors(area);
                generateTerrainTiles(area);
            }
            else
            {
                if (m_BoundaryType == LBT_CHASM && cocos2d::random(0, 1) == 0) {
                    generateWalls(area);
                }
            }
        }
    }
    for (PathGraphNode* node : m_Areas) {
        Area* area = static_cast<Area*>(node);
        if(area)
            generateDoors(area);
    }
}

void StandardLevel::showDebug(bool show)
{
    if(!show)
        return;
    if (VoxelExplorer::getInstance()->getMainLayer() == nullptr)
        return;
    if(!show)
    {
        if(m_pDebugDrawNode)
        {
            m_pDebugDrawNode->clear();
            m_pDebugDrawNode->removeFromParentAndCleanup(true);
            m_pDebugDrawNode = nullptr;
        }
    }
    else
    {
        m_pDebugDrawNode = DrawNode::create();
        VoxelExplorer::getInstance()->getMainLayer()->addChild(m_pDebugDrawNode);
        m_pDebugDrawNode->clear();
        m_pDebugDrawNode->setGlobalZOrder(100);
        m_pDebugDrawNode->setScale(4);
        
        ///绘制地面
        for (PathGraphNode* node : m_Areas) {
            Area* area = static_cast<Area*>(node);
            if(area)
            {
                cocos2d::Rect rect = area->getRect();
                
                Vec2 vertices[4] = {
                    Vec2( rect.getMinX(), rect.getMinY() ),
                    Vec2( rect.getMaxX(), rect.getMinY() ),
                    Vec2( rect.getMaxX(), rect.getMaxY() ),
                    Vec2( rect.getMinX(), rect.getMaxY() ),
                };
                switch (area->getAreaType()) {
                    case Area::AT_UNKNOWN:
                    case Area::AT_MAX:
                        break;
                    case Area::AT_STANDARD:
                    case Area::AT_ENTRANCE:
                    case Area::AT_EXIT:
                        m_pDebugDrawNode->drawPolygon(vertices, 4, Color4F::GRAY, 0.05f, Color4F::RED);
                        break;
                    case Area::AT_PASSAGE:
                    case Area::AT_TUNNEL:
                        m_pDebugDrawNode->drawPolygon(vertices, 4, Color4F::GREEN, 0.05f, Color4F::RED);
                        break;
                    case Area::AT_SPECIAL_SECRET:
                        m_pDebugDrawNode->drawPolygon(vertices, 4, Color4F::MAGENTA, 0.05f, Color4F::RED);
                        break;
                    default:
                        m_pDebugDrawNode->drawPoly(vertices, 4, true, Color4F::RED);
                        break;
                }
            }
        }
        
        ///绘制关键点
        for (PathGraphNode* node : m_Areas) {
            Area* area = static_cast<Area*>(node);
            if(area)
            {
                switch (area->getAreaType()) {
                    case Area::AT_ENTRANCE:
                        m_pDebugDrawNode->drawDot(area->getPos(), 1.0f, Color4F::YELLOW);
                        break;
                    case Area::AT_EXIT:
                        m_pDebugDrawNode->drawDot(area->getPos(), 1.0f, Color4F::GREEN);
                        break;
                    default:
                        break;
                }
                
                Door* door = area->getEntrance();
                if(door)
                    m_pDebugDrawNode->drawDot(door->getPos(), 0.5f, Color4F::BLUE);
            }
        }
        
//        ///绘制路径
//        for (PathGraphNode* node : m_Areas) {
//            Area* area = static_cast<Area*>(node);
//            if(area)
//            {
//                cocos2d::Rect rect = area->getRect();
//                
//                Vec2 vertices[4] = {
//                    Vec2( rect.getMinX(), rect.getMinY() ),
//                    Vec2( rect.getMaxX(), rect.getMinY() ),
//                    Vec2( rect.getMaxX(), rect.getMaxY() ),
//                    Vec2( rect.getMinX(), rect.getMaxY() ),
//                };
//                m_pDebugDrawNode->drawPolygon(vertices, 4, Color4F(1,0,0,node->getWeight()*30), 0.05f, Color4F::RED);
//            }
//        }
    }
}
void StandardLevel::generateTerrainTiles(Area* area)
{
    if(!area)
        return;
    if(VoxelExplorer::getInstance()->getTerrainTilesLayer())
    {
        cocos2d::Rect rect = area->getRect();
        Area::AREA_TYPE type = area->getAreaType();
        TerrainTile* tile = TerrainTile::create(TerrainTile::TT_STANDARD);
        if(!tile)
            return;
        tile->setPosition(rect.getMidX()*TerrainTile::CONTENT_SCALE, rect.getMidY()*TerrainTile::CONTENT_SCALE);
        Texture2D::TexParams texRepeat = {GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT};
        tile->getTexture()->setTexParameters(texRepeat);
        tile->setTextureRect(cocos2d::Rect(0,0,rect.size.width*TerrainTile::CONTENT_SCALE,rect.size.height*TerrainTile::CONTENT_SCALE), true, Size(16,16));
        VoxelExplorer::getInstance()->getTerrainTilesLayer()->addChild(tile);
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
void StandardLevel::generateWalls(Area* area)
{}
void StandardLevel::generateDoors(Area* area)
{
    if(!area)
        return;
    for (auto iter = area->getConnectedAreas().begin(); iter != area->getConnectedAreas().end(); iter++) {
        Area* areaOri = iter->first;
        if(mergeStandardArea(area, areaOri))
            continue;
        Door* door = iter->second;
        if(areaOri)
        {
            int doorIndex = door->getPos().x + door->getPos().y * WIDTH;
            switch (door->getDoorType()) {
                case Door::DT_EMPTY:
                    break;
                    
                default:
                    break;
            }
        }
    }
}
bool StandardLevel::mergeStandardArea(Area* area, Area* other)
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
        
//        rect.top += 1;
//        w.bottom -= 0;
//        
//        w.right++;
//        
//        Painter.fill( this, w.left, w.top, 1, w.height(), Terrain.EMPTY );
        
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
        
//        w.left += 1;
//        w.right -= 0;
//        
//        w.bottom++;
//        
//        Painter.fill( this, w.left, w.top, w.width(), 1, Terrain.EMPTY );
    }
    
    return true;
}
void StandardLevel::generateSpawnPoint()
{
    if(m_AreaEntrance)
        m_spawnPoint = Vec2(m_AreaEntrance->getRect().getMidX()*TerrainTile::CONTENT_SCALE,(m_AreaEntrance->getRect().getMidY())*TerrainTile::CONTENT_SCALE);
}