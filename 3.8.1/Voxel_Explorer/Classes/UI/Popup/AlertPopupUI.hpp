//
//  AlertPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/10.
//
//

#ifndef AlertPopupUI_hpp
#define AlertPopupUI_hpp

#include "PopupUILayer.h"

class AlertPopupUI:public PopupUILayer {
    
    AlertPopupUI();
public:
    typedef std::function<void(cocos2d::Ref*)> onClickListener;
    virtual ~AlertPopupUI();
    CREATE_FUNC(AlertPopupUI);
    virtual bool initUi() override;
    virtual bool addEvents() override;
    void setTitle( std::string title);
    void setMessage( std::string message);
    void setPositiveListerner(onClickListener listener ,std::string str ="");
    void setNegativeListerner(onClickListener listener,std::string str ="");
    virtual void refreshUIView() override;
private:
    void onClickOk(Ref* ref);
    void onClickCancel(Ref* ref);
private:
    cocos2d::ui::Button* m_pOk;
    cocos2d::ui::Button* m_pCancel;
    cocos2d::ui::TextBMFont*   m_pTitle;
    cocos2d::ui::TextBMFont*   m_pMessage;
    onClickListener     m_pNegativeFun;
    onClickListener     m_pPositiveFun;
    
};

#endif /* AlertPopupUI_hpp */
