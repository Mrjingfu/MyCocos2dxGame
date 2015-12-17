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
void AchieveMangerLayerUI::addItem(int index,int itemId,cocos2d::Vec2 pt,std::string itemIcon)
{
    m_items.insert(std::pair<int, int>(index,itemId));
    if (m_pItemImgLayer) {
        ui::ImageView* img = ui::ImageView::create(itemIcon,TextureResType::PLIST);
        img->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        img->setPosition(pt);
        img->setScale(0.9);
        img->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        img->setTag(itemId);
        m_pItemImgLayer->addChild(img);
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

    m_items.clear();
}
void AchieveMangerLayerUI::removeItem(int index)
{
    auto iter = m_items.find(index);
    int itemId = -1;
    if (iter != m_items.end())
    {
        itemId = iter->second;
        m_items.erase(iter);
    }
    if (itemId==-1)
        return;
    if (m_pItemImgLayer) {
        m_pItemImgLayer->removeChildByTag(itemId);
    }
   
    if (m_pAchieveNameLayer) {
        m_pAchieveNameLayer->removeChildByTag(itemId);
    }
    
    if (m_pAchieveTargetLayer) {
        m_pAchieveTargetLayer->removeChildByTag(itemId);
    }
   
}

int AchieveMangerLayerUI::getItemId(int index) const
{
    auto iter = m_items.find(index);
    if (iter != m_items.end())
        return iter->second;
    return -1;
}
