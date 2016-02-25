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
    virtual void onEnter() override;
    virtual void onExit() override;
private:
    void onClickStart(Ref* ref);
    void onClikcRestart(Ref* ref);
    void onClickMuisc(Ref* ref);
    void onClickRank(Ref*);
    void onClickRate(Ref*);
    void onClickAchieve(Ref*);
    void startGameAction();
    void switchToGameScene();
    
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) ;
private:
    cocos2d::LayerColor* m_pWhiteLayer;
    cocos2d::ui::Button* m_pArchiveStart;
    cocos2d::ui::Button* m_pArchiveRestart;
    cocos2d::ui::ImageView* m_pMuiscImg;
    
    AchievePopupUI* m_pAchievePopupUI;
    cocos2d::Sprite* m_pEyes;
};

#endif /* MenuUILayer_h */
