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
protected:
    ShopPopupUI();
    
public:
    virtual ~ShopPopupUI();
    virtual bool init() override;
    virtual bool addEvents() override;
    
    //更新商店购买界面
    virtual void updateShopBuyItems();
    virtual void refreshUIView() override;
    virtual void updateShopDataItems() = 0;
    virtual void shopItemOpe(int itemId) = 0;
protected:

    virtual void selectItemEvent(Ref *pSender, TGridView::EventType type);
    
protected:
    cocos2d::ui::Button* m_pBtnBuyFrame;
    BagShopLayer*     m_pBagLayer;
    TGridView*    m_pShopGridView;
    BagMangerLayerUI* m_pShopMangerLayer;

};

#endif /* ShopPopupUI_hpp */
