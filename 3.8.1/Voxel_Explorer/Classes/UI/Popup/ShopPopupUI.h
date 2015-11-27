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
class BagShopLayer;
class BagMangerLayerUI;
class ShopPopupUI:public PopupUILayer {
    ShopPopupUI();
    
public:
    CREATE_FUNC(ShopPopupUI);
    virtual ~ShopPopupUI();
    virtual bool init() override;
    virtual bool addEvents() override;
    
    //更新商店购买界面
    void updateShopBuyItems();
    void refreshUIView() override;
private:

    void onClickFrameBuy(Ref*,cocos2d::ui::Widget::TouchEventType);
    void selectItemEvent(Ref *pSender, TGridView::EventType type);
    
    private:

    cocos2d::ui::Button* m_pBtnBuyFrame;
    
    
    BagShopLayer*     m_pBagLayer;
    TGridView*    m_pShopGridView;
    BagMangerLayerUI* m_pShopMangerLayer;

};

#endif /* ShopPopupUI_hpp */
