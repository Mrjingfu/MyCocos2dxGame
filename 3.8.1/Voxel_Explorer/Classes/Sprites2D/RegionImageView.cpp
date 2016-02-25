//
//  RegionButton.cpp
//  MazeJump
//
//
//

#include "RegionImageView.h"
#include "cocos2d.h"
USING_NS_CC;

RegionImageView::RegionImageView()
{
    m_regionTouchSize = cocos2d::Size::ZERO;
}

RegionImageView::~RegionImageView()
{
}
void RegionImageView::setTouchRegionSize(cocos2d::Size _size)
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
RegionImageView* RegionImageView::create()
{
    RegionImageView* widget = new (std::nothrow) RegionImageView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;

}
RegionImageView* RegionImageView::create(const std::string& imageFileName, TextureResType texType )
{
    RegionImageView *widget = new (std::nothrow) RegionImageView;
    if (widget && widget->init(imageFileName, texType))
    {
        
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;

}

bool RegionImageView::hitTest(const cocos2d::Vec2 &pt, const cocos2d::Camera* camera, cocos2d::Vec3 *p) const
{
    cocos2d::Rect rect;
    rect.origin = cocos2d::Vec2(-m_regionTouchSize.width*0.5,0);
    rect.size = getContentSize()+ m_regionTouchSize;
    return isScreenPointInRect(pt, camera, getWorldToNodeTransform(), rect, p);
}
