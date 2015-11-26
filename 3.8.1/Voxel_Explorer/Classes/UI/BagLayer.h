//
//  BagLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/24.
//
//

#ifndef BagLayer_hpp
#define BagLayer_hpp
#include "ui/CocosGUI.h"
#include "TGridView.h"
class PickableItemProperty;
class BagMangerLayerUI;

class SellItem :public Ref
{
    SellItem():m_nItemId(-1),m_nItemCount(1){};
public:
    virtual ~SellItem(){};
    static SellItem* create(int itemId,int count =1);
    void setItemCount(int count){ m_nItemCount +=count;};
    int getItemId() const{return m_nItemId;};
    int getItemCount() const{return m_nItemCount;};
private:
    int m_nItemId;
    int m_nItemCount;
};

class BagLayer:public cocos2d::ui::Layout
{
    BagLayer();
public:
    enum eSortBagType{
        SBT_ALL,
        SBT_EQUIP,
        SBT_POTION
    };
    virtual ~BagLayer();
    static BagLayer* create(cocos2d::Size size);
    bool init(cocos2d::Size size);
    //更新背包界面
    void updateBagProp(bool isOpenIdentify= false,eSortBagType sortType = SBT_ALL);
    void selectItemEvent(Ref *pSender, TGridView::EventType type);
    //扩展背包
    void extendBag();
    bool isIdentIfy(){return _isOpenIdentify;}
    //设置出售状态
    void setShopSellStatus(bool status){m_bIsShopSell = status;}
    const cocos2d::Vector<SellItem*>& getSellItems() const{return m_vSellItems;}
    void clearSellItems(){m_vSellItems.clear();}
    void removeItemForSell(int itemId);
    //更新商店界面
    void updateShopItems();
private:
    //显示道具详情
    void showItemInfo(int itemId);
    //道具出售操作
    void shopSellOpe(int index);
    //更新贩卖道具数据
    void updateItemSplit(void*,SellItem* ,int ItemId);
    std::vector<PickableItemProperty*> getItems(eSortBagType sortType);
private:
    cocos2d::Vector<SellItem*> m_vSellItems;        //需要贩卖的道具
    
    bool _isOpenIdentify;
    bool m_bIsShopSell;
    TGridView* m_pGridView;

    BagMangerLayerUI* m_BagMsgLayer;
};

#endif /* BagLayer_hpp */
