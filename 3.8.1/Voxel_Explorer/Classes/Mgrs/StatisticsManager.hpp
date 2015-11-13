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
class StatisticsManager {
    StatisticsManager();
    
public:
    virtual ~StatisticsManager();
    static StatisticsManager* getInstance();
    
    void addMonsterKillNum(BaseMonster::MonsterType type);
    CChaosNumber  getMonsterKillNum(BaseMonster::MonsterType type){return m_mMonsterKills[type];}
    
    void setGoodCollectdNum(CChaosNumber num);
    CChaosNumber getGoodCollectdNum(){return m_nGoodCollectedNum;};
    
    void setFoodEaten(CChaosNumber food);
    CChaosNumber  getFoodEaten(){return m_nfoodEaten;}
    
    void setStepNum(CChaosNumber num);
    CChaosNumber  getStepNum(){return m_nStepNum;}
    
    void addPotionUse();
    CChaosNumber getPotionUse(){return m_nPotionsUse;}
    
    CChaosNumber getMonsterKillTotalNum(){return m_nMonsterKillTotalNum;};
    
    void load();
    void save();
    
private:
    CChaosNumber m_mMonsterKills[BaseMonster::MT_MAX];//杀死不同类型敌人数
//  std::map<BaseMonster::MonsterType,bool> m_mBossKills;//boos被杀死  //暂时不用 boss没定义
    CChaosNumber m_nGoodCollectedNum;//金币收集数
    CChaosNumber m_nfoodEaten;       //到达最远深度
    CChaosNumber m_nStepNum;          //步数
    CChaosNumber m_nPotionsUse;      //药水使用次数
    CChaosNumber m_nMonsterKillTotalNum;
    
};

#endif /* StatisticsManager_hpp */
