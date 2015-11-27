//
//  MonsterProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/19.
//
//

#include "MonsterProperty.hpp"
#include "RandomDungeon.hpp"
#include "AlisaMethod.h"
USING_NS_CC;

MonsterProperty::MonsterProperty()
{
    m_nLevel                = 1;                    ///等级
    m_nValueCopper          = 0;                    ///价值铜币
    m_nMaxHP                = 10;                   ///最大生命值
    m_nCurrentHP            = 10;                   ///当前生命值
    m_nAddedMinAttack       = 0;                    ///额外最小攻击增加值
    m_nAddedMaxAttack       = 0;                    ///额外最大攻击增加值
    m_nAttackDiceNum        = 1;                    ///攻击骰子数
    m_nAttackDiceFaceNum    = 4;                    ///攻击骰子面数
    m_nArmorClass           = 4;                    ///防御等级
    m_nBaseArmorClass       = 4;                    ///基础防御等级
    m_fBlockRate            = 0.01f;                ///格挡率
    m_fCriticalStrikeRate   = 0.02f;                ///暴击率
    m_fDodgeRate            = 0.01f;                ///闪避率
    m_nDropItemNum          = 0;                    ///掉落物品个数
    
    m_bIsElite              = false;                ///是否为精英怪
}
MonsterProperty::~MonsterProperty()
{
}

CChaosNumber MonsterProperty::getMinAttack()
{
    return m_nAttackDiceNum + m_nAddedMinAttack.GetLongValue();
}
CChaosNumber MonsterProperty::getMaxAttack()
{
    return m_nAttackDiceNum*m_nAttackDiceFaceNum.GetLongValue() + m_nAddedMaxAttack.GetLongValue();
}
CChaosNumber MonsterProperty::getDefense()
{
    return -m_nArmorClass.GetLongValue() + m_nBaseArmorClass.GetLongValue();
}
void MonsterProperty::setCurrentHP(CChaosNumber hp)
{
    if(m_nCurrentHP == hp)
        return;
    if(hp >= m_nMaxHP)
        m_nCurrentHP = m_nMaxHP;
    else if(hp <= 0)
        m_nCurrentHP = 0;
    else
        m_nCurrentHP = hp;
}
void MonsterProperty::adjustByDC()
{
    if(RandomDungeon::getInstance()->getCurrentDungeonNode() == nullptr)
        return;
    if(!m_bIsElite)
    {
        float percentElite = 0.005f;
        float percentStandard = 1.0 - percentElite;
        AlisaMethod* amElite = AlisaMethod::create(percentStandard,percentElite,-1.0, NULL);
        if(amElite)
            m_bIsElite = (amElite->getRandomIndex() == 1);
    }
    
    CChaosNumber dc = RandomDungeon::getInstance()->getDifficultClass();
    CChaosNumber nodeDepth = RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nNodeDepth;
    CChaosNumber currentDepth = RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth;
    m_nLevel = m_nLevel.GetLongValue() + (dc-1)*30 + (nodeDepth-1)*5 + cocos2d::random(0, (int)currentDepth.GetLongValue());
    if(m_bIsElite)
        m_nLevel = m_nLevel + 5;
    
    m_nValueCopper = cocos2d::random((int)m_nLevel*10, (int)m_nLevel*15);
    if(m_bIsElite)
        m_nValueCopper = m_nValueCopper*5;
    
    m_nMaxHP = m_nMaxHP + m_nLevel.GetLongValue()*m_nMaxHP.GetLongValue();
    m_nCurrentHP = m_nMaxHP;
    
    m_nAddedMinAttack = (int)(m_nAddedMinAttack*dc.GetLongValue()*1.5f) + (nodeDepth-1)*10 + (int)((currentDepth-1)*0.5f);
    m_nAddedMaxAttack = m_nAddedMaxAttack*dc.GetLongValue() + (nodeDepth-1)*10 + (int)(currentDepth-1);
    
    m_nAttackDiceNum = m_nAttackDiceNum + (dc-1)*2;
    m_nAttackDiceFaceNum = m_nAttackDiceFaceNum + dc*2;
    
    m_nArmorClass = m_nArmorClass - (dc-1)*m_nBaseArmorClass.GetLongValue()*10 - (nodeDepth-1)*5 - (currentDepth-1) * 2;
    
    m_fBlockRate = MIN(m_fBlockRate + m_fBlockRate*(nodeDepth-1)*0.5f + m_fBlockRate*(dc-1)*5, 0.2f);
    m_fCriticalStrikeRate = MIN(m_fCriticalStrikeRate + m_fCriticalStrikeRate*(nodeDepth-1)*0.5f + m_fCriticalStrikeRate*(dc-1)*5, 0.3f);
    m_fDodgeRate = MIN(m_fDodgeRate + m_fDodgeRate*(nodeDepth-1)*0.5f + m_fDodgeRate*(dc-1)*5, 0.2f);
    
    float rand = cocos2d::rand_0_1();
    if(rand < 0.1f)
        m_nDropItemNum = 1;
    else if(rand > 0.95f)
        m_nDropItemNum = 2;
    else
        m_nDropItemNum = 0;
    
    if(m_bIsElite)
        m_nDropItemNum = 4;
}
CChaosNumber MonsterProperty::getRandomAttack()
{
    return cocos2d::random(getMinAttack().GetLongValue(), getMaxAttack().GetLongValue());
}