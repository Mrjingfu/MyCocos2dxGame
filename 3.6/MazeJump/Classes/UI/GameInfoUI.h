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
    void setPopUpId(BasePopUpUI::PopUp_UI popUpId);
    void removePopUpId();
    void onhideEndPopup();
private:
    void onGoldChange(cocos2d::EventCustom* sender);
    void onHeartChange(cocos2d::EventCustom* sender);
    void onMaxDistanceChange(cocos2d::EventCustom* sender);
    void onRunnerLose(cocos2d::EventCustom* sender);
    void onMazeJumpWin(cocos2d::EventCustom* sender);
    void onMazeJumpLose(cocos2d::EventCustom* sender);
    
    void onDelayTimeRunnerLose();
    void onDelayTimeMazeJumpWin();
    void onDelayTimeMazeJumpLose();
    
    void onGroundRecordEnd(cocos2d::EventCustom* sender);
    
    void onPause(cocos2d::Ref *ref);
    
    void onshowStartEnd();
    cocos2d::ui::Text* goldTv;
    cocos2d::ui::Text* heartTv;
    cocos2d::ui::Text* gameScoreTv;
    cocos2d::ui::Button* pauseImg;
    cocos2d::Layer* disLayer;
    std::vector<BasePopUpUI::PopUp_UI> m_popUpIds;
    bool  isNowHidePopup;
};

#endif /* defined(__MazeJump__GameInfoUI__) */
