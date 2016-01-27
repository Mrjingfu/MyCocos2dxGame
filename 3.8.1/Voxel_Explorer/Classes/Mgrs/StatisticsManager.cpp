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
#include "RandomDungeon.hpp"
StatisticsManager::StatisticsManager()
{
    init();
}
StatisticsManager::~StatisticsManager()
{
    
}
StatisticsManager* StatisticsManager::getInstance()
{
    static StatisticsManager instance;
    return &instance;
}
void StatisticsManager::init()
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
    
    
    m_nNineTime                 =0;
    m_nThirtyTime               =0;
    m_nNineStepRecord           =0;
    m_nThirtyStepRecord         =0;
    
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
    //初始化地城信息数据
    for (int i = DUNGEON_TYPE::DT_UNKNOWN; i<DT_MAX; i++) {
        m_mArriveDungeon[i] = 0;
    }
}

void StatisticsManager::addMonsterKillNum(BaseMonster::MonsterType type)
{
    ++m_mMonsterKills[type] ;
    ++m_nMonsterKillTotalNum;
    AchievementManager::getInstance()->checkKillMonsterAchievement();
}

void StatisticsManager::addBossKillNum(BaseBoss::BossType type)
{
    ++m_mBossKills[type];
    AchievementManager::getInstance()->checkKillBossAchievement();
}
void StatisticsManager::addHideInfoNum(eHideInfoType type)
{
    ++m_mHideInfoTypeNums[type];
    if (type>=HIT_DOOR && type<=HIT_TRAP) {
        ++m_nFoundHideDoorTrapNum;
    }
    AchievementManager::getInstance()->checkFoundHideAchievement();
}
void StatisticsManager::addUserableOpenNum(UseableItem::UseableItemType type)
{
    CCASSERT(type>=UseableItem::UseableItemType::UIT_CHEST_NO_LOCK_COPPER && type<UseableItem::UseableItemType::UIT_UNKNOWN, "Tile type error");
    
    if (type==UseableItem::UseableItemType::UIT_CHEST_NO_LOCK_COPPER || type==UseableItem::UseableItemType::UIT_CHEST_COPPER) {
        ++m_nChestCopperTotalNum ;
    }
    if (type==UseableItem::UseableItemType::UIT_CHEST_NO_LOCK_SILVER || type==UseableItem::UseableItemType::UIT_CHEST_SILVER) {
        ++m_nChestSilverTotalNum ;
    }
    if (type==UseableItem::UseableItemType::UIT_CHEST_NO_LOCK_GOLD || type==UseableItem::UseableItemType::UIT_CHEST_GOLD) {
        ++m_nChestGoldTotalNum ;
    }
    
    if (type >= UseableItem::UseableItemType::UIT_CHEST_NO_LOCK_COPPER && type <=UseableItem::UseableItemType::UIT_CHEST_GOLD) {
        ++m_nBoxNum;
    }
    
    if (type>=UseableItem::UseableItemType::UIT_JAR_1 && type<=UseableItem::UseableItemType::UIT_JAR_3) {
        ++m_nJarTotalNum;
    }
    AchievementManager::getInstance()->checkBoxAchievement();
}


void StatisticsManager::addRoleDeadNum(eRoleDeadType type)
{
    ++m_mDeadTypeNums[type] ;
    ++m_nRoleDeadTotalNum;
    AchievementManager::getInstance()->checkRoleDeadAchievement();
}
void StatisticsManager::addArriveDungeon(DUNGEON_TYPE type)
{
    ++m_mArriveDungeon[type];
}
void StatisticsManager::addCopperTotalNum(int num)
{
    m_nCopperTotalNum+=num;
    AchievementManager::getInstance()->checkHaveGoldAchievement();
}

void StatisticsManager::addStepNum()
{
    ++m_nStepNum;
    AchievementManager::getInstance()->handleAchievement(ADT_MARATHON);
    addNineStepTenNum();
    addThirtyNotMoveNum();
}
void StatisticsManager::addUseKeyNum()
{
    ++m_nUseKeyTotalNum;
    AchievementManager::getInstance()->handleAchievement(ADT_USE_KEY);
}
void StatisticsManager::addCriticalTotalNum()
{
    ++m_nCriticalTotalNum;
    AchievementManager::getInstance()->handleAchievement(ADT_ROLE_CRIT);
}
void StatisticsManager::addDodgeTotalNum()
{
    ++m_nDodgeTotalNum;
    AchievementManager::getInstance()->handleAchievement(ADT_ROLE_DODGE);
}
void StatisticsManager::addBlockTotalNum()
{
    ++m_nBlockTotalNum;
    AchievementManager::getInstance()->handleAchievement(ADT_ROLE_BLOCK);
}
void StatisticsManager::addMonsterEliteNum()
{
    ++m_nMonsterEliteKillNum;
}
void StatisticsManager::addIdentifyNum()
{
    ++m_nIdentifyNum;
    AchievementManager::getInstance()->handleAchievement(eAchievementDetailType::ADT_IDENTIFY_1);
    AchievementManager::getInstance()->handleAchievement(eAchievementDetailType::ADT_IDENTIFY_4);
}
void StatisticsManager::addIdentifyAttrNum()
{
    ++m_nIdentifyAttrNum;
    AchievementManager::getInstance()->handleAchievement(eAchievementDetailType::ADT_IDENTIFY_2);
}
void StatisticsManager::addIdentifyLegendNum()
{
    ++m_nIdentifyLegend;
    AchievementManager::getInstance()->handleAchievement(eAchievementDetailType::ADT_IDENTIFY_3);
}

void StatisticsManager::addBagFullNum()
{
    if (PlayerProperty::getInstance()->getPlayerBag().size() >= PlayerProperty::getInstance()->getBagMaxSpace().GetLongValue()) {
         m_nBagFullNum = 1;
    }
     AchievementManager::getInstance()->handleAchievement(eAchievementDetailType::ADT_BAG_FULL);
}

void StatisticsManager::addDiscardItemNum()
{
    ++m_nDiscardItemNum;
    AchievementManager::getInstance()->handleAchievement(ADT_WEALTHY_MEN);
}

void StatisticsManager::addDiscardEquipNum()
{
    ++m_nDiscardEquipNum;
    AchievementManager::getInstance()->handleAchievement(ADT_SPENDERS_MEN);
}

void StatisticsManager::addPickItemNum()
{
    ++m_nPickItemNum;
    AchievementManager::getInstance()->handleAchievement(ADT_PICK_ITEM);
}

void StatisticsManager::addPickMagicItemNum()
{
    ++m_nPickMagicItemNum;
    AchievementManager::getInstance()->handleAchievement(ADT_PICK_NOT_MARIC_ITEM);
}

void StatisticsManager::addNineStepTenNum()
{
    if (m_nNineStepTenNum ==0)
    {
        if (!cocos2d::Director::getInstance()->getScheduler()->isScheduled(SCHEDU_NINE_KEY, this)) {
            m_nNineStepRecord = m_nStepNum;
            cocos2d::Director::getInstance()->getScheduler()->schedule([this](float dt){
                CCLOG("addNineStepTenNum");
                ++m_nNineTime;
                if (m_nNineTime >=TIME_NINE )
                {
                    if (m_nStepNum - m_nNineStepRecord> 30)
                    {
                        m_nNineStepTenNum = 1;
                        cocos2d::Director::getInstance()->getScheduler()->unschedule(SCHEDU_NINE_KEY, this);
                        AchievementManager::getInstance()->handleAchievement(eAchievementDetailType::ADT_WORLD_RECORD);

                    }else
                    {
                        m_nNineStepRecord = 0;
                        m_nNineTime = 0;
                        m_nNineStepRecord = m_nStepNum;
                    }
                }
            }, this, 1.0f, false, SCHEDU_NINE_KEY);
        }

    }
}

void StatisticsManager::addThirtyNotMoveNum()
{
    if (m_nThirtyNotMoveNum ==0)
    {
        m_nThirtyStepRecord = m_nStepNum;
        m_nThirtyTime = 0;
        if (!cocos2d::Director::getInstance()->getScheduler()->isScheduled(SCHEDU_THIRTY_KEY, this)) {
            
            cocos2d::Director::getInstance()->getScheduler()->schedule([this](float dt){
                CCLOG("addThirtyNotMoveNum");
                ++m_nThirtyTime;
                if (m_nThirtyTime >=TIME_THIRTY )
                {
                    if (m_nStepNum == m_nThirtyStepRecord)
                    {
                        m_nThirtyNotMoveNum = 1;
                        cocos2d::Director::getInstance()->getScheduler()->unschedule(SCHEDU_THIRTY_KEY, this);
                        AchievementManager::getInstance()->handleAchievement(eAchievementDetailType::ADT_THIRTY_NOT_MOVE);
                    }else
                    {
                        m_nThirtyStepRecord = 0;
                        m_nThirtyTime = 0;
                        m_nThirtyStepRecord = m_nStepNum;
                    }
                    
                }
            }, this, 1.0f, false, SCHEDU_THIRTY_KEY);
        }
        
    }
}

void StatisticsManager::addExploreAllAreaNum()
{
    if(!RandomDungeon::getInstance()->getCurrentDungeonNode()->isBossDepth())
    {
        //检测区域
        m_nExploreAllAreaNum = 1;
        AchievementManager::getInstance()->handleAchievement(ADT_OBSESSION_MEN);

    }
}
void StatisticsManager::decreaseExploreAllAreaNum()
{
    m_nExploreAllAreaNum = 0;
}
void StatisticsManager::addSearchNum()
{
    ++m_nSearchNum;
    AchievementManager::getInstance()->handleAchievement(ADT_LOVE_QUESTION);
    AchievementManager::getInstance()->handleAchievement(ADT_SEARCH_KING);
}


void StatisticsManager::addMeetThiefNum()
{
    m_nMeetThiefNum  = 1;
    AchievementManager::getInstance()->handleAchievement(ADT_MEET_THIEF_FIRST);
}

void StatisticsManager::addMeetHagNum()
{
    m_nMeetSageNum  =1;
     AchievementManager::getInstance()->handleAchievement(ADT_MEET_HAG_FIRST);
}

void StatisticsManager::addMeetSageNum()
{
    ++m_nMeetSageNum;
    AchievementManager::getInstance()->handleAchievement(ADT_SAGE_STORY);
}

void StatisticsManager::addNurseTreatNum()
{
    ++m_nNurseTreatNum;
    AchievementManager::getInstance()->handleAchievement(ADT_NURSE_TREAT);
}

void StatisticsManager::addBuyEquipNum()
{
    m_nBuyEquipNum = 1;
    AchievementManager::getInstance()->handleAchievement(ADT_BUY_EQUIP);
}

void StatisticsManager::addBuyPotionScrollNum()
{
    m_nBuyPotionScrollNum  = 1;
    AchievementManager::getInstance()->handleAchievement(ADT_BUY_SCROLL_POTION);
}
void StatisticsManager::addBuyMagicOramNum()
{
    m_nBuyMagicOramNum = 1;
    AchievementManager::getInstance()->handleAchievement(ADT_BUY_MARICORIM);
}

void StatisticsManager::addStealthNum()
{
    m_nStealthNum =1;
    AchievementManager::getInstance()->handleAchievement(ADT_STEALTHY_FIRST);
}

void StatisticsManager::addNotFailDeadNum()
{
    m_nNotFailDeadNum =1;
    AchievementManager::getInstance()->handleAchievement(ADT_ROLE_LUCK_NOT_DEAD);
}

void StatisticsManager::addWeakRecoverNum()
{
    m_nWeakRecoverNum =1;
    AchievementManager::getInstance()->handleAchievement(ADT_WEAK_RECOVER);
}

void StatisticsManager::addPoisonRecoverNum()
{
    m_nPoisonRecoverNum =1;
    AchievementManager::getInstance()->handleAchievement(ADT_POISON_NOT_DEAD);
}

void StatisticsManager::addSpeedUpNum()
{
    m_nSpeedUpNum =1;
    AchievementManager::getInstance()->handleAchievement(ADT_SPEED_UP_FIRST);
}

void StatisticsManager::addStrongNum()
{
    m_nStrongNum =1;
    AchievementManager::getInstance()->handleAchievement(ADT_STRONG_FIRST);
}

void StatisticsManager::addRoleAttr()
{
    AchievementManager::getInstance()->handleAchievement(ADT_ROLE_LEVEL_1);
    AchievementManager::getInstance()->handleAchievement(ADT_ROLE_LEVEL_2);
    AchievementManager::getInstance()->handleAchievement(ADT_ROLE_HP);
    AchievementManager::getInstance()->handleAchievement(ADT_ROLE_ATTACK);
}
void StatisticsManager::addBagExtend()
{
    AchievementManager::getInstance()->handleAchievement(ADT_EXTEND_BAG);
    AchievementManager::getInstance()->handleAchievement(ADT_EXTEND_BAG_MAX);
}
void StatisticsManager::pauseSchedu()
{
    cocos2d::Director::getInstance()->getScheduler()->pauseTarget(this);
}
void StatisticsManager::resumeSchedu()
{
     cocos2d::Director::getInstance()->getScheduler()->resumeTarget(this);
}

bool StatisticsManager::load(const cocos2d::ValueMap& rootNode )
{
   
    if (rootNode.find(ARCHIVE_STATISTICS)==rootNode.end() ) {
         init();
        return true;
    }
    
    cocos2d::ValueMap statistValueMap = rootNode.at(ARCHIVE_STATISTICS).asValueMap();
    if (statistValueMap.empty()) {
        return false;
    }
    
    CCLOG("statistValueMap:%s",cocos2d::Value(statistValueMap).getDescription().c_str());
    cocos2d::ValueMap monsterKillsMap = statistValueMap.at(ARCHIVE_MONSTER_KILL_KEY).asValueMap();
    for (int i = BaseMonster::MT_UNKNOWN; i<BaseMonster::MT_MAX; i++) {
        m_mMonsterKills[i] = monsterKillsMap.at(cocos2d::Value(i).asString()).asInt();
    }
    cocos2d::ValueMap bossKillsMap = statistValueMap.at(ARCHIVE_BOSS_KILL_KEY).asValueMap();
    for (int i = BaseBoss::BT_UNKNOWN; i<BaseBoss::BT_MAX; i++) {
        m_mBossKills[i] = bossKillsMap.at(cocos2d::Value(i).asString()).asInt();
    }
    cocos2d::ValueMap userableOpenMap = statistValueMap.at(ARCHIVE_USEABLEOPEN_KEY).asValueMap();
    for (int i= UseableItem::UIT_CHEST_NO_LOCK_COPPER; i<UseableItem::UIT_UNKNOWN; i++) {
        m_mUserableOpenNums[i] = userableOpenMap.at(cocos2d::Value(i).asString()).asInt();
    }

    cocos2d::ValueMap deadTypeMap = statistValueMap.at(ARCHIVE_DEAD_TYPE_KEY).asValueMap();
    for (int i= eRoleDeadType::RET_MONSTER_ATTACK; i<eRoleDeadType::RET_MAX; i++) {
        m_mDeadTypeNums[i] = deadTypeMap.at(cocos2d::Value(i).asString()).asInt();
    }
    cocos2d::ValueMap hideInfoTypeMap = statistValueMap.at(ARCHIVE_HIDE_INFO_KEY).asValueMap();
    for (int i= eHideInfoType::HIT_MSG; i<eHideInfoType::HIT_MAX; i++) {
        m_mHideInfoTypeNums[i] = hideInfoTypeMap.at(cocos2d::Value(i).asString()).asInt();
    }
    cocos2d::ValueMap arriveDungeonMap = statistValueMap.at(ARCHIVE_DUNGEON_KEY).asValueMap();
    for (int i = DUNGEON_TYPE::DT_UNKNOWN; i<DT_MAX; i++) {
        m_mArriveDungeon[i] = arriveDungeonMap.at(cocos2d::Value(i).asString()).asInt();
    }
    
    m_nCopperTotalNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_COPPER]).asInt();
    m_nStepNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_STEP]).asInt();
    m_nMonsterKillTotalNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_MONSTER_KILL]).asInt();
    m_nUseKeyTotalNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_USE_KEY]).asInt();
    m_nCriticalTotalNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_CRITICAL]).asInt();
    m_nDodgeTotalNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_DODGE]).asInt();
    m_nBlockTotalNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_BLOCK]).asInt();
    m_nRoleDeadTotalNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_ROLE_DEAD]).asInt();
    m_nChestCopperTotalNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_CHEST_COPPER]).asInt();
    m_nChestSilverTotalNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_CHEST_SILVER]).asInt();
    m_nChestGoldTotalNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_CHEST_GOLD]).asInt();
    m_nJarTotalNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_JAR]).asInt();
    m_nRoleLevelNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_ROLE_LEVEL]).asInt();
    m_nMonsterEliteKillNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_ELITE_MONSTER]).asInt();
    m_nIdentifyNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_IDENTIFY]).asInt();
    m_nIdentifyAttrNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_IDENTIFY_BEOW_TOW]).asInt();
    m_nIdentifyLegend = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_IDENTIFY_QUALITY]).asInt();
    //
    m_nBagFullNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_BAG_FULL]).asInt();
    m_nDiscardItemNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_DISCARD_ITEM]).asInt();
    m_nDiscardEquipNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_DISCARD_EQUIP]).asInt();
    m_nPickItemNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_PICK_ITEM]).asInt();
    m_nPickMagicItemNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_PICK_NOT_MARIC]).asInt();
    m_nNineStepTenNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_NINE_STEP]).asInt();
    m_nThirtyNotMoveNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_THIRTY_NOT_MOVE]).asInt();
    m_nExploreAllAreaNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_EXPLORE_ALL_AREA]).asInt();
    m_nFoundHideDoorTrapNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_FOUND_DOOR_TRAP]).asInt();
    m_nSearchNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_SEARCH]).asInt();
    
    m_nBoxNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_CHEST_BOX]).asInt();
    m_nMeetThiefNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_MEET_THIEF]).asInt();
    m_nMeetHagNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_MEET_HAG]).asInt();
    m_nMeetSageNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_MEET_SAGE]).asInt();
    m_nNurseTreatNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_NURSE_TREAT]).asInt();
    m_nBuyEquipNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_BUY_EQUIP]).asInt();
    m_nBuyPotionScrollNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_BUY_POTION_SCROLL]).asInt();
    m_nBuyMagicOramNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_BUY_MARICORAM]).asInt();
    //
    //
    m_nStealthNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_STEALTH]).asInt();
    m_nNotFailDeadNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_NOT_FAIL_DEAD]).asInt();
    m_nWeakRecoverNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_WEAK_RECOVER]).asInt();
    m_nPoisonRecoverNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_POISON_RECOVER]).asInt();
    m_nSpeedUpNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_SPEED_UP]).asInt();
    m_nStrongNum = statistValueMap.at(STATIST_TYPE_NAME[ST_TOTAL_STRONG]).asInt();
    
    return true;
}
bool StatisticsManager::save(cocos2d::ValueMap& rootNode )
{
    
    cocos2d::ValueMap statistValueMap;
    cocos2d::ValueMap monsterKillsMap;
    cocos2d::ValueMap bossKillsMap;
    cocos2d::ValueMap userableOpenMap;
    cocos2d::ValueMap deadTypeMap;
    cocos2d::ValueMap hideInfoTypeMap;
    cocos2d::ValueMap arriveDungeonMap;
    for (int i = BaseMonster::MT_UNKNOWN; i<BaseMonster::MT_MAX; i++) {
        monsterKillsMap.insert(cocos2d::ValueMap::value_type(cocos2d::Value(i).asString(),cocos2d::Value(int(m_mMonsterKills[i]))));
    }
    statistValueMap.insert(cocos2d::ValueMap::value_type(ARCHIVE_MONSTER_KILL_KEY,cocos2d::Value(monsterKillsMap)));
    
    for (int i = BaseBoss::BT_UNKNOWN; i<BaseBoss::BT_MAX; i++) {
        bossKillsMap.insert(cocos2d::ValueMap::value_type(cocos2d::Value(i).asString(),cocos2d::Value(int(m_mBossKills[i]))));
    }
    statistValueMap.insert(cocos2d::ValueMap::value_type(ARCHIVE_BOSS_KILL_KEY,cocos2d::Value(bossKillsMap)));
    
    for (int i= UseableItem::UIT_CHEST_NO_LOCK_COPPER; i<UseableItem::UIT_UNKNOWN; i++) {
        userableOpenMap.insert(cocos2d::ValueMap::value_type(cocos2d::Value(i).asString(),cocos2d::Value(int(m_mUserableOpenNums[i]))));
    }
    statistValueMap.insert(cocos2d::ValueMap::value_type(ARCHIVE_USEABLEOPEN_KEY,cocos2d::Value(userableOpenMap)));
    
    for (int i= eRoleDeadType::RET_MONSTER_ATTACK; i<eRoleDeadType::RET_MAX; i++) {
        deadTypeMap.insert(cocos2d::ValueMap::value_type(cocos2d::Value(i).asString(),cocos2d::Value(int(m_mDeadTypeNums[i]))));
    }
    statistValueMap.insert(cocos2d::ValueMap::value_type(ARCHIVE_DEAD_TYPE_KEY,cocos2d::Value(deadTypeMap)));
    
    for (int i= eHideInfoType::HIT_MSG; i<eHideInfoType::HIT_MAX; i++) {
        hideInfoTypeMap.insert(cocos2d::ValueMap::value_type(cocos2d::Value(i).asString(),cocos2d::Value(int(m_mHideInfoTypeNums[i]))));
    }
    statistValueMap.insert(cocos2d::ValueMap::value_type(ARCHIVE_HIDE_INFO_KEY,cocos2d::Value(hideInfoTypeMap)));
    
    for (int i = DUNGEON_TYPE::DT_UNKNOWN; i<DT_MAX; i++) {
        arriveDungeonMap.insert(cocos2d::ValueMap::value_type(cocos2d::Value(i).asString(),cocos2d::Value(int(m_mArriveDungeon[i]))));
    }
    statistValueMap.insert(cocos2d::ValueMap::value_type(ARCHIVE_DUNGEON_KEY,cocos2d::Value(arriveDungeonMap)));
    
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_COPPER],cocos2d::Value(int(m_nCopperTotalNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_STEP],cocos2d::Value(int(m_nStepNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_MONSTER_KILL],cocos2d::Value(int(m_nMonsterKillTotalNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_USE_KEY],cocos2d::Value(int(m_nUseKeyTotalNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_CRITICAL],cocos2d::Value(int(m_nCriticalTotalNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_DODGE],cocos2d::Value(int(m_nDodgeTotalNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_BLOCK],cocos2d::Value(int(m_nBlockTotalNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_ROLE_DEAD],cocos2d::Value(int(m_nRoleDeadTotalNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_CHEST_COPPER],cocos2d::Value(int(m_nChestCopperTotalNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_CHEST_SILVER],cocos2d::Value(int(m_nChestSilverTotalNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_CHEST_GOLD],cocos2d::Value(int(m_nChestGoldTotalNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_JAR],cocos2d::Value(int(m_nJarTotalNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_ROLE_LEVEL],cocos2d::Value(int(m_nRoleLevelNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_ELITE_MONSTER],cocos2d::Value(int(m_nMonsterEliteKillNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_IDENTIFY],cocos2d::Value(int(m_nIdentifyNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_IDENTIFY_BEOW_TOW],cocos2d::Value(int(m_nIdentifyAttrNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_IDENTIFY_QUALITY],cocos2d::Value(int(m_nIdentifyLegend))));
    //ST_TOTAL_BAG_EXTEND
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_BAG_FULL],cocos2d::Value(int(m_nBagFullNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_DISCARD_ITEM],cocos2d::Value(int(m_nDiscardItemNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_DISCARD_EQUIP],cocos2d::Value(int(m_nDiscardEquipNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_PICK_ITEM],cocos2d::Value(int(m_nPickItemNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_PICK_NOT_MARIC],cocos2d::Value(int(m_nPickMagicItemNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_NINE_STEP],cocos2d::Value(int(m_nNineStepTenNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_THIRTY_NOT_MOVE],cocos2d::Value(int(m_nThirtyNotMoveNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_EXPLORE_ALL_AREA],cocos2d::Value(int(m_nExploreAllAreaNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_FOUND_DOOR_TRAP],cocos2d::Value(int(m_nFoundHideDoorTrapNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_SEARCH],cocos2d::Value(int(m_nSearchNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_CHEST_BOX],cocos2d::Value(int(m_nBoxNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_MEET_THIEF],cocos2d::Value(int(m_nMeetThiefNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_MEET_HAG],cocos2d::Value(int(m_nMeetHagNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_MEET_SAGE],cocos2d::Value(int(m_nMeetSageNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_NURSE_TREAT],cocos2d::Value(int(m_nNurseTreatNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_BUY_EQUIP],cocos2d::Value(int(m_nBuyEquipNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_BUY_POTION_SCROLL],cocos2d::Value(int(m_nBuyPotionScrollNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_BUY_MARICORAM],cocos2d::Value(int(m_nBuyMagicOramNum))));
    //ST_TOTAL_ROLE_HP
    //ST_TOTAL_ROLE_MAX_ATTACK
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_STEALTH],cocos2d::Value(int(m_nStealthNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_NOT_FAIL_DEAD],cocos2d::Value(int(m_nNotFailDeadNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_WEAK_RECOVER],cocos2d::Value(int(m_nWeakRecoverNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_POISON_RECOVER],cocos2d::Value(int(m_nPoisonRecoverNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_SPEED_UP],cocos2d::Value(int(m_nSpeedUpNum))));
    statistValueMap.insert(cocos2d::ValueMap::value_type(STATIST_TYPE_NAME[ST_TOTAL_STRONG],cocos2d::Value(int(m_nStrongNum))));
    rootNode.insert(cocos2d::ValueMap::value_type(ARCHIVE_STATISTICS,cocos2d::Value(statistValueMap)));
    
    return true;
}
CChaosNumber StatisticsManager::getDataStatistType(eStatistType type) const
{
    CCASSERT(type>=ST_MONSTER_RAT && type <ST_MAX, "Statist type error");
    
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
    
    if (type>=ST_DT_SEWER && type<=ST_DT_LICH_TOMB) {
        return getDataArriveDungeon(type);
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
            return PlayerProperty::getInstance()->getLevel();
            break;
        case ST_TOTAL_ELITE_MONSTER:
            return m_nMonsterEliteKillNum;
            break;
        case ST_TOTAL_IDENTIFY:
            return m_nIdentifyNum;
            break;
        case ST_TOTAL_IDENTIFY_BEOW_TOW:         ///鉴定属性超过两条次数
            return m_nIdentifyAttrNum;
            break;
        case ST_TOTAL_IDENTIFY_QUALITY:          //鉴定品质
            return m_nIdentifyLegend;
            break;
        case ST_TOTAL_BAG_EXTEND:               //背包扩容次数
            return PlayerProperty::getInstance()->getBagExtendTimes();
            break;
        case ST_TOTAL_BAG_FULL:                  //背包装满
            return m_nBagFullNum;
            break;
        case ST_TOTAL_DISCARD_ITEM:              //道具丢弃总计
            return m_nDiscardItemNum;
            break;
        case ST_TOTAL_DISCARD_EQUIP:             //丢弃装备
            return m_nDiscardEquipNum;
            break;
        case ST_TOTAL_PICK_ITEM:                 //拾取道具
            return m_nPickItemNum;
            break;
        case ST_TOTAL_PICK_NOT_MARIC:            //拾取费魔法物品
            return m_nPickMagicItemNum;
            break;
        case ST_TOTAL_NINE_STEP:                 //9秒移动超过10步
            return m_nNineStepTenNum;
            break;
        case ST_TOTAL_THIRTY_NOT_MOVE:           //30秒不动
            return m_nThirtyNotMoveNum;
            break;
        case ST_TOTAL_EXPLORE_ALL_AREA:          //探索区域
            return m_nExploreAllAreaNum;
            break;
        case ST_TOTAL_FOUND_DOOR_TRAP:           //隐藏门_陷阱
            return m_nFoundHideDoorTrapNum;
            break;
        case ST_TOTAL_SEARCH:                    //检索
            return m_nSearchNum;
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
            return PlayerProperty::getInstance()->getMaxHP();
            break;
        case ST_TOTAL_ROLE_MAX_ATTACK:           //攻击力
            return PlayerProperty::getInstance()->getMaxAttack();
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
    return m_mBossKills[bossType];
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
CChaosNumber StatisticsManager::getDataArriveDungeon(eStatistType type) const
{
    CCASSERT(type>=ST_DT_SEWER && type <=ST_DT_LICH_TOMB,"DataHideInfo type error");
    DUNGEON_TYPE dungeonType = DT_UNKNOWN;
    switch (type) {
        case ST_DT_SEWER:              ////下水道
            dungeonType =DT_SEWER;
            break;
        case ST_DT_PRISON:             ////监狱
            dungeonType =DT_PRISON;
            break;
        case ST_DT_FANE:               ////神殿
            dungeonType =DT_FANE;
            break;
        case ST_DT_MINES:              ////矿坑
            dungeonType =DT_MINES;
            break;
        case ST_DT_CAVE:               ////洞穴
            dungeonType =DT_CAVE;
            break;
        case ST_DT_TOMB:               ////古墓
            dungeonType =DT_TOMB;
            break;
        case ST_DT_DWARF_CASTLE:       ////矮人城堡
            dungeonType =DT_DWARF_CASTLE;
            break;
        case ST_DT_MAGA_TOWER:         ////法师塔
            dungeonType =DT_MAGA_TOWER;
            break;
        case ST_DT_ORC_FORTRESS:       ////兽人堡垒
            dungeonType =DT_ORC_FORTRESS;
            break;
        case ST_DT_ELF_FOREST:         ////妖精森林
            dungeonType =DT_ELF_FOREST;
            break;
        case ST_DT_TROLL_TEMPLE:       ////巨魔神庙
            dungeonType =DT_TROLL_TEMPLE;
            break;
        case ST_DT_BEHOLDER_CASTLE:     ////眼魔
            dungeonType =DT_BEHOLDER_CASTLE;
            break;
        case ST_DT_WARP_SPACE:          ////异空间
            dungeonType =DT_WARP_SPACE;
            break;
        case ST_DT_DRAGON_LAIR:         ////龙穴
            dungeonType =DT_DRAGON_LAIR;
            break;
        case ST_DT_LICH_TOMB:           ////巫妖墓室
            dungeonType =DT_LICH_TOMB;
            break;
        default:
            break;
    }
    return m_mArriveDungeon[dungeonType];
}
