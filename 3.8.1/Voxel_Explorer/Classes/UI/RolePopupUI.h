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

class BagLayerUI;
class  RolePopupUI:public PopupUILayer {
    RolePopupUI();

public:
    CREATE_FUNC(RolePopupUI);
    virtual ~RolePopupUI();
    virtual bool initUi() override;
    void onEnter() override;
    void onExit()override;
    void updateItems();
    void setStateIdentify(bool state){ _isOpenIdentify = state;}
private:
    
    void onClickColse(Ref* ref);
    void onClickChnageBag(Ref*);
    void onClickSortAll(Ref*,Widget::TouchEventType);
    void onClickSortEquip(Ref*,Widget::TouchEventType);
    void onClickSortPotion(Ref*,Widget::TouchEventType);
    
    void selectItemEvent(Ref *pSender, TGridView::EventType type);
 
    void onEventUpdateData(cocos2d::EventCustom *sender);
    void onEventEquipWeapon(cocos2d::EventCustom *sender);
    void onEventEquipArmor(cocos2d::EventCustom *sender);
    void onEventEquipOrnament(cocos2d::EventCustom *sender);
    void onEventExtendBag(cocos2d::EventCustom *sender);
    //设置已经装备道具位置
    void setEquipItem(cocos2d::Vec2 pt,std::string icon);
    
private:
   bool _isOpenIdentify;
   TGridView* m_pGridView;
   cocos2d::ui::ImageView* m_pGridFrame;
    cocos2d::ui::Layout* m_pEquipFrame;
   cocos2d::ui::Button* m_pBtnClose;
   cocos2d::ui::Button* m_pBtnAllBag;
   cocos2d::ui::Button* m_pBtnChangeBag;
   cocos2d::ui::Button* m_pBtnWeaponBag;
   cocos2d::ui::Button* m_pBtnPotionBag;
   cocos2d::ui::ImageView* m_pWeaponUi;
   cocos2d::ui::ImageView* m_pArmorUi;
   cocos2d::ui::ImageView* m_pOrnamentUi;
   cocos2d::ui::ImageView* m_pSecondWeaponUi;
    
    cocos2d::ui::Text*  m_pRoleHp;
    cocos2d::ui::Text*  m_pRoleMp;
    cocos2d::ui::Text*  m_pRoleExp;
    cocos2d::ui::Text*  m_pRoleLightDis;
    cocos2d::ui::Text*  m_pRoleSearchDis;
    cocos2d::ui::Text*  m_pRoleMargicFind;
    cocos2d::ui::Text*  m_pRoleCriticalStrike;
    cocos2d::ui::Text*  m_pRoleBlock;
    cocos2d::ui::Text*  m_pRoleDodge;
    
   cocos2d::ui::ImageView* m_pShopBtn;
    
    BagLayerUI* m_BagLayer;
};

#endif /* RolePopUpUI_hpp */
