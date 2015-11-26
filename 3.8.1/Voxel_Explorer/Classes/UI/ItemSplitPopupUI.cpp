//
//  ItemSplitPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#include "ItemSplitPopupUI.h"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "ShopPopupUI.h"
#include "PopupUILayerManager.h"
USING_NS_CC;
ItemSplitPopupUI::ItemSplitPopupUI()
{
    m_cActionType   =eNone;
    m_nIsBlankClose = false;
    m_pBtnOk    = nullptr;
    m_pSlider   = nullptr;
    m_pIcon     = nullptr;
    m_pCount   = nullptr;
}
ItemSplitPopupUI::~ItemSplitPopupUI()
{
    
}
bool ItemSplitPopupUI::initUi()
{
    return load("itemSplitLayer.csb",false);
}
bool ItemSplitPopupUI::addEvents()
{
    m_pBtnOk= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_split_btn_ok"));
    if (!m_pBtnOk)
        return false;
    
    m_pSlider = dynamic_cast<ui::Slider*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_split_slider"));
    if (!m_pSlider)
        return false;
    
    m_pIcon = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_split_item_icon"));
    if (!m_pIcon)
        return false;
    
    m_pCount = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_split_item_count"));
    if (!m_pCount)
        return false;
    
    m_pCount->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pBtnOk->addClickEventListener(CC_CALLBACK_1(ItemSplitPopupUI::onClickOk, this));
    m_pSlider->addEventListener(CC_CALLBACK_2(ItemSplitPopupUI::sliderEvent, this));
    return true;
}
void ItemSplitPopupUI::updateItemSplit(int itemId,int count)
{
    PickableItemProperty* itemProp = PlayerProperty::getInstance()->getItemFromBag(itemId);
    if (!itemProp)
        return;
    m_pIcon->loadTexture(itemProp->getIconRes(),cocos2d::ui::TextureResType::PLIST);
    m_pIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    
    m_pSlider->setMaxPercent(count-1);
    m_pSlider->setPercent(m_pSlider->getMaxPercent());
    CCLOG("maxPercent:%d",m_pSlider->getMaxPercent());
    CCLOG("Percent:%d",m_pSlider->getPercent());
    m_pCount->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("ITEM_SPLITE_COUNT").c_str(),1+m_pSlider->getPercent()));
}
void ItemSplitPopupUI::onClickOk(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    int count = 1+m_pSlider->getPercent();
    setCloseCallbackParamD(&count);
    closePopup();
}
void ItemSplitPopupUI::sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        cocos2d::ui::Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
        if (slider && m_pCount) {
            m_pCount->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("ITEM_SPLITE_COUNT").c_str(),1+m_pSlider->getPercent()));
        }
    }
}