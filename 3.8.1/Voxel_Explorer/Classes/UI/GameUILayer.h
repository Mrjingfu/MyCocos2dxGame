//
//  GameUILayer.h
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/16.
//
//

#ifndef GameUILayer_h
#define GameUILayer_h

#include "WrapperUILayer.h"
class HudTipUi;
class TGridView;
class BaseMonster;
class GameUILayer:public WrapperUILayer {
    
public:
    GameUILayer();
    virtual ~GameUILayer();
public:
    CREATE_FUNC(GameUILayer);
    virtual bool addEvents() override;
    void onEnter() override;
    void onExit()override;
   
protected:
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;
private:
    void onClickRole(Ref* ref);
    void onClickMap(Ref* ref);
    void onClickSearch(Ref* ref);
    void onClickDist(Ref* ref);
    void onClickMsg(Ref* ref);
    void onClickPause(Ref* ref);

    void onClickDistTipsFrame(Ref* ref);

    
    void onEventRoleUpdateProp(cocos2d::EventCustom *sender);   //更新角色信息
    void onEventRoleLevelUp(cocos2d::EventCustom *sender);      //角色升级
    void onEventRoleDead(cocos2d::EventCustom *sender);         //角色死亡
    void onEventRoleHud(cocos2d::EventCustom *sender);         //更新角色hud伤害
    
    
    void onEventMonsterUpdateProp(cocos2d::EventCustom *sender); //更新怪物信息
    void onEventMonsterHud(cocos2d::EventCustom *sender);        //更新怪物hud伤害
    void onEventMonsterDead(cocos2d::EventCustom *sender);      //怪物死亡
    void onEventMonsterAlert(cocos2d::EventCustom *sender);
    void onEventMonsterConfusing(cocos2d::EventCustom *sender);
    
    
    void onEventUserPotion(cocos2d::EventCustom *sender);//使用药水物品
    void onEventUserScroll(cocos2d::EventCustom *sender);//使用卷轴物品
    
    void onEventTriggerToxic(cocos2d::EventCustom *sender); //中毒机关
    void onEventTriggerFire(cocos2d::EventCustom *sender); //火机关
    void onEventTriggerParalyic(cocos2d::EventCustom *sender);//麻痹机关
    void onEventTriggerGripping(cocos2d::EventCustom *sender);//夹子机关
    void onEventTriggerSummoning(cocos2d::EventCustom *sender);//召唤机关
    void onEventTriggerWeak(cocos2d::EventCustom *sender);  //虚弱机关
    

    void onEventFoundHidderDoor(cocos2d::EventCustom *sender); //发现隐藏门
    void onEventFoundHidderTrapToxic(cocos2d::EventCustom *sender);//发现隐藏中毒机关
    void onEventFoundHidderTrapFire(cocos2d::EventCustom *sender);//发现隐藏火机关
    void onEventFoundHidderTrapParalyic(cocos2d::EventCustom *sender);//发现隐藏麻痹机关
    void onEventFoundHidderTrapGripping(cocos2d::EventCustom *sender);//发现隐藏夹子机关
    void onEventFoundHidderTrapSummoning(cocos2d::EventCustom *sender);//发现隐藏召唤机关
    void onEventFoundHidderTrapWeak(cocos2d::EventCustom *sender);//发现隐藏虚弱机关
    void onEventFoundHidderMsg(cocos2d::EventCustom *sender);
    void onEventFoundHidderItem(cocos2d::EventCustom *sender);

    void onEventGoUpStairs(cocos2d::EventCustom *sender);
    void onEventGoUpStairsForbidden(cocos2d::EventCustom *sender);
    void onEventGoDownStairs(cocos2d::EventCustom *sender);
    void onEventGoBossRoom(cocos2d::EventCustom *sender);
    
    void updateRoleBuff();
    //注册触摸事件
    bool registerTouchEvent();
    //更新角色信息
    void updateRoleUi();
    //更新怪物信息
    void updateMonsterUi(BaseMonster* monster);
    //更新游戏信息
    void updateGameInfo();
    //初始化消息框
    void initMessageFrame();
    //添加游戏文本信息
    void sendMessage(std::string msg,cocos2d::Color3B msgColor = cocos2d::Color3B::WHITE);
    void setMsgItem(std::string msg,cocos2d::Color3B msgColor = cocos2d::Color3B::WHITE);
private:
    bool _isOpenSmailMap;                       //是否打开小地图
    bool _isDist;                               //是否点击地图查看信息
    cocos2d::ui::ListView*   m_pListMsgs;
    cocos2d::ui::ImageView*  m_pMsgFrame;
    TGridView*               m_pRoleBufferList;
    
    cocos2d::ui::Layout*     m_pRoleLayout;
    cocos2d::ui::ImageView*  m_pRoleBtn;
    cocos2d::ui::LoadingBar* m_pRoleHpBar;
    cocos2d::ui::Text*       m_pRoleCurHp;
    cocos2d::ui::Text*       m_pRoleMaxHp;
    cocos2d::ui::LoadingBar* m_pRoleMpBar;
    cocos2d::ui::Text*       m_pRoleCurMp;
    cocos2d::ui::Text*       m_pRoleMaxMp;
    cocos2d::ui::LoadingBar* m_pRoleExpBar;
    cocos2d::ui::Text*       m_pRoleLevel;
    cocos2d::ui::Text*       m_pRoleName;

    
    cocos2d::ui::Layout*     m_pMonsterLayout;
    cocos2d::ui::ImageView*  m_pMonsterBtn;
    cocos2d::ui::LoadingBar* m_pMonsterHpBar;
    cocos2d::ui::Text*       m_pMonsterCurHp;
    cocos2d::ui::Text*       m_pMonsterMaxHp;
    cocos2d::ui::LoadingBar* m_pMonsterMpBar;
    cocos2d::ui::Text*       m_pMonsterCurMp;
    cocos2d::ui::Text*       m_pMonsterMaxMp;
    cocos2d::ui::Text*       m_pMonsterLevel;
    cocos2d::ui::Text*       m_pMonsterName;
    cocos2d::ui::ImageView*  m_pMonsterIcon;

    
    cocos2d::ui::ImageView*  m_pGameMsgBtn;
    cocos2d::ui::ImageView*  m_pGameMapBtn;
    cocos2d::ui::ImageView*  m_pGameSearchBtn;
    cocos2d::ui::ImageView*  m_pGameBagBtn;
    cocos2d::ui::ImageView*  m_pGameDistBtn;
    cocos2d::ui::ImageView*  m_pGamePauseBtn;
    
    cocos2d::ui::Text*       m_pGameGoldNum;            // 金币
    cocos2d::ui::Text*       m_pGameSilverNum;          // 银币
    cocos2d::ui::Text*       m_pGameCopperNum;          // 铜币
    cocos2d::ui::Text*       m_pGameLevelInfoName;      // 关卡名
    cocos2d::ui::ImageView*     m_pGameDistTipsFrame;
    cocos2d::ui::Button*     m_pGameDistFrameCloseBtn;
    cocos2d::ui::Text*       m_pGameDistFrameDesc;
   
};

#endif /* GameUILayer_h */
