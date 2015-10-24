//
//  QuestItemProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#ifndef QuestItemProperty_hpp
#define QuestItemProperty_hpp

#include "PickableItemProperty.hpp"
class QuestItemProperty : public PickableItemProperty
{
public:
    QuestItemProperty(unsigned int instanceID, PickableItem::PickableItemType type);
};

#endif /* QuestItemProperty_hpp */
