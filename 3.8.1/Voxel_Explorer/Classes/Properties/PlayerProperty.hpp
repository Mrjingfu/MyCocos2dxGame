//
//  PlayerProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/19.
//
//

#ifndef PlayerProperty_hpp
#define PlayerProperty_hpp

#include "cocos2d.h"
#include "ChaosNumber.h"
#include "PickableItem.hpp"
#include "PickableItemProperty.hpp"

typedef enum {
    PB_NONE = 0,                    ///无状态
    PB_SPEEDUP = 1<<0,                ///加速
    PB_STEALTH = 1<<1,              ///隐身
    PB_STRONGER = 1<<2,             ///强壮
    
    PB_POISONING = 1<<3,            ///中毒
    PB_FROZEN = 1<<4,               ///冰冻
    PB_PARALYTIC = 1<<5,            ///麻痹
    PB_WEAK = 1<<6,                 ///虚弱
    PB_FIRE = 1<<7,                 ///着火
    
    PB_BLOCKRATEUP = 1<<8,          ///格挡率上升
    PB_MAX
} PlayerBuffer;

typedef enum {
    PS_NONE = 0,                 ///无状态
    PS_BLOCKRATEUP = 1,          ///格挡率上升
    PS_MAGICARROW = 2,           ///魔法箭矢
    PS_FIREBALL = 3,             ///火球术
    PS_MAX
} PlayerSkill;

class PlayerProperty : public cocos2d::Ref
{
    PlayerProperty();
    virtual ~PlayerProperty();
public:
    static PlayerProperty* getInstance();

    bool initNewPlayer();   ///新角色初始化
    
    void update(float delta);
    

    CChaosNumber getValueCopper() const { return m_nValueCopper; }
    CChaosNumber getLevel() const { return m_nLevel; }
    CChaosNumber getExp() const { return m_nExp; }
    CChaosNumber getLightDistance() const { return m_nLightDistance; }
    CChaosNumber getSearchDistance() const { return m_nSearchDistance; }
    CChaosNumber getMaxHP() const { return m_nMaxHP; }
    CChaosNumber getMaxMP() const { return m_nMaxMP; }
    CChaosNumber getCurrentHP() const { return m_nCurrentHP; }
    CChaosNumber getCurrentMP() const { return m_nCurrentMP; }

    CChaosNumber getMinAttack();
    CChaosNumber getMaxAttack();
    CChaosNumber getDefense();

    CChaosNumber getBlockRate() const { return m_fBlockRate; }
    CChaosNumber getCriticalStrikeRate() const { return m_fCriticalStrikeRate; }
    CChaosNumber getDodgeRate() const { return m_fDodgeRate; }
    CChaosNumber getMagicItemFindRate() const { return m_fMagicItemFindRate; }
    
    CChaosNumber getEquipedWeaponID() const { return m_nEquipedWeaponID; }
    CChaosNumber getEquipedArmorID() const { return m_nEquipedArmorID; }
    CChaosNumber getEquipedOrnamentsID() const { return m_nEquipedOrnamentsID; }
    CChaosNumber getEquipedSecondWeaponID() const{return m_nEquipedSecondWeaponID;}
    
    CChaosNumber getBagMaxSpace() const { return m_nBagMaxSpace; }
    CChaosNumber getBagExtendTimes() const { return m_nBagExtendTimes; }
    CChaosNumber getBagExtendMaxTimes() const { return m_nBagExtendMaxTimes; }
    
    int getPlayerBuffer() const { return m_BufferFlag; }
    
    void addPlayerBuffer(PlayerBuffer buff);
    void removePlayerBuffer(PlayerBuffer buff);
    void resetPlayerBuffer();
    
    void healedbyNurse();
    
    void addMoney(CChaosNumber copper, bool sound = true);
    bool costMoney(CChaosNumber copper);
    void setExp(CChaosNumber exp);
    void setCurrentHP(CChaosNumber hp);
    void setCurrentMP(CChaosNumber mp);
    bool equipWeapon(CChaosNumber id, bool sound = true);
    bool equipSecondWeapon(CChaosNumber id, bool sound = true);
    bool equipArmor(CChaosNumber id, bool sound = true);
    bool equipOrnaments(CChaosNumber id, bool sound = true);
    bool indentifyItem(CChaosNumber id);
    bool usePotion(CChaosNumber id);
    bool useScroll(CChaosNumber id);
    bool useKey(PickableItem::PickableItemType type);
    bool equipBreakDown(CChaosNumber id,std::map<PickableItem::PickableItemType,CChaosNumber>& resultDatas);   //分解
    bool equipRefine(CChaosNumber id);//洗练
    PickableItemProperty* getStackableItemForBag(PickableItem::PickableItemType type);
    
    void playPickupItemSound(PickableItemProperty* itemProperty);
    bool buyItemToBag(PickableItemProperty* buyItemProperty, CChaosNumber count, bool toIndentify = false, bool sound = true);
    bool sellItemFromBag(PickableItemProperty* sellItemProperty, CChaosNumber count);
    bool addItemToBag(PickableItem::PickableItemType type, CChaosNumber level, bool sound = true);
    bool removeStackableItemFromBag(PickableItem::PickableItemType type, CChaosNumber count);
    bool removeItemFromBag(CChaosNumber id);
    void extendBagSpace();
    const std::vector<PickableItemProperty*>& getPlayerBag() const { return m_Bag; }
    PickableItemProperty* getItemFromBag(CChaosNumber id) const;
    
    PlayerSkill getPlayerSkill() const { return m_curPlayerSkill; }
    
    CChaosNumber getRandomAttack();
    
    void reset();
    bool refreshAfterCreatePlayer();
    bool load(const cocos2d::ValueMap& data);
    bool save(cocos2d::ValueMap& data);
private:
    void levelUp();
private:
    CChaosNumber    m_nValueCopper;         ///价值
    CChaosNumber    m_nLevel;               ///等级
    CChaosNumber    m_nExp;                 ///经验
    CChaosNumber    m_nLightDistance;       ///光照范围
    CChaosNumber    m_nSearchDistance;      ///侦查范围
    CChaosNumber    m_nMaxHP;               ///最大生命值
    CChaosNumber    m_nMaxMP;               ///最大魔法值
    CChaosNumber    m_nCurrentHP;           ///当前生命值
    CChaosNumber    m_nCurrentMP;           ///当前魔法值
    CChaosNumber    m_nAddedMinAttack;      ///额外最小攻击增加值
    CChaosNumber    m_nAddedMaxAttack;      ///额外最大攻击增加值
    CChaosNumber    m_nAttackDiceNum;       ///攻击骰子数
    CChaosNumber    m_nAttackDiceFaceNum;   ///攻击骰子面数
    CChaosNumber    m_nArmorClass;          ///防御等级
    CChaosNumber    m_nBaseArmorClass;      ///基础防御等级
    CChaosNumber    m_fBlockRate;           ///格挡率
    CChaosNumber    m_fCriticalStrikeRate;  ///暴击率
    CChaosNumber    m_fDodgeRate;           ///闪避率
    CChaosNumber    m_fBasicMagicItemFindRate;   ///基本魔法物品获得率
    CChaosNumber    m_fMagicItemFindRate;   ///魔法物品获得率
    CChaosNumber    m_fMaxMagicItemFindRate;   ///最大魔法物品获得率
    
    CChaosNumber            m_nEquipedWeaponID;       ///装备了武器ID
    CChaosNumber            m_nEquipedSecondWeaponID; ///装备了副手武器ID
    CChaosNumber            m_nEquipedArmorID;        ///装备了护甲ID
    CChaosNumber            m_nEquipedOrnamentsID;    ///装备了饰品ID
    
    std::vector<PickableItemProperty*>  m_Bag;
    CChaosNumber                        m_nBagMaxSpace;         ///背包最大容量
    CChaosNumber                        m_nBagExtendTimes;      ///背包扩容次数
    CChaosNumber                        m_nBagExtendMaxTimes;   ///背包最大扩容次数
    
    int                                 m_BufferFlag;           ///状态标记
    
    bool                    m_bDirty;                 ///数据是否修改了
    
    bool                    m_bNeedRefreshAfterCreatePlayer;
    
    PlayerSkill             m_curPlayerSkill;
    
public:
    static unsigned int     m_snItemInstanceIDCounter;
};

#endif /* PlayerProperty_hpp */
