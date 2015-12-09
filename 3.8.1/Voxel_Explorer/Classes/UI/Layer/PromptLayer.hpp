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
#include "Actor.hpp"
class PromptLayer:public cocos2d::ui::ImageView
{
    PromptLayer();
public:
    enum ePromptType{
        PT_AWAKE,
        PT_CONFUSING
    };
    virtual ~PromptLayer();
    void onEnter() override;
    void onExit() override;
    static PromptLayer* create(ePromptType type);
    bool init(ePromptType type);
    void update(float delta) override;
    void setActor(Actor* actor){m_pActor = actor;};
private:
    Actor* m_pActor;
    bool m_bIsAction;
};

#endif /* PromptLayer_hpp */
