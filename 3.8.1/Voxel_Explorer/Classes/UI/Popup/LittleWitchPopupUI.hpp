//
//  LittleWitchPopupUI.hpp
//  Voxel_Explorer
//  随机事件
//  Created by 创李 on 15/12/1.
//
//

#ifndef LittleWitchPopupUI_hpp
#define LittleWitchPopupUI_hpp

#include "PopupUILayer.h"

class LittleWitchPopupUI:public PopupUILayer {
    
    LittleWitchPopupUI();
public:
    virtual ~LittleWitchPopupUI();
    CREATE_FUNC(LittleWitchPopupUI);
    virtual bool initUi() override;
    virtual void refreshUIView() override ;
    virtual bool addEvents() override;
};

#endif /* LittleWitchPopupUI_hpp */
