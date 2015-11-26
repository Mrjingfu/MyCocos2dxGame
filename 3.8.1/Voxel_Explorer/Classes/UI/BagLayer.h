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
    void updateBagProp(bool isOpenIdentify= false,eSortBagType sortType = SBT_ALL);
    void selectItemEvent(Ref *pSender, TGridView::EventType type);
    void extendBag();
    bool isIdentIfy(){return _isOpenIdentify;}
    void setShopSellStatus(bool status){m_bIsShopSell = status;}
    const std::vector<int>& getSellItems() const{return m_vSellItems;}
    void clearSellItems(){m_vSellItems.clear();}
private:
    void showItemInfo(int itemId);
    void shopSellOpe(int index);
    std::vector<PickableItemProperty*> getItems(eSortBagType sortType);
private:
    std::vector<int> m_vSellItems;
    
    bool _isOpenIdentify;
    bool m_bIsShopSell;
    TGridView* m_pGridView;
    eSortBagType m_eBagSortType;
    BagMangerLayerUI* m_BagMsgLayer;
};

#endif /* BagLayer_hpp */
