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
public:

    void setPopUpId(BasePopUpUI::PopUp_UI popUpId);
protected:

    GameInfoUI();
    virtual ~GameInfoUI();
    virtual bool init() ;

    
public:

    static GameInfoUI* create();
private:
    void onAddGold();
    void onAddHeart();
    void onAddScore();
    void onRunLost();
    void onGroundWin();
    void onGrounLost();
    void onGroundRecordEnd();
    
    void onPause(cocos2d::Ref *ref);
    void onhidePopup();
    cocos2d::ui::Text* goldTv;
    cocos2d::ui::Text* heartTv;
    cocos2d::ui::Text* gameScoreTv;
    cocos2d::ui::Button* pauseImg;
    BasePopUpUI::PopUp_UI m_popUpUiId;
    bool  isNowHidePopup;
};

#endif /* defined(__MazeJump__GameInfoUI__) */
