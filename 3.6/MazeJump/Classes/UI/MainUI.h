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
class MainUI : public cocos2d::ui::Layout
{
protected:
    MainUI();
    virtual ~MainUI();
    virtual bool init() override;
public:
    static MainUI* create();
    void onPlayGame(Ref* ref);
    void onResumeGame(Ref* ref);
    void onShop(Ref* ref);
    void onSound(Ref* ref);
    void onRank(Ref* ref);

};

#endif /* defined(__MazeJump__MainUI__) */
