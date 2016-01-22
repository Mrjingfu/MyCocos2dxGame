//
//  GlobalPromptLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/15.
//
//

#ifndef GlobalPromptLayer_hpp
#define GlobalPromptLayer_hpp

#include "WrapperUILayer.h"
#include "PopupUILayerManager.h"
class GlobalPromptLayer: public WrapperUILayer {
    
    GlobalPromptLayer();
public:
    CREATE_FUNC(GlobalPromptLayer);
    virtual ~GlobalPromptLayer();
    virtual void refreshUIView();
    virtual bool initUi();
    void shwoGlobalPrompt(TipTypes tipType,std::string text);
    void clearGlobalPrompt();
private:
    void removePrompt(cocos2d::Node* node);
private:
    cocos2d::Vector<cocos2d::ui::TextBMFont*> m_vPrompts;
};

#endif /* GlobalPromptLayer_hpp */
