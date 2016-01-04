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
    
    virtual bool load(const cocos2d::ValueMap& data);
    virtual bool save(cocos2d::ValueMap& data);
};

#endif /* QuestItemProperty_hpp */
