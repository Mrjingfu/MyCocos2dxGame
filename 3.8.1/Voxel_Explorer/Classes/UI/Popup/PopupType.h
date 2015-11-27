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
    ePopupTest,
    ePopupRole,
    ePopupEquipItem,
    ePopupItem,
    ePopupInfo,
    ePopupShop,
    ePopupPause,
    epopupItemShop,
    ePopupCount
};
typedef enum {
    TIP_DEFAULT,
    TIP_POSITIVE,
    TIP_NEGATIVE,
    TIP_WARNING,
    TIP_NEUTRAL,
    TIP_QUESTION,
    TIP_EFFECT,
    TIP_BLUE,
    TIP_DODGE,
    TIP_BOLOCK,
    TIP_CRITICAL_STRIKE,

}TipTypes;
#endif
