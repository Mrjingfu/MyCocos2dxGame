//
//  WeirdoPopupUI.hpp
//  Voxel_Explorer
//  赌博商店
//  Created by 创李 on 15/12/1.
//
//

#ifndef GambleShopPopupUI_hpp
#define GambleShopPopupUI_hpp

#include "ShopPopupUI.h"

class GambleShopPopupUI:public ShopPopupUI {
    
    GambleShopPopupUI();
public:
    virtual ~GambleShopPopupUI();
    CREATE_FUNC(GambleShopPopupUI);
    virtual bool init() override;
    virtual bool addEvents() override;
     virtual const std::vector<PickableItemProperty*>& getShopItems() const override;
    virtual void updateShopDataItems() override;
    
};

#endif /* GambleShopPopupUI_hpp */
