//
//  ItemUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/23.
//
//

#include "BagMangerLayerUI.h"
#include "UtilityHelper.h"
USING_NS_CC;
BagMangerLayerUI::BagMangerLayerUI()
{
    m_pItemImgLayer = nullptr;
    m_pEquipMarkLayer = nullptr;
    m_pItemCountLayer = nullptr;
}

BagMangerLayerUI::~BagMangerLayerUI()
{
    
}
bool BagMangerLayerUI::init(cocos2d::Size size)
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
    
    m_pIteminIentifyLayer = Layout::create();
    m_pIteminIentifyLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pIteminIentifyLayer->setContentSize(size);
    m_pIteminIentifyLayer->setPosition(getContentSize()*0.5);
//        m_pItemCountLayer->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
//        m_pItemCountLayer->setBackGroundColor(Color3B::ORANGE);
    addChild(m_pIteminIentifyLayer);
    
    m_pItemNoUse  = Layout::create();
    m_pItemNoUse->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pItemNoUse->setContentSize(size);
    m_pItemNoUse->setPosition(getContentSize()*0.5);
    //        m_pItemNoUse->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    //        m_pItemNoUse->setBackGroundColor(Color3B::ORANGE);
    addChild(m_pItemNoUse);
    
    return true;
}
BagMangerLayerUI* BagMangerLayerUI::create(cocos2d::Size size)
{
    BagMangerLayerUI* itemUi = new (std::nothrow) BagMangerLayerUI();
    if (itemUi && itemUi->init(size))
    {
        itemUi->autorelease();
        return itemUi;
    }
    CC_SAFE_DELETE(itemUi);
    return nullptr;
}
void BagMangerLayerUI::setLayerContentSize(const cocos2d::Size &contentSize)
{
    setContentSize(contentSize);
    
    if (m_pItemImgLayer) {
         m_pItemImgLayer->setContentSize(contentSize);
        m_pItemImgLayer->setPosition(getContentSize()*0.5);
    }
    if (m_pItemCountLayer) {
        m_pItemCountLayer->setContentSize(contentSize);
        m_pItemCountLayer->setPosition(getContentSize()*0.5);
    }
    
    if (m_pEquipMarkLayer) {
        m_pEquipMarkLayer->setContentSize(contentSize);
        m_pEquipMarkLayer->setPosition(getContentSize()*0.5);
    }
    if (m_pIteminIentifyLayer) {
        m_pIteminIentifyLayer->setContentSize(contentSize);
        m_pIteminIentifyLayer->setPosition(getContentSize()*0.5);

    }
    if (m_pItemNoUse) {
        m_pItemNoUse->setContentSize(contentSize);
        m_pItemNoUse->setPosition(getContentSize()*0.5);
    }
    
}
void BagMangerLayerUI::addItem(int index,int itemId,cocos2d::Vec2 pt,std::string itemIcon)
{
    m_items.insert(std::pair<int, int>(index,itemId));
    if (m_pItemImgLayer) {
        ui::ImageView* img = ui::ImageView::create(itemIcon,ui::TextureResType::PLIST);
        img->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        img->setPosition(pt);
        img->setScale(0.9);
        img->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        img->setTag(itemId);
        m_pItemImgLayer->addChild(img);
    }
}

void BagMangerLayerUI::setItemCount(int itemId,cocos2d::Vec2 pt,int count)
{
    if (m_pItemCountLayer) {
        Label* itemCount = Label::createWithTTF(StringUtils::format("X%d",count), UtilityHelper::getLocalString("FONT_NAME"), 36);
        itemCount->setPosition(pt+cocos2d::Vec2(16,-20));
        itemCount->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
        itemCount->setScale(0.23);
        itemCount->setTag(itemId);
        itemCount->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pItemCountLayer->addChild(itemCount);
    }
 }
void BagMangerLayerUI::setItemEquipMark(int itemId,cocos2d::Vec2 pt)
{
    if (m_pEquipMarkLayer) {
        ui::ImageView* img = ui::ImageView::create("ui_equip_label.png",ui::TextureResType::PLIST);
        img->setScale(0.5);
        img->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        img->setPosition(pt+cocos2d::Vec2(-13,13));
        img->setTag(itemId);
        img->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pEquipMarkLayer->addChild(img);
    }
}
void BagMangerLayerUI::setItemInIentify(int itemId,cocos2d::Vec2 pt)
{
    if (m_pIteminIentifyLayer) {
        ui::ImageView* img = ui::ImageView::create("ui_indentify_icon.png",ui::TextureResType::PLIST);
        img->setScale9Enabled(true);
        img->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        img->setPosition(pt);
        img->setTag(itemId);
        img->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pIteminIentifyLayer->addChild(img);
    }
}
void BagMangerLayerUI::setItemNoUse(int itemId,cocos2d::Vec2 pt)
{
    if (m_pItemNoUse) {
        Sprite* img = cocos2d::Sprite::createWithSpriteFrameName("ui_no_user.png");
//        img->setScale9Enabled(true);
        img->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        img->setPosition(pt);
        img->setTag(itemId);
        img->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        // 黑暗中的带背景图片纹理的光圈~
//         BlendFunc tmp_oBlendFunc = {GL_DST_COLOR, GL_ZERO};
        
        // 黑暗中的黄色光圈(前面表示upper，后面表示lower)~
//                BlendFunc tmp_oBlendFunc = {GL_ONE, GL_ZERO};
        
        // 黑暗中的黄色光圈(前面表示upper，后面表示lower)~
//                BlendFunc tmp_oBlendFunc = {GL_DST_ALPHA, GL_ZERO};
        
        // 默认的 blend 配置~
        //        BlendFunc tmp_oBlendFunc = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
        
        // premultiplied~
//                BlendFunc tmp_oBlendFunc = {GL_ONE, GL_ONE_MINUS_SRC_ALPHA};
        
        // 仅背景图片有所显示~
//                BlendFunc tmp_oBlendFunc = {GL_ZERO, GL_ONE};
        
        // 黄色光圈区域亮度加强(2倍的强度)~
        //        BlendFunc tmp_oBlendFunc = {GL_DST_COLOR, GL_SRC_COLOR};
        
        // 正片叠底~
//                BlendFunc tmp_oBlendFunc = {GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA};
        
        // 类似柔光：黄色光圈区域亮度加强，其他地方也不会显示为纯黑（接近我想要的想过了）~
//                BlendFunc tmp_oBlendFunc = {GL_DST_COLOR, GL_ONE};
        
        // Screen~
//                BlendFunc tmp_oBlendFunc = {GL_ONE_MINUS_DST_COLOR, GL_ONE};
        
        // Linear Dodge~
        //        BlendFunc tmp_oBlendFunc = {GL_ONE, GL_ONE};
        
        // 很类似柔光效果，这个也最接近我的需求了~
//        BlendFunc tmp_oBlendFunc = {GL_SRC_ALPHA, GL_ONE};
        
        // GL_ONE_MINUS_SRC_ALPHA 注定是不行的（光晕中心会被模糊掉）~
        //        BlendFunc tmp_oBlendFunc = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
        
        // 标准的正片叠底~
                BlendFunc tmp_oBlendFunc = {GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA};
//        / 1.正片叠底
//                BlendFunc tmp_oBlendFunc = {GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA};
        
        // 2.
//                BlendFunc tmp_oBlendFunc = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
        
        // 3.黄色光圈区域显示背景图片，其他区域显示黑色(黄色光圈很柔和)~
//                BlendFunc tmp_oBlendFunc = {GL_ZERO, GL_SRC_ALPHA};
        
        // 4.背景图片在黄色光圈区域的图片尤为阴暗~
        //        BlendFunc tmp_oBlendFunc = {GL_ZERO, GL_ONE_MINUS_SRC_ALPHA};
        
        // 5.仅仅显示出了原始的背景图片~
        //        BlendFunc tmp_oBlendFunc = {GL_ZERO, GL_DST_ALPHA};
        
        // 6.全黑~
        //        BlendFunc tmp_oBlendFunc = {GL_ZERO, GL_ONE_MINUS_DST_ALPHA};
        
        // ----------------------------------------
        
        // 7.仅显示黄色光圈图片~
        //        BlendFunc tmp_oBlendFunc = {GL_ONE, GL_ZERO};
        
        // 8.纯粹的添加光圈图片到背景图片上面~
        //        BlendFunc tmp_oBlendFunc = {GL_ONE, GL_ONE};
        
        // 9.纯粹的添加光圈图片到背景图片上面~
        //        BlendFunc tmp_oBlendFunc = {GL_ONE, GL_DST_COLOR};
        
        // 10.纯粹的添加光圈图片到背景图片上面~
        //        BlendFunc tmp_oBlendFunc = {GL_ONE, GL_ONE_MINUS_DST_COLOR};
        
        // 11.纯粹的添加光圈图片到背景图片上面~
        //        BlendFunc tmp_oBlendFunc = {GL_ONE, GL_SRC_ALPHA_SATURATE};
        
        // 12.黄色光圈区域显示背景图片，其他区域显示黑色(黄色光圈很刺眼)~
//                BlendFunc tmp_oBlendFunc = {GL_ONE, GL_SRC_ALPHA};  
        
        // 13.  
//                BlendFunc tmp_oBlendFunc = {GL_SRC_COLOR, GL_DST_COLOR};
        img->setBlendFunc(tmp_oBlendFunc);
        img->setOpacity(100);
        m_pItemNoUse->addChild(img);
    }
}
void BagMangerLayerUI::removeItems()
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
    
    if (m_pIteminIentifyLayer) {
        m_pIteminIentifyLayer->removeAllChildren();
    }
    
    if (m_pItemNoUse) {
        m_pItemNoUse->removeAllChildren();
    }
    m_items.clear();
}
void BagMangerLayerUI::removeItem(int index)
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
    if (m_pEquipMarkLayer) {
        m_pEquipMarkLayer->removeChildByTag(itemId);
    }
    
    if (m_pItemCountLayer) {
        m_pItemCountLayer->removeChildByTag(itemId);
    }
    
    if (m_pIteminIentifyLayer) {
        m_pIteminIentifyLayer->removeChildByTag(itemId);
    }
    
}
void BagMangerLayerUI::removeCountForItems()
{
    if (m_pItemCountLayer) {
        m_pItemCountLayer->removeAllChildren();
    }
}
void BagMangerLayerUI::removeIndetifyForItems()
{
    if (m_pIteminIentifyLayer) {
        m_pIteminIentifyLayer->removeAllChildren();
    }
}
int BagMangerLayerUI::getItemId(int index) const
{
    auto iter = m_items.find(index);
    if (iter != m_items.end())
        return iter->second;
    return -1;
}
