//
//  WeirdoPopupUI.hpp
//  Voxel_Explorer
//  赌博商店
//  Created by 创李 on 15/12/1.
//
//

#ifndef GamblePopupUI_hpp
#define GamblePopupUI_hpp

#include "PopupUILayer.h"

class GamblePopupUI:public PopupUILayer {
    
    GamblePopupUI();
public:
    virtual ~GamblePopupUI();
    CREATE_FUNC(GamblePopupUI);
    virtual bool initUi() override;
    virtual void refreshUIView() override ;
    virtual bool addEvents() override;
};

#endif /* WeirdoPopupUI_hpp */
