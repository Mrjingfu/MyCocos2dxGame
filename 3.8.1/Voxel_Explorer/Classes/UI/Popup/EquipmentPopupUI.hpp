//
//  EquipmentPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/15.
//
//

#ifndef EquipmentPopupUI_hpp
#define EquipmentPopupUI_hpp
#include "PopupUILayer.h"
class BagEquipLayer;
class TGridView;
class BagMangerLayerUI;
class  EquipmentPopupUI : public PopupUILayer{
    EquipmentPopupUI();
    
public:
    ~EquipmentPopupUI();
    CREATE_FUNC(EquipmentPopupUI);
    
    virtual bool initUi() override;
    virtual bool addEvents() override;
    void refreshUIView() override;
    virtual void onEnter() override;
    virtual void onExit() override;
private:
     void onClickClose(Ref* ref);
    void updateMaterialDataItems();
    void onEventPlayerBagItemUpdate(cocos2d::EventCustom *sender);
private:
    BagEquipLayer* m_pBagEquipLayer;
    cocos2d::ui::TextBMFont*  m_pEquipTitleText;
    TGridView* m_pMaterialGridView;
    BagMangerLayerUI* m_pBagManagerLayer;
    
};

#endif /* EquipmentPopupUI_hpp */
