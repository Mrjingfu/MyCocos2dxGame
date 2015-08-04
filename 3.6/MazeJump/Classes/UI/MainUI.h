//
//  MainUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__MainUI__
#define __MazeJump__MainUI__

#include "cocos2d.h"
#include "BaseUI.h"
class StartUI;
class MainUI : public BaseUI
{
protected:
    MainUI();
    virtual ~MainUI();
    bool init();
public:
    virtual void onEnter();
    virtual void onExit();
    static MainUI* create();
    void onPlayGame(Ref* ref);
    void onShop(Ref* ref);
    void onSound(Ref* ref);
    void onRank(Ref* ref);
private:
    StartUI* startui;
    
};

#endif /* defined(__MazeJump__MainUI__) */
