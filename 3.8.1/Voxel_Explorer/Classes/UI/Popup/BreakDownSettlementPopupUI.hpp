//
//  BreadDownSettlementPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/17.
//
//

#ifndef BreakDownSettlementPopupUI_hpp
#define BreakDownSettlementPopupUI_hpp

#include "PopupUILayer.h"
#include "PickableItemProperty.hpp"
class BreakDownSettlementPopupUI :public PopupUILayer{
    BreakDownSettlementPopupUI();
    
public:
    CREATE_FUNC(BreakDownSettlementPopupUI);
    ~BreakDownSettlementPopupUI();
    bool initUi() override;
    cocos2d::ui::Layout* createBreakDownItem(std::string icon,CChaosNumber count );
    bool addEvents() override;
    void updateUIView(const std::map<PickableItem::PickableItemType,CChaosNumber>* reslutDatas) ;
private:
    void onClickConfirm(cocos2d::Ref* ref);
private:

    cocos2d::ui::Layout* m_pMaterialFrame;
    cocos2d::ui::Button* m_pBtnConfirm;
};

#endif /* BreakDownSettlementPopupUI_hpp */
