//
//  Area.h
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#ifndef __Voxel_Explorer__Area__
#define __Voxel_Explorer__Area__

#include "cocos2d.h"
#include "Door.h"
#include "Graph.h"
#include "TerrainTile.hpp"
class BaseLevel;
class Area : public cocos2d::Ref, public PathGraphNode
{
    Area();
    virtual ~Area();
public:
    typedef enum{
        AT_UNKNOWN = 0,
        AT_STANDARD,
        AT_ENTRANCE,
        AT_EXIT,
        AT_PASSAGE,      ///通道
        AT_TUNNEL,       ///隧道
        AT_SHOP,         ///商店
        
        AT_SPECIAL_SECRET,      ///秘密地点
        AT_SPECIAL_WEAKFLOOR,   ///坏地板
        AT_SPECIAL_PIT,     ///坑
        AT_MAX
    }
    AREA_TYPE;
    
    static std::vector<AREA_TYPE>       SPECIALS;
    
    static Area* create();
    virtual bool init();
    
    void addNeigbourArea(Area* other );
    void connectArea(Area* other);
    Door* getEntrance();
    
    void generate(BaseLevel* level);
    
    AREA_TYPE getAreaType() const;
    void setAreaType(AREA_TYPE type);
    
    cocos2d::Rect getRect() const;
    void setRect(const cocos2d::Rect& rect);
    
    cocos2d::Vec2 getCenter();
    
    bool checkInside(int p, BaseLevel* level);
    bool checkInside(const cocos2d::Vec2& pos);
    
    cocos2d::Rect getIntersectRect(Area* other);
    
    std::unordered_map<Area*, Door*>& getConnectedAreas() { return m_ConnectedAreas; }
    
    int getRandomTile(BaseLevel* level);
    int getRandomTile(BaseLevel* level, int m);
    
    std::vector<int> getTilesOnEdge(BaseLevel* level, int m);
    std::vector<int> getTilesOnCorner(BaseLevel* level);
    
    void updateAreaFogOfWar(BaseLevel* level, bool visited);
private:
    void generateStandardArea(BaseLevel* level);
    void generateEntranceArea(BaseLevel* level);
    void generateExitArea(BaseLevel* level);
    void generateTunnelArea(BaseLevel* level);
    void generatePassageArea(BaseLevel* level);
    void generateShopArea(BaseLevel* level);
    
    void generateTerrainTiles(BaseLevel* level, TerrainTile::TileType type);
    void generateTerrainTiles(BaseLevel* level, int m, TerrainTile::TileType type);
    void generateTerrainTiles(BaseLevel* level, cocos2d::Rect rect, TerrainTile::TileType type);
    
    void wrapTerrainTiles(BaseLevel* level, TerrainTile::TileType type, TerrainTile::TileType withType);
    void setTerrainTile(BaseLevel* level, int x, int y, TerrainTile::TileType type);
    void setRandomTerrainTile(BaseLevel* level, int m, TerrainTile::TileType type);
    
    ///for passage
    static int xy2p(const cocos2d::Rect& rect, const cocos2d::Vec2& pos);
    static cocos2d::Vec2 p2xy(const cocos2d::Rect& rect, int p);
protected:
    AREA_TYPE           m_Type;
    cocos2d::Rect       m_Rect;
    
    std::unordered_map<Area*, Door*>    m_ConnectedAreas;
};

#endif /* defined(__Voxel_Explorer__Area__) */
