//
//  ItemUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/23.
//
//

#include "BagLayerUI.h"
#include "UtilityHelper.h"
USING_NS_CC;
BagLayerUI::BagLayerUI()
{
    m_pItemImgLayer = nullptr;
    m_pEquipMarkLayer = nullptr;
    m_pItemCountLayer = nullptr;
}

BagLayerUI::~BagLayerUI()
{
    
}
bool BagLayerUI::init(cocos2d::Size size)
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
    
    m_pEquipMarkLayer = Layout::create();
    m_pEquipMarkLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pEquipMarkLayer->setContentSize(size);
    m_pEquipMarkLayer->setPosition(getContentSize()*0.5);
//    m_pEquipMarkLayer->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
//    m_pEquipMarkLayer->setBackGroundColor(Color3B::YELLOW);
    addChild(m_pEquipMarkLayer);
    
    m_pItemCountLayer = Layout::create();
    m_pItemCountLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pItemCountLayer->setContentSize(size);
    m_pItemCountLayer->setPosition(getContentSize()*0.5);
//    m_pItemCountLayer->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
//    m_pItemCountLayer->setBackGroundColor(Color3B::ORANGE);
    addChild(m_pItemCountLayer);
    
    return true;
}
BagLayerUI* BagLayerUI::create(cocos2d::Size size)
{
    BagLayerUI* itemUi = new (std::nothrow) BagLayerUI();
    if (itemUi && itemUi->init(size))
    {
        itemUi->autorelease();
        return itemUi;
    }
    CC_SAFE_DELETE(itemUi);
    return nullptr;
}
void BagLayerUI::addItem(int index,int itemId,cocos2d::Vec2 pt,std::string itemIcon)
{
    m_items.insert(std::pair<int, int>(index,itemId));
    if (m_pItemImgLayer) {
        ui::ImageView* img = ui::ImageView::create(itemIcon,ui::TextureResType::PLIST);
        img->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        img->setPosition(pt);
        img->setScale(0.9);
        img->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pItemImgLayer->addChild(img);
    }
}

void BagLayerUI::setItemCount(cocos2d::Vec2 pt,int count)
{
    if (m_pItemCountLayer) {
        Label* itemCount = Label::createWithTTF(StringUtils::format("X%d",count), UtilityHelper::getLocalString("FONT_NAME"), 36);
        itemCount->setPosition(pt+cocos2d::Vec2(16,-20));
        itemCount->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
        itemCount->setScale(0.23);
        itemCount->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pItemCountLayer->addChild(itemCount);
    }
 }
void BagLayerUI::setItemEquipMark(cocos2d::Vec2 pt)
{
    if (m_pEquipMarkLayer) {
        ui::ImageView* img = ui::ImageView::create("ui_equip_label.png",ui::TextureResType::PLIST);
        img->setScale(0.5);
        img->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        img->setPosition(pt+cocos2d::Vec2(-13,13));
        img->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pEquipMarkLayer->addChild(img);
    }
}
void BagLayerUI::removeItems()
{
    if (m_pItemImgLayer) {
        m_pItemImgLayer->removeAllChildren();
    }
    
    if (m_pEquipMarkLayer) {
        m_pEquipMarkLayer->removeAllChildren();
    }
    
    if (m_pItemCountLayer) {
        m_pItemCountLayer->removeAllChildren();
    }
    m_items.clear();
}
int BagLayerUI::getItemId(int index) const
{
    auto iter = m_items.find(index);
    if (iter != m_items.end())
        return iter->second;
    return -1;
}
