//
//  BagEquipLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/15.
//
//

#ifndef BagWashLayer_hpp
#define BagWashLayer_hpp

#include "BagLayer.h"

class  BagWashLayer:public BagLayer{
    
    BagWashLayer();
public:
    CREATE_FUNC(BagWashLayer);
    virtual bool init() override;
    ~BagWashLayer();
private:
    virtual void bagItemOpe(int itemId) override;
    std::vector<PickableItemProperty*> getItems() override;
};

#endif /* BagEquipLayer_hpp */
