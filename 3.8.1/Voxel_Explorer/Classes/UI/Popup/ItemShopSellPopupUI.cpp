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
#include "AlertPopupUI.hpp"
#include "PopupUILayerManager.h"
ItemShopSellPopupUI::ItemShopSellPopupUI()
{
    
}
ItemShopSellPopupUI::~ItemShopSellPopupUI()
{
    
}


PickableItemProperty* ItemShopSellPopupUI::getItemIdProperty() const
{
    if (m_nItemId!=-2) {
        return PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    }
    return nullptr;
}

void ItemShopSellPopupUI::refreshUIView()
{
    ItemPopupUI::refreshUIView();
    PickableItemProperty* itemprop = getItemIdProperty();
    
    if (!itemprop)
        return;
    int count = itemprop->getCount();
    if (itemprop->isStackable() && count >1) {
        
        m_pItemSlider->setMaxPercent(count-1);
        m_pItemSlider->setPercent(m_pItemSlider->getMaxPercent());
        m_pSellCount->setString(cocos2d::StringUtils::format(UtilityHelper::getLocalStringForUi("ITEM_SPLITE_COUNT").c_str(),1+m_pItemSlider->getPercent()));
        m_pBtnEquip->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
        m_pBtnEquip->setPosition(cocos2d::Vec2(m_pBottomFrame->getContentSize().width*0.045,m_pBtnEquip->getPositionY()));
        
    }else
    {
        m_pItemSlider->setVisible(false);
        m_pSellCount->setVisible(false);
        m_pBtnEquip->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
       m_pBtnEquip->setPosition(cocos2d::Vec2(m_pBottomFrame->getContentSize().width*0.5,m_pBtnEquip->getPositionY()));
        
    }
    m_pBtnEquip->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_SELL"));
    m_pBtnEquip->getTitleRenderer()->setScale(0.7);
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
void ItemShopSellPopupUI::itemSell()
{
    bool isSuccess = false;
    PickableItemProperty* itemprop = getItemIdProperty();
    if (!itemprop) {
        isSuccess = false;
    }else
    {
        
        int count =1;
        if (itemprop->isStackable()) {
            count = m_pItemSlider->getPercent() +1;
        }
        CCLOG("onClickSell count:%d",count);
        isSuccess = PlayerProperty::getInstance()->sellItemFromBag(itemprop, count);
    }
    
    if (isSuccess) {
        CCLOG("贩卖成功");
        closePopup();
    }else
    {
        CCLOG("贩卖失败");
    }
}
void ItemShopSellPopupUI::onClickSell(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickSell");
    PickableItemProperty* itemprop = getItemIdProperty();
    if (itemprop)
    {
        if (itemprop->getQuality() >=PICKABLEITEM_QUALITY::PIQ_RARE || !itemprop->isIdentified())
        {
            
            AlertPopupUI* popupUILayer = static_cast<AlertPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupAlert));
            if (popupUILayer)
            {
                PopupUILayer* pplayer = nullptr;
                if (PopupUILayerManager::getInstance()->isOpenPopup(ePopupItemShopSell, pplayer)) {
                    pplayer->getRootNode()->setVisible(false);
                }
                this->getRootNode()->setVisible(false);
                
                popupUILayer->setMessage(UtilityHelper::getLocalStringForUi("ITEM_BAG_SELL"));
                popupUILayer->setPositiveListerner([this](Ref*){
                    
                    this->itemSell();
                });
                popupUILayer->setNegativeListerner([this,pplayer](Ref*)
                                                   {
                                                       if (pplayer)
                                                       {
                                                           pplayer->getRootNode()->setVisible(true);
                                                       }
                                                       this->getRootNode()->setVisible(true);
                                                   });
                popupUILayer->setDarkLayerVisble(false);
            }
        }else
            itemSell();
    }
}
