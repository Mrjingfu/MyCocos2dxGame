//
//  MainUiLayer.h
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/16.
//
//

#ifndef MainUiLayer_h
#define MainUiLayer_h

#include "WrapperUILayer.h"

class MainUiLayer:public WrapperUILayer {
    
public:
    MainUiLayer();
    virtual ~MainUiLayer();
public:
    CREATE_FUNC(MainUiLayer);
    virtual bool initUi();
};

#endif /* MainUiLayer_h */
