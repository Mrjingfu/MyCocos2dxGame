//
//  ItemShopPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#ifndef ItemBreadDownPopupUI_hpp
#define ItemBreadDownPopupUI_hpp

#include "ItemPopupUI.h"

class PickableItemProperty;
class ItemBreadDownPopupUI:public ItemPopupUI {
    
    ItemBreadDownPopupUI();
public:

    CREATE_FUNC(ItemBreadDownPopupUI);
    virtual ~ItemBreadDownPopupUI();
    virtual void refreshUIView() override;
private:
    void onClickBreadDown(Ref* ref);
    void onClickCancel(Ref* ref);
};


#endif /* ItemBreadDownPopupUI */
