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
    m_nAddedLightDistance       = 0;
    m_nAddedSearchDistance      = 0;
    m_nAddedMaxHP               = 0;
    m_nAddedMaxMP               = 0;
    m_nAddedMinAttack           = 0;
    m_nAddedMaxAttack           = 0;
    m_nAttackDiceNum            = 0;
    m_nAttackDiceFaceNum        = 0;
    m_fAddedCriticalStrikeRate  = 0;
    m_fAddedMagicItemFindRate   = 0;
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