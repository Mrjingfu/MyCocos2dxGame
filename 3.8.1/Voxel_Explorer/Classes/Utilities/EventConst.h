//
//  EventConst.h
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/20.
//
//

#ifndef EventConst_h
#define EventConst_h

struct HurtData
{
    bool m_bDodge;
    bool m_bCriticalStrike;
    bool m_bBlocked;
    int m_nDamage;
    HurtData()
    {
        m_bDodge = false;
        m_bCriticalStrike = false;
        m_bBlocked = false;
        m_nDamage = false;
    }
};

//EVENT
static const std::string EVENT_PLAYER_PROPERTY_DIRTY = "PLAYER_PROPERTY_DIRTY";
static const std::string EVENT_PLAYER_DEATH = "PLAYER_DEATH";
static const std::string EVENT_PLAYER_MONEY_NOT_ENOUGH = "PLAYER_MONEY_NOT_ENOUGH";
static const std::string EVENT_PLAYER_NO_MANA = "PLAYER_NO_MANA";
static const std::string EVENT_PLAYER_EQUIPED_WEAPON = "PLAYER_EQUIPED_WEAPON";
static const std::string EVENT_PLAYER_EQUIPED_ARMOR = "PLAYER_EQUIPED_ARMOR";
static const std::string EVENT_PLAYER_EQUIPED_ORNAMENTS = "PLAYER_EQUIPED_ORNAMENTS";
static const std::string EVENT_PLAYER_LEVEL_UP = "PLAYER_LEVEL_UP";
static const std::string EVENT_PLAYER_BAG_NO_SPACE = "PLAYER_BAG_NO_SPACE";
static const std::string EVENT_PLAYER_BAG_EXTEND_OK = "PLAYER_BAG_EXTEND_OK";
static const std::string EVENT_PLAYER_BAG_EXTEND_HAS_REACH_MAXTIMES = "PLAYER_BAG_EXTEND_HAS_REACH_MAXTIMES";

static const std::string EVENT_PLAYER_HURT = "PLAYER_HURT";

static const std::string EVENT_MONSTER_PROPERTY_DIRTY = "MONSTER_PROPERTY_DIRTY";
static const std::string EVENT_MONSTER_DEATH = "MONSTER_DEATH";
static const std::string EVENT_MONSTER_HURT = "MONSTER_HURT";

#endif /* EventConst_h */
