//
//  ItemShopPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#ifndef ItemShopSellPopupUI_hpp
#define ItemShopSellPopupUI_hpp

#include "ItemShopBuyPopupUI.hpp"

class PickableItemProperty;
class ItemShopSellPopupUI:public ItemShopBuyPopupUI {
    
    ItemShopSellPopupUI();
public:

    CREATE_FUNC(ItemShopSellPopupUI);
    virtual ~ItemShopSellPopupUI();
    virtual void refreshUIView() override;
protected:
    virtual PickableItemProperty* getItemIdProperty()const override;
private:
    void onClickSell(Ref* ref);
    void itemSell();
    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) override;
};


#endif /* ItemShopSellPopupUI_hpp */
