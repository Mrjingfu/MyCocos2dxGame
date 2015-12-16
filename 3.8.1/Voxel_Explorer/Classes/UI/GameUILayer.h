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
#include "PopupType.h"
class HudTipUi;
class TGridView;
class BaseMonster;
class GameInfoLayer;
class GameToolbarLayer;
class RolePropLayer;
class MonsterPropLayer;
class NpcPropLayer;
class BossPropLayer;
struct HurtData;
class HudPromptLayer;
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
    
    void onEventRoleMoneyNotEnough(cocos2d::EventCustom *sender);
    void onEventRoleNoMana(cocos2d::EventCustom *sender);
    void onEventRoleBagNoSpace(cocos2d::EventCustom *sender);
    void onEventRoleNoCopperKey(cocos2d::EventCustom *sender);
    void onEventRoleNoSilverKey(cocos2d::EventCustom *sender);
    void onEventRoleNoGoldKey(cocos2d::EventCustom *sender);
    void onEventRoleNoRoomKey(cocos2d::EventCustom *sender);
    void onEventRoleNoBossKey(cocos2d::EventCustom *sender);
    
    void onEventRoleUserPotion(cocos2d::EventCustom *sender);//使用药水物品
    void onEventRoleUserScroll(cocos2d::EventCustom *sender);//使用卷轴物品

    
    
    void onEventMonsterUpdateProp(cocos2d::EventCustom *sender); //更新怪物信息
    void onEventMonsterHud(cocos2d::EventCustom *sender);        //更新怪物hud伤害
    void onEventMonsterDead(cocos2d::EventCustom *sender);      //怪物死亡
    void onEventMonsterAlert(cocos2d::EventCustom *sender);
    void onEventMonsterConfusing(cocos2d::EventCustom *sender);
    
    void onEventTriggerToxic(cocos2d::EventCustom *sender); //中毒机关
    void onEventTriggerFire(cocos2d::EventCustom *sender); //火机关
    void onEventTriggerParalyic(cocos2d::EventCustom *sender);//麻痹机关
    void onEventTriggerGripping(cocos2d::EventCustom *sender);//夹子机关
    void onEventTriggerSummoning(cocos2d::EventCustom *sender);//召唤机关
    void onEventTriggerWeak(cocos2d::EventCustom *sender);  //虚弱机关
    void onEventTriggerFrozen(cocos2d::EventCustom *sender);  //冰冻，不一定是机关
    
    void onEventUseGoldChestKey(cocos2d::EventCustom *sender);
    void onEventUseSilverChestKey(cocos2d::EventCustom *sender);
    void onEventUseCopperChestKey(cocos2d::EventCustom *sender);
    void onEventUseRoomKey(cocos2d::EventCustom *sender);
    void onEventUseBossKey(cocos2d::EventCustom *sender);
    
    void onEventDoorMagicLocked(cocos2d::EventCustom *sender);
    void onEventDoorMagicClosed(cocos2d::EventCustom *sender);
    
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
    void onEventGoChasm(cocos2d::EventCustom *sender);
    
    void onEventNpcKnightAnsWer(cocos2d::EventCustom *sender);          //武器店
    void onEventNpcChildAnsWer(cocos2d::EventCustom *sender);           //任务
    void onEventNpcShopGirlAnsWer(cocos2d::EventCustom *sender);        //魔法物品店
    void onEventNpcOldLadyAnsWer(cocos2d::EventCustom *sender);         //炼金店
    void onEventNpcWeiRdoAnsWer(cocos2d::EventCustom *sender);          //赌博店
    void onEventNpcOldManAnsWer(cocos2d::EventCustom *sender);          //智者
    void onEventNpcLittleWitchAnsWer(cocos2d::EventCustom *sender);     //魔女随机事件
    void onEventNpcNurseAnsWer(cocos2d::EventCustom *sender);           //护士站
    
    
    void onEventBossUpdateProp(cocos2d::EventCustom *sender);
    void onEventBossDeath(cocos2d::EventCustom *sender);
    void onEventBossHud(cocos2d::EventCustom *sender);
    void onEventBossAlert(cocos2d::EventCustom *sender);
    void onEventBossSkill1(cocos2d::EventCustom *sender);
    void onEventBossSkill2(cocos2d::EventCustom *sender);
    void onEventBossSkill3(cocos2d::EventCustom *sender);
    
    void onEvenetAchieveComplete(cocos2d::EventCustom *sender);
    
    //isWho true角色 false 怪物
    void updateCharacterHud(HurtData*,TipTypes tipDodge,TipTypes tipBolock,TipTypes tipCriticalStike,TipTypes tipNormal,bool isWho = true);
    
    
    //注册触摸事件
    bool registerTouchEvent();
    
    void setCharacterPropLayerVisible(bool isMonster,bool isNpc,bool isBoss);
private:
   GameInfoLayer*    m_pGameInfoLayer;
   GameToolbarLayer* m_pGameToolBarLayer;
   RolePropLayer*    m_pRolePropLayer;
   MonsterPropLayer* m_pMonsterPropLayer;
   NpcPropLayer*     m_pNpcPropLayer;
   BossPropLayer*    m_pBossPropLayer;
   HudPromptLayer*   m_pRoleHudLayer;
   HudPromptLayer*   m_pMonsterHudLayer;
};

#endif /* GameUILayer_h */
