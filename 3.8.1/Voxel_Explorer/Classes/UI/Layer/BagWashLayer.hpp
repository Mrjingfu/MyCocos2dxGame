//
//  BagEquipLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/15.
//
//

#ifndef BagWashLayer_hpp
#define BagWashLayer_hpp

#include "BagEquipLayer.hpp"

class  BagWashLayer:public BagEquipLayer{
    
    BagWashLayer();
public:
    CREATE_FUNC(BagWashLayer);
    ~BagWashLayer();
private:
    virtual void bagItemOpe(int itemId) override;
    std::vector<PickableItemProperty*> getItems() override;
};

#endif /* BagEquipLayer_hpp */
