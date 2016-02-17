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
#include "WrapperUILayer.h"
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

class BagLayer:public WrapperUILayer
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
    CREATE_FUNC(BagLayer);
    virtual bool init() override;
    virtual void refreshUIView() override;
    virtual void selectItemEvent(Ref *pSender, TGridView::EventType type);
    void extendBag();
    bool isIdentIfy(){return m_bIsIndetify;}
    void setIdentIfy(bool _isIndetify){m_bIsIndetify = _isIndetify;}
    void setSortBtnEnable(bool allEnable,bool equipEnable,bool potionEnable);
protected:
    virtual void bagItemOpe(int itemId);
    virtual std::vector<PickableItemProperty*> getItems();
    virtual void onClickSortAll(Ref*,cocos2d::ui::Widget::TouchEventType);
    virtual void onClickSortEquip(Ref*,cocos2d::ui::Widget::TouchEventType);
    virtual void onClickSortPotion(Ref*,cocos2d::ui::Widget::TouchEventType);
    void onClickBagExtend(Ref* ref);
    int getItemIndexForVector(const std::vector<PickableItemProperty*>& items, int itemId) const ;
protected:
    
    cocos2d::ui::Button* m_pBtnAllBag;
    cocos2d::ui::Button* m_pBtnWeaponBag;
    cocos2d::ui::Button* m_pBtnPotionBag;
    cocos2d::ui::Button* m_pBtnBagExtend;
    bool m_bIsIndetify;
    TGridView* m_pGridView;
    BagMangerLayerUI* m_BagMsgLayer;
};

#endif /* BagLayer_hpp */
