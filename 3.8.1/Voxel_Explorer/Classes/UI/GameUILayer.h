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
class GameUILayer:public WrapperUILayer {
    
public:
    GameUILayer();
    virtual ~GameUILayer();
public:
    CREATE_FUNC(GameUILayer);
    virtual bool addEvents() override;
    void onEnter() override;
    void onExit()override;
private:
    void onClickRole(Ref* ref);
    void onClickMap(Ref* ref);
    void onClickSearch(Ref* ref);
    void onClickMsg(Ref* ref);

    void onEventUpdateRoleProp(cocos2d::EventCustom *sender);
    void onEventRoleLevelUp(cocos2d::EventCustom *sender);
    void onEventRoleDead(cocos2d::EventCustom *sender);
    void onEvenetRoleHud(cocos2d::EventCustom *sender);
    
    
    void onEventUpdateMonsterProp(cocos2d::EventCustom *sender);
    void onEventMonsterHud(cocos2d::EventCustom *sender);
    void onEvenetMonsterDead(cocos2d::EventCustom *sender);

    
    void updateRoleUi();
    void updateMonsterUi();
private:
    bool _isOpenSmailMap;
    cocos2d::ui::ListView*   m_pListMsgs;
    cocos2d::ui::ImageView*  m_pMsgFrame;
    
    cocos2d::ui::ImageView*  m_pRoleBtn;
    cocos2d::ui::LoadingBar* m_pRoleHpBar;
    cocos2d::ui::Text*       m_pRoleCurHp;
    cocos2d::ui::Text*       m_pRoleMaxHp;
    cocos2d::ui::LoadingBar* m_pRoleMpBar;
    cocos2d::ui::Text*       m_pRoleCurMp;
    cocos2d::ui::Text*       m_pRoleMaxMp;
    cocos2d::ui::LoadingBar* m_pRoleExpBar;
    cocos2d::ui::Text*       m_pRoleLevel;
    cocos2d::ui::ImageView*  m_pRoleBuffers[8];
    
    cocos2d::ui::Layout*     m_pMonsterLayout;
    cocos2d::ui::Text*       m_pMonsterCurHp;
    cocos2d::ui::Text*       m_pMonsterMaxHp;
    cocos2d::ui::Text*       m_pMonsterLevel;
    cocos2d::ui::Text*       m_pMonsterName;
    cocos2d::ui::LoadingBar* m_pMonsterHpBar;
    cocos2d::ui::ImageView*  m_pMonsterBtn;
    cocos2d::Sprite*  m_pMonsterIcon;
    
    cocos2d::ui::ImageView*  m_pMonsterBuffers[8];
    
    cocos2d::ui::ImageView*  m_pGameMsgBtn;
    cocos2d::ui::ImageView*  m_pGameMapBtn;
    cocos2d::ui::ImageView*  m_pGameSearchBtn;
   
};

#endif /* GameUILayer_h */
