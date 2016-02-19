//
//  OldLadyPopupUI.hpp
//  Voxel_Explorer
//   炼金商店
//  Created by 创李 on 15/12/1.
//
//

#ifndef AlchemyShopPopupUI_hpp
#define AlchemyShopPopupUI_hpp

#include "ShopPopupUI.h"

class AlchemyShopPopupUI:public ShopPopupUI {
    
    AlchemyShopPopupUI();
public:
    virtual ~AlchemyShopPopupUI();
    CREATE_FUNC(AlchemyShopPopupUI);
    virtual bool init() override;
    virtual bool addEvents() override;
    virtual const std::vector<PickableItemProperty*>& getShopItems() const override;
   
};

#endif /* AlchemyShopPopupUI_hpp */
