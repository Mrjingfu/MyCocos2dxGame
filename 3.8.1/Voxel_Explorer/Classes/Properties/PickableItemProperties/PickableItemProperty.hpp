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
typedef enum{
    AE_MIN_ATTACK = 0,
    AE_MAX_ATTACK,
    AE_MAX_HP,
    AE_MAX_MP,
    AE_BLOCK_RATE,
    AE_CRITICALSTRICK_RATE,
    AE_DODGE_RATE,
    AE_MAGICITEM_FIND_RATE,
    AE_SEARCH_DISTANCE,
    AE_LIGHT_DISTANCE,
}ADDED_EFFECT;

typedef enum{
    PIQ_GENERAL = 0,        ///普通       0特效
    PIQ_RARE,               ///稀有       1-2特效
    PIQ_EPIC,               ///史诗       3-4特效
    PIQ_LEGEND              ///传说       5-6特效
}PICKABLEITEM_QUALITY;

class IStackable
{
public:
    virtual void increaseCount() = 0;
    virtual void decreaseCount() = 0;
    virtual void addCount(CChaosNumber count) = 0;
    virtual void removeCount(CChaosNumber count) = 0;
};

const std::string PICKABLE_ITEM_PROPERTY_TYPE_NAMES[] = {
    
    "PIPN_KEY",                   ///钥匙
    "PIPN_WEAPON",                ///武器
    "PIPN_SECOND_WEAPON",         ///副手武器
    "PIPN_ARMOR",                 ///护甲
    "PIPN_MAGIC_ORNAMENT",        ///饰品
    "PIPN_SCROLL",                ///卷轴
    "PIPN_POTIONS",               ///药水
    "PIPN_MATERIAL",              ///宝石
    "PIPN_QUEST",                 ///任务物品
    "PIPN_SUNDRIES"               ///杂物
};

class PickableItemProperty : public cocos2d::Ref,public cocos2d::Clonable
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
    void setLevel( CChaosNumber level){m_nLevel = level.GetLongValue();}
    CChaosNumber getValueCopper() const { return m_nValueCopper; }
    CChaosNumber getCopperWhenBuy() { return m_nCopperWhenBuy; }
    void setCopperWhenBuy(CChaosNumber copper) { m_nCopperWhenBuy = copper; }
    std::string getName() const { return m_strName; }
    std::string getDesc() const { return m_strDesc; }
    std::string getBeforeIndentifyDesc() const {return m_strBeforeIndentifyDesc;}
    std::string getIconRes() const { return m_strIconRes; }
    bool isIdentified() const { return m_bIdentified; }
    void setIdentified(bool identified) { m_bIdentified = identified; }
    bool isStackable() const { return m_bStackable; }
    bool isEquipable() const { return m_bEquipable; }
    bool isCombinable() const { return m_bCombinable; }
    bool isDiscardable() const { return m_bDiscardable; }
    bool isCursed() const { return m_bCursed; }
    CChaosNumber getCount() const { return m_nCount; }
    void setCount(CChaosNumber count) { m_nCount = count; }
    virtual PickableItemProperty* clone() const override {return nullptr;}
    
    PICKABLEITEM_QUALITY getQuality() const { return m_Quality; }
    const std::vector<ADDED_EFFECT>& getAddedEffectList() const { return m_AddedEffectList; }
protected:
    PickableItemProperty(unsigned int instanceID, PickableItem::PickableItemType type);
public:
    virtual ~PickableItemProperty(){}
    virtual void adjustByLevel() = 0;
    virtual void handleIdentify() = 0;
    
    virtual bool load(const cocos2d::ValueMap& data) = 0;
    virtual bool save(cocos2d::ValueMap& data) = 0;
protected:
    unsigned int                    m_nInstanceID;
    PickableItemPropertyType        m_PropertyType;         ///物品属性类型
    PickableItem::PickableItemType  m_ItemType;             ///物品类型
    CChaosNumber                    m_nLevel;               ///等级
    CChaosNumber                    m_nValueCopper;         ///价值
    CChaosNumber                    m_nCopperWhenBuy;       ///购买时的价值
    std::string                     m_strName;              ///名称
    std::string                     m_strBeforeIndentifyDesc;   ///未辨识前的描述
    std::string                     m_strDesc;              ///描述
    std::string                     m_strPropertyTypeName;  ///类型描述
    std::string                     m_strIconRes;           ///icon资源
    bool                            m_bIdentified;          ///是否辨识过
    bool                            m_bStackable;           ///是否可以合并
    bool                            m_bEquipable;           ///是否可被装备
    bool                            m_bCombinable;          ///是否可组合的
    bool                            m_bDiscardable;         ///是否可被丢弃的
    bool                            m_bCursed;              ///被诅咒的(被诅咒的装备不能卸载下)
    
    CChaosNumber                    m_nCount;               ///个数
    
    std::vector<ADDED_EFFECT>       m_AddedEffectList;      ///附加属性类型列表
    PICKABLEITEM_QUALITY            m_Quality;              ///物品品质
};

#endif /* PickableItemProperty_hpp */
