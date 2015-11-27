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
protected:
    BagLayer();
public:
    enum eSortBagType{
        SBT_ALL,
        SBT_EQUIP,
        SBT_POTION
    };
    virtual ~BagLayer();
    static BagLayer* create(cocos2d::Size size);
    virtual bool init(cocos2d::Size size);
    //更新背包界面
    virtual void updateBagProp(bool isOpenIdentify= false,eSortBagType sortType = SBT_ALL);
    virtual void selectItemEvent(Ref *pSender, TGridView::EventType type);
    //更新商店界面
    virtual void updatePopupItems();
    //扩展背包
    void extendBag();
    bool isIdentIfy(){return _isOpenIdentify;}
protected:
    //显示道具详情
    void showItemInfo(int itemId);
    virtual std::vector<PickableItemProperty*> getItems(eSortBagType sortType);
protected:
    
    
    bool _isOpenIdentify;
    TGridView* m_pGridView;
    BagMangerLayerUI* m_BagMsgLayer;
};

#endif /* BagLayer_hpp */
