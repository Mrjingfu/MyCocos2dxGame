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
class ItemUI;
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
    void updateItems();
private:
   TGridView* gridView;
   ValueVector m_pItemUis;
   ItemUI* m_pWeaponUi;
   ItemUI* m_pArmorUi;
   ItemUI* m_pOrnament;
};

#endif /* RolePopUpUI_hpp */
