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
class  RolePopupUI:public PopupUILayer {
    RolePopupUI();

public:
    CREATE_FUNC(RolePopupUI);
    virtual ~RolePopupUI();
    virtual bool initUi() override;
    void onEnter() override;
    void onExit()override;
private:
    void onClickColse(Ref* ref);
    void onClickChnageBag(Ref*);
    void selectItemEvent(Ref *pSender, TGridView::EventType type);
    void updateItems();
    void onEventEquipWeapon(cocos2d::EventCustom *sender);
    void onEventEquipArmor(cocos2d::EventCustom *sender);
    void onEventEquipOrnament(cocos2d::EventCustom *sender);
    void onEventExtendBag(cocos2d::EventCustom *sender);
private:
   TGridView* m_pGridView;
   cocos2d::ui::Button* m_pBtnClose;
   cocos2d::ui::Button* m_pBtnChangeBag;
   ItemUI* m_pWeaponUi;
   ItemUI* m_pArmorUi;
   ItemUI* m_pOrnamentUi;
   ItemUI* m_pOtherUi;
   cocos2d::ui::ImageView* m_pShopBtn;
};

#endif /* RolePopUpUI_hpp */
