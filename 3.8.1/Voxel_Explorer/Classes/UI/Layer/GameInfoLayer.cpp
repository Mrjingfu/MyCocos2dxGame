//
//  GameInfoLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#include "GameInfoLayer.hpp"
#include "UtilityHelper.h"
#include "RandomDungeon.hpp"
#include "PlayerProperty.hpp"
USING_NS_CC;
GameInfoLayer::GameInfoLayer()
{
    m_pGameGoldNum = nullptr;
    m_pGameSilverNum = nullptr;
    m_pGameCopperNum = nullptr;
    m_pGameLevelInfoName = nullptr;
}
GameInfoLayer::~GameInfoLayer()
{
    
}
bool GameInfoLayer::initUi()
{
    if (!load("gameinfoLayer.csb",false))
        return false;
    setContentSize(m_pRootNode->getContentSize());
    m_pRootNode->setPosition(getContentSize()*0.5);
    return true;
}
bool GameInfoLayer::addEvents()
{
    m_pGameGoldNum   = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_gold_num"));
    if (!m_pGameGoldNum)
        return false;
    m_pGameSilverNum    = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_silver_num"));
    if (!m_pGameSilverNum)
        return false;
    m_pGameCopperNum    = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_copper_num"));
    if (!m_pGameCopperNum)
        return false;
    
    m_pGameLevelInfoName    = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "game_level_info_name"));
    if (!m_pGameLevelInfoName)
        return false;
    
    
    m_pGameLevelInfoName->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pGameGoldNum->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pGameSilverNum->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pGameCopperNum->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    
    return true;
}

void GameInfoLayer::refreshUIView()
{
    if(RandomDungeon::getInstance()->getCurrentDungeonNode()->isBossDepth())
        m_pGameLevelInfoName->setString(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_strDungeonBossName.c_str());
    else
        m_pGameLevelInfoName->setString(StringUtils::format("%s %d",RandomDungeon::getInstance()->getCurrentDungeonNode()->m_strDungeonName.c_str(),int(RandomDungeon::getInstance()->getCurrentDungeonNode()->m_nCurrentDepth)));
    CCLOG(" gold: %s",StringUtils::format("%d",int(PlayerProperty::getInstance()->getGold())).c_str());
    CCLOG(" silver: %s",StringUtils::format("%d",int(PlayerProperty::getInstance()->getGold())).c_str());
    CCLOG(" copper: %s",StringUtils::format("%d",int(PlayerProperty::getInstance()->getGold())).c_str());
    
    
    m_pGameGoldNum->setString(StringUtils::format("%d",int(PlayerProperty::getInstance()->getGold())));
    m_pGameSilverNum->setString(StringUtils::format("%d",int(PlayerProperty::getInstance()->getSilver())));
    m_pGameCopperNum->setString(StringUtils::format("%d",int(PlayerProperty::getInstance()->getCopper())));

}


