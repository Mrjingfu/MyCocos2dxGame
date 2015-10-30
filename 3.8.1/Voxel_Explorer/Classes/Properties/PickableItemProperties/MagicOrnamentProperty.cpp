//
//  MagicOrnamentProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "MagicOrnamentProperty.hpp"
USING_NS_CC;

MagicOrnamentProperty::MagicOrnamentProperty(unsigned int instanceID, PickableItem::PickableItemType type, bool identified)
    :PickableItemProperty(instanceID, type)
{
    m_PropertyType = PIPT_MAGIC_ORNAMENT;
    m_bIdentified = identified;
    m_bStackable = false;
    m_bEquipable = true;
    m_bCombinable = false;
    m_bDiscardable = true;
    
    m_bHasEquiped = false;
    
    m_nAddedLightDistance       =0;
    m_nAddedSearchDistance      =0;
    m_nAddedMaxHP               =0;
    m_nAddedMaxMP               =0;
    m_nAddedMinAttack           =0;
    m_nAddedMaxAttack           =0;
    m_nAddedArmorClass          =0;
    m_fAddedBlockRate           =0;
    m_fAddedCriticalStrikeRate  =0;
    m_fAddedDodgeRate           =0;
    m_fAddedMagicItemFindRate   =0;
}
void MagicOrnamentProperty::adjustByDC()
{
    
}
void MagicOrnamentProperty::handleIdentify()
{
    if(m_bIdentified)
        return;
}
CChaosNumber MagicOrnamentProperty::getAddedDefense()
{
    return -m_nAddedArmorClass.GetLongValue();
}