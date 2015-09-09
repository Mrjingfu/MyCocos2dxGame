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
#include "SkillButton.h"
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
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
    static void setDeadCount(int count){m_DeadCount = count;}
private:
    static int m_DeadCount;
    int m_conut;
    bool isRecover;
    bool isShwoHelp;
    bool isDead;
    bool isTouchShopBuy;
    bool isTouchKeyBack;
    cocos2d::Layer* m_maskLayerBg;
    cocos2d::ui::ImageView* m_countDonwImg;
    cocos2d::ui::Button* pauseImg;
    cocos2d::LayerColor* helpLayer;
    
    void onPauseEvent(cocos2d::EventCustom* sender);
    
    void showPause();
    void showPopupEnd();
    
    void onRecoverPause(cocos2d::EventCustom* sender);
    void onRunnerLose(cocos2d::EventCustom* sender);
    void onShopBuyGold(Ref* ref);
    void onShopBuyHeart(Ref* ref);
    void onDelayTimeRunnerLose();
    void onShowLosePopUpEnd();
    void onHelp(Ref* ref);
    void onPause(cocos2d::Ref *ref);
    void onEventSetResume(cocos2d::EventCustom* sender);
    void onResumeAn(float dt);
    void setPause();
    void setResume();
    
    void onShopBuyEvenet(cocos2d::EventCustom* sender);
    void onChangeLifeStatus(cocos2d::EventCustom* sender);
private:
    SkillButton*        m_pSkillBtn;
};

#endif /* defined(__MazeJump__GameUI__) */
