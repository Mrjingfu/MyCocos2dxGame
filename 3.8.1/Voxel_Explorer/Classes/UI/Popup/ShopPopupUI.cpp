//
//  ShopPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "ShopPopupUI.h"
#include "BagShopLayer.hpp"
#include "UtilityHelper.h"
#include "PickableItemProperty.hpp"
#include "PlayerProperty.hpp"
#include "BagMangerLayerUI.h"
#include "ItemShopPopupUI.hpp"
#include "PopupUILayerManager.h"
ShopPopupUI::ShopPopupUI()
{
    m_cActionType       = eNone;
    m_pBagLayer         = nullptr;
    m_pShopMangerLayer  = nullptr;
    m_pShopGridView     = nullptr;
    m_pBtnBuyFrame      = nullptr;

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
  
    
    m_pBtnBuyFrame= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "shop_prop_btn_frame_buy"));
    if (!m_pBtnBuyFrame)
        return false;
    
    m_pBagLayer = BagShopLayer::create();
    m_pBagLayer->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
    m_pBagLayer->setPosition(cocos2d::Size(m_pRootNode->getContentSize().width*0.5,0));
    m_pRootNode->addChild(m_pBagLayer);
    
    m_pBtnBuyFrame->loadTextures(UtilityHelper::getLocalStringForUi("SHOP_BTN_FRAME_BUY_NORMAL"), UtilityHelper::getLocalStringForUi("SHOP_BTN_FRAME_BUY_PRESS"),UtilityHelper::getLocalStringForUi("SHOP_BTN_FRAME_BUY_PRESS"),TextureResType::PLIST);
    m_pBtnBuyFrame->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);

    
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
    
    
    refreshUIView();
    
    return true;
}

void ShopPopupUI::refreshUIView()
{
    if (m_pBagLayer) {
        m_pBagLayer->refreshUIView();
    }
    updateShopBuyItems();
}
void ShopPopupUI::updateShopBuyItems()
{
    if (!m_pBagLayer || !m_pShopGridView)
        return;
    if (m_pShopMangerLayer) {
        m_pShopMangerLayer->removeItems();
    }
    
    //添加商品 测试
    updateShopDataItems();

}


void ShopPopupUI::selectItemEvent(cocos2d::Ref *pSender, TGridView::EventType type)
{
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END) {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        int currentItemId = m_pShopMangerLayer->getItemId(gridView->getCurSelectedIndex());
        if (currentItemId!=-1) {
            shopItemOpe(currentItemId);
//            ItemShopPopupUI* shopItem = static_cast<ItemShopPopupUI*>( PopupUILayerManager::getInstance()->openPopup(ePopupItemShop));
//            if (shopItem) {
//                shopItem->updateItemPopup(ItemShopPopupUI::IST_BUY,currentItemId);
//                shopItem->registerCloseCallback(CC_CALLBACK_0(ShopPopupUI::refreshUIView, this));
//            }
        }
    }
}
