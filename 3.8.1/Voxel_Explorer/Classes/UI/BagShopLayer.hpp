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
    static BagShopLayer* create(cocos2d::Size size);
    virtual ~BagShopLayer();
    virtual void selectItemEvent(Ref *pSender, TGridView::EventType type);
    virtual void updateBagProp(bool isOpenIdentify= false,eSortBagType sortType = SBT_ALL);
    const cocos2d::Vector<SellItem*>& getSellItems() const{return m_vSellItems;}
    virtual void removeItemForSell(int itemId);
    void clearSellItems(){m_vSellItems.clear();}
protected:
   
    virtual std::vector<PickableItemProperty*> getItems(eSortBagType sortType);
    void shopSellOpe(int index);
    void updateItemSplit(void*,SellItem* ,int ItemId);
    
private:
    cocos2d::Vector<SellItem*> m_vSellItems;        //需要贩卖的道具
};

#endif /* BagShopLayer_hpp */
