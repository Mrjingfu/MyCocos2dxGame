//
//  CustomScrollView.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/9/22.
//
//

#include "CustomScrollView.h"
CustomScrollView::CustomScrollView()
{
    
}
CustomScrollView::~CustomScrollView()
{
    
}
CustomScrollView* CustomScrollView::create()
{
    CustomScrollView* widget = new (std::nothrow) CustomScrollView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
void CustomScrollView::setCameraMask(unsigned short mask, bool applyChildren )
{
    Widget::setCameraMask(mask, applyChildren);
    if (_clippingStencil){
        _clippingStencil->setCameraMask(mask, applyChildren);
    }
}