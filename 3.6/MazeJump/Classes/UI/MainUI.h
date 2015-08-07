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
    static MainUI* create();
    void onPlayGame(Ref* ref);
    void onShop(Ref* ref);
    void onSound(Ref* ref);
    void onRank(Ref* ref);
    void onComment(Ref* ref);
    void showStarUi();
    void showShopUi();
private:
    cocos2d::ui::Button* soundBtn;
    bool m_sound;
};

#endif /* defined(__MazeJump__MainUI__) */
