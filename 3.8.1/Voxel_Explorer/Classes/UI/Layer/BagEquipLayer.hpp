//
//  BagEquipLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/15.
//
//

#ifndef BagEquipLayer_hpp
#define BagEquipLayer_hpp

#include "BagLayer.h"

class  BagEquipLayer:public BagLayer{
protected:
    BagEquipLayer();
public:
    CREATE_FUNC(BagEquipLayer);
    ~BagEquipLayer();
    virtual bool init() override;
protected:
    virtual std::vector<PickableItemProperty*> getItems() override;
    virtual void bagItemOpe(int itemId) override;
};

#endif /* BagEquipLayer_hpp */
