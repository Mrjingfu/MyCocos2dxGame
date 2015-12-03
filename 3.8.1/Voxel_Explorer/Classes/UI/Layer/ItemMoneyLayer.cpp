//
//  ItemMoneyLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/2.
//
//

#include "ItemMoneyLayer.hpp"
#include "UtilityHelper.h"
#include "GameFormula.hpp"
USING_NS_CC;
ItemMoneyLayer::ItemMoneyLayer()
{
    m_pItemGoldNum= nullptr;
    m_pItemSilverNum= nullptr;
    m_pItemCopperNum= nullptr;
    m_pItemGoldIcon = nullptr;
    m_pItemSilverIcon= nullptr;
    m_pItemCopperIcon= nullptr;
}
ItemMoneyLayer::~ItemMoneyLayer()
{
    
}
bool ItemMoneyLayer::initUi()
{
    if (!WrapperUILayer::initUi())
        return false;
     if(!load("itemMoneyLayer.csb",false))
         return false;
    setContentSize(m_pRootNode->getContentSize());
    m_pRootNode->setPosition(getContentSize()*0.5);
    return true;
}
bool ItemMoneyLayer::addEvents()
{
    if (!WrapperUILayer::addEvents())
        return false;
    
    m_pItemGoldIcon =   dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_gold_icon"));
    if (!m_pItemGoldIcon)
        return false;
    
    m_pItemSilverIcon =   dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_silver_icon"));
    if (!m_pItemSilverIcon)
        return false;
    
    m_pItemCopperIcon =   dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_copper_icon"));
    if (!m_pItemCopperIcon)
        return false;
    
    m_pItemGoldNum = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_gold_num"));
    if (!m_pItemGoldNum)
        return false;
    
    m_pItemSilverNum = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_silver_num"));
    if (!m_pItemSilverNum)
        return false;
    
    m_pItemCopperNum = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_copper_num"));
    if (!m_pItemCopperNum)
        return false;
    
    ui::Text* m_pItemMoneyDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_money_desc"));
    if (!m_pItemMoneyDesc)
        return false;
    m_pItemMoneyDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemMoneyDesc->setString(UtilityHelper::getLocalStringForUi("ITEM_MONEY_DESC"));

    
    return true;
}

void ItemMoneyLayer::updateItemMoney(CChaosNumber money)
{
    CChaosNumber goldNum = 0;
    CChaosNumber silverNum = 0;
    CChaosNumber copperNum = 0;
    GameFormula::exchangeMoney(money, goldNum, silverNum, copperNum);
    CCLOG("=======%d=====, %d, %d, %d", (int)(money), (int)(goldNum.GetLongValue()), (int)(silverNum.GetLongValue()), (int)(copperNum.GetLongValue()));
   
    m_pItemGoldNum->setString(StringUtils::format("%d",int(goldNum)));
    m_pItemSilverNum->setString(StringUtils::format("%d",int(silverNum)));
    m_pItemCopperNum->setString(StringUtils::format("%d",int(copperNum)));
    
    
//    if (goldNum > 0) {
//        m_pItemGoldIcon->setVisible(true);
//        m_pItemGoldNum->setString(StringUtils::format("%d",int(goldNum)));
//        m_pItemSilverIcon->setVisible(true);
//        m_pItemSilverNum->setString(StringUtils::format("%d",int(silverNum)));
//        m_pItemCopperIcon->setVisible(true);
//        m_pItemCopperNum->setString(StringUtils::format("%d",int(copperNum)));
//    }
//    else if (silverNum > 0) {
//        m_pItemSilverIcon->setVisible(true);
//        m_pItemSilverNum->setString(StringUtils::format("%d",int(silverNum)));
//        m_pItemCopperIcon->setVisible(true);
//        m_pItemCopperNum->setString(StringUtils::format("%d",int(copperNum)));
//    }
//    else if (copperNum > 0) {
//        m_pItemCopperIcon->setVisible(true);
//        m_pItemCopperNum->setString(StringUtils::format("%d",int(copperNum)));
//    }
    
}