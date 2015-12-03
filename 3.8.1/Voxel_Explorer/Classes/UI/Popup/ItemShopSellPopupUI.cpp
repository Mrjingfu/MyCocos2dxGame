//
//  ItemShopPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#include "ItemShopSellPopupUI.hpp"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "GameFormula.hpp"
#include "NpcDataManager.hpp"
#include "ItemMoneyLayer.hpp"
ItemShopSellPopupUI::ItemShopSellPopupUI()
{
    
}
ItemShopSellPopupUI::~ItemShopSellPopupUI()
{
    
}
bool ItemShopSellPopupUI::initUi()
{
    return this->load("itemShopPopupLayer.csb",false);
}
bool ItemShopSellPopupUI::addEvents()
{
    if (!ItemPopupUI::addEvents())
        return false;
    m_pItemSlider = dynamic_cast<cocos2d::ui::Slider*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_shop_slider"));
    if (!m_pItemSlider)
        return false;;
    m_pSellCount =  dynamic_cast<cocos2d::ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_shop_item_count"));
    if (!m_pSellCount)
        return false;
    
    m_pSellCount->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemSlider->addEventListener(CC_CALLBACK_2(ItemShopSellPopupUI::sliderEvent, this));
    
    return true;
}
PickableItemProperty* ItemShopSellPopupUI::getItemIdProperty() const
{
    if (m_nItemId!=-2) {
        return PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    }
    return nullptr;
}
void ItemShopSellPopupUI::updateItemPopup(int itemId)
{
    ItemPopupUI::updateItemPopup(itemId);

    m_pBtnDiscard->setVisible(false);
    
    PickableItemProperty* itemprop = getItemIdProperty();
    
    if (!itemprop)
        return;
    int count = itemprop->getCount();
    if (itemprop->isStackable() && count >1) {
        
        m_pItemSlider->setMaxPercent(count-1);
        m_pItemSlider->setPercent(m_pItemSlider->getMaxPercent());
        m_pSellCount->setString(cocos2d::StringUtils::format(UtilityHelper::getLocalStringForUi("ITEM_SPLITE_COUNT").c_str(),1+m_pItemSlider->getPercent()));
        
    }else
    {
        m_pItemSlider->setVisible(false);
        m_pSellCount->setVisible(false);
        m_pBtnEquip->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.5,m_pBtnEquip->getPositionY()));
        
    }
    //暂时
    cocos2d::Label* btnLabel =  m_pBtnEquip->getTitleRenderer();
    btnLabel->setSystemFontName(UtilityHelper::getLocalStringForUi("FONT_NAME"));

    btnLabel->setString("SELL");
    m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemShopSellPopupUI::onClickSell, this));
    
     m_pItemMoneyLayer->updateItemMoney(itemprop->getValueCopper()*(1+m_pItemSlider->getPercent()));
}
void ItemShopSellPopupUI::sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        cocos2d::ui::Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
        if (slider && m_pSellCount) {
            m_pSellCount->setString(cocos2d::StringUtils::format(UtilityHelper::getLocalStringForUi("ITEM_SPLITE_COUNT").c_str(),1+m_pItemSlider->getPercent()));
            
            PickableItemProperty* itemprop = getItemIdProperty();
            if (!itemprop)
                return;

             m_pItemMoneyLayer->updateItemMoney(itemprop->getValueCopper()*(1+m_pItemSlider->getPercent()));
        }
    }
}

void ItemShopSellPopupUI::onClickSell(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickSell");
}
