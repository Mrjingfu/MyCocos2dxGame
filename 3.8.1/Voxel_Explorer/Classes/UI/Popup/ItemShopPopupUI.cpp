//
//  ItemShopPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#include "ItemShopPopupUI.hpp"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "GameFormula.hpp"
ItemShopPopupUI::ItemShopPopupUI()
{
    
}
ItemShopPopupUI::~ItemShopPopupUI()
{
    
}
bool ItemShopPopupUI::initUi()
{
    return this->load("itemShopPopupLayer.csb",false);
}
bool ItemShopPopupUI::addEvents()
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
    m_pItemSlider->addEventListener(CC_CALLBACK_2(ItemShopPopupUI::sliderEvent, this));
    
    return true;
}
void ItemShopPopupUI::updateItemPopup(eItemShopType type,int itemId)
{
    ItemPopupUI::updateItemPopup(itemId);

    m_pBtnDiscard->setVisible(false);
    
    PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    
    if (!itemprop)
        return;
    int count = itemprop->getCount();
    if (itemprop->isStackable() && count >1) {
        
        
        if (type==IST_BUY) {
            //暂时
            count = 15;
        }
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

    
    if (type==IST_SELL)
    {
        btnLabel->setString("SELL");
        m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemShopPopupUI::onClickSell, this));
    }else if (type == IST_BUY)
    {
        btnLabel->setString("BUY");
        m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemShopPopupUI::onClickBuy, this));
    }

    updateItemMoney(itemprop->getValueCopper()*(1+m_pItemSlider->getPercent()));
}
void ItemShopPopupUI::sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        cocos2d::ui::Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
        if (slider && m_pSellCount) {
            m_pSellCount->setString(cocos2d::StringUtils::format(UtilityHelper::getLocalStringForUi("ITEM_SPLITE_COUNT").c_str(),1+m_pItemSlider->getPercent()));
            
            PickableItemProperty* itemprop = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
            if (!itemprop)
                return;

            updateItemMoney(itemprop->getValueCopper()*(1+m_pItemSlider->getPercent()));
        }
    }
}

void ItemShopPopupUI::onClickBuy(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickBuy");
}

void ItemShopPopupUI::onClickSell(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickSell");
}
