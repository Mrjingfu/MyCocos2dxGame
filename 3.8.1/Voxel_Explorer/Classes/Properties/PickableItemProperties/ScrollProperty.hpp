//
//  ScrollProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#ifndef ScrollProperty_hpp
#define ScrollProperty_hpp

#include "PickableItemProperty.hpp"
class ScrollProperty : public PickableItemProperty
{
public:
    ScrollProperty(unsigned int instanceID, PickableItem::PickableItemType type, bool identified);
};

#endif /* ScrollProperty_hpp */
