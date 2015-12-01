//
//  DistPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/30.
//
//

#ifndef DistPopupUI_hpp
#define DistPopupUI_hpp

#include "PopupUILayer.h"

class DistPopupUI:public PopupUILayer {
    DistPopupUI();
public:
    virtual ~DistPopupUI();
    CREATE_FUNC(DistPopupUI);
    virtual bool initUi() override;
    virtual bool addEvents() override;
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    

};

#endif /* DistPopupUI_hpp */
