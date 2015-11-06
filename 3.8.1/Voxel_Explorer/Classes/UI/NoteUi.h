//
//  NoteUi.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/3.
//
//

#ifndef NoteUi_hpp
#define NoteUi_hpp

#include "ui/CocosGUI.h"
class Label;
class NoteUi:public cocos2d::ui::Layout
{
    NoteUi();
public:
    CREATE_FUNC(NoteUi);
    bool init() override;
    virtual ~NoteUi();
    void setMsg(std::string msg,cocos2d::Color3B fontColor = cocos2d::Color3B::WHITE);
private:
    cocos2d::Label* m_pLabel;
};

#endif /* NoteUi_hpp */
