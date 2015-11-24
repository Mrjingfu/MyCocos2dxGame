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
ShopPopupUI::ShopPopupUI()
{
    m_cActionType   = eNone;
    m_pBagLayer     = nullptr;
    m_pBtnAllBag    = nullptr;
    m_pBtnWeaponBag = nullptr;
    m_pBtnPotionBag = nullptr;
    
    m_pShopGridView = nullptr;
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
    
    m_pBagLayer = BagLayer::create(m_girdFrame->getContentSize());
    m_pBagLayer->setPosition(m_girdFrame->getContentSize()*0.5);
    m_girdFrame->addChild(m_pBagLayer);
    
    m_pBtnWeaponBag->addTouchEventListener(CC_CALLBACK_2(ShopPopupUI::onClickSortEquip, this));
    m_pBtnPotionBag->addTouchEventListener(CC_CALLBACK_2(ShopPopupUI::onClickSortPotion, this));
    m_pBtnAllBag->addTouchEventListener(CC_CALLBACK_2(ShopPopupUI::onClickSortAll, this));
    
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
void ShopPopupUI::selectItemEvent(cocos2d::Ref *pSender, TGridView::EventType type)
{
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END) {
        TGridView* gridView = static_cast<TGridView*>(pSender);
    }
}