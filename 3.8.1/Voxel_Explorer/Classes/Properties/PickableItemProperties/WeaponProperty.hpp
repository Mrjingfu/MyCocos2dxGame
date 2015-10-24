//
//  WeaponProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#ifndef WeaponProperty_hpp
#define WeaponProperty_hpp

#include "PickableItemProperty.hpp"
class WeaponProperty : public PickableItemProperty
{
public:
    WeaponProperty(unsigned int instanceID, PickableItem::PickableItemType type, bool identified);
    virtual void adjustByDC();
    virtual void handleIdentify();
    
    bool hasEquiped() const { return m_bHasEquiped; }
    void setEquiped(bool equiped) { m_bHasEquiped = equiped; }
    
    CChaosNumber getLightDistance() const { return m_nLightDistance; }
    CChaosNumber getSearchDistance() const { return m_nSearchDistance; }
    CChaosNumber getMaxHp() const { return m_nMaxHP; }
    CChaosNumber getMaxMp() const { return m_nMaxMP; }
    
    CChaosNumber getMinAttack();
    CChaosNumber getMaxAttack();
    
    CChaosNumber getAddedMinAttack() const { return m_nAddedMinAttack; }
    CChaosNumber getAddedMaxAttack() const { return m_nAddedMaxAttack; }
    
    CChaosNumber getAttackDiceNum() const { return m_nAttackDiceNum; }
    CChaosNumber getAttackDiceFaceNum() const { return m_nAttackDiceFaceNum; }
    
    CChaosNumber getCriticalStrikeRate() const { return m_fCriticalStrikeRate; }
private:
    bool            m_bHasEquiped;
    
    CChaosNumber    m_nLightDistance;       ///光照范围
    CChaosNumber    m_nSearchDistance;      ///侦查范围
    CChaosNumber    m_nMaxHP;               ///最大生命值
    CChaosNumber    m_nMaxMP;               ///最大魔法值

    CChaosNumber    m_nAddedMinAttack;      ///额外最小攻击增加值
    CChaosNumber    m_nAddedMaxAttack;      ///额外最大攻击增加值
    CChaosNumber    m_nAttackDiceNum;       ///攻击骰子数
    CChaosNumber    m_nAttackDiceFaceNum;   ///攻击骰子面数

    CChaosNumber    m_fCriticalStrikeRate;  ///暴击率
};

#endif /* WeaponProperty_hpp */
