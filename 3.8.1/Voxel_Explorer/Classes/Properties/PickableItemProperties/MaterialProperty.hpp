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
    
private:
    CChaosNumber    m_nValue;
};

#endif /* MaterialProperty_hpp */
