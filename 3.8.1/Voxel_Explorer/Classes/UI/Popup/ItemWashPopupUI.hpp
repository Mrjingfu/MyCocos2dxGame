//
//  ItemShopPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#ifndef ItemWashPopupUI_hpp
#define ItemWashPopupUI_hpp

#include "ItemPopupUI.h"
#include "PickableItemProperty.hpp"
class PickableItemProperty;
class ItemWashPopupUI:public ItemPopupUI {
    
    ItemWashPopupUI();
public:

    CREATE_FUNC(ItemWashPopupUI);
    virtual ~ItemWashPopupUI();
    virtual void refreshUIView() override;
    void setOldItemProp( PickableItemProperty* itemProp);
private:
    void IdentifyEquiipFrame() override;
    void updateBottomUi() override;
    void onClickConfirm(Ref* ref);
    void onKeyBackClick() override;
private:
    PickableItemProperty* m_pOldItemProp;
};


#endif /* ItemWashPopupUI_hpp */
