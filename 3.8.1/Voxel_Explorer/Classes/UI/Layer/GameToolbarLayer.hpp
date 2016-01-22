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
    void onClickBag(Ref* ref);
    void onClickMap(Ref* ref);
    void onClickSearch(Ref* ref);
    void onClickDist(Ref* ref);
    void onClickMsg(Ref* ref);
    void onClickPause(Ref* ref);
    void setMsgItem(std::string msg,cocos2d::Color3B msgColor = cocos2d::Color3B::WHITE);
    
    
private:
    bool m_bIsOpenSmailMap;                       //是否打开小地图
    bool m_bIsDist;                               //是否点击地图查看信息
    
    cocos2d::ui::ListView*   m_pListMsgs;
    cocos2d::ui::ImageView*  m_pMsgFrame;
    cocos2d::ui::ImageView*  m_pGameMsgBtn;
    cocos2d::ui::ImageView*  m_pGameMapBtn;
    cocos2d::ui::ImageView*  m_pGameSearchBtn;
    cocos2d::ui::ImageView*  m_pGameBagBtn;
    cocos2d::ui::ImageView*  m_pGameDistBtn;
    cocos2d::ui::ImageView*  m_pGamePauseBtn;
    cocos2d::ui::LoadingBar* m_pRoleExpBar;
    cocos2d::ui::ImageView*  m_pGameDistTipsFrame;
    cocos2d::ui::Button*     m_pGameDistFrameCloseBtn;
    cocos2d::ui::TextBMFont*       m_pGameDistFrameDesc;
    
    

};

#endif /* GameToolbarLayer_hpp */
