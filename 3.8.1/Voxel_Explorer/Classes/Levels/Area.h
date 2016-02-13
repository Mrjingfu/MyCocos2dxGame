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
        AT_BOSS_ROOM,    ///boss房间
        AT_BOSS_EXIT,    ///boss房间出口
        AT_PASSAGE,      ///通道
        AT_TUNNEL,       ///隧道
        
        AT_SPECIAL_EQUIPMENT_SHOP,          ///装备商店
        AT_SPECIAL_MAGIC_SHOP,              ///魔法商店
        AT_SPECIAL_AID_STATION,             ///救护站
        AT_SPECIAL_ALCHEMIST_ROOM,          ///炼金术师房间
        AT_SPECIAL_WITCH_ROOM,              ///魔女的房间
        AT_SPECIAL_THEIF_ROOM,              ///盗贼的房间
        AT_SPECIAL_SAGE_ROOM,               ///智者房间
        AT_SPECIAL_MISSION_ROOM,            ///任务房间
        AT_SPECIAL_TREASURE_ROOM,           ///宝藏房间
        AT_SPECIAL_DECORATION_ROOM,         ///装饰品屋子
        AT_SPECIAL_TRANSPOT_ROOM,           ///传送房间
        
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
    
    bool isHiddenArea();
    
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
    void generateBossRoomArea(BaseLevel* level);
    void generateBossExitArea(BaseLevel* level);
    void generateTunnelArea(BaseLevel* level);
    void generatePassageArea(BaseLevel* level);
    void generateSpecialArea(BaseLevel* level);
    void generateSpecialHiddenArea(BaseLevel* level);
    void generateSpecialLockedArea(BaseLevel* level);
    void generateSpecialTranspotArea(BaseLevel* level);
    
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
