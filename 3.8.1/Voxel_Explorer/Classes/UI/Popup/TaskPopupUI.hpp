//
//  ChildPopupUI.hpp
//  Voxel_Explorer
//  任务商店
//  Created by 创李 on 15/12/1.
//
//

#ifndef TaskPopupUI_hpp
#define TaskPopupUI_hpp

#include "PopupUILayer.h"

class TaskPopupUI:public PopupUILayer {
    
    TaskPopupUI();
public:
    virtual ~TaskPopupUI();
    CREATE_FUNC(TaskPopupUI);
    virtual bool initUi() override;
    virtual void refreshUIView() override ;
    virtual bool addEvents() override;
};

#endif /* TaskPopupUI_hpp */
