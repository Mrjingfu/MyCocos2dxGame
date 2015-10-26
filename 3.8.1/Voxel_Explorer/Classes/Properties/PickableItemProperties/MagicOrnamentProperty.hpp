//
//  MagicOrnamentProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#ifndef MagicOrnamentProperty_hpp
#define MagicOrnamentProperty_hpp

#include "PickableItemProperty.hpp"
class MagicOrnamentProperty : public PickableItemProperty
{
public:
    MagicOrnamentProperty(unsigned int instanceID, PickableItem::PickableItemType type, bool identified);
    
    virtual void adjustByDC();
    virtual void handleIdentify();
    
    bool hasEquiped() const { return m_bHasEquiped; }
    void setEquiped(bool equiped) { m_bHasEquiped = equiped; }
    
    CChaosNumber getAddedLightDistance() const { return m_nAddedLightDistance; }
    CChaosNumber getAddedSearchDistance() const { return m_nAddedSearchDistance; }
    CChaosNumber getAddedMaxHp() const { return m_nAddedMaxHP; }
    CChaosNumber getAddedMaxMp() const { return m_nAddedMaxMP; }
    
    CChaosNumber getAddedMinAttack() const { return m_nAddedMinAttack; }
    CChaosNumber getAddedMaxAttack() const { return m_nAddedMaxAttack; }
    
    CChaosNumber getAddedDefense();
    
    CChaosNumber getAddedArmorClass() const { return m_nAddedArmorClass; }
    
    CChaosNumber getAddedBlockRate() const { return m_fAddedBlockRate; }
    CChaosNumber getAddedCriticalStrikeRate() const { return m_fAddedCriticalStrikeRate; }
    CChaosNumber getAddedDodgeRate() const { return m_fAddedDodgeRate; }

    CChaosNumber getAddedMagicItemFindRate() const { return m_fAddedMagicItemFindRate; }
private:
    bool            m_bHasEquiped;
    
    CChaosNumber    m_nAddedLightDistance;       ///光照范围
    CChaosNumber    m_nAddedSearchDistance;      ///侦查范围
    CChaosNumber    m_nAddedMaxHP;               ///最大生命值
    CChaosNumber    m_nAddedMaxMP;               ///最大魔法值
    
    CChaosNumber    m_nAddedMinAttack;           ///额外最小攻击增加值
    CChaosNumber    m_nAddedMaxAttack;           ///额外最大攻击增加值
    
    CChaosNumber    m_nAddedArmorClass;          ///防御等级
    
    CChaosNumber    m_fAddedBlockRate;           ///格挡率
    CChaosNumber    m_fAddedCriticalStrikeRate;  ///暴击率
    CChaosNumber    m_fAddedDodgeRate;           ///闪避率
    CChaosNumber    m_fAddedMagicItemFindRate;   ///附加取魔率
};

#endif /* MagicOrnamentProperty_hpp */
