//
//  WeaponProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "WeaponProperty.hpp"
USING_NS_CC;

WeaponProperty::WeaponProperty(unsigned int instanceID, PickableItem::PickableItemType type, bool identified)
    :PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_WEAPON;
    m_bIdentified = identified;
    m_bStackable = false;
    m_bEquipable = true;
    m_bCombinable = false;
    m_bDiscardable = true;
    
    m_bHasEquiped = false;
}


void WeaponProperty::adjustByDC()
{

}
void WeaponProperty::handleIdentify()
{
    if(m_bIdentified)
        return;
}
CChaosNumber WeaponProperty::getMinAttack()
{
    return m_nAttackDiceNum + m_nAddedMinAttack.GetLongValue();
}
CChaosNumber WeaponProperty::getMaxAttack()
{
    return m_nAttackDiceNum*m_nAttackDiceFaceNum.GetLongValue() + m_nAddedMaxAttack.GetLongValue();
}