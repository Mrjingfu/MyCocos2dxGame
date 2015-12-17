//
//  ShopPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "AchievePopupUI.h"
#include "UtilityHelper.h"
#include "PickableItemProperty.hpp"
#include "AchieveMangerLayerUI.h"
#include "PopupUILayerManager.h"
#include "EventConst.h"
AchievePopupUI::AchievePopupUI()
{
    m_cActionType       = eNone;
    m_pAchieveGridView         = nullptr;
    m_pAchieveMangerLayer = nullptr;

}
AchievePopupUI::~AchievePopupUI()
{
    
}
bool AchievePopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
     return this->load("achievementLayer.csb",false);
   
}
bool AchievePopupUI::addEvents()
{
    cocos2d::ui::ImageView* m_achieveFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "achieve_layer_bg"));
    if (!m_achieveFrame)
        return false;
  

    
    m_pAchieveGridView = TGridView::create();
    m_pAchieveGridView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pAchieveGridView->setContentSize(cocos2d::Size(m_achieveFrame->getContentSize().width,m_achieveFrame->getContentSize().height-5));
    m_pAchieveGridView->setCol(2);
    m_pAchieveGridView->setPosition(m_achieveFrame->getContentSize()*0.5);
    m_pAchieveGridView->setScrollBarWidth(2);
    m_pAchieveGridView->setScrollBarColor(Color3B::WHITE);
    m_pAchieveGridView->setScrollBarPositionFromCornerForVertical(cocos2d::Vec2(0,0));
//    m_pShopGridView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    m_pAchieveGridView->setItemsMargin(cocos2d::Size(3,5));
    m_pAchieveGridView->setFrameMargin(cocos2d::Size(9,5));
//    m_pAchieveGridView->addEventListener(CC_CALLBACK_2(ShopPopupUI::selectItemEvent, this));
    m_pAchieveGridView->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_achieveFrame->addChild(m_pAchieveGridView);

    int shopItemSize = 10;
    
    for (int j =0; j<shopItemSize; j++) {
        
        ImageView* itemui = ImageView::create();
        itemui->setTouchEnabled(true);
        itemui->setScale9Enabled(true);
        itemui->setContentSize(cocos2d::Size(130,50));
        itemui->loadTexture("ui_frame_3.png",TextureResType::PLIST);
        itemui->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pAchieveGridView->pushBackCustomItem(itemui);
    }
    m_pAchieveGridView->forceDoLayout();
    
    m_pAchieveMangerLayer = AchieveMangerLayerUI::create(m_pAchieveGridView->getInnerContainerSize());
    m_pAchieveMangerLayer->setPosition(m_pAchieveGridView->getContentSize()*0.5);
    m_pAchieveMangerLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pAchieveGridView->addChildLayer(m_pAchieveMangerLayer,60);
    
    
    refreshUIView();
    
    return true;
}
void AchievePopupUI::onEnter()
{
    PopupUILayer::onEnter();
//    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_NPC_DATA_DIRTY, CC_CALLBACK_1(ShopPopupUI::onEventUpdateNpcData,this));
//    EventListenerCustom *listener = EventListenerCustom::create(EVENT_PLAYER_PROPERTY_DIRTY, CC_CALLBACK_1(ShopPopupUI::onEventUpdateNpcData,this));
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
}
void AchievePopupUI::onExit()
{
//    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_NPC_DATA_DIRTY);
//    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    PopupUILayer::onExit();
}

void AchievePopupUI::refreshUIView()
{
    
//    updateShopBuyItems();
}
//void AchievePopupUI::updateShopBuyItems()
//{
//    
//    updateShopDataItems();
//
//}

