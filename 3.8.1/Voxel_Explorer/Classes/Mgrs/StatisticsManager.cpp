//
//  StatisticsManager.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/12.
//
//

#include "StatisticsManager.hpp"
#include "AchievementManager.h"
#include "PlayerProperty.hpp"
#include "VoxelExplorer.h"
StatisticsManager::StatisticsManager()
{
    m_nCopperTotalNum           =0;         //铜币收集总数
    m_nStepNum                  =0;         //步数
    m_nMonsterKillTotalNum      =0;         //杀死敌人总数
    m_nUseKeyTotalNum           =0;         //使用钥匙数
    m_nCriticalTotalNum         =0;         //暴击数
    m_nDodgeTotalNum            =0;         //闪避数
    m_nBlockTotalNum            =0;         //格挡数
    m_nRoleDeadTotalNum         =0;         //人物死亡次数
    m_nChestCopperTotalNum      =0;         //打开铜宝箱数
    m_nChestSilverTotalNum      =0;         //打开银宝箱数
    m_nChestGoldTotalNum        =0;         //打开金宝箱数
    m_nJarTotalNum              =0;         //打破罐子数
    //
    m_nMonsterEliteKillNum      =0;         //杀死精英怪
    m_nIdentifyNum              =0;         //鉴定次数
    m_nIdentifyAttrNum          =0;         //鉴定属性两条以上
    m_nIdentifyLegend           =0;         //鉴定传说品质
    //
    m_nBagFullNum               =0;         //背包装满
    m_nDiscardItemNum           =0;         //道具丢弃
    m_nDiscardEquipNum          =0;         //武器丢弃
    m_nPickItemNum              =0;         //道具拾取
    m_nPickMagicItemNum         =0;         //拾取魔法物品
    m_nNineStepTenNum           =0;         //9秒移动10步
    m_nThirtyNotMoveNum         =0;         //30秒不动
    m_nExploreAllAreaNum        =0;         //当前区域全部探索完成
    m_nFoundHideDoorTrapNum     =0;         //发现隐藏门和陷阱
    m_nSearchNum                =0;         //搜索
    m_nfoodEaten                =0;         //到达最远深度
    m_nBoxNum                   =0;         //开启宝箱
    m_nMeetThiefNum             =0;         //遇见盗贼
    m_nMeetHagNum               =0;         //魔女
    m_nMeetSageNum              =0;         //遇见智者对话
    m_nNurseTreatNum            =0;         //护士治疗
    m_nBuyEquipNum              =0;         //购买装备
    m_nBuyPotionScrollNum       =0;         //购买药水
    m_nBuyMagicOramNum          =0;         //购买卷轴
    //
    //
    m_nStealthNum               =0;         //隐身
    m_nNotFailDeadNum           =0;         //没有摔死
    m_nWeakRecoverNum           =0;         //虚弱恢复
    m_nPoisonRecoverNum         =0;         //中毒恢复
    m_nSpeedUpNum               =0;         //加速
    m_nStrongNum                =0;         //强壮
    

    
    //初始化怪物死亡数据
    for (int i = BaseMonster::MT_UNKNOWN; i<BaseMonster::MT_MAX; i++) {
        
        m_mMonsterKills[i]=0;
    }
    //初始化Boss死亡数据
    for (int i = BaseBoss::BT_UNKNOWN; i<BaseBoss::BT_MAX; i++) {
        m_mBossKills[i]=0;
    }
   
    //初始化可以打破的道具
    for (int i= UseableItem::UIT_CHEST_NO_LOCK_COPPER; i<UseableItem::UIT_UNKNOWN; i++) {
        m_mUserableOpenNums[i] = 0;;
    }
     //初始化死亡类型
    for (int i= eRoleDeadType::RET_MONSTER_ATTACK; i<eRoleDeadType::RET_MAX; i++) {
        m_mDeadTypeNums[i]=0;
    }
    //初始化隐藏信息数据
    for (int i= eHideInfoType::HIT_MSG; i<eHideInfoType::HIT_MAX; i++) {
        m_mHideInfoTypeNums[i]=0;
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
    AchievementManager::getInstance()->checkAllAchievement();
}

void StatisticsManager::addBossKillNum(BaseBoss::BossType type)
{
    ++m_mBossKills[type];
    AchievementManager::getInstance()->checkAllAchievement();
}
void StatisticsManager::addHideInfoNum(eHideInfoType type)
{
    ++m_mHideInfoTypeNums[type];
    if (type>=HIT_DOOR && type<=HIT_TRAP) {
        ++m_nFoundHideDoorTrapNum;
    }
}
void StatisticsManager::addUserableOpenNum(UseableItem::UseableItemType type)
{
    CCASSERT(type>=UseableItem::UseableItemType::UIT_CHEST_NO_LOCK_COPPER && type<UseableItem::UseableItemType::UIT_UNKNOWN, "Tile type error");
    
    if (type==UseableItem::UseableItemType::UIT_CHEST_NO_LOCK_COPPER || type==UseableItem::UseableItemType::UIT_CHEST_COPPER) {
        m_nChestCopperTotalNum = 1;
    }
    if (type==UseableItem::UseableItemType::UIT_CHEST_NO_LOCK_SILVER || type==UseableItem::UseableItemType::UIT_CHEST_COPPER) {
        m_nChestSilverTotalNum = 1;
    }
    if (type==UseableItem::UseableItemType::UIT_CHEST_NO_LOCK_GOLD || type==UseableItem::UseableItemType::UIT_CHEST_GOLD) {
        m_nChestGoldTotalNum = 1;
    }
    
    if (type >= UseableItem::UseableItemType::UIT_CHEST_NO_LOCK_COPPER && type <=UseableItem::UseableItemType::UIT_CHEST_GOLD) {
        ++m_nBoxNum;
    }
    
    if (type>=UseableItem::UseableItemType::UIT_JAR_1 && type<=UseableItem::UseableItemType::UIT_JAR_3) {
        ++m_nJarTotalNum;
    }
    AchievementManager::getInstance()->checkAllAchievement();
}


void StatisticsManager::addRoleDeadNum(eRoleDeadType type)
{
    ++m_mDeadTypeNums[type] ;
    ++m_nRoleDeadTotalNum;
    AchievementManager::getInstance()->checkAllAchievement();
}
void StatisticsManager::addCopperTotalNum(int num)
{
    m_nCopperTotalNum+=num;
    AchievementManager::getInstance()->handleAchievement(eAchievementDetailType::ADT_HAVE_GOLD_1);
}

void StatisticsManager::addStepNum()
{
    ++m_nStepNum;
    AchievementManager::getInstance()->checkAllAchievement();
}
void StatisticsManager::addUseKeyNum()
{
    ++m_nUseKeyTotalNum;
}
void StatisticsManager::addCriticalTotalNum()
{
    ++m_nCriticalTotalNum;
    AchievementManager::getInstance()->checkAllAchievement();
}
void StatisticsManager::addDodgeTotalNum()
{
    ++m_nDodgeTotalNum;
}
void StatisticsManager::addBlockTotalNum()
{
    ++m_nBlockTotalNum;
    AchievementManager::getInstance()->checkAllAchievement();
}
void StatisticsManager::addMonsterEliteNum()
{
    ++m_nMonsterEliteKillNum;
}
void StatisticsManager::addIdentifyNum()
{
    ++m_nIdentifyNum;
}
void StatisticsManager::addIdentifyAttrNum()
{
    ++m_nIdentifyAttrNum;
}
void StatisticsManager::addIdentifyLegendNum()
{
    ++m_nIdentifyLegend;
}

void StatisticsManager::addBagFullNum()
{
    ++m_nBagFullNum;
}

void StatisticsManager::addDiscardItemNum()
{
    ++m_nDiscardItemNum;
}

void StatisticsManager::addDiscardEquipNum()
{
    ++m_nDiscardEquipNum;
}

void StatisticsManager::addPickItemNum()
{
    ++m_nPickItemNum;
}

void StatisticsManager::addPickMagicItemNum()
{
    ++m_nPickMagicItemNum;
}

void StatisticsManager::addNineStepTenNum()
{
    ++m_nNineStepTenNum;
}

void StatisticsManager::addThirtyNotMoveNum()
{
    ++m_nThirtyNotMoveNum;
}

void StatisticsManager::addExploreAllAreaNum()
{
    //检测区域
    m_nExploreAllAreaNum = 1;
}
void StatisticsManager::decreaseExploreAllAreaNum()
{
    m_nExploreAllAreaNum = 0;
}
void StatisticsManager::addSearchNum()
{
    ++m_nSearchNum;
}

void StatisticsManager::addfoodEaten()
{
    //深度
}

void StatisticsManager::addMeetThiefNum()
{
    m_nMeetThiefNum  = 1;
}

void StatisticsManager::addMeetHagNum()
{
    m_nMeetSageNum  =1;
}

void StatisticsManager::addMeetSageNum()
{
    ++m_nMeetSageNum;
}

void StatisticsManager::addNurseTreatNum()
{
    ++m_nNurseTreatNum;
}

void StatisticsManager::addBuyEquipNum()
{
    m_nBuyEquipNum = 1;
}

void StatisticsManager::addBuyPotionScrollNum()
{
    m_nBuyPotionScrollNum  = 1;
}
void StatisticsManager::addBuyMagicOramNum()
{
    m_nBuyMagicOramNum = 1;
}

void StatisticsManager::addStealthNum()
{
    m_nStealthNum =1;
}

void StatisticsManager::addNotFailDeadNum()
{
    m_nNotFailDeadNum =1;
}

void StatisticsManager::addWeakRecoverNum()
{
    m_nWeakRecoverNum =1;
}

void StatisticsManager::addPoisonRecoverNum()
{
    m_nPoisonRecoverNum =1;
}

void StatisticsManager::addSpeedUpNum()
{
    m_nSpeedUpNum =1;
}

void StatisticsManager::addStrongNum()
{
    m_nStrongNum =1;
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
       return getDataMonsterType(type);
    }

    if (type>=ST_DEAD_MONSTER_ATTACK && type <=ST_DEAD_FALL) {
        return getDataDeadType(type);
    }
    
    if (type>=ST_FOUND_HIDE_MSG && type<=ST_FOUND_HIDE_TRAP) {
        return getDataHideInfoType(type);
    }
    
    if (type>=ST_BOSS_SLIMEKING && type<=ST_BOSS_SKELETONKING) {
        return getDataBossType(type);
    }
    
    if (type>=ST_TOTAL_COPPER && type <=ST_TOTAL_STRONG) {
        return getDataTotalType(type).GetLongValue();
    }
    return CChaosNumber(0);
}
CChaosNumber StatisticsManager::getDataMonsterType(eStatistType type) const
{
    CCASSERT(type>=ST_MONSTER_RAT && type <=ST_MONSTER_GHOUL, "monster type error");
    return m_mMonsterKills[type];
}

CChaosNumber StatisticsManager::getDataTotalType(eStatistType type) const
{
    CCASSERT(type>=ST_TOTAL_COPPER && type <ST_MAX,"DataTotal type error");
    
    switch (type) {
        case ST_TOTAL_COPPER:
            return m_nCopperTotalNum;
            break;
        case ST_TOTAL_STEP:
            return m_nStepNum;
            break;
        case ST_TOTAL_MONSTER_KILL:
            return m_nMonsterKillTotalNum;
            break;
        case ST_TOTAL_USE_KEY:
            return m_nUseKeyTotalNum;
            break;
        case ST_TOTAL_CRITICAL:
            return m_nCriticalTotalNum;
            break;
        case ST_TOTAL_DODGE:
            return m_nDodgeTotalNum;
            break;
        case ST_TOTAL_BLOCK:
            return m_nBlockTotalNum;
            break;
        case ST_TOTAL_ROLE_DEAD:
            return m_nRoleDeadTotalNum;
            break;
        case ST_TOTAL_CHEST_COPPER:
            return m_nChestCopperTotalNum;
            break;
        case ST_TOTAL_CHEST_SILVER:
            return m_nChestSilverTotalNum;
            break;
        case ST_TOTAL_CHEST_GOLD:
            return m_nChestGoldTotalNum;
            break;
        case ST_TOTAL_JAR:
            return m_nJarTotalNum;
            break;
        case ST_TOTAL_ROLE_LEVEL:
            break;
        case ST_TOTAL_ELITE_MONSTER:
            return m_nMonsterEliteKillNum;
            break;                                                      ///NEW
        case ST_TOTAL_IDENTIFY:
            return m_nIdentifyNum;
            break;                                                             ///NEW
        case ST_TOTAL_IDENTIFY_BEOW_TOW:         ///鉴定属性超过两条次数   ///NEW
            return m_nIdentifyAttrNum;
            break;
        case ST_TOTAL_IDENTIFY_QUALITY:          //鉴定品质               ///NEW
            return m_nIdentifyLegend;
            break;
        case ST_TOTAL_BAG_EXTEND:               //背包扩容次数           ///NEW
            break;
        case ST_TOTAL_BAG_FULL:                  //背包装满               ///NEW
            return m_nBagFullNum;
            break;
        case ST_TOTAL_DISCARD_ITEM:              //道具丢弃总计            ///NEW
            return m_nDiscardItemNum;
            break;
        case ST_TOTAL_DISCARD_EQUIP:             //丢弃装备                ///NEW
            return m_nDiscardEquipNum;
            break;
        case ST_TOTAL_PICK_ITEM:                 //拾取道具                ///new
            return m_nPickItemNum;
            break;
        case ST_TOTAL_PICK_NOT_MARIC:            //拾取费魔法物品           ///new
            return m_nPickMagicItemNum;
            break;
        case ST_TOTAL_NINE_STEP:                 //9秒移动超过10步          ///new
            return m_nNineStepTenNum;
            break;
        case ST_TOTAL_THIRTY_NOT_MOVE:           //30秒不动                 ///new
            return m_nThirtyNotMoveNum;
            break;
        case ST_TOTAL_EXPLORE_ALL_AREA:          //探索区域                  ///NEW
            return m_nExploreAllAreaNum;
            break;
        case ST_TOTAL_FOUND_DOOR_TRAP:           //隐藏门_陷阱               ///NEW
            return m_nFoundHideDoorTrapNum;
            break;
        case ST_TOTAL_SEARCH:                    //检索                    ///NEW
            return m_nSearchNum;
            break;
        case ST_TOTAL_STEP_DUNGEON:              //到达过所有地下城         ///NEW
            return m_nfoodEaten;
            break;
        case ST_TOTAL_CHEST_BOX:                 //开启宝箱
            return m_nBoxNum;
            break;
        case ST_TOTAL_MEET_THIEF:                //遇见盗贼
            return m_nMeetThiefNum;
            break;
        case ST_TOTAL_MEET_HAG:                  //遇见魔女
            return m_nMeetHagNum;
            break;
        case ST_TOTAL_MEET_SAGE:                 //遇见智者
            return m_nMeetSageNum;
            break;
        case ST_TOTAL_NURSE_TREAT:               //护士治疗
            return m_nNurseTreatNum;
            break;
        case ST_TOTAL_BUY_EQUIP:                 //购买装备
            return m_nBuyEquipNum;
            break;
        case ST_TOTAL_BUY_POTION_SCROLL:         //购买药水卷轴
            return m_nBuyPotionScrollNum;
            break;
        case ST_TOTAL_BUY_MARICORAM:                //购买
            return m_nBuyMagicOramNum;
            break;
        case ST_TOTAL_ROLE_HP:                   //生命值
            break;
        case ST_TOTAL_ROLE_MAX_ATTACK:           //攻击力
            break;
        case ST_TOTAL_STEALTH:                   //隐身
            return m_nStealthNum;
            break;
        case ST_TOTAL_NOT_FAIL_DEAD:             //没有摔死
            return m_nNotFailDeadNum;
            break;
        case ST_TOTAL_WEAK_RECOVER:              //虚弱恢复
            return m_nWeakRecoverNum;
            break;
        case ST_TOTAL_POISON_RECOVER:            //中毒恢复
            return m_nPoisonRecoverNum;
            break;
        case ST_TOTAL_SPEED_UP:                  //加速
            return m_nSpeedUpNum;
            break;
        case ST_TOTAL_STRONG:                    //进入强壮
            return m_nStrongNum;
            break;
        default:
            break;
    }
    return CChaosNumber(0);
}

CChaosNumber StatisticsManager::getDataDeadType(eStatistType type) const
{
    CCASSERT(type>=ST_DEAD_MONSTER_ATTACK && type <=ST_DEAD_FALL,"DataDead type error");
    eRoleDeadType deadType = eRoleDeadType::RET_MAX;
    switch (type) {
        case ST_DEAD_MONSTER_ATTACK:
            deadType = eRoleDeadType::RET_MONSTER_ATTACK;
            break;
        case ST_DEAD_TRIGGER_GRIPPING_TRAP:
            deadType = eRoleDeadType::RET_TRIGGER_GRIPPING_TRAP;
            break;
        case ST_DEAD_BUFFER_FIRE:
            deadType = eRoleDeadType::RET_BUFFER_FIRE;
            break;
        case ST_DEAD_BUFFER_POISONING:
            deadType = eRoleDeadType::RET_BUFFER_POISONING;
            break;
        case ST_DEAD_FALL:
            deadType= eRoleDeadType::RET_FAIL;
            break;
        default:
            break;
    }
    return m_mDeadTypeNums[deadType];
}
CChaosNumber StatisticsManager::getDataBossType(eStatistType type) const
{
    CCASSERT(type>=ST_BOSS_SLIMEKING && type <=ST_BOSS_SKELETONKING,"DataBoss type error");
    BaseBoss::BossType bossType = BaseBoss::BT_UNKNOWN;
    switch (type) {
        case ST_BOSS_SLIMEKING:
            bossType = BaseBoss::BossType::BT_SLIMEKING;
            break;
        case ST_BOSS_WARDEN:
            bossType = BaseBoss::BossType::BT_WARDEN;
            break;
        case ST_BOSS_ARCHBISHOP:
            bossType = BaseBoss::BossType::BT_ARCHBISHOP;
            break;
        case ST_BOSS_KOBOLDLEADER:
            bossType = BaseBoss::BossType::BT_KOBOLDLEADER;
            break;
        case ST_BOSS_GIANT:
            bossType= BaseBoss::BossType::BT_GIANT;
            break;
        case ST_BOSS_SKELETONKING:
            bossType= BaseBoss::BossType::BT_SKELETONKING;
            break;
        default:
            break;
    }
    return m_mDeadTypeNums[bossType];
}
CChaosNumber StatisticsManager::getDataHideInfoType(eStatistType type) const
{
    CCASSERT(type>=ST_FOUND_HIDE_MSG && type <=ST_FOUND_HIDE_TRAP,"DataHideInfo type error");
    eHideInfoType infoType = eHideInfoType::HIT_MAX;
    switch (type) {
        case ST_FOUND_HIDE_MSG:
            infoType = eHideInfoType::HIT_MSG;
            break;
        case ST_FOUND_HIDE_DOOR:
             infoType = eHideInfoType::HIT_DOOR;
            break;
        case ST_FOUND_HIDE_TRAP:
             infoType = eHideInfoType::HIT_TRAP;
        default:
            break;
    }
    return m_mHideInfoTypeNums[infoType];
}
