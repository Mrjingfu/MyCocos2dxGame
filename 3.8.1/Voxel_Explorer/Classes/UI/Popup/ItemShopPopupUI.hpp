//
//  ItemShopPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#ifndef ItemShopPopupUI_hpp
#define ItemShopPopupUI_hpp

#include "ItemPopupUI.h"
class PickableItemProperty;
class ItemShopPopupUI:public ItemPopupUI {
    
    ItemShopPopupUI();
public:
    enum eItemShopType{
        IST_BUY,
        IST_SELL
    };
    CREATE_FUNC(ItemShopPopupUI);
    virtual ~ItemShopPopupUI();
    virtual bool initUi() override;
    virtual bool addEvents() override;
    virtual void updateItemPopup(eItemShopType type,int itemId);
private:
    void onClickBuy(Ref* ref);
    void onClickSell(Ref* ref);
    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
private:
    eItemShopType m_eItemShopType;
    cocos2d::ui::Slider*     m_pItemSlider;
    cocos2d::ui::Text*       m_pSellCount;
   };


#endif /* ItemShopPopupUI_hpp */
