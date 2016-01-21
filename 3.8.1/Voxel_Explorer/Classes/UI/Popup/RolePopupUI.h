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

class BagLayer;
class RoleLayer;
class  RolePopupUI:public PopupUILayer {
    RolePopupUI();

public:
    CREATE_FUNC(RolePopupUI);
    virtual ~RolePopupUI();
    virtual bool initUi() override;
    void onEnter() override;
    void onExit()override;
    void refreshUIView() override;
    void updateItems(bool _isOpenIdentify = false);//更新背包角色信息
    
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
private:
    
    void onClickColse(Ref* ref);
    void onClickChnageBag(Ref*);
    void onClickShop(Ref*);
 
    void onEventUpdateData(cocos2d::EventCustom *sender);

    void onEventBagExtend(cocos2d::EventCustom *sender);  //背包扩展成功
    void onEventBagExtendHasReachMaxtimes(cocos2d::EventCustom *sender);//背包扩展达到上限
    
    void resetBagLayer();

private:
   BagLayer*      m_pBagLayer;
   RoleLayer*     m_pRoleLayer;
   cocos2d::ui::Button* m_pBtnClose;
   cocos2d::ui::Button* m_pBtnChangeBag;


  
};

#endif /* RolePopUpUI_hpp */
