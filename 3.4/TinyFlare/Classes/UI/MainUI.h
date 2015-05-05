//
//  MainUI.h
//  TinyFlare
//
//  Created by wang haibo on 15/4/20.
//
//

#ifndef __TinyFlare__MainUI__
#define __TinyFlare__MainUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BufferContainer.h"
#include "Player.h"
#include "ChaosNumber.h"
class MainUI : public cocos2d::ui::Layout, public PlayerListener
{
protected:
    MainUI();
    virtual ~MainUI();
    virtual bool init() override;
public:
    static MainUI* create();
    
    virtual void onBeginAccel(float time);
    virtual void onEndAccel();
    
    virtual void onBeginMulti(float time);
    virtual void onEndMulti();
    
    virtual void onBeginProtected(float time);
    virtual void onEndProtected();
    
    virtual void onBeginTime(float time);
    virtual void onEndTime();
    
    void onPause();
    void onResume();
    
    void nextStage(int stage);
    void addStardust(ChaosNumber& num);
    void subStardust(ChaosNumber& num);
    
    void spawnLevelStardust();
    
    void setLevelPercent(float percent);
private:
    void pressPauseGameBtn(Ref* p,TouchEventType eventType);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event);
private:
    cocos2d::ui::Button*     m_pPauseGameBtn;
    cocos2d::ui::ImageView*  m_pLevelProgressBg;
    cocos2d::ui::LoadingBar* m_pLevelProgress;
    cocos2d::ui::ImageView*  m_pLevelProgressBar;
    cocos2d::ui::ImageView*  m_pLevelProgressComplete;
    cocos2d::ui::Text*       m_pStageText;
    cocos2d::ui::Text*       m_pStageTextBottom;
    BufferContainer*         m_pBufferContainer;
    
    cocos2d::ui::ImageView*  m_pStardust;
    cocos2d::ui::Text*       m_pStardustX;
    cocos2d::ui::Text*       m_pStardustNum;
};

#endif /* defined(__TinyFlare__MainUI__) */
