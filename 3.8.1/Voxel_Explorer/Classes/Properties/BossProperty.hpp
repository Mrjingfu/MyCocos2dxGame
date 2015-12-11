//
//  BossProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/8.
//
//

#ifndef BossProperty_hpp
#define BossProperty_hpp

#include "cocos2d.h"
#include "ChaosNumber.h"
#include "PlayerProperty.hpp"
class BossProperty : public cocos2d::Ref
{
public:
    BossProperty();
    virtual ~BossProperty();
public:
    CChaosNumber getValueCopper() const { return m_nValueCopper; }
    CChaosNumber getMaxHP() const { return m_nMaxHP; }
    CChaosNumber getCurrentHP() const { return m_nCurrentHP; }
    
    CChaosNumber getMinAttack();
    CChaosNumber getMaxAttack();
    CChaosNumber getDefense();
    
    CChaosNumber getBlockRate() const { return m_fBlockRate; }
    CChaosNumber getCriticalStrikeRate() const { return m_fCriticalStrikeRate; }
    CChaosNumber getDodgeRate() const { return m_fDodgeRate; }
    
    void setCurrentHP(CChaosNumber hp);
    
    void adjustByDC();
    
    CChaosNumber getRandomAttack();
    
    int getAttackAddBuffer() const { return m_nAttackAddBuffer; }
    
    void addAttackAddBuffer(PlayerBuffer buff);
    void removeAttackAddBuffer(PlayerBuffer buff);
private:
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
    
    int             m_nAttackAddBuffer;          ///攻击附加效果
};

#endif /* BossProperty_hpp */
