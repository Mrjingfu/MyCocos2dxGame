//
//  EquipmentPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/15.
//
//

#include "BreadDownPopupUI.hpp"
#include "BagEquipLayer.hpp"
#include "UtilityHelper.h"
#include "TGridView.h"
#include "BagMangerLayerUI.h"
#include "PlayerProperty.hpp"
#include "EventConst.h"
#include "BreadDownSettlementPopupUI.hpp"
#include "PopupUILayerManager.h"
USING_NS_CC;
BreadDownPopupUI::BreadDownPopupUI()
{
    m_cActionType       = eNone;
    m_nIsBlankClose     = false;
    m_pBagEquipLayer = nullptr;
    m_pEquipTitleText = nullptr;
    m_pMaterialGridView = nullptr;
    m_pBagManagerLayer = nullptr;
    m_bIsCallBack = false;
}
BreadDownPopupUI::~BreadDownPopupUI()
{
    
}
void BreadDownPopupUI::onEnter()
{
    PopupUILayer::onEnter();
    scheduleUpdate();
    EventListenerCustom *listener = EventListenerCustom::create(EVENT_PLAYER_BAG_ITEM_UPDATE, CC_CALLBACK_1(BreadDownPopupUI::onEventPlayerBagItemUpdate,this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    
}
void BreadDownPopupUI::onExit()
{
    unscheduleUpdate();
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    PopupUILayer::onExit();
}
void BreadDownPopupUI::update(float dt)
{
    if (m_bIsCallBack) {
        m_pBagEquipLayer->registerCloseCallbackD(CC_CALLBACK_1(BreadDownPopupUI::showSucessBreadDownPopup, this));
        m_bIsCallBack = false;
    }
}
void BreadDownPopupUI::onEventPlayerBagItemUpdate(cocos2d::EventCustom *sender)
{
    refreshUIView();
}
bool BreadDownPopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    return load("breaddownpopupLayer.csb",false);
}

bool BreadDownPopupUI::addEvents()
{
    cocos2d::ui::Layout* m_equipFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "equip_bg_frame"));
    if (!m_equipFrame)
        return false;
    
    cocos2d::ui::ImageView* m_equipMaterialFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "euqip_material_frame"));
    if (!m_equipMaterialFrame)
        return false;
    
    
    cocos2d::ui::ImageView* m_equipTitleImgFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "equip_prop_title_img"));
    if (!m_equipTitleImgFrame)
        return false;

    
    m_pEquipTitleText= dynamic_cast<ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode, "equip_title_text"));
    if (!m_pEquipTitleText)
        return false;
    
    
    Button*  m_pBtnClose = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "equip_btn_close"));
    if (!m_pBtnClose)
        return false;
    
    m_pBtnClose->addClickEventListener(CC_CALLBACK_1(BreadDownPopupUI::onClickClose, this));
    
    m_pEquipTitleText->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pEquipTitleText->setString(UtilityHelper::getLocalStringForUi("BAG_TEXT_BREADDOWN"));
    
    m_pBagEquipLayer = BagEquipLayer::create();
    m_pBagEquipLayer->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    m_pBagEquipLayer->setPosition(cocos2d::Vec2(m_equipFrame->getContentSize().width*0.5,m_equipFrame->getContentSize().height*0.5));
    m_pBagEquipLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_equipFrame->addChild(m_pBagEquipLayer);
    
    m_pMaterialGridView = TGridView::create();
    m_pMaterialGridView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pMaterialGridView->setContentSize(cocos2d::Size(m_equipMaterialFrame->getContentSize().width-10,m_equipMaterialFrame->getContentSize().height-7));
    m_pMaterialGridView->setCol(5);
    m_pMaterialGridView->setPosition(m_equipMaterialFrame->getContentSize()*0.5);
    m_pMaterialGridView->setItemsMargin(cocos2d::Size(3,5));
    m_pMaterialGridView->setFrameMargin(cocos2d::Size(2,3));
    m_pMaterialGridView->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_equipMaterialFrame->addChild(m_pMaterialGridView);
    
    for (int j =0; j<5; j++) {
        
        ImageView* itemui = ImageView::create();
        itemui->setTouchEnabled(true);
        itemui->setScale9Enabled(true);
        itemui->setContentSize(cocos2d::Size(45,45));
        itemui->loadTexture("ui_frame_5.png",TextureResType::PLIST);
        itemui->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pMaterialGridView->pushBackCustomItem(itemui);
    }
    m_pMaterialGridView->forceDoLayout();
    
    m_pBagManagerLayer = BagMangerLayerUI::create(m_pMaterialGridView->getInnerContainerSize());
    m_pBagManagerLayer->setPosition(m_pMaterialGridView->getContentSize()*0.5);
    m_pBagManagerLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pMaterialGridView->addChildLayer(m_pBagManagerLayer);
    m_pBagManagerLayer->setZOrder(m_pMaterialGridView->getItems().size());

    
    m_pBagEquipLayer->registerCloseCallbackD(CC_CALLBACK_1(BreadDownPopupUI::showSucessBreadDownPopup, this));
    
    
    refreshUIView();
    
    return true;
}
void BreadDownPopupUI::refreshUIView()
{
    if (m_pBagEquipLayer) {
        m_pBagEquipLayer->refreshUIView();
    }
    updateMaterialDataItems();
}
void BreadDownPopupUI::onClickClose(Ref* ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickClose");
    closePopup();
}
void BreadDownPopupUI::updateMaterialDataItems()
{
    if (!m_pMaterialGridView)
        return;
    
    if (m_pBagManagerLayer)
        m_pBagManagerLayer->removeItems();
    
    //重置边框颜色
    for(int i=0; i<m_pMaterialGridView->getItems().size(); i++)
    {
        ImageView* itemImg = static_cast<ImageView*>(m_pMaterialGridView->getItem(i));
        if (itemImg) {
            itemImg->loadTexture("ui_frame_5.png",TextureResType::PLIST);
            itemImg->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        }
    }

 
    std::vector<PickableItemProperty*> materialProps;
    for (int i=0; i<PlayerProperty::getInstance()->getPlayerBag().size(); i++)
    {
        PickableItemProperty* itemProp = PlayerProperty::getInstance()->getPlayerBag()[i];
        if (itemProp && itemProp->getPickableItemPropertyType() == PickableItemProperty::PIPT_MATERIAL)
        {
            materialProps.push_back(itemProp);
        }
    }
    
    for (int i=0; i<materialProps.size(); i++)
    {
        PickableItemProperty* property = materialProps[i];
        ui::ImageView* img =static_cast<ui::ImageView*>( m_pMaterialGridView->getItem(i));
        if (property && img)
        {
            m_pBagManagerLayer->addItem(i, property->getInstanceID(), img->getPosition(), property->getIconRes());
            if (property->getCount()>1) {
                 m_pBagManagerLayer->setItemCount(property->getInstanceID(), img->getPosition(), property->getCount());
            }
           
        }
    }
    
}
void BreadDownPopupUI::showSucessBreadDownPopup( void* datas )
{
    m_bIsCallBack = true;
    if (datas) {
        std::map<PickableItem::PickableItemType,CChaosNumber>* reslutDatas = static_cast<std::map<PickableItem::PickableItemType,CChaosNumber>*>(datas);
        if (!reslutDatas->empty()) {
            BreadDownSettlementPopupUI* popup = static_cast<BreadDownSettlementPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupBreadDownSettlement));
            if (popup) {
                popup->updateUIView(reslutDatas);
            }
        }else
        {
            CCLOG("分解失败");
        }

    }
   
}
