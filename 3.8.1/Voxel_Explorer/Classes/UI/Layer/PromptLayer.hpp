//
//  PromptLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/24.
//
//

#ifndef PromptLayer_hpp
#define PromptLayer_hpp

#include "ui/CocosGUI.h"

class PromptLayer:public cocos2d::ui::ImageView
{
    PromptLayer();
public:
    enum ePromptType{
        PT_AWAKE
    };
    virtual ~PromptLayer();
    void onEnter() override;
    void onExit() override;
    static PromptLayer* create(ePromptType type);
    bool init(ePromptType type);
    void update(float delta) override;
    void setDisplayPt(cocos2d::Vec3 pt){m_vDisplayPt = pt;};
private:
    cocos2d::Vec3 m_vDisplayPt;
};

#endif /* PromptLayer_hpp */
