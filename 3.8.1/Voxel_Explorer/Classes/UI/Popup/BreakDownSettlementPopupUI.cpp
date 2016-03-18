//
//  BreadDownSettlementPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/17.
//
//

#include "BreakDownSettlementPopupUI.hpp"
#include "UtilityHelper.h"
USING_NS_CC;
BreakDownSettlementPopupUI::BreakDownSettlementPopupUI()
{

    m_pMaterialFrame    = nullptr;
    m_pBtnConfirm       = nullptr;
}
BreakDownSettlementPopupUI::~BreakDownSettlementPopupUI()
{
    
}
bool BreakDownSettlementPopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    return load("breadkDownbalance.csb",false);
}
cocos2d::ui::Layout* BreakDownSettlementPopupUI::createBreakDownItem(std::string icon,CChaosNumber count )
{
    cocos2d::Node*  m_pBottomNode = cocos2d::CSLoader::createNode("breadkDownbalanceItem.csb");
    if (!m_pBottomNode)
        return nullptr;
    
    ui::Layout* m_pBreadDownItem = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pBottomNode, "breadDown_item"));
    if (!m_pBreadDownItem)
        return nullptr;
    
   cocos2d::ui::ImageView* m_pMaterialIcon = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pBottomNode, "breadDown_item_material"));
    if (!m_pMaterialIcon)
        return nullptr;
    
    cocos2d::ui::TextBMFont* m_pMaterialCount= dynamic_cast<ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pBottomNode, "breadDown_item_material_text"));
    if (!m_pMaterialCount)
        return nullptr;
    
    cocos2d::ui::TextBMFont* m_pMaterialDesc= dynamic_cast<ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pBottomNode, "breadDown_item_material_desc"));
    if (!m_pMaterialDesc)
        return nullptr;
    
    m_pMaterialCount->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pMaterialDesc->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pMaterialDesc->setString(UtilityHelper::getLocalStringForUi("BREAK_DOWN_SETTLEMENT_DESC"));
    m_pMaterialCount->setString(StringUtils::format("x%ld",count.GetLongValue()));
    m_pMaterialIcon->loadTexture(icon,TextureResType::PLIST);
    
    
    m_pBreadDownItem->removeFromParentAndCleanup(true);
    m_pBreadDownItem->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    
    return m_pBreadDownItem;
}
bool  BreakDownSettlementPopupUI::addEvents()
{
    m_pMaterialFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "breadDown_layer_frame"));
    if (!m_pMaterialFrame)
        return false;
    
    m_pBtnConfirm = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "breadDown_btn_ok"));
    if (!m_pBtnConfirm)
        return false;
    
    m_pBtnConfirm->setTitleFontName(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    m_pBtnConfirm->getTitleRenderer()->setScale(0.7);
    m_pBtnConfirm->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_OK"));
    
    
    m_pBtnConfirm->addClickEventListener(CC_CALLBACK_1(BreakDownSettlementPopupUI::onClickConfirm, this));
    
    m_pMaterialFrame->setLayoutType(ui::Layout::Type::VERTICAL);
    
    return true;
}
void BreakDownSettlementPopupUI::onClickConfirm(cocos2d::Ref* ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onClickConfirm");
    closePopup();
}
void BreakDownSettlementPopupUI::updateUIView(const std::map<PickableItem::PickableItemType,CChaosNumber>* reslutDatas)
{
    if (!reslutDatas->empty())
    {
        CChaosNumber whiteCount = reslutDatas->at(PickableItem::PickableItemType::PIT_MATERIAL_WHITE);
        CChaosNumber greenCount = reslutDatas->at(PickableItem::PickableItemType::PIT_MATERIAL_GREEN);
        CChaosNumber blueCount = reslutDatas->at(PickableItem::PickableItemType::PIT_MATERIAL_BLUE);
        CChaosNumber puprpleCount = reslutDatas->at(PickableItem::PickableItemType::PIT_MATERIAL_PURPLE);
        CCLOG("whiteCount:%ld greenCount:%ld blueCount:%ld puprpleCount:%ld",whiteCount.GetLongValue(),greenCount.GetLongValue(),blueCount.GetLongValue(),puprpleCount.GetLongValue());
        ui::LinearLayoutParameter* linerParmter = ui::LinearLayoutParameter::create();
        linerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        linerParmter->setMargin(ui::Margin(0,0,0,0));
        int count=-1;
        if (whiteCount.GetLongValue() !=0)
        {
            ui::Layout* whiteLayout = createBreakDownItem("I_Crystal_white.png",whiteCount);
            whiteLayout->setLayoutParameter(linerParmter);
            m_pMaterialFrame->addChild(whiteLayout);
            ++count;
        }
        if (greenCount.GetLongValue() !=0)
        {
            ui::Layout* greenLayout = createBreakDownItem("I_Crystal_green.png",greenCount);
            greenLayout->setLayoutParameter(linerParmter);
            m_pMaterialFrame->addChild(greenLayout);
            ++count;
        }
        if (blueCount.GetLongValue() !=0)
        {
            ui::Layout* blueLayout = createBreakDownItem("I_Crystal_blue.png",blueCount);
            blueLayout->setLayoutParameter(linerParmter);
            m_pMaterialFrame->addChild(blueLayout);
            ++count;
        }
        if (puprpleCount.GetLongValue() !=0)
        {
            ui::Layout* puprpleLayout = createBreakDownItem("I_Crystal_purple.png",puprpleCount);
            puprpleLayout->setLayoutParameter(linerParmter);
            m_pMaterialFrame->addChild(puprpleLayout);
            ++count;
        }
        cocos2d::Size addSize = cocos2d::Size(0,35*count);
        m_pRootNode->setContentSize(m_pRootNode->getContentSize()+addSize);
        m_pMaterialFrame->setContentSize(cocos2d::Size(m_pMaterialFrame->getContentSize() + addSize));
        m_pMaterialFrame->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
        m_pMaterialFrame->setPosition(m_pRootNode->getContentSize()*0.5);
    }
}