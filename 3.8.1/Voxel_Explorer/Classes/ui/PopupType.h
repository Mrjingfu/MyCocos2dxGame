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
    TIP_QUESTION,
    
    TIP_ROLE_DEFAULT,
    TIP_ROLE_DODGE,
    TIP_ROLE_BOLOCK,
    TIP_ROLE_CRITICAL_STRIKE,
    TIP_MONSTER_DEFAULT,
    TIP_MONSTER_DODGE,
    TIP_MONSTER_BOLOCK,
    TIP_MONSTER_CRITICAL_STRIKE

}TipTypes;
#endif
