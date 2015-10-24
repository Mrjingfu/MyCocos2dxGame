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
private:
    bool            m_bHasEquiped;
};

#endif /* MagicOrnamentProperty_hpp */