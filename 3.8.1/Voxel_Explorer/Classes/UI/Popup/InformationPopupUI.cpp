//
//  SettingUILayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "InformationPopupUI.h"
#include "UtilityHelper.h"
#include "VoxelExplorer.h"
USING_NS_CC;
InformationPopupUI::InformationPopupUI()
{
   
    m_cActionType = eNone;
    m_nIsBlankClose = false;
    m_pInfoIcon = nullptr;
    m_pInfoDesc = nullptr;
    m_pInfoFrame = nullptr;
    m_pTitleFrame = nullptr;
    m_pBtnNext = nullptr;
    m_pInfoTitle = nullptr;
    m_pOk = nullptr;

}
InformationPopupUI::~InformationPopupUI()
{
    
}


bool InformationPopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    if(!load("informationLayer.csb",false))
        return false;
    return true;
}

bool InformationPopupUI::addEvents()
{
    if(!PopupUILayer::addEvents())
        return false;
     
    m_pInfoDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "info_text_message"));
    if (!m_pInfoDesc)
        return false;
    
    m_pBtnNext = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "info_btn_next"));
    if (!m_pBtnNext)
        return false;
    
    m_pInfoTitle =   dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "info_title_text"));
    if (!m_pInfoTitle)
        return false;
    
    m_pInfoFrame =   dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "info_layer_frame"));
    if (!m_pInfoFrame)
        return false;
    
    m_pTitleFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "info_title_img"));
    if (!m_pTitleFrame)
        return false;
    
    m_pOk =  dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "info_btn_ok"));
    if (!m_pOk)
        return false;
    
    m_pInfoDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pInfoTitle->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    
    m_pBtnNext->setVisible(false);
    MoveBy* moveByNext = MoveBy::create(0.5, cocos2d::Vec2(0,-2));
    m_pBtnNext->runAction(RepeatForever::create(Sequence::create(moveByNext,moveByNext->reverse(), nullptr)));
   
    
    
    m_pOk->setVisible(false);
    m_pOk->setTitleFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pOk->setTitleFontSize(36);
    m_pOk->getTitleRenderer()->setScale(0.3);
    m_pOk->setTitleText(UtilityHelper::getLocalStringForUi("BTN_TEXT_OK"));
    m_pOk->addClickEventListener(CC_CALLBACK_1(InformationPopupUI::onClickOk, this));
 
    if (m_pBtnNext )
    {
        cocos2d::Director::getInstance()->getScheduler()->resumeTarget(m_pBtnNext);
        MoveBy* moveByNext = MoveBy::create(0.5, cocos2d::Vec2(0,-2));
        m_pBtnNext->runAction(RepeatForever::create(Sequence::create(moveByNext,moveByNext->reverse(), nullptr)));
        
    }
    
    return true;
}
void InformationPopupUI::refreshUIView()
{

     float frameHeight =  m_pRootNode->getContentSize().height;
    if (!m_vInfos.empty())
    {
        m_pBtnNext->setVisible(true);
    }else{
        m_pOk->setVisible(true);
        frameHeight =  m_pRootNode->getContentSize().height - m_pOk->getContentSize().height-m_pOk->getPositionY()-15;
    }
    
    
    float fontFrameWidth = m_pRootNode->getContentSize().width;
    if (m_pInfoIcon) {
        fontFrameWidth = m_pRootNode->getContentSize().width - m_pInfoIcon->getContentSize().width*m_pInfoIcon->getScale()-m_pRootNode->getContentSize().width*0.03-10;
    }
    int charYCount = 1;
    if (!m_sInfoDesc.empty()) {
        
       cocos2d::Size fonSize = UtilityHelper::getSingleStrFontSize(m_pInfoDesc, m_sInfoDesc);
       int charXCount  = (int)(fontFrameWidth/fonSize.width);
       UtilityHelper::getLineStr(m_sInfoDesc, charXCount);
       m_pInfoDesc->setString(m_sInfoDesc);
        
        //字体高度超过窗体大小是调整窗体大小
        float infoTextHeight = m_pInfoDesc->getContentSize().height*m_pInfoDesc->getScale();
        charYCount = (int)(infoTextHeight/fonSize.height);
        if (infoTextHeight >frameHeight) {
            CCLOG("max height:%f",infoTextHeight -frameHeight);
            float exceedHeight = infoTextHeight -frameHeight;
            m_pRootNode->setContentSize(m_pRootNode->getContentSize()+cocos2d::Size(0,exceedHeight+15));
            m_pInfoFrame->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
            m_pInfoFrame->setContentSize(m_pRootNode->getContentSize());
            m_pInfoFrame->setPosition(m_pRootNode->getContentSize()*0.5);
            
            m_pTitleFrame->setPosition(cocos2d::Vec2(m_pInfoFrame->getContentSize().width*0.5,m_pInfoFrame->getContentSize().height));
            
        }
        
        CCLOG("m_pInfoDesc width:%f height:%f",m_pInfoDesc->getContentSize().width*m_pInfoDesc->getScale(),m_pInfoDesc->getContentSize().height*m_pInfoDesc->getScale());
    }
    
     m_pInfoDesc->setTextHorizontalAlignment(TextHAlignment::CENTER);
    if (m_pInfoDesc&& charYCount>1) {
        m_pInfoDesc->setTextHorizontalAlignment(TextHAlignment::LEFT);
    }
    
    if (m_pInfoIcon) {
        CCLOG("m_pInfoIcon WIDTH:%f",m_pInfoIcon->getContentSize().width);
        m_pInfoIcon->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
        m_pInfoIcon->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.03,m_pRootNode->getContentSize().height*0.5));
        m_pInfoDesc->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
        m_pInfoDesc->setPosition(cocos2d::Vec2(m_pInfoIcon->getPositionX()+10+m_pInfoIcon->getContentSize().width*m_pInfoIcon->getScale(),m_pRootNode->getContentSize().height*0.5));
    }else
    {
        m_pInfoDesc->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
        m_pInfoDesc->setPosition(m_pRootNode->getContentSize()*0.5);
    }
    
    if (m_pOk) {
        m_pOk->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
        m_pOk->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.5,m_pRootNode->getContentSize().height*0.05));
    }
   
    
    if (m_vInfos.empty()) {
        m_pBtnNext->setVisible(false);
        m_pOk->setVisible(true);
        CCLOG("结束");
    }
}
void InformationPopupUI::setTitle(std::string title)
{
    if (m_pInfoTitle) {
        m_pInfoTitle->setString(title);
    }
}
void InformationPopupUI::setInfoIcon(std::string icon)
{
    if (icon.empty())
        return;
    if (!m_pInfoIcon) {
        m_pInfoIcon = cocos2d::ui::ImageView::create();
        m_pInfoIcon->setScale(0.5);
        m_pInfoIcon->loadTexture(icon,TextureResType::PLIST);
        m_pInfoIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pRootNode->addChild(m_pInfoIcon);
    }
    refreshUIView();
}
void InformationPopupUI::setInfoDesc(std::string desc)
{
    m_sInfoDesc =desc;
    
    refreshUIView();
}
void InformationPopupUI::setInfoVector(cocos2d::ValueVector infos)
{
    m_vInfos = infos;
    if(m_pInfoFrame)
    {
        m_pInfoFrame->setTouchEnabled(true);
        m_pInfoFrame->addClickEventListener(CC_CALLBACK_1(InformationPopupUI::onClickNext, this));
    }
    updateInfoVectorDesc();
}

void InformationPopupUI::updateInfoVectorDesc()
{
    if (!m_vInfos.empty()) {
        m_sInfoDesc = m_vInfos.front().asString();
        m_vInfos.erase(m_vInfos.begin());
        refreshUIView();
    }

}
void InformationPopupUI::onClickOk(Ref* ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    closePopup();
}
void InformationPopupUI::onClickNext(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    updateInfoVectorDesc();
}
