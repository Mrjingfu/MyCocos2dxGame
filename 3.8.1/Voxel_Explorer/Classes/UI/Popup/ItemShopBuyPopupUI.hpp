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
protected:
    ItemShopBuyPopupUI();
public:
  
    CREATE_FUNC(ItemShopBuyPopupUI);
    virtual ~ItemShopBuyPopupUI();
    virtual bool initBottom() override;
    virtual void refreshUIView() override;
    virtual void updateUseItem() override;
    virtual void setItemShopProp(ShopPopupUI::eShopType type,int itemId) ;
    virtual PickableItemProperty* getItemIdProperty()const override;
protected:
    
    virtual void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
private:
    void onClickBuy(Ref* ref);
protected:
    ShopPopupUI::eShopType   m_eShopType;
    cocos2d::ui::Slider*     m_pItemSlider;
    cocos2d::ui::TextBMFont*       m_pSellCount;
   };


#endif /* ItemShopBuyPopupUI_hpp */
