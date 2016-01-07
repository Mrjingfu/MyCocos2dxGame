//
//  SettingUILayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#ifndef RandomMsgPopupUI_hpp
#define RandomMsgPopupUI_hpp

#include "InformationPopupUI.h"

class RandomMsgPopupUI: public InformationPopupUI{
    RandomMsgPopupUI();
    
public:
    CREATE_FUNC(RandomMsgPopupUI);
    virtual ~RandomMsgPopupUI();

    void updateFrameWidth() override;


};

#endif /* InfoPopupUI_hpp */
