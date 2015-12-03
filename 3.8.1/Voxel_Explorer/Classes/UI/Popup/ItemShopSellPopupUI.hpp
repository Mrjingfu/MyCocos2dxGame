//
//  ItemShopPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#ifndef ItemShopSellPopupUI_hpp
#define ItemShopSellPopupUI_hpp

#include "ItemPopupUI.h"
class PickableItemProperty;
class ItemShopSellPopupUI:public ItemPopupUI {
    
    ItemShopSellPopupUI();
public:

    CREATE_FUNC(ItemShopSellPopupUI);
    virtual ~ItemShopSellPopupUI();
    virtual bool initUi() override;
    virtual bool addEvents() override;
    virtual void updateItemPopup(int itemId) override;
protected:
    virtual PickableItemProperty* getItemIdProperty()const override;
private:
    void onClickSell(Ref* ref);
    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
private:
   
    cocos2d::ui::Slider*     m_pItemSlider;
    cocos2d::ui::Text*       m_pSellCount;
   };


#endif /* ItemShopSellPopupUI_hpp */
