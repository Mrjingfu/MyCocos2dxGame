//
//  ItemShopPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#ifndef ItemShopBuyPopupUI_hpp
#define ItemShopBuyPopupUI_hpp

#include "ItemPopupUI.h"
#include "ShopPopupUI.h"
class PickableItemProperty;
class ItemShopBuyPopupUI:public ItemPopupUI {
    
    ItemShopBuyPopupUI();
public:
  
    CREATE_FUNC(ItemShopBuyPopupUI);
    virtual ~ItemShopBuyPopupUI();
    virtual bool initUi() override;
    virtual bool addEvents() override;
    virtual void updateItemPopup(ShopPopupUI::eShopType type,int itemId) ;
protected:
    virtual PickableItemProperty* getItemIdProperty()const override;
private:
    void onClickBuy(Ref* ref);
    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
private:
    ShopPopupUI::eShopType   m_eShopType;
    cocos2d::ui::Slider*     m_pItemSlider;
    cocos2d::ui::Text*       m_pSellCount;
   };


#endif /* ItemShopBuyPopupUI_hpp */
