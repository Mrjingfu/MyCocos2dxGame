//
//  ArmorProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#ifndef ArmorProperty_hpp
#define ArmorProperty_hpp

#include "PickableItemProperty.hpp"
class ArmorProperty : public PickableItemProperty
{
public:
    ArmorProperty(unsigned int instanceID, PickableItem::PickableItemType type, bool identified);
    
    virtual void adjustByDC();
    virtual void handleIdentify();
    
    bool hasEquiped() const { return m_bHasEquiped; }
    void setEquiped(bool equiped) { m_bHasEquiped = equiped; }
    
    CChaosNumber getLightDistance() const { return m_nLightDistance; }
    CChaosNumber getSearchDistance() const { return m_nSearchDistance; }
    CChaosNumber getMaxHp() const { return m_nMaxHP; }
    CChaosNumber getMaxMp() const { return m_nMaxMP; }
    
    CChaosNumber getDefense();
    
    CChaosNumber getArmorClass() const { return m_nArmorClass; }
    CChaosNumber getDodgeRate() const { return m_fDodgeRate; }
private:
    bool            m_bHasEquiped;
    
    CChaosNumber    m_nLightDistance;       ///光照范围
    CChaosNumber    m_nSearchDistance;      ///侦查范围
    CChaosNumber    m_nMaxHP;               ///最大生命值
    CChaosNumber    m_nMaxMP;               ///最大魔法值
    
    CChaosNumber    m_nArmorClass;          ///防御等级
    CChaosNumber    m_fDodgeRate;           ///闪避率

};

#endif /* ArmorProperty_hpp */
