//
//  MonsterPropLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#include "MonsterPropLayer.hpp"
#include "BaseMonster.hpp"
#include "UtilityHelper.h"
#include "PopupUILayerManager.h"
USING_NS_CC;
MonsterPropLayer::MonsterPropLayer()
{
    m_pMonster = nullptr;
}
MonsterPropLayer::~MonsterPropLayer()
{
    
}
bool MonsterPropLayer::initUi()
{
    if (!load("monsterInfoLayer.csb",false))
        return false;
    setContentSize(m_pRootNode->getContentSize());
    m_pRootNode->setPosition(getContentSize()*0.5);
    return true;
}
bool MonsterPropLayer::addEvents()
{
    
    if(!CharacterPropLayer::addEvents())
        return false;
    
    m_pCharacterHpBar->setDirection(cocos2d::ui::LoadingBar::Direction::RIGHT);
    m_pCharacterMpBar->setDirection(cocos2d::ui::LoadingBar::Direction::RIGHT);
    
    m_pCharacterCurMp->setString("??");
    m_pCharacterMaxMp->setString("/??");
    return true;
}

void MonsterPropLayer::updateCharacterBuff()
{
    
}

void MonsterPropLayer::updateCharacterProp()
{

    if (!m_pMonster)
        return;
    if (m_pMonster->getState() != BaseMonster::MonsterState::MS_DEATH)
    {
        this->setVisible(true);
        float hpPer =m_pMonster->getMonsterProperty()->getCurrentHP().GetFloatValue()/m_pMonster->getMonsterProperty()->getMaxHP().GetFloatValue() *100.0f;
        m_pCharacterHpBar->setPercent(hpPer);
        m_pCharacterCurHp->setString(StringUtils::format("%d",int(m_pMonster->getMonsterProperty()->getCurrentHP())));
        m_pCharacterMaxHp->setString(StringUtils::format("/%d",int(m_pMonster->getMonsterProperty()->getMaxHP())));
        m_pCharacterLevel->setString(StringUtils::format("%d",int(m_pMonster->getMonsterProperty()->getLevel())));
        std::string monsterName =UtilityHelper::getLocalString(MONSTER_MODEL_NAMES[m_pMonster->getMonsterType()]);
        if (m_pMonster->getMonsterProperty()->isElite()) {
            m_pCharacterName->setColor(PopupUILayerManager::getInstance()->getTipsColor(TIP_POSITIVE));
            monsterName = StringUtils::format(UtilityHelper::getLocalStringForUi("MONSTER_ELITE_NAME").c_str(),monsterName.c_str());
        }else{
            m_pCharacterName->setColor(PopupUILayerManager::getInstance()->getTipsColor(TIP_DEFAULT));
        }
        m_pCharacterIcon->loadTexture(m_pMonster->getIconRes(),TextureResType::PLIST);
        m_pCharacterIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pCharacterName->setString(monsterName);
    }else
    {
        m_pCharacterHpBar->setPercent(100);
    }
    m_pMonster =nullptr;
}