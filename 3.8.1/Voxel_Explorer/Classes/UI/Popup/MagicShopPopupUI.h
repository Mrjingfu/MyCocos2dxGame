//
//  ShopPopupUI.hpp
//  Voxel_Explorer
//  魔法物品商店
//  Created by 创李 on 15/10/26.
//
//

#ifndef MagicShopPopupUI_hpp
#define MagicShopPopupUI_hpp

#include "ShopPopupUI.h"
#include "TGridView.h"

class MagicShopPopupUI:public ShopPopupUI {
    MagicShopPopupUI();
    
public:
    CREATE_FUNC(MagicShopPopupUI);
    virtual ~MagicShopPopupUI();
    virtual bool init() override;
    virtual bool addEvents() override;
    virtual const std::vector<PickableItemProperty*>& getShopItems() const override;
    virtual void shopItemOpe(int itemId) override;
private:


};

#endif /* MagicShopPopupUI_hpp */
