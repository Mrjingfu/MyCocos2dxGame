//
//  MenuUILayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/20.
//
//

#ifndef MenuUILayer_h
#define MenuUILayer_h

#include "WrapperUILayer.h"
class MenuUILayer:public WrapperUILayer {
    
public:
    MenuUILayer();
    virtual ~MenuUILayer();
public:
    CREATE_FUNC(MenuUILayer);
    virtual bool addEvents();
protected:
    void onTouchStart(Ref*,cocos2d::ui::Widget::TouchEventType);
    void onTouchSetting(Ref*,cocos2d::ui::Widget::TouchEventType);
    void onTouchRank(Ref*,cocos2d::ui::Widget::TouchEventType);
    void onTouchRate(Ref*,cocos2d::ui::Widget::TouchEventType);
    void onTouchAchieve(Ref*,cocos2d::ui::Widget::TouchEventType);
};

#endif /* MenuUILayer_h */
