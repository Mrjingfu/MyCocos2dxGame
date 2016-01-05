//
//  SundriesProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#ifndef SundriesProperty_hpp
#define SundriesProperty_hpp

#include "PickableItemProperty.hpp"
class SundriesProperty : public PickableItemProperty
{
public:
    SundriesProperty(unsigned int instanceID, PickableItem::PickableItemType type);
    virtual ~SundriesProperty(){}
    virtual bool load(const cocos2d::ValueMap& data);
    virtual bool save(cocos2d::ValueMap& data);
};

#endif /* SundriesProperty_hpp */
