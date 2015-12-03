//
//  ShopPopupUI.hpp
//  Voxel_Explorer
//  武器商店
//  Created by 创李 on 15/10/26.
//
//

#ifndef WeaponShopPopupUI_hpp
#define WeaponShopPopupUI_hpp

#include "ShopPopupUI.h"

class WeaponShopPopupUI:public ShopPopupUI {
    WeaponShopPopupUI();
    
public:
    CREATE_FUNC(WeaponShopPopupUI);
    virtual ~WeaponShopPopupUI();
    virtual bool init() override;
    virtual bool addEvents() override;
    virtual const std::vector<PickableItemProperty*>& getShopItems() const override;
    virtual void shopItemOpe(int itemId) override;
};

#endif /* WeaponShopPopupUI_hpp */
