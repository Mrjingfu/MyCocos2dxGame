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
#include "PickableItem.hpp"

typedef enum {
    MF_NONE   = 0,
    MF_WHITE  = 1<<0,
    MF_BLUE   = 1<<1,
    MF_GREEN  = 1<<2,
    MF_PURPLE = 1<<3,
    MF_MAX
} MaterialFlag;

class MaterialProperty : public PickableItemProperty,public IStackable
{
public:
    

    MaterialProperty(unsigned int instanceID, PickableItem::PickableItemType type);
    virtual ~MaterialProperty(){}
    
    virtual void increaseCount() { ++m_nCount; }
    virtual void decreaseCount() { --m_nCount; }
    
    virtual void addCount(CChaosNumber count) { m_nCount += count; }
    virtual void removeCount(CChaosNumber count) { m_nCount -= count; }
    
    virtual bool load(const cocos2d::ValueMap& data);
    virtual bool save(cocos2d::ValueMap& data);
    
    virtual void adjustByLevel();
    virtual void handleIdentify();
    
    static std::map<PickableItem::PickableItemType, int> WASH_PIQ_RARE;
    static std::map<PickableItem::PickableItemType, int> WASH_PIQ_EPIC;
    static std::map<PickableItem::PickableItemType, int> WASH_PIQ_LEGEND;

};

#endif /* MaterialProperty_hpp */
