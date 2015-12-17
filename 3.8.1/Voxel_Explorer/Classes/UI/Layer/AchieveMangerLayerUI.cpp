//
//  ItemUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/23.
//
//

#include "AchieveMangerLayerUI.h"
#include "UtilityHelper.h"
USING_NS_CC;
AchieveMangerLayerUI::AchieveMangerLayerUI()
{
    m_pItemImgLayer = nullptr;
    m_pAchieveTargetLayer = nullptr;
    m_pAchieveNameLayer = nullptr;
}

AchieveMangerLayerUI::~AchieveMangerLayerUI()
{
    
}
bool AchieveMangerLayerUI::init(cocos2d::Size size)
{
    if (!Layout::init())
        return false;
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setContentSize(size);
//    setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
//    setBackGroundColor(Color3B::BLUE);
    
    m_pItemImgLayer = Layout::create();
    m_pItemImgLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pItemImgLayer->setContentSize(size);
    m_pItemImgLayer->setPosition(getContentSize()*0.5);
//    m_pItemImgLayer->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
//    m_pItemImgLayer->setBackGroundColor(Color3B::RED);
    addChild(m_pItemImgLayer);
    
    m_pAchieveNameLayer = Layout::create();
    m_pAchieveNameLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pAchieveNameLayer->setContentSize(size);
    m_pAchieveNameLayer->setPosition(getContentSize()*0.5);
//    m_pEquipMarkLayer->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
//    m_pEquipMarkLayer->setBackGroundColor(Color3B::YELLOW);
    addChild(m_pAchieveNameLayer);
    
    m_pAchieveTargetLayer = Layout::create();
    m_pAchieveTargetLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pAchieveTargetLayer->setContentSize(size);
    m_pAchieveTargetLayer->setPosition(getContentSize()*0.5);
    //    m_pEquipMarkLayer->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    //    m_pEquipMarkLayer->setBackGroundColor(Color3B::YELLOW);
    addChild(m_pAchieveTargetLayer);

   return true;
}
AchieveMangerLayerUI* AchieveMangerLayerUI::create(cocos2d::Size size)
{
    AchieveMangerLayerUI* itemUi = new (std::nothrow) AchieveMangerLayerUI();
    if (itemUi && itemUi->init(size))
    {
        itemUi->autorelease();
        return itemUi;
    }
    CC_SAFE_DELETE(itemUi);
    return nullptr;
}
void AchieveMangerLayerUI::setLayerContentSize(const cocos2d::Size &contentSize)
{
    setContentSize(contentSize);
    
    if (m_pItemImgLayer) {
         m_pItemImgLayer->setContentSize(contentSize);
        m_pItemImgLayer->setPosition(getContentSize()*0.5);
    }
    
    if (m_pAchieveTargetLayer) {
        m_pAchieveTargetLayer->setContentSize(contentSize);
        m_pAchieveTargetLayer->setPosition(getContentSize()*0.5);
    }
    
    if (m_pAchieveNameLayer) {
        m_pAchieveNameLayer->setContentSize(contentSize);
        m_pAchieveNameLayer->setPosition(getContentSize()*0.5);
    }
    
}
void AchieveMangerLayerUI::addItemAchieve(eAchievementDetailType achieveId,cocos2d::Vec2 pt,std::string itemIcon,std::string name,std::string targetDesc,bool isHideAchieve,bool isCommple)
{
    m_Achieves.push_back(achieveId);
    if (m_pItemImgLayer && m_pAchieveNameLayer && m_pAchieveTargetLayer)
    {
        ui::ImageView* img = ui::ImageView::create(itemIcon,TextureResType::PLIST);
        img->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        img->setPosition(pt-cocos2d::Vec2(img->getContentSize().width,0));
        img->setScale(0.7);
        img->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        img->setTag(achieveId);
        if (!isCommple &&isHideAchieve) {
            img->loadTexture("achievement_lock.png",TextureResType::PLIST);
        }
         img->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        cocos2d::ui::Scale9Sprite* scale9sp=dynamic_cast<cocos2d::ui::Scale9Sprite*>(img->getVirtualRenderer());
        scale9sp->setState(cocos2d::ui::Scale9Sprite::State::GRAY);
        if (isCommple) {
           scale9sp->setState(cocos2d::ui::Scale9Sprite::State::NORMAL);
        }
        m_pItemImgLayer->addChild(img);
        
        ui::Text* nameText = ui::Text::create();
        nameText->setFontSize(36);
        nameText->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
        nameText->setScale(0.3);
        nameText->setString(name);
        nameText->setTag(achieveId);
        float textHeight =nameText->getContentSize().height*nameText->getScale();
        nameText->setPosition(cocos2d::Vec2(img->getPositionX()+img->getContentSize().width*0.55,pt.y+textHeight*0.5));
        nameText->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
        nameText->setColor(Color3B(105, 87, 055));
        if (isCommple) {
            nameText->setColor(Color3B(200, 182, 150));
        }
        if (!isCommple &&isHideAchieve)
        {
            nameText->setString("????");
            nameText->setPosition(cocos2d::Vec2(img->getPositionX()+img->getContentSize().width*0.55,pt.y));
        }
        m_pAchieveNameLayer->addChild(nameText);
        
        ui::Text* targetText = ui::Text::create();
        targetText->setFontSize(36);
        targetText->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
        targetText->setScale(0.18);
        targetText->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
        targetText->setTag(achieveId);
        cocos2d::Size fonSize = UtilityHelper::getSingleStrFontSize(targetText, targetDesc);
        
        int charCount  = (int)((130.0 - img->getContentSize().width)/fonSize.width);
        UtilityHelper::getLineStr(targetDesc, charCount);

        targetText->setString(targetDesc);
        float targetTextHeight =targetText->getContentSize().height*targetText->getScale();
        targetText->setPosition(cocos2d::Vec2(nameText->getPositionX(),pt.y-targetTextHeight*0.5 ));
        m_pAchieveTargetLayer->addChild(targetText);


        
        targetText->setColor(Color3B(105, 87, 055));
        if (isCommple) {
            targetText->setColor(Color3B(180, 150, 106));
        }
        if (!isCommple &&isHideAchieve)
        {
            targetText->setVisible(false);
        }

    }
}


void AchieveMangerLayerUI::removeItems()
{
    if (m_pItemImgLayer) {
        m_pItemImgLayer->removeAllChildren();
    }
    
    if (m_pAchieveNameLayer) {
        m_pAchieveNameLayer->removeAllChildren();
    }
    
    if (m_pAchieveTargetLayer) {
        m_pAchieveTargetLayer->removeAllChildren();
    }

    m_Achieves.clear();
}

