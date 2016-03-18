//
//  BreadDownSettlementPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/17.
//
//

#ifndef BreadDownSettlementPopupUI_hpp
#define BreadDownSettlementPopupUI_hpp

#include "PopupUILayer.h"
#include "PickableItemProperty.hpp"
class BreadDownSettlementPopupUI :public PopupUILayer{
    BreadDownSettlementPopupUI();
    
public:
    CREATE_FUNC(BreadDownSettlementPopupUI);
    ~BreadDownSettlementPopupUI();
    bool initUi() override;
    cocos2d::ui::Layout* createBreadDownItem(std::string icon,CChaosNumber count );
    bool addEvents() override;
    void updateUIView(const std::map<PickableItem::PickableItemType,CChaosNumber>* reslutDatas) ;
private:
    void onClickConfirm(cocos2d::Ref* ref);
private:

    cocos2d::ui::Layout* m_pMaterialFrame;
    cocos2d::ui::Button* m_pBtnConfirm;
};

#endif /* BreadDownSettlementPopupUI_hpp */
