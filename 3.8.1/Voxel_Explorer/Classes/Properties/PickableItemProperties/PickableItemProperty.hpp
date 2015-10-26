//
//  PickableItemProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#ifndef PickableItemProperty_hpp
#define PickableItemProperty_hpp

#include "cocos2d.h"
#include "ChaosNumber.h"
#include "PickableItem.hpp"
class PickableItemProperty : public cocos2d::Ref
{
    friend class PlayerProperty;
public:
    typedef enum{
        PIPT_KEY = 0,               ///钥匙
        PIPT_WEAPON,                ///武器
        PIPT_SECOND_WEAPON,         ///副手武器
        PIPT_ARMOR,                 ///护甲
        PIPT_MAGIC_ORNAMENT,        ///饰品
        PIPT_SCROLL,                ///卷轴
        PIPT_POTIONS,               ///药水
        PIPT_MATERIAL,              ///宝石
        PIPT_QUEST,                 ///任务物品
        PIPT_SUNDRIES,              ///杂物
        PIPT_UNKNOWN
    }PickableItemPropertyType;
public:
    unsigned int getInstanceID() const { return m_nInstanceID; }
    PickableItemPropertyType getPickableItemPropertyType() const { return m_PropertyType; }
    PickableItem::PickableItemType getPickableItemType() const { return m_ItemType; }
    CChaosNumber getLevel() const { return m_nLevel; }
    CChaosNumber getValueCopper() const { return m_nValueCopper; }
    std::string getName() const { return m_strName; }
    std::string getDesc() const { return m_strDesc; }
    std::string getIconRes() const { return m_strIconRes; }
    bool isIdentified() const { return m_bIdentified; }
    void setIdentified(bool identified) { m_bIdentified = identified; }
    bool isStackable() const { return m_bStackable; }
    bool isEquipable() const { return m_bEquipable; }
    bool isCombinable() const { return m_bCombinable; }
    bool isDiscardable() const { return m_bDiscardable; }
    bool isCursed() const { return m_bCursed; }
protected:
    PickableItemProperty(unsigned int instanceID, PickableItem::PickableItemType type);

public:
    virtual void adjustByDC() = 0;
    virtual void handleIdentify() = 0;
protected:
    unsigned int                    m_nInstanceID;
    PickableItemPropertyType        m_PropertyType;         ///物品属性类型
    PickableItem::PickableItemType  m_ItemType;             ///物品类型
    CChaosNumber                    m_nLevel;               ///等级
    CChaosNumber                    m_nValueCopper;         ///价值
    std::string                     m_strName;              ///名称
    std::string                     m_strDesc;              ///描述
    std::string                     m_strIconRes;           ///icon资源
    bool                            m_bIdentified;          ///是否辨识过
    bool                            m_bStackable;           ///是否可以合并
    bool                            m_bEquipable;           ///是否可被装备
    bool                            m_bCombinable;          ///是否可组合的
    bool                            m_bDiscardable;         ///是否可被丢弃的
    bool                            m_bCursed;              ///被诅咒的(被诅咒的装备不能卸载下)
};

#endif /* PickableItemProperty_hpp */
