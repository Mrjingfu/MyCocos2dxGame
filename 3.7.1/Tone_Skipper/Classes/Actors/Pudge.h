//
//  Dog.h
//  Tone_Skipper
//
//

#ifndef __Tone_Skipper__Dog__
#define __Tone_Skipper__Dog__

#include "Player.h"
class Pudge : public Player
{
    friend class ActorFactory;
protected:
    Pudge();
    virtual ~Pudge();
    
    virtual bool loadModel();
    virtual bool loadAnimations();
    virtual void onLand();
    
    virtual void onLeftBtnPressed() override;
    virtual void onLeftBtnReleased() override;
    
    virtual void onUpBtnPressed() override;
    virtual void onUpBtnReleased() override;
    
    virtual void onRightBtnPressed() override;
    virtual void onRightBtnReleased() override;

    virtual void onABtnPressed() override;
    virtual void onABtnReleased() override;
    
    virtual void onBBtnPressed() override;
    virtual void onBBtnReleased() override;
};

#endif /* defined(__Tone_Skipper__Dog__) */
