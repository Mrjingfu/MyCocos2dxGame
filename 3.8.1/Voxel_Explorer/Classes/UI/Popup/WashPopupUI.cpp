//
//  WashPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/15.
//
//

#include "WashPopupUI.hpp"
#include "BagMangerLayerUI.h"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "BagWashLayer.hpp"
#include "MaterialProperty.hpp"
#include "PopupUILayerManager.h"
#include "ItemWashPopupUI.hpp"
#include "AlertPopupUI.hpp"
USING_NS_CC;
WashPopupUI::WashPopupUI()
{
    m_cActionType       = eNone;
    m_nIsBlankClose     = false;
    
    m_pBgFrame              = nullptr;
    m_pEquipFrame           = nullptr;
    m_pWhiteMaterial        = nullptr;
    m_pGreenMaterial        = nullptr;
    m_pBlueMaterial         = nullptr;
    m_pPurpleMaterial       = nullptr;
    
    m_pWhiteMaterialText    = nullptr;
    m_pGreenMaterialText    = nullptr;
    m_pBlueMaterialText     = nullptr;
    m_pPurpleMaterialText   = nullptr;
    
    m_pBtnWash              = nullptr;
    m_pBagEquipLayer        = nullptr;
    m_pEquipTitleText       = nullptr;
    
    m_pTipText              = nullptr;
    m_bIsCallBack           = false;
    m_nEquipWashId = -1;
    
    m_pOldProp              = nullptr;
}
WashPopupUI::~WashPopupUI()
{
    if (m_pOldProp) {
        CC_SAFE_DELETE(m_pOldProp);
    }
}
void WashPopupUI::onEnter()
{
    PopupUILayer::onEnter();
    scheduleUpdate();
}
void WashPopupUI::onExit()
{
    unscheduleUpdate();
    PopupUILayer::onExit();
}
void WashPopupUI::update(float dt)
{
    if (m_bIsCallBack) {
        m_pBagEquipLayer->registerCloseCallbackO(CC_CALLBACK_1(WashPopupUI::updateMaterial, this));
        m_bIsCallBack = false;
    }
}
bool WashPopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    return load("washpracticePopupLayer.csb",false);
}

bool WashPopupUI::addEvents()
{
    m_pBgFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "wash_bg_frame"));
    if (!m_pBgFrame)
        return false;
    
    m_pEquipFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "wash_equip_frame"));
    if (!m_pEquipFrame)
        return false;
    
    m_pWhiteMaterial = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "wash_white_material"));
    if (!m_pWhiteMaterial)
        return false;
    m_pGreenMaterial = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "wash_green_material"));
    if (!m_pGreenMaterial)
        return false;
    m_pBlueMaterial = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "wash_blue_material"));
    if (!m_pBlueMaterial)
        return false;
    m_pPurpleMaterial = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "wash_purple_material"));
    if (!m_pPurpleMaterial)
        return false;
    
    m_pWhiteMaterialText= dynamic_cast<ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode, "wash_white_material_text"));
    if (!m_pWhiteMaterialText)
        return false;
    m_pGreenMaterialText= dynamic_cast<ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode, "wash_green_material_text"));
    if (!m_pGreenMaterialText)
        return false;
    m_pBlueMaterialText= dynamic_cast<ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode, "wash_blue_material_text"));
    if (!m_pBlueMaterialText)
        return false;
    m_pPurpleMaterialText= dynamic_cast<ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode, "wash_purple_material_text"));
    if (!m_pPurpleMaterialText)
        return false;
    
    m_pBtnWash = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "wash_btn_wash"));
    if (!m_pBtnWash)
        return false;
    
    m_pEquipTitleText = dynamic_cast<ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode, "shop_title_text"));
    if (!m_pEquipTitleText)
        return false;
    
    m_pTipText = dynamic_cast<ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode, "wash_tip_text"));
    if (!m_pTipText)
        return false;
    
   Button*  m_pBtnClose = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "wash_btn_close"));
    if (!m_pBtnClose)
        return false;
    
    m_pBtnClose->addClickEventListener(CC_CALLBACK_1(WashPopupUI::onClickClose, this));
    
    m_pTipText->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pTipText->setString(UtilityHelper::getLocalStringForUi("BAG_TEXT_WASH_TIP"));
    
    m_pWhiteMaterialText->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pGreenMaterialText->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pBlueMaterialText->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pPurpleMaterialText->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    
    m_pEquipTitleText->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pEquipTitleText->setString(UtilityHelper::getLocalStringForUi("BTN_TEXT_WASH"));
    
    m_pBtnWash->setTitleFontName(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pBtnWash->getTitleRenderer()->setScale(0.7);
    m_pBtnWash->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_WASH"));

    
    
    addIconImg(m_pWhiteMaterial,"I_Crystal_white.png");
    addIconImg(m_pGreenMaterial,"I_Crystal_green.png");
    addIconImg(m_pBlueMaterial,"I_Crystal_blue.png");
    addIconImg(m_pPurpleMaterial,"I_Crystal_purple.png");
    
    m_pBagEquipLayer = BagWashLayer::create();
    m_pBagEquipLayer->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
    m_pBagEquipLayer->setPosition(cocos2d::Size(m_pRootNode->getContentSize().width*0.5,0));
    m_pBagEquipLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pRootNode->addChild(m_pBagEquipLayer);

    
    updateMaterialDisplay(false,false,false,false);

    m_pBtnWash->setTouchEnabled(false);
    m_pBtnWash->setEnabled(false);
    m_pBtnWash->addClickEventListener(CC_CALLBACK_1(WashPopupUI::onClickWash, this));
    
    
    m_pEquipFrame->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.5,m_pEquipFrame->getPositionY()));
    
    m_pBagEquipLayer->registerCloseCallbackO(CC_CALLBACK_1(WashPopupUI::updateMaterial, this));
    
    refreshUIView();
    return true;
}
void WashPopupUI::refreshUIView()
{
    if(m_pBagEquipLayer)
        m_pBagEquipLayer->refreshUIView();
}

void WashPopupUI::updateMaterial(Ref* data)
{
    if (m_pBtnWash)
    {
        m_pBtnWash->setTouchEnabled(false);
        m_pBtnWash->setEnabled(false);
    }

    m_bIsCallBack = true;
    bool isMaterialEnough = false;
    PickableItemProperty* itemProp = static_cast<PickableItemProperty*>(data);
    if (itemProp)
    {
       
        m_nEquipWashId =itemProp->getInstanceID();
        updateEquipFrame(itemProp);
        m_pTipText->setVisible(false);
        PICKABLEITEM_QUALITY quality = itemProp->getQuality();
        m_pEquipFrame->setPosition(cocos2d::Vec2(m_pBgFrame->getContentSize().width*0.2,m_pEquipFrame->getPositionY()));
        addIconImg(m_pEquipFrame,itemProp->getIconRes());
        
        int whiteTargetCount = 0;
        int blueTargetCount = 0;
        int greenTargetCount = 0;
        int purpleTargetCount = 0;
        
        PickableItemProperty* whiteProp = PlayerProperty::getInstance()->getStackableItemForBag(PickableItem::PIT_MATERIAL_WHITE);
        PickableItemProperty* greenProp = PlayerProperty::getInstance()->getStackableItemForBag(PickableItem::PIT_MATERIAL_GREEN);
        PickableItemProperty* blueProp = PlayerProperty::getInstance()->getStackableItemForBag(PickableItem::PIT_MATERIAL_BLUE);
        PickableItemProperty* purpleProp = PlayerProperty::getInstance()->getStackableItemForBag(PickableItem::PIT_MATERIAL_PURPLE);
        
        if (quality == PICKABLEITEM_QUALITY::PIQ_RARE)
        {
            updateMaterialDisplay(true,true,false,false);

            
            m_pWhiteMaterial->setPosition(cocos2d::Vec2(m_pBgFrame->getContentSize().width*0.66,m_pBgFrame->getContentSize().height*0.32));
            m_pGreenMaterial->setPosition(cocos2d::Vec2(m_pBgFrame->getContentSize().width*0.66,m_pBgFrame->getContentSize().height*0.78));
            
            whiteTargetCount = MaterialProperty::WASH_PIQ_RARE[PickableItem::PIT_MATERIAL_WHITE];
            greenTargetCount = MaterialProperty::WASH_PIQ_RARE[PickableItem::PIT_MATERIAL_GREEN];
            
            int whilePropCount = whiteProp==nullptr? 0:whiteProp->getCount().GetLongValue();
            int greenPropCount =  greenProp==nullptr? 0:greenProp->getCount().GetLongValue();
            
            m_pWhiteMaterialText->setString(StringUtils::format("%d/%d",whilePropCount,whiteTargetCount));
            m_pGreenMaterialText->setString(StringUtils::format("%d/%d",greenPropCount,greenTargetCount));
            
            if (whilePropCount < whiteTargetCount)
                m_pWhiteMaterialText->setColor(Color3B::RED);
            if (greenPropCount < greenTargetCount)
                m_pGreenMaterialText->setColor(Color3B::RED);
 
            
            if (whilePropCount >= whiteTargetCount && greenPropCount  >= greenTargetCount) {
                
                isMaterialEnough = true;
            }
            
            
        }else if (quality == PICKABLEITEM_QUALITY::PIQ_EPIC)
        {
            updateMaterialDisplay(true,true,true,false);

            m_pWhiteMaterial->setPosition(cocos2d::Vec2(m_pBgFrame->getContentSize().width*0.52,m_pBgFrame->getContentSize().height*0.32));
            m_pGreenMaterial->setPosition(cocos2d::Vec2(m_pBgFrame->getContentSize().width*0.83,m_pBgFrame->getContentSize().height*0.32));
            m_pBlueMaterial->setPosition(cocos2d::Vec2(m_pBgFrame->getContentSize().width*0.66,m_pBgFrame->getContentSize().height*0.78));

            whiteTargetCount = MaterialProperty::WASH_PIQ_EPIC[PickableItem::PIT_MATERIAL_WHITE];
            greenTargetCount = MaterialProperty::WASH_PIQ_EPIC[PickableItem::PIT_MATERIAL_GREEN];
            blueTargetCount = MaterialProperty::WASH_PIQ_EPIC[PickableItem::PIT_MATERIAL_BLUE];
            
            int whilePropCount = whiteProp==nullptr? 0:whiteProp->getCount().GetLongValue();
            int greenPropCount =  greenProp==nullptr? 0:greenProp->getCount().GetLongValue();
            int bluePropCount =  blueProp==nullptr? 0:blueProp->getCount().GetLongValue();
            
            m_pWhiteMaterialText->setString(StringUtils::format("%d/%d",whilePropCount,whiteTargetCount));
            m_pGreenMaterialText->setString(StringUtils::format("%d/%d",greenPropCount,greenTargetCount));
            m_pBlueMaterialText->setString(StringUtils::format("%d/%d",bluePropCount,blueTargetCount));
            
            if (whilePropCount < whiteTargetCount)
                m_pWhiteMaterialText->setColor(Color3B::RED);
            if (greenPropCount < greenTargetCount)
                m_pGreenMaterialText->setColor(Color3B::RED);
            if (bluePropCount < blueTargetCount)
                m_pBlueMaterialText->setColor(Color3B::RED);
            
            if (whilePropCount >= whiteTargetCount && greenPropCount  >= greenTargetCount
                && bluePropCount>=blueTargetCount) {
                
                isMaterialEnough = true;
            }
            
            
        }else if (quality == PICKABLEITEM_QUALITY::PIQ_LEGEND)
        {
            updateMaterialDisplay(true,true,true,true);
            
            m_pWhiteMaterial->setPosition(cocos2d::Vec2(m_pBgFrame->getContentSize().width*0.52,m_pBgFrame->getContentSize().height*0.32));
            m_pGreenMaterial->setPosition(cocos2d::Vec2(m_pBgFrame->getContentSize().width*0.52,m_pBgFrame->getContentSize().height*0.78));
            m_pBlueMaterial->setPosition(cocos2d::Vec2(m_pBgFrame->getContentSize().width*0.83,m_pBgFrame->getContentSize().height*0.78));
            m_pPurpleMaterial->setPosition(cocos2d::Vec2(m_pBgFrame->getContentSize().width*0.83,m_pBgFrame->getContentSize().height*0.32));
            
            
            whiteTargetCount = MaterialProperty::WASH_PIQ_LEGEND[PickableItem::PIT_MATERIAL_WHITE];
            greenTargetCount = MaterialProperty::WASH_PIQ_LEGEND[PickableItem::PIT_MATERIAL_GREEN];
            blueTargetCount = MaterialProperty::WASH_PIQ_LEGEND[PickableItem::PIT_MATERIAL_BLUE];
            purpleTargetCount = MaterialProperty::WASH_PIQ_LEGEND[PickableItem::PIT_MATERIAL_PURPLE];
            
            int whilePropCount = whiteProp==nullptr? 0:whiteProp->getCount().GetLongValue();
            int greenPropCount =  greenProp==nullptr? 0:greenProp->getCount().GetLongValue();
            int bluePropCount =  blueProp==nullptr? 0:blueProp->getCount().GetLongValue();
            int purplePropCount = purpleProp==nullptr? 0:purpleProp->getCount().GetLongValue();
            
           m_pWhiteMaterialText->setString(StringUtils::format("%d/%d",whilePropCount,whiteTargetCount));
           m_pGreenMaterialText->setString(StringUtils::format("%d/%d",greenPropCount,greenTargetCount));
           m_pBlueMaterialText->setString(StringUtils::format("%d/%d",bluePropCount,blueTargetCount));
           m_pPurpleMaterialText->setString(StringUtils::format("%d/%d",purplePropCount,purpleTargetCount));
            
            if (whilePropCount < whiteTargetCount)
                m_pWhiteMaterialText->setColor(Color3B::RED);
            if (greenPropCount < greenTargetCount)
                m_pGreenMaterialText->setColor(Color3B::RED);
            if (bluePropCount < blueTargetCount)
                m_pBlueMaterialText->setColor(Color3B::RED);
            if (purplePropCount < purpleTargetCount)
                m_pPurpleMaterialText->setColor(Color3B::RED);
            
            
            if (whilePropCount >= whiteTargetCount && greenPropCount  >= greenTargetCount
                && bluePropCount>=blueTargetCount  && purplePropCount >= purpleTargetCount) {
                
                isMaterialEnough = true;
            }

        }
    }
    
    if (isMaterialEnough)
    {
        m_pBtnWash->setTouchEnabled(true);
        m_pBtnWash->setEnabled(true);
    }

}
void WashPopupUI::onClickClose(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickClose");
    closePopup();
}
void WashPopupUI::onClickWash(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickWash");
    AlertPopupUI* alertPopupUi = static_cast<AlertPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupAlert));
    if (alertPopupUi)
    {
        PickableItemProperty* itemProp = PlayerProperty::getInstance()->getItemFromBag(m_nEquipWashId);
        if (itemProp)
        {
            PICKABLEITEM_QUALITY quality = itemProp->getQuality();
            CChaosNumber extendSilver = 0;
            switch (quality) {
                case PIQ_RARE:
                    extendSilver = 2;
                    break;
                case PIQ_EPIC:
                    extendSilver = 25;
                    break;
                case PIQ_LEGEND:
                    extendSilver = 200;
                    break;
                default:
                    break;
            }
            alertPopupUi->setPositiveListerner([](Ref* ref){
                
            },UtilityHelper::getLocalStringForUi("BTN_TEXT_CANCEL"));
            alertPopupUi->setNegativeListerner([this,extendSilver](Ref* ref){

                    if(PlayerProperty::getInstance()->costMoney(extendSilver.GetLongValue()*100))
                        this->itemWash();
                
            },UtilityHelper::getLocalStringForUi("BTN_TEXT_OK"));
            alertPopupUi->setMessage(cocos2d::StringUtils::format(UtilityHelper::getLocalStringForUi("BAG_TEXT_WASH_ITEM").c_str(),int(extendSilver)));
        }

    }
    
}
void WashPopupUI::itemWash()
{
    PickableItemProperty* itemProp = PlayerProperty::getInstance()->getItemFromBag(m_nEquipWashId);
    if (itemProp) {
        if (m_pOldProp) {
            CC_SAFE_DELETE(m_pOldProp);
        }
        m_pOldProp= itemProp->clone();
            bool isSucess = PlayerProperty::getInstance()->equipWashPractice(m_nEquipWashId);
            if (isSucess) {
                ItemWashPopupUI* itemPopup = static_cast<ItemWashPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupItemWash)) ;
                if (itemPopup) {
                    itemPopup->setOldItemProp(m_pOldProp);
                    itemPopup->setItemId(m_nEquipWashId);
                    itemPopup->registerCloseCallbackO(CC_CALLBACK_1(WashPopupUI::updateMaterial, this));
                }
            }else
            {
                CCLOG("洗练失败");
            }
        
    }
}
void WashPopupUI::addIconImg(cocos2d::ui::ImageView* sourceImg,std::string iconStr)
{
    ui::ImageView* iconImg = static_cast<ui::ImageView*>(sourceImg->getChildByTag(10));
    if (!iconImg ) {
        iconImg = ui::ImageView::create();
        iconImg->setTag(10);
        iconImg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        iconImg->setPosition(sourceImg->getContentSize()*0.5);
        iconImg->loadTexture(iconStr,TextureResType::PLIST);
        sourceImg->addChild(iconImg);
    }else
    {
        iconImg->loadTexture(iconStr,TextureResType::PLIST);
    }
    iconImg->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
}
void WashPopupUI::updateMaterialDisplay(bool isWhite,bool isGreen,bool isBlue,bool isPurple)
{
    if (m_pWhiteMaterial)
        m_pWhiteMaterial->setVisible(isWhite);
    if (m_pGreenMaterial)
        m_pGreenMaterial->setVisible(isGreen);
    if (m_pBlueMaterial)
        m_pBlueMaterial->setVisible(isBlue);
    if (m_pPurpleMaterial)
        m_pPurpleMaterial->setVisible(isPurple);
}
void WashPopupUI::updateEquipFrame(PickableItemProperty* prop)
{
    if (prop)
    {
         PICKABLEITEM_QUALITY quality = prop->getQuality();
        switch (quality) {
            case PIQ_RARE:
                m_pEquipFrame->loadTexture("ui_rape.png",TextureResType::PLIST);
                break;
            case PIQ_EPIC:
                m_pEquipFrame->loadTexture("ui_epic.png",TextureResType::PLIST);
                break;
            case PIQ_LEGEND:
                m_pEquipFrame->loadTexture("ui_legend.png",TextureResType::PLIST);
                break;
            default:
                break;
        }
        m_pEquipFrame->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    }
}