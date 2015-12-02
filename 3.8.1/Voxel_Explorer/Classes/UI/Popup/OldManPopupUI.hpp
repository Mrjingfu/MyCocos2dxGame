//
//  OldManPopupUI.hpp
//  Voxel_Explorer
//  智者
//  Created by 创李 on 15/12/1.
//
//

#ifndef OldManPopupUI_hpp
#define OldManPopupUI_hpp

#include "PopupUILayer.h"

class OldManPopupUI:public PopupUILayer {
    
    OldManPopupUI();
public:
    virtual ~OldManPopupUI();
    CREATE_FUNC(OldManPopupUI);
    virtual bool initUi() override;
    virtual void refreshUIView() override ;
    virtual bool addEvents() override;
};

#endif /* OldManPopupUI_hpp */
