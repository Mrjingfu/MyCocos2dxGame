//
//  SettingUILayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#ifndef InfoPopupUI_hpp
#define InfoPopupUI_hpp

#include "PopupUILayer.h"

class InfoPopupUI: public PopupUILayer{
    InfoPopupUI();
    
public:
    CREATE_FUNC(InfoPopupUI);
    virtual ~InfoPopupUI();
    bool initUi() override;

    void setInfoData(const std::string& infoRes, std::string& infoDesc);

private:
    cocos2d::ui::ImageView* m_pInfoIcon;
    cocos2d::Label*      m_pInfoDesc;
};

#endif /* InfoPopupUI_hpp */
