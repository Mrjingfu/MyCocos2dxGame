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
    const cocos2d::Vector<SellItem*>& getSellItems() const{return m_vSellItems;}
    virtual void removeItemForSell(int itemId);
    void clearSellItems(){m_vSellItems.clear();}
    void updatePopupUI();
protected:
  
    virtual std::vector<PickableItemProperty*> getItems() override;
    virtual void bagItemOpe(int itemId) override;
    void updateItemSplit(void*,SellItem* ,int ItemId);
    
private:
    cocos2d::Vector<SellItem*> m_vSellItems;        //需要贩卖的道具
};

#endif /* BagShopLayer_hpp */
