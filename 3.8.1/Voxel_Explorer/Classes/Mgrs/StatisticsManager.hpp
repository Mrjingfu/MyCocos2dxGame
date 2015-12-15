//
//  StatisticsManager.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/12.
//
//

#ifndef StatisticsManager_hpp
#define StatisticsManager_hpp
#include "BaseMonster.hpp"
#include "PickableItem.hpp"
#include "TerrainTile.hpp"
#include "UseableItem.hpp"
#include "AchieveConst.h"
class StatisticsManager {
    StatisticsManager();
    
public:
    //死亡类型
    enum eRoleDeadType
    {
        RET_MONSTER_ATTACK = 0,         //怪物攻击死亡
        RET_TRIGGER_GRIPPING_TRAP,      //夹子陷阱死亡
        RET_BUFFER_FIRE,                //火 死亡
        RET_BUFFER_POISONING,           //中毒死亡
        RET_MAX
    };
    virtual ~StatisticsManager();
    static StatisticsManager* getInstance();
    
    void addMonsterKillNum(BaseMonster::MonsterType type);
    void addUseItemNum(PickableItem::PickableItemType type);
    void addTriggerTrapNum(TerrainTile::TileType type);
    void addUserableOpenNum(UseableItem::UseableItemType type);
    void addRoleDeadNum(eRoleDeadType type);
    
    void addCopperTotalNum(int num);
    void addCostCopperNum(int num);
    void addStepNum();
    void addCriticalTotalNum();
    void addDodgeTotalNum();
    void addBlockTotalNum();
    void addSearchHideInfoNum();
   
    CChaosNumber getDataStatistType(eStatistType type) const;
    
    void load();
    void save();
private:
    CChaosNumber getDataMonsterType(eStatistType type) const;
    CChaosNumber getDataUseType(eStatistType type) const;
    CChaosNumber getDataTriggerType(eStatistType type) const;
    CChaosNumber getDataTotalType(eStatistType type) const;
    CChaosNumber getDataDeadType(eStatistType type) const;
private:
    CChaosNumber m_mMonsterKills[BaseMonster::MT_MAX];//杀死不同类型敌人数
    std::map<PickableItem::PickableItemType,CChaosNumber> m_mUseItemNums; //使用不同道具数
    std::map<TerrainTile::TileType,CChaosNumber> m_mTriggerToxicNums;  //触发不同机关数
    CChaosNumber m_mUserableOpenNums[UseableItem::UseableItemType::UIT_UNKNOWN]; //
    CChaosNumber m_mDeadTypeNums[eRoleDeadType::RET_MAX];
    CChaosNumber m_nCopperTotalNum;         //铜币收集总数
    CChaosNumber m_nCostCopperNum;          //花费铜币个数
    CChaosNumber m_nfoodEaten;              //到达最远深度
    CChaosNumber m_nStepNum;                //步数
    CChaosNumber m_nMonsterKillTotalNum;    //杀死敌人总数
    CChaosNumber m_nSearchHideInfoNum;      //搜索隐藏信息次数
    CChaosNumber m_nUsePotionTotalNum;      //使用药品数
    CChaosNumber m_nUseScrollTotalNum;      //使用卷轴数
    CChaosNumber m_nUseKeyTotalNum;         //使用钥匙数
    CChaosNumber m_nUserItemTotalNum;       //使用道具数
    CChaosNumber m_nCriticalTotalNum;       //暴击数
    CChaosNumber m_nDodgeTotalNum;          //闪避数
    CChaosNumber m_nBlockTotalNum;          //格挡数
    CChaosNumber m_nTriggerToxicTotalNum;    //触发机关总数
    CChaosNumber m_nRoleDeadTotalNum;       //人物死亡次数
    CChaosNumber m_nChestCopperTotalNum;    //打开铜宝箱数
    CChaosNumber m_nChestSilverTotalNum;    //打开银宝箱数
    CChaosNumber m_nChestGoldTotalNum;      //打开金宝箱数
    CChaosNumber m_nJarTotalNum;            //打破罐子数
};

#endif /* StatisticsManager_hpp */
