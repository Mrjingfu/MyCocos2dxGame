//
//  Archivelayer.hpp
//  lichuang
//
//  Created by lichuang on 2016/01/11.
//
//

#ifndef LoadingLayer_hpp
#define LoadingLayer_hpp

#include "WrapperUILayer.h"

class LoadingLayer : public WrapperUILayer
{   
public:
    LoadingLayer();
    virtual ~LoadingLayer();
    
    CREATE_FUNC(LoadingLayer);
    virtual bool initUi() override;
    virtual bool addEvents() override;
    void refreshUIView() override;
private:
    cocos2d::ui::ImageView* m_LoadingIcon;
    cocos2d::ui::Text*  m_pTipDesc;
};

#endif /* LoadingLayer_hpp */

