//
//  EquipmentPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/15.
//
//

#ifndef BreadDownPopupUI_hpp
#define BreadDownPopupUI_hpp
#include "PopupUILayer.h"
#include "PickableItemProperty.hpp"
class BagEquipLayer;
class TGridView;
class BagMangerLayerUI;
class  BreadDownPopupUI : public PopupUILayer{
    BreadDownPopupUI();
    
public:
    ~BreadDownPopupUI();
    CREATE_FUNC(BreadDownPopupUI);
    
    virtual bool initUi() override;
    virtual bool addEvents() override;
    void refreshUIView() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    void update(float dt) override;
private:
    void onClickClose(Ref* ref);
    void updateMaterialDataItems();
    void showSucessBreadDownPopup( void* datas);
    void onEventPlayerBagItemUpdate(cocos2d::EventCustom *sender);
private:
    BagEquipLayer* m_pBagEquipLayer;
    cocos2d::ui::TextBMFont*  m_pEquipTitleText;
    TGridView* m_pMaterialGridView;
    BagMangerLayerUI* m_pBagManagerLayer;
    bool m_bIsCallBack;
};

#endif /* BreadDownPopupUI_hpp */
