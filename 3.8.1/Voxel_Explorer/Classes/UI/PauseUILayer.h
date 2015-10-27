//
//  SettingUILayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#ifndef PauseUILayer_hpp
#define PauseUILayer_hpp

#include "PopupUILayer.h"

class PauseUILayer: public PopupUILayer{
    PauseUILayer();
    
public:
    CREATE_FUNC(PauseUILayer);
    virtual ~PauseUILayer();
};

#endif /* PauseUILayer_hpp */
