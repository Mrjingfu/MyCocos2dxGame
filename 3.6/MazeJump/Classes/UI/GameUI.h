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
private:
    void onRunnerLose(cocos2d::EventCustom* sender);
    void onDelayTimeRunnerLose();
};

#endif /* defined(__MazeJump__GameUI__) */
