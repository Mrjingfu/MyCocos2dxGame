//
//  BagEquipLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/15.
//
//

#ifndef BagBreakDownLayer_hpp
#define BagBreakDownLayer_hpp

#include "BagLayer.h"

class  BagBreakDownLayer:public BagLayer{
protected:
    BagBreakDownLayer();
public:
    CREATE_FUNC(BagBreakDownLayer);
    ~BagBreakDownLayer();
    virtual bool init() override;
protected:
    virtual std::vector<PickableItemProperty*> getItems() override;
    virtual void bagItemOpe(int itemId) override;
};

#endif /* BagBreakDownLayer_hpp */
