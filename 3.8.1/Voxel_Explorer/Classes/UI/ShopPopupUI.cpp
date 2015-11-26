//
//  ShopPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "ShopPopupUI.h"
#include "BagLayer.h"
#include "UtilityHelper.h"
#include "PickableItemProperty.hpp"
#include "PlayerProperty.hpp"
#include "BagMangerLayerUI.h"
ShopPopupUI::ShopPopupUI()
{
    m_cActionType       = eNone;
    m_pBagLayer         = nullptr;
    m_pBtnAllBag        = nullptr;
    m_pBtnWeaponBag     = nullptr;
    m_pBtnPotionBag     = nullptr;
    m_pShopMangerLayer  = nullptr;
    m_pShopGridView     = nullptr;
    m_pBtnBuyFrame      = nullptr;
    m_pBtnSellFrame     = nullptr;
}
ShopPopupUI::~ShopPopupUI()
{
    
}
bool ShopPopupUI::init()
{
    if (PopupUILayer::init()) {
         return this->load("shopPopupLayer.csb",false);
    }
    
    return false;
    
}
bool ShopPopupUI::addEvents()
{
    cocos2d::ui::ImageView* m_shopFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "shop_bg_frame"));
    if (!m_shopFrame)
        return false;
    
    cocos2d::ui::ImageView* m_girdFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "shop_grid_frame"));
    if (!m_girdFrame)
        return false;
    
    m_pBtnWeaponBag= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "shop_prop_btn_bag_wepon"));
    if (!m_pBtnWeaponBag)
        return false;
    m_pBtnPotionBag = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "shop_prop_btn_bag_poition"));
    if (!m_pBtnPotionBag)
        return false;
    m_pBtnAllBag= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "shop_prop_btn_bag_all"));
    if (!m_pBtnAllBag)
        return false;
    
    m_pBtnBuyFrame= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "shop_prop_btn_frame_buy"));
    if (!m_pBtnBuyFrame)
        return false;
    
    m_pBtnSellFrame= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "shop_prop_btn_frame_sell"));
    if (!m_pBtnSellFrame)
        return false;
    
    m_pShopGridView = TGridView::create();
    m_pShopGridView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pShopGridView->setContentSize(cocos2d::Size(m_shopFrame->getContentSize().width-10,m_shopFrame->getContentSize().height-7));
    m_pShopGridView->setCol(5);
    m_pShopGridView->setPosition(m_shopFrame->getContentSize()*0.5);
    m_pShopGridView->setScrollBarWidth(5);
    m_pShopGridView->setScrollBarColor(Color3B::WHITE);
    m_pShopGridView->setScrollBarPositionFromCornerForVertical(cocos2d::Vec2(0,0));
//    m_pShopGridView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    m_pShopGridView->setItemsMargin(cocos2d::Size(1,5));
    m_pShopGridView->setFrameMargin(cocos2d::Size(7,15));
    m_pShopGridView->addEventListener(CC_CALLBACK_2(ShopPopupUI::selectItemEvent, this));
    m_pShopGridView->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_shopFrame->addChild(m_pShopGridView);

    for (int j =0; j<15; j++) {
        
        ImageView* itemui = ImageView::create();
        itemui->setTouchEnabled(true);
        itemui->setScale9Enabled(true);
        itemui->setContentSize(cocos2d::Size(45,45));
        itemui->loadTexture("ui_frame_5.png",TextureResType::PLIST);
        itemui->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pShopGridView->pushBackCustomItem(itemui);
    }
    m_pShopGridView->forceDoLayout();
    
    m_pShopMangerLayer = BagMangerLayerUI::create(m_pShopGridView->getInnerContainerSize());
    m_pShopMangerLayer->setPosition(m_pShopGridView->getContentSize()*0.5);
    m_pShopMangerLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pShopGridView->addChildLayer(m_pShopMangerLayer,60);
    
    m_pBagLayer = BagLayer::create(m_girdFrame->getContentSize());
    m_pBagLayer->setPosition(m_girdFrame->getContentSize()*0.5);
    m_girdFrame->addChild(m_pBagLayer);
    
    m_pBtnBuyFrame->loadTextures(UtilityHelper::getLocalStringForUi("SHOP_BTN_FRAME_BUY_NORMAL"), UtilityHelper::getLocalStringForUi("SHOP_BTN_FRAME_BUY_PRESS"),UtilityHelper::getLocalStringForUi("SHOP_BTN_FRAME_BUY_PRESS"),TextureResType::PLIST);
    m_pBtnSellFrame->loadTextures(UtilityHelper::getLocalStringForUi("SHOP_BTN_FRAME_SELL_NORMAL"), UtilityHelper::getLocalStringForUi("SHOP_BTN_FRAME_SELL_PRESS"),UtilityHelper::getLocalStringForUi("SHOP_BTN_FRAME_SELL_PRESS"),TextureResType::PLIST);
    m_pBtnBuyFrame->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pBtnSellFrame->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pBtnWeaponBag->addTouchEventListener(CC_CALLBACK_2(ShopPopupUI::onClickSortEquip, this));
    m_pBtnPotionBag->addTouchEventListener(CC_CALLBACK_2(ShopPopupUI::onClickSortPotion, this));
    m_pBtnAllBag->addTouchEventListener(CC_CALLBACK_2(ShopPopupUI::onClickSortAll, this));
    m_pBtnBuyFrame->addTouchEventListener(CC_CALLBACK_2(ShopPopupUI::onClickFrameBuy, this));
    m_pBtnSellFrame->addTouchEventListener(CC_CALLBACK_2(ShopPopupUI::onClickFrameSell, this));

    
    updateItems();
    
    return true;
}

void ShopPopupUI::updateItems()
{
    if (m_pBagLayer) {
        BagLayer::eSortBagType sortType = BagLayer::SBT_ALL;
        if (!m_pBtnWeaponBag->isEnabled())
        {
            sortType = BagLayer::SBT_EQUIP;
            
        }else if (!m_pBtnPotionBag->isEnabled())
        {
            sortType = BagLayer::SBT_POTION;
        }
        m_pBagLayer->updateBagProp(false, sortType);
    }
    
    if (!m_pBtnBuyFrame->isEnabled()) {
        updateShopBuyItems();
    }else if(!m_pBtnSellFrame->isEnabled()){
         updateShopSellItems();
    }
   
}
void ShopPopupUI::updateShopBuyItems()
{
    if (!m_pBagLayer || !m_pShopGridView)
        return;
    if (m_pShopMangerLayer) {
        m_pShopMangerLayer->removeItems();
    }
    
    //添加商品
    
}
void ShopPopupUI::updateShopSellItems()
{
    if (!m_pBagLayer || !m_pShopGridView)
        return;
    if (m_pShopMangerLayer) {
        m_pShopMangerLayer->removeItems();
    }
    cocos2d::Vector<SellItem*> m_vSellItems = m_pBagLayer->getSellItems();
    
    if (m_vSellItems.empty())
        return;
    
    std::vector<PickableItemProperty*> bagItems = PlayerProperty::getInstance()->getPlayerBag();
        for (int j=0;j<m_vSellItems.size();j++)
        {
            ui::ImageView* itemUi = static_cast<ui::ImageView*>( m_pShopGridView->getItem(j));
            for (int i =0 ; i<bagItems.size(); i++)
            {
                PickableItemProperty* itemProp =bagItems[i];
                
                if (!itemProp) {
                    continue;
                }
                
                if (itemUi && itemProp->getInstanceID() == m_vSellItems.at(j)->getItemId())
                {
                    m_pShopMangerLayer->addItem(j, itemProp->getInstanceID(), itemUi->getPosition(), itemProp->getIconRes());
                    if (m_vSellItems.at(j)->getItemCount() >1) {
                        m_pShopMangerLayer->setItemCount(itemProp->getInstanceID(), itemUi->getPosition(), m_vSellItems.at(j)->getItemCount());
                    }
                    break;
                }
            }
            if (j==13) {
                break;
            }
        }
}
void ShopPopupUI::onClickSortAll(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
        m_pBtnAllBag->setEnabled(false);
        m_pBtnPotionBag->setEnabled(true);
        m_pBtnWeaponBag->setEnabled(true);
    }
    if (m_pBagLayer) {
        m_pBagLayer->updateBagProp();
    }
}
void ShopPopupUI::onClickSortEquip(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
        m_pBtnAllBag->setEnabled(true);
        m_pBtnPotionBag->setEnabled(true);
        m_pBtnWeaponBag->setEnabled(false);
    }
    if (m_pBagLayer) {
        m_pBagLayer->updateBagProp(false,BagLayer::SBT_EQUIP);
    }
}
void ShopPopupUI::onClickSortPotion(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
        m_pBtnAllBag->setEnabled(true);
        m_pBtnPotionBag->setEnabled(false);
        m_pBtnWeaponBag->setEnabled(true);
        
    }
    if (m_pBagLayer) {
        m_pBagLayer->updateBagProp(false,BagLayer::SBT_POTION);
    }
}

void ShopPopupUI::onClickFrameBuy(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
        m_pBtnBuyFrame->setEnabled(false);
        m_pBtnSellFrame->setEnabled(true);
    }
    if (m_pBagLayer) {
        m_pBagLayer->setShopSellStatus(false);
    }

    updateItems();
}

void ShopPopupUI::onClickFrameSell(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
        m_pBtnBuyFrame->setEnabled(true);
        m_pBtnSellFrame->setEnabled(false);
    }
    if (m_pBagLayer) {
         m_pBagLayer->setShopSellStatus(true);
    }

    updateItems();
}

void ShopPopupUI::selectItemEvent(cocos2d::Ref *pSender, TGridView::EventType type)
{
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END) {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        int currentItemId = m_pShopMangerLayer->getItemId(gridView->getCurSelectedIndex());
        if (currentItemId!=-1) {
            if (!m_pBtnBuyFrame->isEnabled()) {
                updateShopBuyItems();
            }else if(!m_pBtnSellFrame->isEnabled()){
                m_pBagLayer->removeItemForSell(currentItemId);
                updateItems();
            }
           
        }
    }
}
