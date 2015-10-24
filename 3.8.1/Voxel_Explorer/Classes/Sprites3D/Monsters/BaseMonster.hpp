//
//  BaseMonster.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#ifndef BaseMonster_hpp
#define BaseMonster_hpp

#include "Actor.hpp"
#include "TerrainTile.hpp"
extern const std::string MONSTER_MODEL_NAMES[];
class BaseMonster : public Actor
{
public:
    typedef enum{
        MT_UNKNOWN = 0,
        
        //SEWER_BEGIN
        MT_RAT,             ///老鼠
        MT_BAT,             ///蝙蝠
        MT_SNAKE,           ///蛇
        MT_SPIDER,          ///蜘蛛
        MT_SLIME,           ///史莱姆
        //SEWER_END
        
        //PRISON_BEGIN
        MT_ALLIP,           ///怨魂
        MT_PRISONER,        ///囚犯
        MT_PRISONGUARD,     ///监狱守卫
        MT_TORTURE,         ///拷问者
        MT_MOB,             ///暴徒
        //PRISON_END
        
        //FANE_BEGIN
        MT_BELIEVER,        ///信徒
        MT_GATEKEEPER,      ///看门人
        MT_APOLOGIST,       ///辩护者
        MT_ADJUDICATOR,     ///审判者
        MT_PRIEST,          ///牧师
        //FANE_END
        
        //MINES_BEGIN
        MT_DEATHMINER,      ///死亡矿工
        MT_KOBOLD,          ///狗头人
        MT_OOZE,            ///软泥怪
        MT_SHADOW,          ///阴影怪
        MT_ANKHEG,          ///掘地虫
        //MINES_END

        //CAVE_BEGIN
        MT_WOLF,            ///狼
        MT_BEAR,            ///熊
        MT_GOBLIN,          ///地精
        MT_DINOSAUR,        ///恐龙
        MT_GNOLL,           ///豺狼人
        //CAVE_END
        
        //TOMB_BEGIN
        MT_SKELETON,        ///骷髅
        MT_ZOMBIE,          ///僵尸
        MT_GARGOYLE,        ///石像鬼
        MT_GHOST,           ///幽灵
        MT_GHOUL,           ///食尸鬼
        //TOMB_END

        MT_MAX
    } MonsterType;
    typedef enum{
        MS_UNKNOWN,
        MS_MAX
    } MonsterState;
protected:
    BaseMonster();
    ~BaseMonster();
protected:
    MonsterType         m_Type;
    MonsterState        m_State;
};

#endif /* BaseMonster_hpp */
