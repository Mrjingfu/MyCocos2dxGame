//
//  GlobalPromptLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/15.
//
//

#ifndef HudPromptLayer_hpp
#define HudPromptLayer_hpp

#include "WrapperUILayer.h"
#include "PopupUILayerManager.h"
class Actor;
class HudPromptLayer: public WrapperUILayer {
    
    HudPromptLayer();
public:
    CREATE_FUNC(HudPromptLayer);
    virtual ~HudPromptLayer();
    virtual void refreshUIView();
    virtual bool initUi();
    void shwoPrompt(cocos2d::Vec2 pos,TipTypes tipType,std::string text);
private:
    void removePrompt(cocos2d::Node* node);
private:
    cocos2d::Vector<cocos2d::ui::TextBMFont*> m_vPrompts;
    TipTypes m_eTipType;
    cocos2d::Vec2 m_vPos;
};

#endif /* HudPromptLayer_hpp */
