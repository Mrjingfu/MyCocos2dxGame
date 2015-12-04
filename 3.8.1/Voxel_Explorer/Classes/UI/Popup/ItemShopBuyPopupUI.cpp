//
//  ItemShopPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#include "ItemShopBuyPopupUI.hpp"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "GameFormula.hpp"
#include "NpcDataManager.hpp"
#include "ItemMoneyLayer.hpp"
ItemShopBuyPopupUI::ItemShopBuyPopupUI()
{
    
}
ItemShopBuyPopupUI::~ItemShopBuyPopupUI()
{
    
}

PickableItemProperty* ItemShopBuyPopupUI::getItemIdProperty() const
{
    if (m_nItemId!=-2) {
        if (m_eShopType == ShopPopupUI::ST_GAMBLE)
        {
            return NpcDataManager::getInstance()->getItemFromTheifRoom(CChaosNumber(m_nItemId));
            
        }else if (m_eShopType == ShopPopupUI::ST_WEAPON)
        {
            return NpcDataManager::getInstance()->getItemFromEquipMentShop(CChaosNumber(m_nItemId));
            
        }else if(m_eShopType == ShopPopupUI::ST_MAGIC)
        {
            return NpcDataManager::getInstance()->getItemFromMagicShop(CChaosNumber(m_nItemId));
        }
        
    }
    return nullptr;
}
bool ItemShopBuyPopupUI::initBottom()
{
    cocos2d::Node*     m_pBottomNode = cocos2d::CSLoader::createNode("itemShopBottomLayer.csb");
    if (!m_pBottomNode)
        return false;
    
    m_pBottomFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pBottomNode, "item_bottom_Layer"));
    if (!m_pBottomFrame)
        return false;
    
    m_pBtnEquip = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pBottomNode, "item_btn_equip"));
    if (!m_pBtnEquip)
        return false;
    
    m_pItemSlider = dynamic_cast<cocos2d::ui::Slider*>(UtilityHelper::seekNodeByName(m_pBottomNode, "item_shop_slider"));
    if (!m_pItemSlider)
        return false;;
    m_pSellCount =  dynamic_cast<cocos2d::ui::Text*>(UtilityHelper::seekNodeByName(m_pBottomNode, "item_shop_item_count"));
    if (!m_pSellCount)
        return false;
    
    m_pSellCount->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemSlider->addEventListener(CC_CALLBACK_2(ItemShopBuyPopupUI::sliderEvent, this));
    
    m_pBottomFrame->removeFromParentAndCleanup(false);
    return true;

}
void ItemShopBuyPopupUI::setItemShopProp(ShopPopupUI::eShopType type,int itemId)
{
     m_eShopType = type;
     m_nItemId = itemId;
   
    refreshUIView();
}
void ItemShopBuyPopupUI::refreshUIView()
{
    ItemPopupUI::refreshUIView();
    
    
    PickableItemProperty* itemprop = getItemIdProperty();
    if (!itemprop)
        return;
    
    m_pItemMoneyLayer->updateItemMoney(itemprop->getCopperWhenBuy());
    
    int count = itemprop->getCount();
    if (itemprop->isStackable() && count >1) {
        
        m_pItemSlider->setMaxPercent(count-1);
        m_pItemSlider->setPercent(m_pItemSlider->getMaxPercent());
        m_pSellCount->setString(cocos2d::StringUtils::format(UtilityHelper::getLocalStringForUi("ITEM_SPLITE_COUNT").c_str(),1+m_pItemSlider->getPercent()));
        
    }else
    {
        m_pItemSlider->setVisible(false);
        m_pSellCount->setVisible(false);
        m_pBtnEquip->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
        m_pBtnEquip->setPosition(cocos2d::Vec2(m_pBottomFrame->getContentSize().width*0.5,m_pBtnEquip->getPositionY()));
        
    }
    //暂时
    cocos2d::Label* btnLabel =  m_pBtnEquip->getTitleRenderer();
    btnLabel->setSystemFontName(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    
    btnLabel->setString("BUY");
    m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemShopBuyPopupUI::onClickBuy, this));
    m_pItemMoneyLayer->updateItemMoney(itemprop->getCopperWhenBuy()*(1+m_pItemSlider->getPercent()));
}
void ItemShopBuyPopupUI::sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        cocos2d::ui::Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
        if (slider && m_pSellCount) {
            m_pSellCount->setString(cocos2d::StringUtils::format(UtilityHelper::getLocalStringForUi("ITEM_SPLITE_COUNT").c_str(),1+m_pItemSlider->getPercent()));
            
            PickableItemProperty* itemprop = getItemIdProperty();
            if (!itemprop)
                return;

             m_pItemMoneyLayer->updateItemMoney(itemprop->getCopperWhenBuy()*(1+m_pItemSlider->getPercent()));
        }
    }
}

void ItemShopBuyPopupUI::onClickBuy(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickBuy");
    bool isSuccess = false;
    PickableItemProperty* buyItemProperty = getItemIdProperty();
    if (!buyItemProperty) {
        isSuccess =false;
    }else
    {
        int count =1;
        if (buyItemProperty->isStackable()) {
            count = m_pItemSlider->getPercent() +1;
        }
        CCLOG("onClickBuy count:%d",count);
        if (m_eShopType == ShopPopupUI::eShopType::ST_GAMBLE) {
            isSuccess = PlayerProperty::getInstance()->buyItemToBag(buyItemProperty, CChaosNumber(count),true);
        }else
            isSuccess = PlayerProperty::getInstance()->buyItemToBag(buyItemProperty, CChaosNumber(count));

    }
    
    if (isSuccess) {
        int itemid = buyItemProperty->getInstanceID();
        int isRemoveSucces = false;
        if (m_eShopType == ShopPopupUI::ST_GAMBLE)
        {
            isRemoveSucces = NpcDataManager::getInstance()->removeItemFromTheifRoomList(itemid);
            
        }else if (m_eShopType == ShopPopupUI::ST_WEAPON)
        {
            isRemoveSucces = NpcDataManager::getInstance()->removeItemFromEquipmentShopList(itemid);
            
        }else if(m_eShopType == ShopPopupUI::ST_MAGIC)
        {
            isRemoveSucces = NpcDataManager::getInstance()->removeItemFromMagicShopList(itemid);
            
        }else if (m_eShopType==ShopPopupUI::ST_ALCHEMY)
        {
            isRemoveSucces = NpcDataManager::getInstance()->removeItemFromAlchemistRoomList(itemid);
        }
        if (isRemoveSucces) {
             CCLOG("购买成功");
        }
    }else
    {
         CCLOG("购买失败");
    }
    
   
    closePopup();
}

