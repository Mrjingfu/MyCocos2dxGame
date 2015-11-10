//
//  ItemUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/23.
//
//

#include "ItemUI.h"
#include "UtilityHelper.h"
USING_NS_CC;
ItemUI::ItemUI():_isHaveItem(false),_isEquip(false)
{
    m_pItemImage = nullptr;
    m_pEquipmark = nullptr;
    m_pItemCount = nullptr;
    m_nItemId =-2;
}

ItemUI::~ItemUI()
{
    
}
ItemUI* ItemUI::create()
{
    ItemUI* itemUi = new (std::nothrow) ItemUI();
    if (itemUi && itemUi->init())
    {
        itemUi->autorelease();
        return itemUi;
    }
    CC_SAFE_DELETE(itemUi);
    return nullptr;
}
bool ItemUI::init()
{
    if (!Widget::init())
        return false;
    
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setContentSize(cocos2d::Size(45,45));
    setTouchEnabled(true);
    setBackGroundImageScale9Enabled(true);
    setBackGroundImage("ui_frame_5.png",TextureResType::PLIST);
    
    setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pItemImage = ui::ImageView::create("A_Armor04.png",TextureResType::LOCAL);
    m_pItemImage->setPosition(Vec2(getContentSize().width*0.5, getContentSize().width*0.45));
    m_pItemImage->setScale(0.8);
    m_pItemImage->setVisible(false);
    m_pItemImage->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    addChild(m_pItemImage,2);
    
    m_pEquipmark = ui::ImageView::create("ui_equip_label.png",TextureResType::PLIST);
    m_pEquipmark->setScale(0.5);
    m_pEquipmark->setPosition(Vec2(getContentSize().width*0.15, getContentSize().height*0.82));
    m_pEquipmark->setVisible(false);
    m_pEquipmark->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    addChild(m_pEquipmark,3);

    m_pItemCount = ui::Text::create("", UtilityHelper::getLocalString("FONT_NAME"), 36);
    m_pItemCount->setScale(0.25);
    m_pItemCount->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    m_pItemCount->setPosition(Vec2(getContentSize().width*0.62, getContentSize().height*0.8));
    addChild(m_pItemCount,3);
    
    m_pItemCount->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pItemCount->setVisible(false);
    
    
    
    return true;
}
void ItemUI::addItem(int _itemId,std::string itemIcon)
{
    addItem(_itemId, itemIcon, 0);
}
void ItemUI::addItem(int _itemId, std::string itemIcon, int itemNum)
{
    if (m_pItemImage) {
        m_pItemImage->setVisible(true);
        m_pItemImage->loadTexture(itemIcon,TextureResType::LOCAL);
        m_pItemImage->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        
    }

    std::string num = StringUtils::format("X%d",itemNum);
    if (m_pItemCount && itemNum >1) {
        m_pItemCount->setString(num);
        m_pItemCount->setVisible(true);
    }
    
    _isHaveItem = true;
    m_nItemId = _itemId;
}

void ItemUI::removeItem()
{
    if (m_pItemImage) {
        m_pItemImage->setVisible(false);
    }
    if (m_pItemCount) {
        m_pItemCount->setVisible(false);
    }
    if (m_pEquipmark) {
        m_pEquipmark->setVisible(false);
    }
    _isHaveItem = false;
    _isEquip = false;
}
void ItemUI::setEquipEnable(bool enable)
{
    _isEquip = enable;
    if (m_pEquipmark)
         m_pEquipmark->setVisible(_isEquip);
}