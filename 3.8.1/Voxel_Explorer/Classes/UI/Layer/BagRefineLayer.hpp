//
//  BagEquipLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/15.
//
//

#ifndef BagRefineLayer_hpp
#define BagRefineLayer_hpp

#include "BagLayer.h"

class  BagRefineLayer:public BagLayer{
    
    BagRefineLayer();
public:
    CREATE_FUNC(BagRefineLayer);
    virtual bool init() override;
    ~BagRefineLayer();
private:
    virtual void bagItemOpe(int itemId) override;
    std::vector<PickableItemProperty*> getItems() override;
};

#endif /* BagRefineLayer_hpp */
