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
#include "TerrainTile.hpp"
#include "UseableItem.hpp"
#include "BaseBoss.hpp"
#include "AchieveConst.h"
#include "RandomDungeon.hpp"
#include "ArchiveManager.h"
const int TIME_NINE = 9;
const int TIME_THIRTY = 30;
const std::string SCHEDU_NINE_KEY = "SCHEDU_NINE_KEY";
const std::string SCHEDU_THIRTY_KEY = "SCHEDU_NINE_KEY";

const std::string ARCHIVE_MONSTER_KILL_KEY ="ARCHIVE_MONSTER_KILL_KEY";
const std::string ARCHIVE_BOSS_KILL_KEY ="ARCHIVE_BOSS_KILL_KEY";
const std::string ARCHIVE_USEABLEOPEN_KEY ="ARCHIVE_USEABLEOPEN_KEY";
const std::string ARCHIVE_DEAD_TYPE_KEY ="ARCHIVE_DEAD_TYPE_KEY";
const std::string ARCHIVE_HIDE_INFO_KEY ="ARCHIVE_HIDE_INFO_KEY";
const std::string ARCHIVE_DUNGEON_KEY ="ARCHIVE_DUNGEON_KEY";
const std::string ARCHIVE_STATISTICS = "ARCHIVE_STATISTICS";

class StatisticsManager :public iArchive{
    StatisticsManager();
    
public:
    //死亡类型
    enum eRoleDeadType
    {
        RET_MONSTER_ATTACK = 0,         //怪物攻击死亡
        RET_TRIGGER_GRIPPING_TRAP,      //夹子陷阱死亡
        RET_BUFFER_FIRE,                //火 死亡
        RET_BUFFER_POISONING,           //中毒死亡
        RET_FAIL,                       //摔死
        RET_MAX
    };
    //隐藏信息
    enum eHideInfoType
    {
        HIT_MSG = 0,        //隐藏信息
        HIT_DOOR,       //隐藏门
        HIT_TRAP,       //隐藏陷阱
        HIT_MAX
    };
    virtual ~StatisticsManager();
    static StatisticsManager* getInstance();
    void init();
    void addMonsterKillNum(BaseMonster::MonsterType type);
    void addBossKillNum(BaseBoss::BossType type);
    void addHideInfoNum(eHideInfoType type);
    void addUserableOpenNum(UseableItem::UseableItemType type);
    void addRoleDeadNum(eRoleDeadType type);
    void addArriveDungeon(DUNGEON_TYPE type);
    
    void addCopperTotalNum(int num);
    void addStepNum();
    
    void addUseKeyNum();
    void addCriticalTotalNum();
    void addDodgeTotalNum();
    void addBlockTotalNum();
    void addRoleLevelNum(int Level);
    void addMonsterEliteNum();
    void addIdentifyNum();
    void addIdentifyAttrNum();
    void addIdentifyLegendNum();

    void addBagFullNum();
    void addDiscardItemNum();
    void addDiscardEquipNum();
    void addPickItemNum();
    void addPickMagicItemNum();
    void addNineStepTenNum();
    void addThirtyNotMoveNum();     
    
    void addExploreAllAreaNum();
    void decreaseExploreAllAreaNum();
    
    void addSearchNum();
    void addMeetThiefNum();
    void addMeetHagNum();
    void addMeetSageNum();
    void addNurseTreatNum();        //wait
    void addBuyEquipNum();
    void addBuyPotionScrollNum();
    void addBuyMagicOramNum();
    void addStealthNum();
    void addNotFailDeadNum();
    void addWeakRecoverNum();
    void addPoisonRecoverNum();
    void addSpeedUpNum();
    void addStrongNum();
   
    void addRoleAttr();
    void addBagExtend();
    
    void pauseSchedu();
    void resumeSchedu();
    
    CChaosNumber getDataStatistType(eStatistType type) const;
    
    virtual bool load(const cocos2d::ValueMap& rootNode) ;
    virtual bool save(cocos2d::ValueMap& rootNode);
private:
    CChaosNumber getDataMonsterType(eStatistType type) const;
    CChaosNumber getDataTotalType(eStatistType type) const;
    CChaosNumber getDataDeadType(eStatistType type) const;
    CChaosNumber getDataBossType(eStatistType type) const;
    CChaosNumber getDataHideInfoType(eStatistType type) const;
    CChaosNumber getDataArriveDungeon(eStatistType type) const;
private:
    CChaosNumber m_mMonsterKills[BaseMonster::MT_MAX];//杀死不同类型敌人数
    CChaosNumber m_mBossKills[BaseBoss::BossType::BT_MAX];  //杀死Boss
    CChaosNumber m_mUserableOpenNums[UseableItem::UseableItemType::UIT_UNKNOWN]; //
    CChaosNumber m_mDeadTypeNums[eRoleDeadType::RET_MAX];
    CChaosNumber m_mHideInfoTypeNums[eHideInfoType::HIT_MAX];
    CChaosNumber m_mArriveDungeon[DUNGEON_TYPE::DT_MAX];
    
    CChaosNumber m_nCopperTotalNum;         //铜币收集总数
    CChaosNumber m_nStepNum;                //步数
    CChaosNumber m_nMonsterKillTotalNum;    //杀死敌人总数
    CChaosNumber m_nUseKeyTotalNum;         //使用钥匙数
    CChaosNumber m_nCriticalTotalNum;       //暴击数
    CChaosNumber m_nDodgeTotalNum;          //闪避数
    CChaosNumber m_nBlockTotalNum;          //格挡数
    CChaosNumber m_nRoleDeadTotalNum;       //人物死亡次数
    CChaosNumber m_nChestCopperTotalNum;    //打开铜宝箱数
    CChaosNumber m_nChestSilverTotalNum;    //打开银宝箱数
    CChaosNumber m_nChestGoldTotalNum;      //打开金宝箱数
    CChaosNumber m_nJarTotalNum;            //打破罐子数
    CChaosNumber m_nRoleLevelNum;           //人物等级
    CChaosNumber m_nMonsterEliteKillNum;    //杀死精英怪
    CChaosNumber m_nIdentifyNum;            //鉴定次数
    CChaosNumber m_nIdentifyAttrNum;        //鉴定属性两条以上
    CChaosNumber m_nIdentifyLegend;         //鉴定传说品质
    //
    CChaosNumber m_nBagFullNum;             //背包装满
    CChaosNumber m_nDiscardItemNum;         //道具丢弃
    CChaosNumber m_nDiscardEquipNum;        //武器丢弃
    CChaosNumber m_nPickItemNum;            //道具拾取
    CChaosNumber m_nPickMagicItemNum;       //拾取魔法物品
    CChaosNumber m_nNineStepTenNum;         //9秒移动10步
    CChaosNumber m_nThirtyNotMoveNum;       //30秒不动
    CChaosNumber m_nExploreAllAreaNum;      //当前区域全部探索完成
    CChaosNumber m_nFoundHideDoorTrapNum;   //发现隐藏门和陷阱
    CChaosNumber m_nSearchNum;              //搜索
 
    CChaosNumber m_nBoxNum;                 //开启宝箱
    CChaosNumber m_nMeetThiefNum;           //遇见盗贼
    CChaosNumber m_nMeetHagNum;             //魔女
    CChaosNumber m_nMeetSageNum;            //遇见智者对话
    CChaosNumber m_nNurseTreatNum;          //护士治疗
    CChaosNumber m_nBuyEquipNum;            //购买装备
    CChaosNumber m_nBuyPotionScrollNum;     //购买药水卷轴
    CChaosNumber m_nBuyMagicOramNum;        //购买魔法饰品
    //
    //
    CChaosNumber m_nStealthNum;             //隐身
    CChaosNumber m_nNotFailDeadNum;         //没有摔死
    CChaosNumber m_nWeakRecoverNum;         //虚弱恢复
    CChaosNumber m_nPoisonRecoverNum;       //中毒恢复
    CChaosNumber m_nSpeedUpNum;             //加速
    CChaosNumber m_nStrongNum;              //强壮
    

    int m_nNineTime;
    int m_nThirtyTime;
    int m_nNineStepRecord;
    int m_nThirtyStepRecord;

    
};

#endif /* StatisticsManager_hpp */
