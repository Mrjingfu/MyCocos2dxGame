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
    ePopupCount
};
typedef enum {
    TIP_DEFAULT,
    TIP_POSITIVE,
    TIP_NEGATIVE,
    TIP_WARNING,
    TIP_NEUTRAL,
    TIP_DODGE,
    TIP_BOLOCK,
    TIP_CRITICAL_STRIKE,
    TIP_QUESTION
}TipTypes;
#endif
