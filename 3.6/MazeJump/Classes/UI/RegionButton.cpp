//
//  RegionButton.cpp
//  MazeJump
//
//
//

#include "RegionButton.h"


RegionButton::RegionButton()
{
    m_touchSize = cocos2d::Size::ZERO;
}

RegionButton::~RegionButton()
{
}
void RegionButton::setTouchRegionSize(cocos2d::Size _size)
{
    m_touchSize = _size;
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
bool RegionButton::hitTest(const cocos2d::Vec2 &pt)
{
    Vec2 nsp = convertToNodeSpace(pt);
    cocos2d::Rect bb;
    bb.size = _contentSize + m_touchSize;
    if (bb.containsPoint(nsp))
    {
        return true;
    }
    return false;
}
