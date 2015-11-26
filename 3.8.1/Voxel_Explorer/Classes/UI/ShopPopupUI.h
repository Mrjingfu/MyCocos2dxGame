//
//  ShopPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#ifndef ShopPopupUI_hpp
#define ShopPopupUI_hpp

#include "PopupUILayer.h"
#include "TGridView.h"
class BagLayer;
class BagMangerLayerUI;
class ShopPopupUI:public PopupUILayer {
    ShopPopupUI();
    
public:
    CREATE_FUNC(ShopPopupUI);
    virtual ~ShopPopupUI();
    virtual bool init() override;
    virtual bool addEvents() override;
    
    void updateShopSellItems();
    void updateItems();
private:
    void onClickSortAll(Ref*,cocos2d::ui::Widget::TouchEventType);
    void onClickSortEquip(Ref*,cocos2d::ui::Widget::TouchEventType);
    void onClickSortPotion(Ref*,cocos2d::ui::Widget::TouchEventType);
    void selectItemEvent(Ref *pSender, TGridView::EventType type);
    
    private:
    cocos2d::ui::Button* m_pBtnAllBag;
    cocos2d::ui::Button* m_pBtnWeaponBag;
    cocos2d::ui::Button* m_pBtnPotionBag;
    
    BagLayer*     m_pBagLayer;
    TGridView*    m_pShopGridView;
    BagMangerLayerUI* m_pShopMangerLayer;
};

#endif /* ShopPopupUI_hpp */
