//
//  NursePopupUI.hpp
//  Voxel_Explorer
//  护士站
//  Created by 创李 on 15/12/1.
//
//

#ifndef NursePopupUI_hpp
#define NursePopupUI_hpp

#include "PopupUILayer.h"

class NursePopupUI:public PopupUILayer {
    
    NursePopupUI();
public:
    virtual ~NursePopupUI();
    CREATE_FUNC(NursePopupUI);
    virtual bool initUi() override;
    virtual void refreshUIView() override ;
    virtual bool addEvents() override;
};

#endif /* NursePopupUI_hpp */
