//
//  PopupType.h
//  Tone_Skipper
//
//  Created by 创李 on 15/9/18.
//
//

#ifndef Tone_Skipper_PopupType_h
#define Tone_Skipper_PopupType_h

enum ePopupType
{
    ePopupInvalid = -1,
    ePopupRole,             //角色弹窗
    ePopupEquipItem,        //装备道具弹窗
    ePopupItem,             //道具弹窗
    ePopupPause,            //暂停弹窗
    ePopupItemShopBuy,      //商店道具购买弹窗
    ePopupItemShopSell,
    ePopupNurse,            //护士弹窗
    ePopupLittleWitch,      //随机事件弹窗
    ePopupOldMan,           //智者
    ePopupGambleShop,           //赌博
    ePopupAlchemyShop,          //炼金
    ePopupMagicShop,        //魔法物品
    ePopupWeaponShop,       //装备物品
    ePopupTask,             //任务
    ePopupAlert,            //提示框
    ePopupInformation,
    ePopupRandomMsg,
    ePopupDiscard,
    ePopupAchieve,
    ePopupDead,
    ePopupCount
};
typedef enum {
    TIP_DEFAULT,    //白色
    TIP_POSITIVE,   //绿色
    TIP_NEGATIVE,   //红色
    TIP_WARNING,    //橘色
    TIP_NEUTRAL,    //黄色
    TIP_EFFECT,
    TIP_DODGE,
    TIP_BOLOCK,
    TIP_ROLE_CRITICAL_STRIKE,
    TIP_MONSTER_CRITICAL_STRIKE
}TipTypes;
#endif
