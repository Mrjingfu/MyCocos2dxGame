//
//  StatisticsManager.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/12.
//
//

#include "StatisticsManager.hpp"

StatisticsManager::StatisticsManager()
{
    m_nPoisoningDeadNum         = 0;                //中毒死亡
    m_nCopperTotalNum           = 0;                //金币收集数
    m_nfoodEaten                = 0;                //到达最远深度
    m_nStepNum                  = 0;                //步数
    m_nMonsterKillTotalNum      = 0;                //杀死敌人总数
    m_nSearchHideInfoNum        = 0;                //搜索隐藏信息次数
    m_nUsePotionTotalNum        = 0;                //使用药品数
    m_nUseScrollTotalNum        = 0;                //使用卷轴数
    m_nUseKeyTotalNum           = 0;                //使用钥匙数
    m_nUserItemTotalNum         = 0;                //使用道具数
    m_nCriticalTotalNum         = 0;                //暴击数
    m_nDodgeTotalNum            = 0;                //闪避数
    m_nBlockTotalNum            = 0;                //格挡数
    
    for (int i = BaseMonster::MT_UNKNOWN; i<BaseMonster::MT_MAX; i++) {
        
        m_mMonsterKills[i]=0;
    }
  
    for (int i = TerrainTile::TT_TOXIC_TRAP; i<TerrainTile::TT_HIDE_WEAK_TRAP; i+=2) {
        
       m_nTriggerToxicNums.insert(std::pair<TerrainTile::TileType,CChaosNumber>((TerrainTile::TileType)i,CChaosNumber(0)));
    }
        
    
    {
        for (int i= PickableItem::PIT_KEY_COPPER; i<=PickableItem::PIT_KEY_ROOM; i++) {
            
            m_nUseItemNums.insert(std::pair<PickableItem::PickableItemType, CChaosNumber>(PickableItem::PickableItemType(i),CChaosNumber(0)));
            
        }
        
        for (int i= PickableItem::PIT_SCROLL_INDENTIFY; i<=PickableItem::PIT_POTION_UNIVERSAL; i++) {
            
            m_nUseItemNums.insert(std::pair<PickableItem::PickableItemType, CChaosNumber>(PickableItem::PickableItemType(i),CChaosNumber(0)));
            
        }
        
    }

    
}
StatisticsManager::~StatisticsManager()
{
    
}
StatisticsManager* StatisticsManager::getInstance()
{
    static StatisticsManager instance;
    return &instance;
}

void StatisticsManager::addMonsterKillNum(BaseMonster::MonsterType type)
{
    ++m_mMonsterKills[type] ;
    ++m_nMonsterKillTotalNum;
}
void StatisticsManager::addUseItemNum(PickableItem::PickableItemType type)
{
    CCASSERT(!(type>=PickableItem::PIT_DAGGER_DAGGER && type<=PickableItem::PIT_ORNAMENT_PRO_JEWELS) , "Itemtype error");
    ++m_nUseItemNums[type];
    
    if (type >=PickableItem::PIT_KEY_COPPER && type<=PickableItem::PIT_KEY_ROOM) {
        ++m_nUseKeyTotalNum;
    }
    if (type >=PickableItem::PIT_SCROLL_INDENTIFY && type<=PickableItem::PIT_SCROLL_DESTINY) {
        ++m_nUseScrollTotalNum;
    }
    if (type >=PickableItem::PIT_POTION_MINORHEALTH && type<=PickableItem::PIT_POTION_UNIVERSAL) {
        ++m_nUsePotionTotalNum;
    }
    ++m_nUserItemTotalNum;
}
void StatisticsManager::addTriggerToxicNum(TerrainTile::TileType type)
{
    CCASSERT(type>=TerrainTile::TT_TOXIC_TRAP && type>=TerrainTile::TT_HIDE_WEAK_TRAP, "Tile type error");
    
    ++m_nTriggerToxicNums[type];
    ++m_TriggerToxicTotalNum;
}
void StatisticsManager::addCopperTotalNum(int num)
{
    m_nCopperTotalNum+=num;
}
void StatisticsManager::addCostCopperNum(int num)
{
    m_nCostCopperNum+=num;
}
void StatisticsManager::addStepNum()
{
    ++m_nStepNum;
}
void StatisticsManager::addCriticalTotalNum()
{
    ++m_nCriticalTotalNum;
}
void StatisticsManager::addDodgeTotalNum()
{
    ++m_nDodgeTotalNum;
}
void StatisticsManager::addBlockTotalNum()
{
    ++m_nBlockTotalNum;
}

void StatisticsManager::load()
{
    
}
void StatisticsManager::save()
{
    
}
CChaosNumber StatisticsManager::getDataStatistType(eStatistType type) const
{
    
    if (type>=ST_MONSTER_RAT && type <=ST_MONSTER_GHOUL) {
       return getDataMonsterType(type).GetLongValue();
    }
    if (type>=ST_ITEM_KEY_COPPER && type <=ST_ITEM_POTION_UNIVERSAL) {
       return  getDataUseType(type).GetLongValue();
    }
    if (type>=ST_TRIGGER_TOXIC_TRAP && type <=ST_TRIGGER_WEAK_TRAP) {
        return getDataTriggerType(type).GetLongValue();
    }
    if (type>=ST_TOTAL_COPPER && type <=ST_TOTAL_TRIGGER) {
        return getDataTotalType(type).GetLongValue();
    }
    return CChaosNumber(0);
}
CChaosNumber StatisticsManager::getDataMonsterType(eStatistType type) const
{
    CCASSERT(type>=ST_MONSTER_RAT && type <=ST_MONSTER_GHOUL, "monster type error");
    return m_mMonsterKills[type];
}
CChaosNumber StatisticsManager::getDataUseType(eStatistType type) const
{
    CCASSERT(type>=ST_ITEM_KEY_COPPER && type <=ST_ITEM_POTION_UNIVERSAL,"use type error");
    PickableItem::PickableItemType ptyp = PickableItem::PickableItemType::PIT_UNKNOWN;
        switch (type) {
            case ST_ITEM_KEY_COPPER:
                ptyp =  PickableItem::PickableItemType::PIT_KEY_COPPER;
                break;
            case ST_ITEM_KEY_SILVER:
                 ptyp =  PickableItem::PickableItemType::PIT_KEY_SILVER;
                break;
            case ST_ITEM_KEY_GOLD:
                 ptyp =  PickableItem::PickableItemType::PIT_KEY_GOLD;
                break;
            case ST_ITEM_KEY_BOSS:
                 ptyp =  PickableItem::PickableItemType::PIT_KEY_BOSS;
                break;
            case ST_ITEM_KEY_ROOM:
                 ptyp =  PickableItem::PickableItemType::PIT_KEY_ROOM;
                break;
            case ST_ITEM_SCROLL_INDENTIFY:
                 ptyp =  PickableItem::PickableItemType::PIT_SCROLL_INDENTIFY;
                break;
            case ST_ITEM_SCROLL_TELEPORT:
                 ptyp =  PickableItem::PickableItemType::PIT_SCROLL_TELEPORT;
                break;
            case ST_ITEM_SCROLL_SPEED:
                 ptyp =  PickableItem::PickableItemType::PIT_SCROLL_SPEED;
                break;
            case ST_ITEM_SCROLL_STEALTH:
                 ptyp =  PickableItem::PickableItemType::PIT_SCROLL_STEALTH;
                break;
            case ST_ITEM_SCROLL_STRONGER:
                 ptyp =  PickableItem::PickableItemType::PIT_SCROLL_STRONGER;
                break;
            case ST_ITEM_SCROLL_DESTINY:
                 ptyp =  PickableItem::PickableItemType::PIT_SCROLL_DESTINY;
                break;
            case ST_ITEM_POTION_MINORHEALTH:
                 ptyp =  PickableItem::PickableItemType::PIT_POTION_MINORHEALTH;
                break;
            case ST_ITEM_POTION_LESSERHEALTH:
                 ptyp =  PickableItem::PickableItemType::PIT_POTION_LESSERHEALTH;
                break;
            case ST_ITEM_POTION_HEALTH:
                 ptyp =  PickableItem::PickableItemType::PIT_POTION_HEALTH;
                break;
            case ST_ITEM_POTION_MINORMANA:
                 ptyp =  PickableItem::PickableItemType::PIT_POTION_MINORMANA;
                break;
            case ST_ITEM_POTION_LESSERMANA:
                 ptyp =  PickableItem::PickableItemType::PIT_POTION_LESSERMANA;
                break;
            case ST_ITEM_POTION_MANA:
                 ptyp =  PickableItem::PickableItemType::PIT_POTION_MANA;
                break;
            case ST_ITEM_POTION_MINORRECOVERY:
                ptyp =  PickableItem::PickableItemType::PIT_POTION_MINORRECOVERY;
                break;
            case ST_ITEM_POTION_LESSERRECOVERY:
                ptyp =  PickableItem::PickableItemType::PIT_POTION_LESSERRECOVERY;
                break;
            case ST_ITEM_POTION_RECOVERY:
                ptyp =  PickableItem::PickableItemType::PIT_POTION_RECOVERY;
                break;
            case ST_ITEM_POTION_DETOXIFICATION:
                ptyp =  PickableItem::PickableItemType::PIT_POTION_DETOXIFICATION;
                break;
            case ST_ITEM_POTION_SPECIFIC:
                ptyp =  PickableItem::PickableItemType::PIT_POTION_SPECIFIC;
                break;
            case ST_ITEM_POTION_HEALING:
                ptyp =  PickableItem::PickableItemType::PIT_POTION_HEALING;
                break;
            case ST_ITEM_POTION_UNIVERSAL:
                ptyp =  PickableItem::PickableItemType::PIT_POTION_UNIVERSAL;
                break;
            }
    return m_nUseItemNums.at(ptyp);
}
CChaosNumber StatisticsManager::getDataTriggerType(eStatistType type) const
{
    CCASSERT(type>=ST_TRIGGER_TOXIC_TRAP && type <=ST_TRIGGER_WEAK_TRAP,"use type error");
    TerrainTile::TileType ptyp = TerrainTile::TileType::TT_MAX;
    switch (type) {
        case ST_TRIGGER_TOXIC_TRAP:
            ptyp =  TerrainTile::TileType::TT_TOXIC_TRAP;
            break;
        case ST_TRIGGER_FIRE_TRAP:
            ptyp =  TerrainTile::TileType::TT_FIRE_TRAP;
            break;
        case ST_TRIGGER_PARALYTIC_TRAP:
            ptyp =  TerrainTile::TileType::TT_PARALYTIC_TRAP;
            break;
        case ST_TRIGGER_GRIPPING_TRAP:
            ptyp =  TerrainTile::TileType::TT_GRIPPING_TRAP;
            break;
        case ST_TRIGGER_SUMMONING_TRAP:
            ptyp =  TerrainTile::TileType::TT_SUMMONING_TRAP;
            break;
        case ST_TRIGGER_WEAK_TRAP:
            ptyp =  TerrainTile::TileType::TT_WEAK_TRAP;
            break;
    }
    return m_nTriggerToxicNums.at(ptyp);
}
CChaosNumber StatisticsManager::getDataTotalType(eStatistType type) const
{
    CCASSERT(type>=ST_TOTAL_COPPER && type <=ST_TOTAL_TRIGGER,"use type error");
    
    switch (type) {
        case ST_TOTAL_COPPER:
            return m_nCopperTotalNum;
        case ST_TOTAL_COST_COPPER:
             return m_nCostCopperNum;
        case ST_TOTAL_STEP:
            return m_nStepNum;
        case ST_TOTAL_MONSTER_KILL:
            return m_nMonsterKillTotalNum;
        case ST_TOTAL_SEARCH_HIDE_INFO:
            return m_nSearchHideInfoNum;
        case ST_TOTAL_USE_KEY:
            return m_nUseKeyTotalNum;
        case ST_TOTAL_USE_SCROLL:
            return m_nUseScrollTotalNum;
        case ST_TOTAL_USE_POTION:
            return m_nUsePotionTotalNum;
        case ST_TOTAL_CRITICAL:
            return m_nCriticalTotalNum;
        case ST_TOTAL_DODGE:
            return m_nDodgeTotalNum;
        case ST_TOTAL_BLOCK:
            return m_nBlockTotalNum;
        case ST_TOTAL_TRIGGER:
            return m_TriggerToxicTotalNum;
    }
    return CChaosNumber(0);
}
