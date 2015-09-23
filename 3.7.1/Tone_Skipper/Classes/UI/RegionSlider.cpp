//
//  RegionSlider.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/9/22.
//
//

#include "RegionSlider.h"
RegionSlider::RegionSlider()
{
    
}
RegionSlider::~RegionSlider()
{
    m_touchSize = cocos2d::Size::ZERO;
}
void RegionSlider::setTouchRegionSize(cocos2d::Size _size)
{
    m_touchSize = _size;
}
RegionSlider* RegionSlider::create()
{
    RegionSlider* widget = new (std::nothrow) RegionSlider();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
RegionSlider* RegionSlider::create(const std::string& barTextureName,
                       const std::string& normalBallTextureName,
                       TextureResType resType)
{
    RegionSlider* widget = new (std::nothrow) RegionSlider();
    if (widget && widget->init())
    {
        widget->loadBarTexture(barTextureName);
        widget->loadSlidBallTextureNormal(normalBallTextureName);
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
bool RegionSlider::hitTest(const cocos2d::Vec2 &pt)
{
    cocos2d::Vec2 nsp = this->_slidBallNormalRenderer->convertToNodeSpace(pt);
    cocos2d::Size ballSize = this->_slidBallNormalRenderer->getContentSize()+m_touchSize;
    cocos2d::Rect ballRect = cocos2d::Rect(0,0, ballSize.width, ballSize.height);
    if (ballRect.containsPoint(nsp))
    {
        return true;
    }
    return false;

}