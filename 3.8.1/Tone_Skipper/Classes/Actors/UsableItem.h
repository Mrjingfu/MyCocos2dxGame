//
//  UsableItem.h
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/22.
//
//

#ifndef __Tone_Skipper__UsableItem__
#define __Tone_Skipper__UsableItem__

#include "Actor.h"
class UsableItem : public Actor
{
protected:
    UsableItem();
    virtual ~UsableItem();
public:
    virtual bool loadAnimations();
    virtual void onLand();
protected:
    HueSprite*  m_pMainSprite;
    USABLE_ITEM_TYPE  m_Type;
};

#endif /* defined(__Tone_Skipper__UsableItem__) */
