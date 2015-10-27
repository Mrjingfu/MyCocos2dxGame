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

class GameUILayer:public WrapperUILayer {
    
public:
    GameUILayer();
    virtual ~GameUILayer();
public:
    CREATE_FUNC(GameUILayer);
    virtual bool addEvents();
protected:
    void onClickRole(Ref* ref);
    void onEvenetMeetMonster(cocos2d::EventCustom *sender);
    void onEventLevelUp(cocos2d::EventCustom *sender); 
    void onEventDead(cocos2d::EventCustom *sender);
    void onEventUpdateProp(cocos2d::EventCustom *sender);
private:
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
    cocos2d::ui::ImageView*  m_pMonsterBuffers[8];
};

#endif /* GameUILayer_h */
