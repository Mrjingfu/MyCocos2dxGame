//
//  ShopPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#ifndef AchievePopupUI_hpp
#define AchievePopupUI_hpp

#include "PopupUILayer.h"
#include "TGridView.h"
class AchieveMangerLayerUI;
class AchievePopupUI:public PopupUILayer {
protected:
    AchievePopupUI();
    
public:
    CREATE_FUNC(AchievePopupUI);
    virtual ~AchievePopupUI();
    virtual bool initUi() override;
    virtual bool addEvents() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void refreshUIView() override;
    void removeSelfCallFunc() override;
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
protected:
    void updateAllAchieves();
    void updateCommpleAchieves();
protected:
    
    TGridView*          m_pAchieveGridView;
    AchieveMangerLayerUI*   m_pAchieveMangerLayer;;

};

#endif /* AchievePopupUI_hpp */
