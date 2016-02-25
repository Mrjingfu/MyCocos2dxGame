//
//  RegionButton.cpp
//  MazeJump
//
//
//

#include "RegionButton.h"
#include "cocos2d.h"
USING_NS_CC;

RegionButton::RegionButton()
{
    m_regionTouchSize = cocos2d::Size::ZERO;
}

RegionButton::~RegionButton()
{
}
void RegionButton::setTouchRegionSize(cocos2d::Size _size)
{
    m_regionTouchSize = _size;
#if COCOS2D_DEBUG==1
    cocos2d::Rect rect;
    rect.origin = cocos2d::Vec2(-m_regionTouchSize.width*0.5,0);
    rect.size = getContentSize()+ m_regionTouchSize;
    DrawNode* drawNode = DrawNode::create();
    drawNode->clear();
    drawNode->drawRect(rect.origin, cocos2d::Vec2(rect.size.width -std::abs(rect.origin.x),rect.size.height), cocos2d::Color4F::RED);
    addChild(drawNode);
#endif
}
RegionButton* RegionButton::create(const std::string &normalImage,
                       const std::string& selectedImage ,
                       const std::string& disableImage,
                       TextureResType texType)
{
    RegionButton *btn = new (std::nothrow) RegionButton;
    if (btn && btn->init(normalImage,selectedImage,disableImage,texType))
    {
        btn->autorelease();
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return nullptr;
}
bool RegionButton::hitTest(const cocos2d::Vec2 &pt, const cocos2d::Camera* camera, cocos2d::Vec3 *p) const
{
    cocos2d::Rect rect;
    rect.origin = cocos2d::Vec2(-m_regionTouchSize.width*0.5,0);
    rect.size = getContentSize()+ m_regionTouchSize;
    return isScreenPointInRect(pt, camera, getWorldToNodeTransform(), rect, p);
}
