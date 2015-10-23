//
//  BaseMonster.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#include "BaseMonster.hpp"
USING_NS_CC;
const char* MONSTER_MODEL_NAMES[] = {
    "MMN_UNKNOWN",
    
    "MMN_SEWER_BEGIN",
    "MMN_RAT",             ///老鼠
    "MMN_BAT",             ///蝙蝠
    "MMN_SNAKE",           ///蛇
    "MMN_SPIDER",          ///蜘蛛
    "MMN_SLIME",           ///史莱姆
    "MMN_SEWER_END",
    
    "MMN_PRISON_BEGIN",
    "MMN_ALLIP",           ///怨魂
    "MMN_PRISONER",        ///囚犯
    "MMN_PRISONGUARD",     ///监狱守卫
    "MMN_TORTURE",         ///拷问者
    "MMN_MOB",             ///暴徒
    "MMN_PRISON_END",
    
    "MMN_FANE_BEGIN",
    "MMN_BELIEVER",        ///信徒
    "MMN_GATEKEEPER",      ///看门人
    "MMN_APOLOGIST",       ///辩护者
    "MMN_ADJUDICATOR",     ///审判者
    "MMN_PRIEST",          ///牧师
    "MMN_FANE_END",
    
    "MMN_MINES_BEGIN",
    "MMN_DEATHMINER",      ///死亡矿工
    "MMN_KOBOLD",          ///狗头人
    "MMN_OOZE",            ///软泥怪
    "MMN_SHADOW",          ///阴影怪
    "MMN_ANKHEG",          ///掘地虫
    "MMN_MINES_END",
    
    "MMN_CAVE_BEGIN",
    "MMN_WOLF",            ///狼
    "MMN_BEAR",            ///熊
    "MMN_GOBLIN",          ///地精
    "MMN_DINOSAUR",        ///恐龙
    "MMN_GNOLL",           ///豺狼人
    "MMN_CAVE_END",
    
    "MMN_TOMB_BEGIN",
    "MMN_SKELETON",        ///骷髅
    "MMN_ZOMBIE",          ///僵尸
    "MMN_GARGOYLE",        ///石像鬼
    "MMN_GHOST",           ///幽灵
    "MMN_GHOUL",           ///食尸鬼
    "MMN_TOMB_END",
    
    "MMN_MAX"
};
BaseMonster::BaseMonster()
{
    m_Type = MT_UNKNOWN;
    m_State = MS_UNKNOWN;
}
BaseMonster::~BaseMonster()
{
}