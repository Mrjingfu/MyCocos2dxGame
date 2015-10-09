//
//  GroundGameUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__GroundGameUI__
#define __MazeJump__GroundGameUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GroundGameUI : public cocos2d::Layer
{
protected:
    GroundGameUI();
    virtual ~GroundGameUI();
    bool init() override;
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    static GroundGameUI* create();
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
private:
    bool isShwoHelp;
    cocos2d::LayerColor* helpLayer;
    cocos2d::Label* currentLeve;
    void onHelp(Ref* ref);
    void onMazeJumpWin(cocos2d::EventCustom* sender);
    void onMazeJumpLose(cocos2d::EventCustom* sender);
    void onGroundRecordEnd(cocos2d::EventCustom* sender);
    void onShowAda(cocos2d::EventCustom* sender);
    void onChangeMazeLevel(cocos2d::EventCustom* sender);
    void onShowAdaDelayTime();
    void onShopBuyGold(Ref* ref);
    void onShopBuyHeart(Ref* ref);
    void onGiveUp(Ref* ref);
    void onLosePopupEnd();
};

#endif /* defined(__MazeJump__GameUI__) */
