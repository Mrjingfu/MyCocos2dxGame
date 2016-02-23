//
//  BossProperty.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/8.
//
//

#include "BossProperty.hpp"
#include "RandomDungeon.hpp"
#include "AlisaMethod.h"
USING_NS_CC;

BossProperty::BossProperty()
{
    m_nValueCopper          = 0;                    ///价值铜币
    m_nMaxHP                = 100;                   ///最大生命值
    m_nCurrentHP            = 100;                   ///当前生命值
    m_nAddedMinAttack       = 0;                    ///额外最小攻击增加值
    m_nAddedMaxAttack       = 0;                    ///额外最大攻击增加值
    m_nAttackDiceNum        = 1;                    ///攻击骰子数
    m_nAttackDiceFaceNum    = 4;                    ///攻击骰子面数
    m_nArmorClass           = 4;                    ///防御等级
    m_nBaseArmorClass       = 4;                    ///基础防御等级
    m_fBlockRate            = 0.01f;                ///格挡率
    m_fCriticalStrikeRate   = 0.02f;                ///暴击率
    m_fDodgeRate            = 0.01f;                ///闪避率
    
    m_nAttackAddBuffer            = PB_NONE;          ///默认附加状态
    
    m_fFactor = 1.0f;
}
BossProperty::~BossProperty()
{
}

CChaosNumber BossProperty::getMinAttack()
{
    return (m_nAttackDiceNum + m_nAddedMinAttack.GetLongValue()) * m_fFactor.GetFloatValue();
}
CChaosNumber BossProperty::getMaxAttack()
{
    return (m_nAttackDiceNum*m_nAttackDiceFaceNum.GetLongValue() + m_nAddedMaxAttack.GetLongValue()) * m_fFactor.GetFloatValue();
}
CChaosNumber BossProperty::getDefense()
{
    return (-m_nArmorClass.GetLongValue() + m_nBaseArmorClass.GetLongValue())* m_fFactor.GetFloatValue();
}
void BossProperty::setCurrentHP(CChaosNumber hp)
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
void BossProperty::adjustByDC()
{
    if(RandomDungeon::getInstance()->getCurrentDungeonNode() == nullptr)
        return;
    
    CChaosNumber dc = RandomDungeon::getInstance()->getDifficultClass();
    CChaosNumber nodeDepth = RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nNodeDepth;
    CChaosNumber maxDepth = RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nTotalNum;
    
    m_nValueCopper = (dc-1)*10000 + (nodeDepth-1)*1000 + maxDepth * cocos2d::random(100, 200);
    
    m_nMaxHP = m_nMaxHP + (dc-1)*cocos2d::random(500, 600) + (nodeDepth-1)*cocos2d::random(200, 300) + cocos2d::random(300, 400);
    m_nCurrentHP = m_nMaxHP;
    
    m_nAddedMinAttack = m_nAddedMinAttack + (dc-1)*40 + (nodeDepth-1)*20;
    m_nAddedMaxAttack = m_nAddedMaxAttack + (dc-1)*60 + + (nodeDepth-1)*40;
    
    m_nAttackDiceNum = m_nAttackDiceNum + (dc-1)*5 + (nodeDepth-1)*2 + 2;
    m_nAttackDiceFaceNum = m_nAttackDiceFaceNum + (nodeDepth-1)*4 + maxDepth*2;
    
    m_nArmorClass = m_nArmorClass - (dc-1)*m_nBaseArmorClass.GetLongValue()*40 - (nodeDepth-1)*20 - maxDepth*4;
    
    m_fBlockRate = MIN(m_fBlockRate + m_fBlockRate*(nodeDepth-1)*0.5f + m_fBlockRate*(dc-1)*5.0f, 0.5f);
    m_fCriticalStrikeRate = MIN(m_fCriticalStrikeRate + m_fCriticalStrikeRate*(nodeDepth-1)*0.5f + m_fCriticalStrikeRate*(dc-1)*5.0f, 0.4f);
    m_fDodgeRate = MIN(m_fDodgeRate + m_fDodgeRate*(nodeDepth-1)*0.5f + m_fDodgeRate*(dc-1)*5.0f, 0.3f);
    
    CCLOG("%f, %f, %f",m_fBlockRate.GetFloatValue(), m_fCriticalStrikeRate.GetFloatValue(), m_fDodgeRate.GetFloatValue());
}
CChaosNumber BossProperty::getRandomAttack()
{
    return cocos2d::random(getMinAttack().GetLongValue(), getMaxAttack().GetLongValue());
}
void BossProperty::addAttackAddBuffer(PlayerBuffer buff)
{
    m_nAttackAddBuffer = m_nAttackAddBuffer | buff;
}
void BossProperty::removeAttackAddBuffer(PlayerBuffer buff)
{
    m_nAttackAddBuffer = m_nAttackAddBuffer &~ buff;
}