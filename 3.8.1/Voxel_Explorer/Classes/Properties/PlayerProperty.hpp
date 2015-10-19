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
    
    CChaosNumber getLevel() const { return m_nLevel; }
    CChaosNumber getExp() const { return m_nExp; }
    CChaosNumber getLightDistance() const { return m_nLightDistance; }
    CChaosNumber getMaxHp() const { return m_nMaxHP; }
    CChaosNumber getMaxMp() const { return m_nMaxMP; }
    CChaosNumber getCurrentHp() const { return m_nCurrentHP; }
    CChaosNumber getCurrentMp() const { return m_nCurrentMP; }
    CChaosNumber getAttackDiceNum() const { return m_nAttackDiceNum; }
    CChaosNumber getAttackDiceFaceNum() const { return m_nAttackDiceFaceNum; }
    CChaosNumber getDefense() const { return m_nDefense; }
    CChaosNumber getBlockRate() const { return m_fBlockRate; }
    CChaosNumber getCriticalStrikeRate() const { return m_fCriticalStrikeRate; }
    CChaosNumber getDodgeRate() const { return m_fDodgeRate; }
    CChaosNumber getEquipedWeaponID() const { return m_bEquipedWeaponID; }
    CChaosNumber getEquipedArmorID() const { return m_bEquipedArmorID; }
    CChaosNumber getEquipedOrnamentsID() const { return m_bEquipedOrnamentsID; }
    
    void setExp(CChaosNumber exp);
    void setCurrentHP(CChaosNumber hp);
    void setCurrentMP(CChaosNumber mp);
    void EquipWeapon(CChaosNumber id);
    void EquipArmor(CChaosNumber id);
    void EquipOrnaments(CChaosNumber id);
private:
    void levelUp();

private:
    CChaosNumber    m_nLevel;               ///等级
    CChaosNumber    m_nExp;                 ///经验
    CChaosNumber    m_nLightDistance;       ///光照范围
    CChaosNumber    m_nMaxHP;               ///最大生命值
    CChaosNumber    m_nMaxMP;               ///最大魔法值
    CChaosNumber    m_nCurrentHP;           ///当前生命值
    CChaosNumber    m_nCurrentMP;           ///当前魔法值
    CChaosNumber    m_nAttackDiceNum;       ///攻击骰子数
    CChaosNumber    m_nAttackDiceFaceNum;   ///攻击骰子面数
    CChaosNumber    m_nDefense;             ///防御力
    CChaosNumber    m_fBlockRate;           ///格挡率
    CChaosNumber    m_fCriticalStrikeRate;  ///暴击率
    CChaosNumber    m_fDodgeRate;           ///闪避率
    
    CChaosNumber            m_bEquipedWeaponID;       ///装备了武器ID
    CChaosNumber            m_bEquipedArmorID;        ///装备了护甲ID
    CChaosNumber            m_bEquipedOrnamentsID;    ///装备了饰品ID
    
    bool            m_bDirty;               ///数据变化标记
};

#endif /* PlayerProperty_hpp */
