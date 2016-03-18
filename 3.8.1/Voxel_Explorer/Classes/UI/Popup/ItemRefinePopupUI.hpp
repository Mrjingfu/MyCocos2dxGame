//
//  ItemShopPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#ifndef ItemRefinePopupUI_hpp
#define ItemRefinePopupUI_hpp

#include "ItemPopupUI.h"
#include "PickableItemProperty.hpp"
class PickableItemProperty;
class ItemRefinePopupUI:public ItemPopupUI {
    
    ItemRefinePopupUI();
public:

    CREATE_FUNC(ItemRefinePopupUI);
    virtual ~ItemRefinePopupUI();
    virtual void refreshUIView() override;
    void setOldItemProp( PickableItemProperty* itemProp);
private:
    std::string calculateFloatDiff(CChaosNumber targetNum ,CChaosNumber sourceNum);
    void IdentifyEquiipFrame() override;
    void updateBottomUi() override;
    void onClickConfirm(Ref* ref);
    void onKeyBackClick() override;
private:
    PickableItemProperty* m_pOldItemProp;
};


#endif /* ItemRefinePopupUI_hpp */
