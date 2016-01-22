//
//  Discardlayer.cpp
//  lichuang
//
//  Created by lichuang on 2016/01/07.
//
//

#include "DiscardPopupUI.hpp"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "PopupUILayerManager.h"
#include "StatisticsManager.hpp"
DiscardPopupUI::DiscardPopupUI()
{
    m_nIsBlankClose = false;
    m_pItemIcon     = nullptr;
    m_pOk           = nullptr;
    m_pCancel       = nullptr;
    m_pCountText    = nullptr;
    m_pItemSlider   = nullptr;
    m_nItemId = -1;
}

DiscardPopupUI::~DiscardPopupUI()
{
    
}

bool DiscardPopupUI::initUi()
{
    if (!PopupUILayer::initUi())
            return false;
    return load("discardLayer.csb",false);
}
bool DiscardPopupUI::addEvents()
{
    m_pOk = dynamic_cast<cocos2d::ui::Button *>(UtilityHelper::seekNodeByName(m_pRootNode, "discard_layer_ok"));
    if(!m_pOk)
          return false;
    m_pCancel = dynamic_cast<cocos2d::ui::Button *>(UtilityHelper::seekNodeByName(m_pRootNode, "discard_layer_cancel"));
    if(!m_pCancel)
          return false;
    m_pCountText = dynamic_cast<cocos2d::ui::TextBMFont *>(UtilityHelper::seekNodeByName(m_pRootNode, "discard_item_count"));
    if(!m_pCountText)
          return false;
    m_pItemIcon = dynamic_cast<cocos2d::ui::ImageView *>(UtilityHelper::seekNodeByName(m_pRootNode, "discard_item_icon"));
    if(!m_pItemIcon)
          return false;
    m_pItemSlider = dynamic_cast<cocos2d::ui::Slider*>(UtilityHelper::seekNodeByName(m_pRootNode, "discard_item_slider"));
    if (!m_pItemSlider)
        return false;

    m_pOk->setTitleFontName(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pOk->getTitleRenderer()->setScale(0.7);
    m_pOk->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_OK"));
    
    m_pCancel->setTitleFontName(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pCancel->getTitleRenderer()->setScale(0.7);
    m_pCancel->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_CANCEL"));
    
    m_pOk->addClickEventListener(CC_CALLBACK_1(DiscardPopupUI::onClickOk, this));
    m_pCancel->addClickEventListener(CC_CALLBACK_1(DiscardPopupUI::onClickCancel,this));

    m_pCountText->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pItemSlider->addEventListener(CC_CALLBACK_2(DiscardPopupUI::sliderEvent, this));
    
    return true;
}
void DiscardPopupUI::setDiscardItem(int itemId)
{
    m_nItemId = itemId;
    refreshUIView();
}
void DiscardPopupUI::refreshUIView()
{
    PickableItemProperty* itemprop =  PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    int count = itemprop->getCount();
    
    m_pItemIcon->loadTexture(itemprop->getIconRes(),TextureResType::PLIST);
    m_pItemIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    
    m_pItemSlider->setMaxPercent(count-1);
    m_pItemSlider->setPercent(m_pItemSlider->getMaxPercent());
    m_pCountText->setString(cocos2d::StringUtils::format(UtilityHelper::getLocalStringForUi("ITEM_SPLITE_COUNT").c_str(),1+m_pItemSlider->getPercent()));
    
    
    
}
void DiscardPopupUI::sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        cocos2d::ui::Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
        if (slider && m_pCountText) {
            m_pCountText->setString(cocos2d::StringUtils::format(UtilityHelper::getLocalStringForUi("ITEM_SPLITE_COUNT").c_str(),1+m_pItemSlider->getPercent()));
            
            }
    }

}
void DiscardPopupUI::onClickOk(cocos2d::Ref *ref)
{
    PickableItemProperty* itemprop =  PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    int count = m_pItemSlider->getPercent() +1;

    bool isSuccess = PlayerProperty::getInstance()->removeStackableItemFromBag(itemprop->getPickableItemType(), count);
    if (isSuccess ) {
        StatisticsManager::getInstance()->addDiscardItemNum();
        PopupUILayer* itemPopupLayer;
        if (PopupUILayerManager::getInstance()->isOpenPopup(ePopupItem,itemPopupLayer)) {
            if (itemPopupLayer) {
                itemPopupLayer->closePopup();
            }
        }
    }else
    {
        //移除失败
        PopupUILayerManager::getInstance()->showStatusImport(TIP_NEGATIVE, UtilityHelper::getLocalStringForUi("ITEM_DISCARD_FAIL"));
    }
    closePopup();
}
void DiscardPopupUI::onClickCancel(cocos2d::Ref *ref)
{
    closePopup();
    PopupUILayer* itemPopupLayer;
    if (PopupUILayerManager::getInstance()->isOpenPopup(ePopupItem,itemPopupLayer)) {
        if (itemPopupLayer) {
            itemPopupLayer->getRootNode()->setVisible(true);
        }
    }
    PopupUILayer* equipPopupLayer;
    if (PopupUILayerManager::getInstance()->isOpenPopup(ePopupEquipItem,equipPopupLayer)) {
        if (equipPopupLayer) {
            equipPopupLayer->getRootNode()->setVisible(true);
        }
    }
    

}

