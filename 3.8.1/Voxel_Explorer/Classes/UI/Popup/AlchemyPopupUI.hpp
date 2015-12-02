//
//  OldLadyPopupUI.hpp
//  Voxel_Explorer
//   炼金商店
//  Created by 创李 on 15/12/1.
//
//

#ifndef AlchemyPopupUI_hpp
#define AlchemyPopupUI_hpp

#include "PopupUILayer.h"

class AlchemyPopupUI:public PopupUILayer {
    
    AlchemyPopupUI();
public:
    virtual ~AlchemyPopupUI();
    CREATE_FUNC(AlchemyPopupUI);
    virtual bool initUi() override;
    virtual void refreshUIView() override ;
    virtual bool addEvents() override;
};

#endif /* AlchemyPopupUI_hpp */
