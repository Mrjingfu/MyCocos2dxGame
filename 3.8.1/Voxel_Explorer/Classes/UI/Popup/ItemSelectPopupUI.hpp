//
//  ItemShopPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#ifndef ItemSelectPopupUI_hpp
#define ItemSelectPopupUI_hpp

#include "ItemPopupUI.h"

class PickableItemProperty;
class ItemSelectPopupUI:public ItemPopupUI {
    
    ItemSelectPopupUI();
public:

    CREATE_FUNC(ItemSelectPopupUI);
    virtual ~ItemSelectPopupUI();
    virtual void refreshUIView() override;
private:
    void updateBottomUi() override;
    void onClickSelect(Ref* ref);
    void onClickCancel(Ref* ref);
    
};


#endif /* ItemSelectPopupUI_hpp */
