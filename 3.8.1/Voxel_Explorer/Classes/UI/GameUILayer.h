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
class GameInfoLayer;
class GameToolbarLayer;
class RolePropLayer;
class MonsterPropLayer;
class GameUILayer:public WrapperUILayer {
    
public:
    GameUILayer();
    virtual ~GameUILayer();
public:
    CREATE_FUNC(GameUILayer);
    virtual bool initUi() override;
    virtual void refreshUIView() override;
    void onEnter() override;
    void onExit()override;
   
protected:
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;
private:
 
    
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
    
    
    //注册触摸事件
    bool registerTouchEvent();

private:
   GameInfoLayer*    m_pGameInfoLayer;
   GameToolbarLayer* m_pGameToolBarLayer;
   RolePropLayer*    m_pRolePropLayer;
   MonsterPropLayer* m_pMonsterPropLayer;
   
};

#endif /* GameUILayer_h */
