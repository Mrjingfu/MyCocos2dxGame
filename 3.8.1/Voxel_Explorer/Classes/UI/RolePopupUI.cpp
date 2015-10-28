//
//  RolePopUpUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/22.
//
//

#include "RolePopupUI.h"
#include "ItemUI.h"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
USING_NS_CC;
RolePopupUI::RolePopupUI()
{
    m_cActionType  = eNone;
    m_pGridView = nullptr;
}
RolePopupUI::~RolePopupUI()
{
    
}
void RolePopupUI::onEnter()
{
    PopupUILayer::onEnter();
}
void RolePopupUI::onExit()
{
    PopupUILayer::onExit();
}
bool RolePopupUI::initUi()
{
    
    Node* charNode = cocos2d::CSLoader::createNode("characterLayer.csb");
    if (!charNode)
        return  false;
    charNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    charNode->setPosition(WINDOW_CENTER);
    m_pRootLayer->addChild(charNode);
    Layout* equipFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(charNode, "equip_frame"));
    if (!equipFrame)
        return false;
    Layout* gridFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(charNode, "grid_frame"));
    if (!gridFrame)
        return false;

    
    m_pBtnChangeBag = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(charNode, "prop_btn_change_bag"));
    if (!m_pBtnChangeBag)
        return false;
    m_pBtnChangeBag->addClickEventListener(CC_CALLBACK_1(RolePopupUI::onClickChnageBag, this));
    
    
    m_pWeaponUi = ItemUI::create();
    m_pWeaponUi->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    m_pWeaponUi->setPosition(Vec2(8, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pWeaponUi);
    
    m_pArmorUi = ItemUI::create();
    m_pArmorUi->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    m_pArmorUi->setPosition(Vec2(8+m_pWeaponUi->getContentSize().width+2, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pArmorUi);
    
    m_pOrnamentUi = ItemUI::create();
    m_pOrnamentUi->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    m_pOrnamentUi->setPosition(Vec2(8+m_pWeaponUi->getContentSize().width*2+4, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pOrnamentUi);
    
    m_pOtherUi = ItemUI::create();
    m_pOtherUi->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    m_pOtherUi->setPosition(Vec2(8+m_pWeaponUi->getContentSize().width*3+6, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pOtherUi);
    
    m_pShopBtn = ImageView::create("ui_shop_icon.png",TextureResType::PLIST);
    m_pShopBtn->setScale9Enabled(true);
    m_pShopBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    m_pShopBtn->setContentSize(cocos2d::Size(40,40));
    m_pShopBtn->setPosition(Vec2(8+m_pWeaponUi->getContentSize().width*4+8, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pShopBtn);
    
    m_pGridView = TGridView::create();
    m_pGridView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pGridView->setContentSize(cocos2d::Size(gridFrame->getContentSize().width-10,132));
    m_pGridView->setCol(5);
    m_pGridView->setPosition(gridFrame->getContentSize()*0.5);
    m_pGridView->setScrollBarEnabled(false);
    m_pGridView->setItemsMargin(cocos2d::Size(1,3.5));
    m_pGridView->setFrameMargin(cocos2d::Size(2,4));
    m_pGridView->addEventListener(CC_CALLBACK_2(RolePopupUI::selectItemEvent, this));
    gridFrame->addChild(m_pGridView);

    
    
    m_pBtnClose = ui::Button::create("ui_btn_back_1.png","","",TextureResType::PLIST);
    m_pBtnClose->setScale9Enabled(true);
    m_pBtnClose->setPosition(Vec2(SCREEN_WIDTH*0.9, SCREEN_HEIGHT*0.95));
    m_pRootLayer->addChild(m_pBtnClose);
    m_pBtnClose->addClickEventListener(CC_CALLBACK_1(RolePopupUI::onClickColse, this));
    
    for (int j =0; j<int(PlayerProperty::getInstance()->getBagMaxSpace()); j++) {

        ItemUI* itemui = ItemUI::create();
        itemui->setEquipEnable(true);
        m_pGridView->addChild(itemui);
    }
    
    return true;
}
void RolePopupUI::onClickChnageBag(Ref* ref)
{
    CHECK_ACTION(ref);
    for (int j =0; j<5*3; j++) {
        
        ItemUI* itemui = ItemUI::create();
        itemui->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pGridView->pushBackCustomItem(itemui);
    }
    MessageBox("更新背包成功", "提示");
}
void RolePopupUI::onClickColse(Ref* ref)
{
    CHECK_ACTION(ref);
     closePopup();
}

void RolePopupUI::updateItems()
{

}
void RolePopupUI::selectItemEvent(cocos2d::Ref *pSender, TGridView::EventType type)
{
    
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END) {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        CC_UNUSED_PARAM(gridView);
        ItemUI* currentItem = static_cast<ItemUI*>(gridView->getItem(gridView->getCurSelectedIndex()));
        if (currentItem && currentItem->isHaveItem()) {
            currentItem->setEquipEnable(true);

            CCLOG("select child end index = %ld", gridView->getCurSelectedIndex());
        }
        
    }
    

}