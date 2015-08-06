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
class GameUI : public cocos2d::ui::Layout
{
public:
    typedef enum {
        GU_ADD_GOLD,
        GU_ADD_HEART,
        GU_ADD_SCORE,
        GU_RUN_LOSE,
        GU_GROUND_WIN,
        GU_GROUND_LOST,
        GU_GROUND_RECORD_END,
        GU_UNKNOWN
    } UIMessage;
    void setGameMessage(UIMessage state);
    UIMessage getGameMessage() const{return m_message;}
protected:

    GameUI();
    virtual ~GameUI();
    virtual bool init() ;

    
public:

    static GameUI* create();
private:
    void onAddGold();
    void onAddHeart();
    void onAddScore();
    void onRunLost();
    void onGroundWin();
    void onGrounLost();
    void onGroundRecordEnd();
    UIMessage m_message;
    cocos2d::ui::Text* goldTv;
    cocos2d::ui::Text* heartTv;
    cocos2d::ui::Text* gameScoreTv;

};

#endif /* defined(__MazeJump__GameUI__) */
