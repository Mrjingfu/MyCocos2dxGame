//
//  UIManager.h
//  MazeJump
//
//
//

#ifndef __MazeJump__UIManager__
#define __MazeJump__UIManager__

#include "cocos2d.h"
#include "BasePopUpUI.h"
#include "GameInfoUI.h"
class UIManager : public cocos2d::Ref
{
    UIManager();
    virtual ~UIManager();
public:
    typedef enum {
        UI_MAIN,
        UI_GAME,
        UI_GROUND_GAME,
        UI_UNKOWN
    } Game_UI;
    static UIManager* getInstance();
    
    void addPopUp(BasePopUpUI::PopUp_UI popid);
    void showPopUp(bool isPlayAn = true,BasePopUpUI::Popup_Show popupShow =BasePopUpUI::POPUP_VERTICAL ,const std::function<void()> &endfunc = nullptr,cocos2d::Vec2= cocos2d::Vec2::ZERO );
    
    void setGameUi(Game_UI gameui);
    void hidePopUp(const std::function<void()> &endfunc = nullptr);
    Game_UI getGameId(){return m_gameUiId;}
    void showInfo(bool isShowInfo);
    void init(cocos2d::Layer* layer);
    void destory();
    void removePopUp(BasePopUpUI* popUi);
    void onGameInfoHidePopUp();
private:
    
    
    BasePopUpUI* createPopUp(BasePopUpUI::PopUp_UI popid) ;
    cocos2d::Vector<BasePopUpUI*> m_popUps;
    cocos2d::Node* m_parent;
    cocos2d::Layer* m_gameLayer;
    cocos2d::Layer* m_dialogLayer;
    GameInfoUI* m_gameInfoLayer;
    Game_UI m_gameUiId;
};

#endif /* defined(__MazeJump__UIManager__) */
