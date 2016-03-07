//
//  BagShopLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#ifndef BagShopLayer_hpp
#define BagShopLayer_hpp
#include "BagLayer.h"

class BagShopLayer:public BagLayer {
    BagShopLayer();
public:
    CREATE_FUNC(BagShopLayer);
    virtual ~BagShopLayer();
    virtual void refreshUIView() override;
protected:
  
    virtual std::vector<PickableItemProperty*> getItems() override;
    virtual void bagItemOpe(int itemId) override;
    void sortItem(eSortBagType type,std::vector<PickableItemProperty*>& items) override;
};

#endif /* BagShopLayer_hpp */
