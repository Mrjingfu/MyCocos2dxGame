//
//  BaseLevel.h
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#ifndef __Voxel_Explorer__BaseLevel__
#define __Voxel_Explorer__BaseLevel__

#include "cocos2d.h"
#include "Area.h"
#include "Actor.hpp"
struct TileInfo
{
    typedef enum {
        INITIALISED     = 1<<0,     ///初始化状态,阻挡
        STOPPABLE       = 1<<1,     ///阻挡的
        PASSABLE        = 1<<2,     ///可通过状态
        USEABLE         = 1<<3,     ///可使用状态
        ATTACKABLE      = 1<<4,     ///可攻击状态
        PICKABLE        = 1<<5,     ///可拾取状态
        
    } FLAG;
    typedef enum {
        FORWARD = 0,
        LEFT,
        RIGHT,
        BACK,
        UNKNOWN
    } Direction;
    TerrainTile::TileType   m_Type;
    Area::AREA_TYPE         m_AreaType;
    
    bool        m_bVisited;
    int         m_Flag;
    int         m_nX;
    int         m_nY;
    Actor::ActorDir   m_Dir;
    TileInfo()
    {
        m_Type = TerrainTile::TT_CHASM;
        m_AreaType = Area::AT_UNKNOWN;
        m_Flag = INITIALISED;
        m_bVisited = false;
        m_nX = -1;
        m_nY = -1;
        m_Dir = Actor::AD_UNKNOWN;
    }
    bool isPassable() const
    {
        if((m_Flag & TileInfo::INITIALISED) != 0)
            return false;
        if((m_Flag & TileInfo::STOPPABLE) != 0)
            return false;
        if((m_Flag & TileInfo::ATTACKABLE) != 0)
            return false;
        if((m_Flag & TileInfo::USEABLE) != 0)
            return false;
        if((m_Flag & TileInfo::PASSABLE) != 0)
            return true;
        return false;
    }
    bool isAvalidRandomTransport() const
    {
        if(m_AreaType != Area::AT_STANDARD || m_AreaType != Area::AT_TUNNEL || m_AreaType != Area::AT_PASSAGE)
            return false;
        if(!isPassable())
            return false;
        else if(m_Type >= TerrainTile::TT_TOXIC_TRAP && m_Type <= TerrainTile::TT_HIDE_WEAK_TRAP)
            return false;
        return true;
    }
};
class BaseLevel : public cocos2d::Ref
{
    friend class Area;
protected:
    BaseLevel();
public:
    typedef enum{
        LT_STANDARD,
        LT_MAX
    }
    LEVEL_TYPE;
    
    void create();
    
    LEVEL_TYPE getLevelType() const;
    void setLevelType(LEVEL_TYPE type);
    
    int getWidth() const { return m_nWidth; }
    int getHeight() const { return m_nHeight; }
    int getLength() const { return m_nLenght; }
    
    std::vector<int> getNeighbours4() { return {-m_nWidth, +1, +m_nWidth, -1}; }
    std::vector<int> getNeighbours5() { return {0, -m_nWidth, +1, +m_nWidth, -1}; }
    std::vector<int> getNeighbours8() { return {+1, -1, +m_nWidth, -m_nWidth, +1+m_nWidth, +1-m_nWidth, -1+m_nWidth, -1-m_nWidth}; }
    std::vector<int> getNeighbours9() { return {0, +1, -1, +m_nWidth, -m_nWidth, +1+m_nWidth, +1-m_nWidth, -1+m_nWidth, -1-m_nWidth}; }
    std::vector<int> getNeighbours13() { return {0, +1, -1, +m_nWidth, -m_nWidth, +1+m_nWidth, +1-m_nWidth, -1+m_nWidth, -1-m_nWidth, +2, -2, +m_nWidth*2, -m_nWidth*2}; }
    std::vector<int> getNeighbours21() { return {0, +1, -1, +m_nWidth, -m_nWidth, +1+m_nWidth, +1-m_nWidth, -1+m_nWidth, -1-m_nWidth, +2, -2, +m_nWidth*2, -m_nWidth*2, +1+m_nWidth*2,-1+m_nWidth*2, +1-m_nWidth*2,-1-m_nWidth*2, -2+m_nWidth, +2+m_nWidth, +2-m_nWidth, -2-m_nWidth}; }
    std::vector<int> getNeighbours25() { return {0, +1, -1, +m_nWidth, -m_nWidth, +1+m_nWidth, +1-m_nWidth, -1+m_nWidth, -1-m_nWidth, +2, -2, +m_nWidth*2, -m_nWidth*2, +1+m_nWidth*2,-1+m_nWidth*2, +1-m_nWidth*2,-1-m_nWidth*2, -2+m_nWidth, +2+m_nWidth, +2-m_nWidth, -2-m_nWidth, +2+m_nWidth*2, +2-m_nWidth*2, -2+m_nWidth*2, -2-m_nWidth*2}; }
    
    bool isAdjacent(const cocos2d::Vec2& a, const cocos2d::Vec2& b);
    int getDistance(const cocos2d::Vec2& a, const cocos2d::Vec2& b);
    
    bool isAdjacent(int a, int b);
    int getDistance(int a, int b);
    
    cocos2d::Vec2 getSpawnPoint() const { return  m_spawnPoint; }
    
    std::string getTerrainTileInfoDesc(int x, int y);
    void generateTerrainTiles(int x, int y , int width, int height, TerrainTile::TileType tileType, Area::AREA_TYPE areaType, Actor::ActorDir dir = Actor::AD_UNKNOWN);
    void setTerrainTile(int x, int y, TerrainTile::TileType tileType, Area::AREA_TYPE areaType , Actor::ActorDir dir = Actor::AD_UNKNOWN);
    
    bool isTerrainTilePassable(int index);
    
    int getTerrainTileFlag(int x, int y);
    void setTerrainTileFlag(int x, int y, int flag );
    void wrapTerrainTiles(int x, int y , int width, int height, TerrainTile::TileType type, TerrainTile::TileType withType);
    
    void updateTerrainTileFogOfWar(int x, int y , int width, int height, bool visited);
    void updateTrapTileByPos(const cocos2d::Vec2& pos);
    bool checkMovable(Actor* actor, TileInfo& info);
    
    bool getNextPathStep(const cocos2d::Vec2& from, const cocos2d::Vec2& to, cocos2d::Vec2& nextPos);
    cocos2d::Vec2 getRandomPassableTile();
    cocos2d::Vec2 getRandomTranspotTile();
    void searchAndCheck(int x, int y, int searchDistance);
    
    bool hasShowMap() const { return m_bShowMap; }
    void load();
    void save();
    
public:
    virtual void showMap(bool show) = 0;
    virtual void updateAreaFogOfWarByPos(const cocos2d::Vec2& pos) = 0;
    virtual bool createSummoningMonsters(const cocos2d::Vec2& pos) = 0;
protected:
    virtual bool build() = 0;
    virtual bool createTerrain() = 0;
    virtual bool decorateAreas() = 0;
    virtual bool createUseableItems(Area* area) = 0;
    virtual bool decorateSpecialArea(Area* area) = 0;
    virtual bool createMonsters() = 0;
    virtual bool createPickableItems() = 0;

    virtual int calculateLevelMonsterCount() = 0;
    virtual int calculateLevelUseableItemCount(const cocos2d::Size& areaSize) = 0;
private:
    int assignTerrainTileFlag(TerrainTile::TileType type);
protected:
    bool                m_bShowMap;
    LEVEL_TYPE           m_Type;
    std::vector<TileInfo> m_Map;
    
    cocos2d::Vec2        m_spawnPoint;
    
    cocos2d::DrawNode*   m_pMapDrawNode;
    cocos2d::DrawNode*   m_pDebugDrawNode;
    
    int                 m_nWidth;
    int                 m_nHeight;
    int                 m_nLenght;
};

#endif /* defined(__Voxel_Explorer__BaseLevel__) */
