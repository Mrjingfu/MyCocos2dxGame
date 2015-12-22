//
//  AchieveItemPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/17.
//
//

#include "AchieveItemPopupUI.hpp"
#include "UtilityHelper.h"
USING_NS_CC;
AchieveItemPopupUI::AchieveItemPopupUI()
{
    m_pAchieveIcon  = nullptr;
    m_pAchieveName  = nullptr;
    m_pAchieveTargetDesc = nullptr;
    m_nIsPause =false;
}
AchieveItemPopupUI::~AchieveItemPopupUI()
{
    
}
bool AchieveItemPopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    return load("achieveItemLayer.csb",false);
}
bool AchieveItemPopupUI::addEvents()
{
    m_pAchieveIcon = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "achieveitem_icon"));
    if(!m_pAchieveIcon)
        return false;
    m_pAchieveTargetDesc = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "achieveitem_target_desc"));
    if(!m_pAchieveTargetDesc)
        return false;
    m_pAchieveName = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "achieveitem_name"));
    if(!m_pAchieveName)
        return false;
    
    m_pAchieveTargetDesc->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pAchieveName->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pAchieveTargetDesc->setColor(Color3B(185, 153, 109));
    m_pAchieveName->setColor(Color3B(241, 222, 188));
    return true;
}
void AchieveItemPopupUI::inAction()
{
    if (m_pRootNode) {
        m_pRootNode->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
        m_pRootNode->setPosition(cocos2d::Vec2(getContentSize().width*0.5,getContentSize().height*0.8));
        m_pRootNode->setScale(0.001f);
        
        EaseIn* scale1 = EaseIn::create(ScaleTo::create(0.3f,1.1f *1),0.3f);
        
        ScaleTo* scale2 = ScaleTo::create(0.1f,1.0f * 1);
        CallFunc* callFunc =  CallFunc::create(CC_CALLBACK_0(AchieveItemPopupUI::inActionCallFunc, this));
        m_pRootNode->runAction(Sequence::create(scale1,scale2, callFunc,nullptr));
    }
    
}
void AchieveItemPopupUI::outAction()
{
    if (m_pRootNode) {
        ScaleTo* scale1 = ScaleTo::create(0.1f,1.1f * 1);
        EaseOut* scale2 = EaseOut::create(ScaleTo::create(0.4f,0.001f * 1),0.3f);
        CallFunc* callFunc =  CallFunc::create(CC_CALLBACK_0(PopupUILayer::removeSelfCallFunc, this));
        m_pRootNode->runAction(Sequence::create(scale1,scale2,callFunc,nullptr));
    }
}
void AchieveItemPopupUI::inActionCallFunc()
{
    CallFunc* callFunc =  CallFunc::create([this]()
                                           {
                                               closePopup();
                                           });
    runAction(Sequence::create(DelayTime::create(1.5),callFunc, nullptr));
   
}
bool AchieveItemPopupUI::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return false;
}
void AchieveItemPopupUI::setAchieveDatas(const std::string icon, const std::string name, const std::string targetDesc)
{
    if (m_pAchieveIcon) {
        m_pAchieveIcon->loadTexture(icon,TextureResType::PLIST);
        m_pAchieveIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    }
    if (m_pAchieveName) {
        m_pAchieveName->setString(name);
    }
    if (m_pAchieveTargetDesc) {
        m_pAchieveTargetDesc->setString(targetDesc);
    }
}
