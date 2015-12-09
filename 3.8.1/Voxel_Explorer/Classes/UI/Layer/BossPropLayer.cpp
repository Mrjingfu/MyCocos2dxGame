//
//  MonsterPropLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#include "BossPropLayer.hpp"
#include "BaseMonster.hpp"
#include "UtilityHelper.h"
#include "PopupUILayerManager.h"
#include "BaseBoss.hpp"
USING_NS_CC;
BossPropLayer::BossPropLayer()
{
    m_pBoss = nullptr;
}
BossPropLayer::~BossPropLayer()
{
    
}
bool BossPropLayer::initUi()
{
    if (!load("monsterInfoLayer.csb",false))
        return false;
    setContentSize(m_pRootNode->getContentSize());
    m_pRootNode->setPosition(getContentSize()*0.5);
    return true;
}
bool BossPropLayer::addEvents()
{
    
    if(!CharacterPropLayer::addEvents())
        return false;
    
    m_pCharacterHpBar->setDirection(cocos2d::ui::LoadingBar::Direction::RIGHT);
    m_pCharacterMpBar->setDirection(cocos2d::ui::LoadingBar::Direction::RIGHT);
    
    m_pCharacterCurMp->setString("??");
    m_pCharacterMaxMp->setString("/??");
    m_pCharacterLevel->setString("???");
    return true;
}

void BossPropLayer::updateCharacterBuff()
{
    
}

void BossPropLayer::updateCharacterProp()
{

    if (!m_pBoss)
        return;
    if (m_pBoss->getState() != BaseBoss::BossState::BS_DEATH)
    {
        
        float hpPer =m_pBoss->getBossProperty()->getCurrentHP().GetFloatValue()/m_pBoss->getBossProperty()->getMaxHP().GetFloatValue() *100.0f;
        m_pCharacterHpBar->setPercent(hpPer);
        m_pCharacterCurHp->setString(StringUtils::format("%d",int(m_pBoss->getBossProperty()->getCurrentHP())));
        m_pCharacterMaxHp->setString(StringUtils::format("/%d",int(m_pBoss->getBossProperty()->getMaxHP())));
        std::string BossName =m_pBoss->getDesc();
        m_pCharacterName->setColor(PopupUILayerManager::getInstance()->getTipsColor(TIP_POSITIVE));
        m_pCharacterIcon->loadTexture(m_pBoss->getIconRes(),TextureResType::PLIST);
        m_pCharacterIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pCharacterName->setString(BossName);
    }else
    {
        m_pCharacterHpBar->setPercent(100);
    }
    m_pBoss =nullptr;
}