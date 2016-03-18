//
//  ItemShopPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#ifndef ItemBreakDownPopupUI_hpp
#define ItemBreakDownPopupUI_hpp

#include "ItemPopupUI.h"

class PickableItemProperty;
class ItemBreakDownPopupUI:public ItemPopupUI {
    
    ItemBreakDownPopupUI();
public:

    CREATE_FUNC(ItemBreakDownPopupUI);
    virtual ~ItemBreakDownPopupUI();
    virtual void refreshUIView() override;
private:
    void onClickBreadDown(Ref* ref);
    void onClickCancel(Ref* ref);
};


#endif /* ItemBreadDownPopupUI */
