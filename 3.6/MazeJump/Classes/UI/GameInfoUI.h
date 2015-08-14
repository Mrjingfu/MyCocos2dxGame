//
//  GameUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__GameInfoUI__
#define __MazeJump__GameInfoUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BasePopUpUI.h"


class GameInfoUI : public cocos2d::Layer
{

protected:

    GameInfoUI();
    virtual ~GameInfoUI();
    virtual bool init() ;

    
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    static GameInfoUI* create();


    void onhideEndPopup();
private:
    void onGoldChange(cocos2d::EventCustom* sender);
    void onHeartChange(cocos2d::EventCustom* sender);
    void onMaxDistanceChange(cocos2d::EventCustom* sender);

    
    

    cocos2d::ui::Text* goldTv;
    cocos2d::ui::Text* heartTv;
    cocos2d::ui::Text* gameScoreTv;

    cocos2d::Layer* disLayer;
    
};

#endif /* defined(__MazeJump__GameInfoUI__) */
