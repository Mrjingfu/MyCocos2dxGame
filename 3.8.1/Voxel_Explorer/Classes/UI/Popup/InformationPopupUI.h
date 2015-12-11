//
//  SettingUILayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#ifndef InformationPopupUI_hpp
#define InformationPopupUI_hpp

#include "PopupUILayer.h"

class InformationPopupUI: public PopupUILayer{
    InformationPopupUI();
    
public:
    CREATE_FUNC(InformationPopupUI);
    virtual ~InformationPopupUI();
    bool initUi() override;
    bool addEvents() override;
    void refreshUIView() override;
    void setTitle(std::string title);
    void setInfoIcon(std::string icon);
    void seInfoDesc(std::string desc);
    void setInfoVector(cocos2d::ValueVector infos);
    void setInfoData(const std::string& infoRes, std::string& infoDesc);
    
private:
    cocos2d::ValueVector    m_vInfos;
    cocos2d::ui::ImageView* m_pInfoIcon;
    cocos2d::ui::ImageView* m_pBtnNext;
    cocos2d::ui::Text*      m_pInfoDesc;
    cocos2d::ui::Text*      m_pInfoTitle;
};

#endif /* InfoPopupUI_hpp */
