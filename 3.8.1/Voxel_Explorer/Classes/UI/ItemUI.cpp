//
//  ItemUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/23.
//
//

#include "ItemUI.h"
#include "ui/UIScale9Sprite.h"
USING_NS_CC;
ItemUI::ItemUI():_isHaveItem(false)
{
    m_pItemImage = nullptr;
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
    if (!Layout::init())
        return false;
    
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setBackGroundImageScale9Enabled(true);
    setTouchEnabled(true);
    setBackGroundImage("ui_frame_5.png",TextureResType::PLIST);
    setContentSize(cocos2d::Size(40,40));
//    _backGroundImage->setState(cocos2d::ui::Scale9Sprite::State::GRAY);
    
    return true;
}
void ItemUI::addItem(std::string itemName)
{
    if (!m_pItemImage) {
        m_pItemImage = ui::ImageView::create(itemName,TextureResType::PLIST);
        m_pItemImage->setPosition(getContentSize()*0.5);
        addChild(m_pItemImage);
    }else{
        m_pItemImage->loadTexture(itemName,TextureResType::PLIST);
        m_pItemImage->setVisible(true);
    }
   
    _isHaveItem = true;
    m_pItemProp = itemName;
}

void ItemUI::removeItem()
{
    if (m_pItemImage) {
        m_pItemImage->setVisible(false);
    }
    _isHaveItem = false;
}
void ItemUI::setEquipEnable(bool enable)
{
    _isEquip = enable;
    setBackGroundImageColor(Color3B::GREEN);
}