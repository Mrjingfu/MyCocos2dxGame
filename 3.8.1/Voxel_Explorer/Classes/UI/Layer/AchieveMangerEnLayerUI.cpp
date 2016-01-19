//
//  AchieveMangerEnLayerUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/1/18.
//
//

#include "AchieveMangerEnLayerUI.hpp"
#include "UtilityHelper.h"
USING_NS_CC;
AchieveMangerEnLayerUI* AchieveMangerEnLayerUI::create(cocos2d::Size size)
{
    AchieveMangerEnLayerUI* itemUi = new (std::nothrow) AchieveMangerEnLayerUI();
    if (itemUi && itemUi->init(size))
    {
        itemUi->autorelease();
        return itemUi;
    }
    CC_SAFE_DELETE(itemUi);
    return nullptr;
}
void AchieveMangerEnLayerUI::addItemAchieve(cocos2d::ui::ImageView* achieveItemUi,eAchievementDetailType achieveId,std::string itemIcon,std::string name,std::string targetDesc,bool isUnlockeAchieve,bool isCommple)

{
    m_Achieves.push_back(achieveId);
    cocos2d::Vec2 pt =  achieveItemUi->getPosition();
    cocos2d::Size achieveItemSize = achieveItemUi->getContentSize();
    if (m_pItemImgLayer && m_pAchieveNameLayer && m_pAchieveTargetLayer)
    {
        ui::ImageView* img = static_cast<ui::ImageView*>(m_pItemImgLayer->getChildByTag(achieveId));
        if (!img ) {
            img = ui::ImageView::create();
            img->setScale(0.85);
            img->setTag(achieveId);
            img->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            m_pItemImgLayer->addChild(img);
            
        }
        
        if (isCommple || isUnlockeAchieve) {
            img->loadTexture(itemIcon,TextureResType::PLIST);
        }
        if (!isUnlockeAchieve) {
            img->loadTexture("achieve_icon_07.png",TextureResType::PLIST);
        }
        img->setPosition(pt-cocos2d::Vec2(achieveItemSize.width*0.45,0));
        cocos2d::ui::Scale9Sprite* scale9sp=dynamic_cast<cocos2d::ui::Scale9Sprite*>(img->getVirtualRenderer());
        scale9sp->setState(cocos2d::ui::Scale9Sprite::State::GRAY);
        if (isCommple) {
            scale9sp->setState(cocos2d::ui::Scale9Sprite::State::NORMAL);
        }
        img->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        
        ui::Text* nameText = static_cast<ui::Text*>(m_pAchieveNameLayer->getChildByTag(achieveId));
        if (!nameText) {
            nameText = ui::Text::create();
            nameText->setFontSize(36);
            nameText->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
            nameText->setScale(0.29);
            nameText->setTag(achieveId);
            nameText->setColor(Color3B(105, 87, 055));
            m_pAchieveNameLayer->addChild(nameText);
        }
        UtilityHelper::getLineForText(nameText, name,achieveItemSize.width-img->getPositionX()-img->getContentSize().width);
        nameText->setString(name);
        float textHeight =nameText->getContentSize().height*nameText->getScale();
        nameText->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
        nameText->setPosition(cocos2d::Vec2(img->getPositionX()+img->getContentSize().width,pt.y+achieveItemSize.height*0.20));
        
        if (isCommple) {
            nameText->setColor(Color3B(241, 222, 188));
        }
        if (!isUnlockeAchieve)
        {
            nameText->setString(UtilityHelper::getLocalStringForUi("ACHIEVE_ITEM_LOCK"));
            textHeight = nameText->getContentSize().height*nameText->getScale();
            nameText->setPosition(cocos2d::Vec2(img->getPositionX()+img->getContentSize().width-5,pt.y));
        }
        nameText->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        
        
        ui::Text* targetText = static_cast<ui::Text*>(m_pAchieveTargetLayer->getChildByTag(achieveId));
        if (!targetText) {
            targetText = ui::Text::create();
            targetText->setFontSize(36);
            targetText->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
            targetText->setScale(0.2);
            targetText->setTag(achieveId);
            targetText->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
            m_pAchieveTargetLayer->addChild(targetText);
            targetText->setColor(Color3B(105, 87, 055));
        }
        targetText->setVisible(true);
        UtilityHelper::getLineForText(targetText, targetDesc,achieveItemSize.width-img->getPositionX()-img->getContentSize().width);
        targetText->setString(targetDesc);
        
        targetText->setPosition(cocos2d::Vec2(nameText->getPositionX(),nameText->getPositionY() - textHeight*0.5));
        
        
        if (isCommple) {
            targetText->setColor(Color3B(185, 153, 109));
        }
        if (!isUnlockeAchieve)
        {
            targetText->setVisible(false);
        }
        targetText->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        
    }
}