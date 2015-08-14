//
//  GameUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__GameUI__
#define __MazeJump__GameUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameUI : public cocos2d::Layer
{
protected:
    GameUI();
    virtual ~GameUI();
    bool init();
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    static GameUI* create();
    
     virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
private:
    int conut;
    bool isRecover;
    cocos2d::Layer* m_maskLayerBg;
    cocos2d::Label* resmueLabel;
    cocos2d::ui::Button* pauseImg;

    void onRunnerLose(cocos2d::EventCustom* sender);
    void onRecoverPause(cocos2d::EventCustom* sender);
    void onDelayTimeRunnerLose();
    void onPause(cocos2d::Ref *ref);
    void onEventSetResume(cocos2d::EventCustom* sender);
    void onResumeAn(float dt);
    void setPause();
    void setResume();
};

#endif /* defined(__MazeJump__GameUI__) */
