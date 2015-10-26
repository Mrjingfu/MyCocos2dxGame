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
    
    CChaosNumber getAddedLightDistance() const { return m_nAddedLightDistance; }
    CChaosNumber getAddedSearchDistance() const { return m_nAddedSearchDistance; }
    CChaosNumber getAddedMaxHp() const { return m_nAddedMaxHP; }
    CChaosNumber getAddedMaxMp() const { return m_nAddedMaxMP; }
    
    CChaosNumber getMinAttack();
    CChaosNumber getMaxAttack();
    
    CChaosNumber getAddedMinAttack() const { return m_nAddedMinAttack; }
    CChaosNumber getAddedMaxAttack() const { return m_nAddedMaxAttack; }
    
    CChaosNumber getAttackDiceNum() const { return m_nAttackDiceNum; }
    CChaosNumber getAttackDiceFaceNum() const { return m_nAttackDiceFaceNum; }
    
    CChaosNumber getAddedCriticalStrikeRate() const { return m_fAddedCriticalStrikeRate; }
    
    CChaosNumber getAddedMagicItemFindRate() const { return m_fAddedMagicItemFindRate; }
private:
    bool            m_bHasEquiped;
    
    CChaosNumber    m_nAddedLightDistance;       ///光照范围
    CChaosNumber    m_nAddedSearchDistance;      ///侦查范围
    CChaosNumber    m_nAddedMaxHP;               ///最大生命值
    CChaosNumber    m_nAddedMaxMP;               ///最大魔法值

    CChaosNumber    m_nAddedMinAttack;      ///额外最小攻击增加值
    CChaosNumber    m_nAddedMaxAttack;      ///额外最大攻击增加值
    CChaosNumber    m_nAttackDiceNum;       ///攻击骰子数
    CChaosNumber    m_nAttackDiceFaceNum;   ///攻击骰子面数

    CChaosNumber    m_fAddedCriticalStrikeRate;  ///暴击率
    
    CChaosNumber    m_fAddedMagicItemFindRate;  ///附加取魔率
};

#endif /* WeaponProperty_hpp */
