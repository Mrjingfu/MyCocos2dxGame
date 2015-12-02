//
//  RolePopUpUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/22.
//
//

#include "RolePopupUI.h"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "PopupUILayerManager.h"
#include "ItemPopupUI.h"
#include "EventConst.h"
#include "GameFormula.hpp"
#include "KeyProperty.hpp"
#include "BagLayer.h"
#include "RoleLayer.hpp"
USING_NS_CC;
RolePopupUI::RolePopupUI()
{
    m_nIsBlankClose         = false;
    m_cActionType           = eNone;
    m_pBtnClose             = nullptr;
    m_pBtnChangeBag         = nullptr;

    
}
RolePopupUI::~RolePopupUI()
{
    
}
void RolePopupUI::onEnter()
{

    EventListenerCustom *listener = EventListenerCustom::create(EVENT_PLAYER_PROPERTY_DIRTY, CC_CALLBACK_1(RolePopupUI::onEventUpdateData,this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_BAG_EXTEND_OK, CC_CALLBACK_1(RolePopupUI::onEventBagExtend, this));
        Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_BAG_EXTEND_HAS_REACH_MAXTIMES, CC_CALLBACK_1(RolePopupUI::onEventBagExtendHasReachMaxtimes, this));
    PopupUILayer::onEnter();
}
void RolePopupUI::onExit()
{
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_BAG_EXTEND_OK);
     Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_BAG_EXTEND_HAS_REACH_MAXTIMES);
    PopupUILayer::onExit();
}
bool RolePopupUI::initUi()
{
    m_pRootNode = cocos2d::Node::create();
    m_pRootNode->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    m_pRootNode->setContentSize(cocos2d::Size(250.00,340.00));
    m_pRootNode->setPosition(WINDOW_CENTER);
    addChild(m_pRootNode,1);
    
    m_pBagLayer = BagLayer::create();
    m_pBagLayer->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
    m_pBagLayer->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.5,0));
    m_pRootNode->addChild(m_pBagLayer);
    
    m_pRoleLayer = RoleLayer::create();
    m_pRoleLayer->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
    m_pRoleLayer->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.5,m_pRootNode->getContentSize().height));
    m_pRootNode->addChild(m_pRoleLayer);
    
    m_pBtnClose = ui::Button::create("ui_btn_back_1.png","","",TextureResType::PLIST);
    m_pBtnClose->setScale9Enabled(true);
    m_pBtnClose->setPosition(Vec2(SCREEN_WIDTH*0.8, SCREEN_HEIGHT*0.8));
    m_pRootNode->addChild(m_pBtnClose);
    m_pBtnClose->addClickEventListener(CC_CALLBACK_1(RolePopupUI::onClickColse, this));
  
    refreshUIView();
    
    m_pRootNode->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    return true;
}


void RolePopupUI::onEventUpdateData(cocos2d::EventCustom *sender)
{
    refreshUIView();
}
void RolePopupUI::onEventBagExtend(cocos2d::EventCustom *sender)
{
    if (m_pBagLayer)
        m_pBagLayer->extendBag();
    refreshUIView();
    
}
void RolePopupUI::onEventBagExtendHasReachMaxtimes(cocos2d::EventCustom *sender)
{
    //扩展次数到达上线,给出提示
    CCLOG("onEventBagExtendHasReachMaxtimes");
}
void RolePopupUI::refreshUIView()
{
    if (m_pRoleLayer) {
        m_pRoleLayer->refreshUIView();
    }
    if (m_pBagLayer) {
        m_pRoleLayer->refreshUIView();
    }
}
void RolePopupUI::updateItems(bool _isOpenIdentify)
{

    if (m_pBagLayer) {
        m_pBagLayer->setIdentIfy(_isOpenIdentify);
        
    }
    refreshUIView();

}

void RolePopupUI::onClickChnageBag(Ref* ref)
{
    CHECK_ACTION(ref);
    PlayerProperty::getInstance()->extendBagSpace();
}
void RolePopupUI::onClickColse(Ref* ref)
{
    CHECK_ACTION(ref);
    if (m_pBagLayer) {
        if (m_pBagLayer->isIdentIfy()) {
            m_pBagLayer->setSortBtnEnable(false, true, true);
            refreshUIView();
        }else
        {
            closePopup();
        }
    }
    
}
