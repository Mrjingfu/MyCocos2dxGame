//
//  GameToolbarLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#ifndef GameToolbarLayer_hpp
#define GameToolbarLayer_hpp
#include "WrapperUILayer.h"

class GameToolbarLayer :public WrapperUILayer {
    
    GameToolbarLayer();
public:
    virtual ~GameToolbarLayer();
    CREATE_FUNC(GameToolbarLayer);
    virtual bool initUi() override;
    virtual bool addEvents() override;
    virtual void refreshUIView()override;
    //初始化消息框
    void initMessageFrame();
    //添加游戏文本信息
    void sendMessage(std::string msg,cocos2d::Color3B msgColor = cocos2d::Color3B::WHITE);
    bool isOpenDist(){return m_bIsDist;};
    void setDistTipsFrame();
    void onClickDistTipsFrame(Ref* ref = nullptr);
private:
    void onClickBag(Ref* ref,Widget::TouchEventType type);
    void onClickMap(Ref* ref,Widget::TouchEventType type);
    void onClickSearch(Ref* ref,Widget::TouchEventType type);
    void onClickDist(Ref* ref,Widget::TouchEventType type);
    void onClickMsg(Ref* ref,Widget::TouchEventType type);
    void onClickPause(Ref* ref,Widget::TouchEventType type);
    void onClickHammer(Ref* ref,Widget::TouchEventType type);
    void setMsgItem(std::string msg,cocos2d::Color3B msgColor = cocos2d::Color3B::WHITE);
    
    void onTouchToolBtn(Widget::TouchEventType type,Ref* ref,cocos2d::ui::ImageView* img,float targetScale,float sourceScale,float time,const std::function<void()> &func,bool isPlaySound = true);
    
private:

    bool m_bIsDist;                               //是否点击地图查看信息
    
    cocos2d::ui::ListView*   m_pListMsgs;
    cocos2d::ui::ImageView*  m_pMsgFrame;
    cocos2d::ui::ImageView*  m_pGameMsgBtn;
    cocos2d::ui::ImageView*  m_pGameMsgBtnIcon;
    cocos2d::ui::ImageView*  m_pGameMapBtn;
    cocos2d::ui::ImageView*  m_pGameMapBtnIcon;
    cocos2d::ui::ImageView*  m_pGameSearchBtn;
    cocos2d::ui::ImageView*  m_pGameSearchBtnIcon;
    cocos2d::ui::ImageView*  m_pGameBagBtn;
    cocos2d::ui::ImageView*  m_pGameBagBtnIcon;
    cocos2d::ui::ImageView*  m_pGameDistBtn;
    cocos2d::ui::ImageView*  m_pGameDistBtnIcon;
    cocos2d::ui::ImageView*  m_pGamePauseBtn;
    cocos2d::ui::ImageView*  m_pGamePauseBtnIcon;
    cocos2d::ui::ImageView*  m_pGameHammerBtn;
    cocos2d::ui::ImageView*  m_pGameHammerBtnIcon;
    cocos2d::ui::LoadingBar* m_pRoleExpBar;
    cocos2d::ui::ImageView*  m_pGameDistTipsFrame;
    cocos2d::ui::Button*     m_pGameDistFrameCloseBtn;
    cocos2d::ui::TextBMFont*       m_pGameDistFrameDesc;
    
    

};

#endif /* GameToolbarLayer_hpp */
