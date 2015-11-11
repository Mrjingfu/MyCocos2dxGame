//
//  PotionsProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#ifndef PotionsProperty_hpp
#define PotionsProperty_hpp

#include "PickableItemProperty.hpp"
class PotionsProperty : public PickableItemProperty, public IStackable
{
public:
    PotionsProperty(unsigned int instanceID, PickableItem::PickableItemType type);
    
    virtual void adjustByLevel();
    virtual void handleIdentify();
    
    virtual void increaseCount() { ++m_nCount; }
    virtual void decreaseCount() { --m_nCount; }
};

#endif /* PotionsProperty_hpp */
