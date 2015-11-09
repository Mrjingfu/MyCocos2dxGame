//
//  MonsterProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/19.
//
//

#ifndef MonsterProperty_hpp
#define MonsterProperty_hpp

#include "cocos2d.h"
#include "ChaosNumber.h"
class MonsterProperty : public cocos2d::Ref
{
public:
    MonsterProperty();
    ~MonsterProperty();
public:
    CChaosNumber getLevel() const { return m_nLevel; }
    CChaosNumber getValueCopper() const { return m_nValueCopper; }
    CChaosNumber getMaxHP() const { return m_nMaxHP; }
    CChaosNumber getCurrentHP() const { return m_nCurrentHP; }
    
    CChaosNumber getMinAttack();
    CChaosNumber getMaxAttack();
    CChaosNumber getDefense();
    
    CChaosNumber getBlockRate() const { return m_fBlockRate; }
    CChaosNumber getCriticalStrikeRate() const { return m_fCriticalStrikeRate; }
    CChaosNumber getDodgeRate() const { return m_fDodgeRate; }
    
    CChaosNumber getDropItemNum() const { return m_nDropItemNum; }
    
    void setCurrentHP(CChaosNumber hp);
    
    void adjustByDC();
    
    CChaosNumber getRandomAttack();
    
    bool isElite() const { return m_bIsElite; }
private:
    CChaosNumber    m_nLevel;                    ///等级
    CChaosNumber    m_nValueCopper;              ///价值铜币
    CChaosNumber    m_nMaxHP;                    ///最大生命值
    CChaosNumber    m_nCurrentHP;                ///当前生命值
    CChaosNumber    m_nAddedMinAttack;           ///额外最小攻击增加值
    CChaosNumber    m_nAddedMaxAttack;           ///额外最大攻击增加值
    CChaosNumber    m_nAttackDiceNum;            ///攻击骰子数
    CChaosNumber    m_nAttackDiceFaceNum;        ///攻击骰子面数
    CChaosNumber    m_nArmorClass;               ///防御等级
    CChaosNumber    m_nBaseArmorClass;           ///基础防御等级
    CChaosNumber    m_fBlockRate;                ///格挡率
    CChaosNumber    m_fCriticalStrikeRate;       ///暴击率
    CChaosNumber    m_fDodgeRate;                ///闪避率
    
    CChaosNumber    m_nDropItemNum;              ///掉落物品个数
    
    bool            m_bIsElite;                  ///是否为精英怪
};

#endif /* MonsterProperty_hpp */
