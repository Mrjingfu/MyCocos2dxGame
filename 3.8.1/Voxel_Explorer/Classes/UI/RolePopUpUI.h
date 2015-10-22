//
//  RolePopUpUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/22.
//
//

#ifndef RolePopUpUI_hpp
#define RolePopUpUI_hpp

#include "PopupUILayer.h"
#include "TGridView.h"
class  RolePopUpUI:public PopupUILayer {
    RolePopUpUI();

public:
    CREATE_FUNC(RolePopUpUI);
    virtual ~RolePopUpUI();
    virtual bool initUi();
private:
    void onTouchColse(Ref*,cocos2d::ui::Widget::TouchEventType);
    void onTouchChnageBag(Ref*,cocos2d::ui::Widget::TouchEventType);
    void selectItemEvent(Ref *pSender, TGridView::EventType type);
private:
    TGridView* gridView;
};

#endif /* RolePopUpUI_hpp */
