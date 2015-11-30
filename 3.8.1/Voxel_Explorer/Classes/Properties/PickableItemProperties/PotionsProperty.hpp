//
//  PotionsProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#ifndef PotionsProperty_hpp
#define PotionsProperty_hpp
#include "ChaosNumber.h"
#include "PickableItemProperty.hpp"
class PotionsProperty : public PickableItemProperty, public IStackable
{
public:
    PotionsProperty(unsigned int instanceID, PickableItem::PickableItemType type);
    
    virtual void adjustByLevel();
    virtual void handleIdentify();
    
    virtual void increaseCount() { ++m_nCount; }
    virtual void decreaseCount() { --m_nCount; }
    
    virtual void addCount(CChaosNumber count) { m_nCount += count; }
    virtual void removeCount(CChaosNumber count) { m_nCount -= count; }
    
    CChaosNumber getValue() const { return m_nValue; }
private:
    CChaosNumber    m_nValue;
};

#endif /* PotionsProperty_hpp */
