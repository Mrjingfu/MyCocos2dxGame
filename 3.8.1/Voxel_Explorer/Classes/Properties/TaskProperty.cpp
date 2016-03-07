//
//  TaskProperty.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/5.
//
//

#include "TaskProperty.hpp"
#include "RandomDungeon.hpp"
TaskProperty::TaskProperty()
{
    
}

TaskProperty::~TaskProperty()
{
    
}
TaskProperty* TaskProperty::create()
{
    TaskProperty* prop = new(std::nothrow) TaskProperty();
    if (prop)
    {
        prop->autorelease();
        return prop;
    }else
    {
        delete prop;
        prop = nullptr;
        return nullptr;
    }
}
void TaskProperty::randomDatas()
{
    std::vector<eStatistType> m_vMonsterType;
    DUNGEON_TYPE dungeonType = RandomDungeon::getInstance()->getCurrentDungeonNode()->getDungeonNodeType();
    if (dungeonType == DT_SEWER)
        m_vMonsterType = {ST_MONSTER_RAT,ST_MONSTER_BAT,ST_MONSTER_SNAKE,ST_MONSTER_SPIDER,ST_MONSTER_SLIME};
    else if (dungeonType == DT_PRISON)
        m_vMonsterType = {ST_MONSTER_ALLIP,ST_MONSTER_PRISONER,ST_MONSTER_PRISONGUARD,ST_MONSTER_TORTURE,ST_MONSTER_MOB};
    else if (dungeonType == DT_FANE)
        m_vMonsterType = {ST_MONSTER_BELIEVER,ST_MONSTER_GATEKEEPER,ST_MONSTER_APOLOGIST,ST_MONSTER_ADJUDICATOR,ST_MONSTER_PRIEST};
    else if (dungeonType == DT_MINES)
        m_vMonsterType = {ST_MONSTER_DEATHMINER,ST_MONSTER_KOBOLD,ST_MONSTER_OOZE,ST_MONSTER_SHADOW,ST_MONSTER_ANKHEG};
    else if (dungeonType == DT_CAVE)
        m_vMonsterType = {ST_MONSTER_WOLF,ST_MONSTER_BEAR,ST_MONSTER_GOBLIN,ST_MONSTER_DINOSAUR,ST_MONSTER_GNOLL};
    else if (dungeonType == DT_TOMB)
        m_vMonsterType = {ST_MONSTER_SKELETON,ST_MONSTER_ZOMBIE,ST_MONSTER_GARGOYLE,ST_MONSTER_GHOST,ST_MONSTER_GHOUL};
    
    
    
}