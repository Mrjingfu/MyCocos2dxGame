//
//  DialoguePopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/4.
//
//

#ifndef DialoguePopupUI_hpp
#define DialoguePopupUI_hpp
#include "PopupUILayer.h"

class DialoguePopupUI :public PopupUILayer{
    DialoguePopupUI();
    
public:
    virtual ~DialoguePopupUI();
    CREATE_FUNC(DialoguePopupUI);
    virtual void refreshUIView();
    virtual bool addEvents();          //cocostudio布局用到
    virtual bool initUi(); //手工编写ui布局用到
    

private:
    void onClickNext(Ref* ref);
private:
    cocos2d::ui::ImageView*     m_pBtnNext;
    cocos2d::ui::Text*          m_pTextInfo;
    cocos2d::ui::Text*          m_pTextTitle;
    cocos2d::ui::ImageView*     m_pCharIcon;
    cocos2d::ui::Layout*        m_pDialogueLayout;
    int                         m_nPart;
    bool                        m_bPartEnd;
};

#endif /* DialoguePopupUI_hpp */
