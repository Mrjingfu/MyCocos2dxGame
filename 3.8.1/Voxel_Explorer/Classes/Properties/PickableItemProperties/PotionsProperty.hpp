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
class PotionsProperty : public PickableItemProperty
{
public:
    PotionsProperty(unsigned int instanceID, PickableItem::PickableItemType type, bool identified);
};

#endif /* PotionsProperty_hpp */
