//
//  MenuUILayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/20.
//
//

#ifndef MenuUILayer_h
#define MenuUILayer_h

#include "WrapperUILayer.h"
#include "TGridView.h"
class AchievePopupUI;

class MenuUILayer:public WrapperUILayer {
    
public:
    MenuUILayer();
    virtual ~MenuUILayer();
public:
    CREATE_FUNC(MenuUILayer);
    virtual bool addEvents()override;
    virtual void refreshUIView() override;
private:
    void onClickStart(Ref* ref);
    void onClikcRestart(Ref* ref);
    void onClickSetting(Ref*);
    void onClickRank(Ref*);
    void onClickRate(Ref*);
    void onClickAchieve(Ref*);
    void startGameAction();
    void switchToGameScene();
private:
    cocos2d::LayerColor* m_pWhiteLayer;
    cocos2d::ui::Button* m_pArchiveStart;
    cocos2d::ui::Button* m_pArchiveRestart;

    AchievePopupUI* m_pAchievePopupUI;
    cocos2d::Sprite* m_pEyes;
};

#endif /* MenuUILayer_h */
