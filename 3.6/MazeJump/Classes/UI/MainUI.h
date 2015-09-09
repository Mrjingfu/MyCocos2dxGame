//
//  MainUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__MainUI__
#define __MazeJump__MainUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MainUI : public cocos2d::Layer
{
protected:
    MainUI();
    virtual ~MainUI();
    bool init();
public:
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
    static MainUI* create();
    void onPlayRainbowGame(Ref* ref);
    void onMazeGame(Ref* ref);
    void onShop(Ref* ref);
    void onSound(Ref* ref);
    void onRank(Ref* ref);
    void onComment(Ref* ref);
    void showStarUi();
    void showShopUi();
    void onEnter() override;
    void onExit() override;
    
private:
    void fadeinEnd(bool isEnable );
    void fadeoutEnd();
    void onShowModeBtn(cocos2d::EventCustom* sender);
    void onHideModeBtn(cocos2d::EventCustom* sender);

    cocos2d::Layer* modeLayer;
    cocos2d::ui::Button* mazeBtn;
    cocos2d::ui::Button* rainbowBtn;
    cocos2d::ui::Button* soundBtn;
    bool isTouchRoleMenu;

};

#endif /* defined(__MazeJump__MainUI__) */
