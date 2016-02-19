//
//  ShopPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#ifndef ShopPopupUI_hpp
#define ShopPopupUI_hpp

#include "PopupUILayer.h"
#include "TGridView.h"
#include "NpcDataManager.hpp"
class BagShopLayer;
class BagMangerLayerUI;
class PickableItemProperty;
class ShopPopupUI:public PopupUILayer {
protected:
    ShopPopupUI();
    
public:
    enum eShopType{
        ST_WEAPON,
        ST_MAGIC,
        ST_GAMBLE,
        ST_ALCHEMY
    };
    
    virtual ~ShopPopupUI();
    virtual bool init() override;
    virtual bool addEvents() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    //更新商店购买界面
    virtual void updateShopBuyItems();
    virtual void refreshUIView() override;
    virtual void updateShopDataItems();
    virtual void setShopTitle(const std::string& titleKey);
    virtual const std::vector<PickableItemProperty*>& getShopItems() const = 0;
    virtual void shopItemOpe(int itemId);
protected:
    void onClickClose(Ref* ref);
    virtual void onEventUpdateNpcData(cocos2d::EventCustom *sender);
     void selectItemEvent(Ref *pSender, TGridView::EventType type);
    
protected:
    cocos2d::ui::Button* m_pBtnClose;
    eShopType           m_eShopType;
    cocos2d::ui::TextBMFont*  m_pShopTitleText;
    BagShopLayer*       m_pBagLayer;
    TGridView*          m_pShopGridView;
    BagMangerLayerUI*   m_pShopMangerLayer;

};

#endif /* ShopPopupUI_hpp */
