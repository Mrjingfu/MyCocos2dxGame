//
//  SceneItem.h
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/22.
//
//

#ifndef __Tone_Skipper__SceneItem__
#define __Tone_Skipper__SceneItem__

#include "Actor.h"
class SceneItem : public Actor
{
public:
    typedef enum{
        SIT_EXCALMATION_MARK,
        SIT_UNKNOWN
    }
    SCENE_ITEM_TYPE;
protected:
    SceneItem();
    virtual ~SceneItem();
public:
    virtual bool loadAnimations();
    virtual void onLand();
protected:
    HueSprite*  m_pMainSprite;
    SCENE_ITEM_TYPE  m_Type;
};

#endif /* defined(__Tone_Skipper__SceneItem__) */
