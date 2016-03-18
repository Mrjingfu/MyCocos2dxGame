//
//  EquipmentPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/15.
//
//

#ifndef BreakDownPopupUI_hpp
#define BreakDownPopupUI_hpp
#include "PopupUILayer.h"
#include "PickableItemProperty.hpp"
class BagBreakDownLayer;
class TGridView;
class BagMangerLayerUI;
class  BreakDownPopupUI : public PopupUILayer{
    BreakDownPopupUI();
    
public:
    ~BreakDownPopupUI();
    CREATE_FUNC(BreakDownPopupUI);
    
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
    BagBreakDownLayer* m_pBagEquipLayer;
    cocos2d::ui::TextBMFont*  m_pEquipTitleText;
    TGridView* m_pMaterialGridView;
    BagMangerLayerUI* m_pBagManagerLayer;
    bool m_bIsCallBack;
};

#endif /* BreakDownPopupUI_hpp */
