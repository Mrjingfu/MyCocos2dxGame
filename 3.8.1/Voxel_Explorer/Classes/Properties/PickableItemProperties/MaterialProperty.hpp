//
//  MaterialProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#ifndef MaterialProperty_hpp
#define MaterialProperty_hpp

#include "PickableItemProperty.hpp"
class MaterialProperty : public PickableItemProperty
{
public:
    MaterialProperty(unsigned int instanceID, PickableItem::PickableItemType type);
    virtual ~MaterialProperty(){}
    virtual bool load(const cocos2d::ValueMap& data);
    virtual bool save(cocos2d::ValueMap& data);
};

#endif /* MaterialProperty_hpp */
