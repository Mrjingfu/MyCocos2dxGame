//
//  TerrainTile.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/8.
//
//

#ifndef TerrainTile_hpp
#define TerrainTile_hpp

#include "cocos2d.h"
extern const std::string TERRAIN_TILES_NAME[];
class TerrainTile : public cocos2d::Sprite3D
{
public:
    typedef enum
    {
        TT_CHASM = 0,           ///深渊
        TT_STANDARD,            ///标准地板
        TT_WALL,                ///墙
        TT_ENTRANCE,            ///入口
        TT_EXIT,                ///出口
        TT_STANDARD_PORTAL,     ///标准传送门
        TT_SMALL_PORTAL,        ///小传送门
        TT_TUNNEL,              ///通道
        TT_DOOR,                ///门
        TT_OPENED_DOOR,         ///开了的门
        TT_LOCKED_DOOR,         ///上锁的门
        TT_LOCKED_BOSS_DOOR,    ///上锁的boss房间的门
        TT_LOCKED_MAGIC_DOOR,   ///竞技场的门
        TT_SECRET_DOOR,         ///隐藏的门
        
        TT_TOXIC_TRAP,              ///中毒陷阱
        TT_HIDE_TOXIC_TRAP,         ///隐藏的中毒陷阱
        TT_FIRE_TRAP,               ///火焰陷阱
        TT_HIDE_FIRE_TRAP,          ///隐藏的火焰陷阱
        TT_PARALYTIC_TRAP,          ///麻痹陷阱
        TT_HIDE_PARALYTIC_TRAP,     ///隐藏的麻痹陷阱
        TT_GRIPPING_TRAP,           ///夹子陷阱
        TT_HIDE_GRIPPING_TRAP,      ///隐藏的夹子陷阱
        TT_SUMMONING_TRAP,          ///召唤陷阱
        TT_HIDE_SUMMONING_TRAP,     ///隐藏的召唤陷阱
        TT_WEAK_TRAP,               ///虚弱陷阱
        TT_HIDE_WEAK_TRAP,          ///隐藏的虚弱陷阱
        TT_MAX
    }
    TileType;
    static const int CONTENT_SCALE = 16;
    static TerrainTile* create(TileType type);
    TerrainTile();
    virtual ~TerrainTile();
    
    virtual std::string getDesc();
    
    void setVisited(bool visited);
    
    cocos2d::Vec2 getPosInMap();
protected:
    TileType        m_Type;
};


#endif /* TerrainTile_hpp */
