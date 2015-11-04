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
    void setMsg(std::string msg);
private:
    cocos2d::Label* m_pLabel;
};

#endif /* NoteUi_hpp */
