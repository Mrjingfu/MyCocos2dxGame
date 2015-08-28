//
//  Nilo.h
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/27.
//
//

#ifndef __Tone_Skipper__Nilo__
#define __Tone_Skipper__Nilo__

#include "Player.h"
class Nilo : public Player
{
    friend class ActorMgr;
protected:
    Nilo();
    virtual ~Nilo();
    
    virtual bool loadModel();
    virtual bool loadAnimations();
    
    virtual void onLeftBtnPressed() override;
    virtual void onLeftBtnReleased() override;
    
    virtual void onUpBtnPressed() override;
    virtual void onUpBtnReleased() override;
    
    virtual void onRightBtnPressed() override;
    virtual void onRightBtnReleased() override;
    
    virtual void onDownBtnPressed() override;
    virtual void onDownBtnReleased() override;
    
    virtual void onABtnPressed() override;
    virtual void onABtnReleased() override;
    
    virtual void onBBtnPressed() override;
    virtual void onBBtnReleased() override;
};

#endif /* defined(__Tone_Skipper__Nilo__) */
