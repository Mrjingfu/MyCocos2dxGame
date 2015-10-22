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
class PlayerProperty : public cocos2d::Ref
{
    PlayerProperty();
    ~PlayerProperty();
public:
    static PlayerProperty* getInstance();

    void update(float delta);
    
    CChaosNumber getGold() const { return m_nGold; }
    CChaosNumber getSilver() const { return m_nSilver; }
    CChaosNumber getCopper() const { return m_nCopper; }
    CChaosNumber getLevel() const { return m_nLevel; }
    CChaosNumber getExp() const { return m_nExp; }
    CChaosNumber getLightDistance() const { return m_nLightDistance; }
    CChaosNumber getMaxHp() const { return m_nMaxHP; }
    CChaosNumber getMaxMp() const { return m_nMaxMP; }
    CChaosNumber getCurrentHp() const { return m_nCurrentHP; }
    CChaosNumber getCurrentMp() const { return m_nCurrentMP; }

    CChaosNumber getMinAttack();
    CChaosNumber getMaxAttack();
    CChaosNumber getDefense();

    CChaosNumber getBlockRate() const { return m_fBlockRate; }
    CChaosNumber getCriticalStrikeRate() const { return m_fCriticalStrikeRate; }
    CChaosNumber getDodgeRate() const { return m_fDodgeRate; }
    CChaosNumber getEquipedWeaponID() const { return m_nEquipedWeaponID; }
    CChaosNumber getEquipedArmorID() const { return m_nEquipedArmorID; }
    CChaosNumber getEquipedOrnamentsID() const { return m_nEquipedOrnamentsID; }
    
    void addMoney(CChaosNumber gold, CChaosNumber silver, CChaosNumber copper);
    void costMoney(CChaosNumber gold, CChaosNumber silver, CChaosNumber copper);
    void setExp(CChaosNumber exp);
    void setCurrentHP(CChaosNumber hp);
    void setCurrentMP(CChaosNumber mp);
    void EquipWeapon(CChaosNumber id);
    void EquipArmor(CChaosNumber id);
    void EquipOrnaments(CChaosNumber id);
    
    void load();
    void save();
private:
    void levelUp();
private:
    CChaosNumber    m_nGold;                ///金币
    CChaosNumber    m_nSilver;              ///银币
    CChaosNumber    m_nCopper;              ///铜币
    CChaosNumber    m_nLevel;               ///等级
    CChaosNumber    m_nExp;                 ///经验
    CChaosNumber    m_nLightDistance;       ///光照范围
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
    
    CChaosNumber            m_nEquipedWeaponID;       ///装备了武器ID
    CChaosNumber            m_nEquipedArmorID;        ///装备了护甲ID
    CChaosNumber            m_nEquipedOrnamentsID;    ///装备了饰品ID
    
    bool                    m_bDirty;                 ///数据是否修改了
};

#endif /* PlayerProperty_hpp */
