//
//  ActorMgr.h
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/26.
//
//

#ifndef __Tone_Skipper__ActorMgr__
#define __Tone_Skipper__ActorMgr__

#include "Player.h"
class ActorMgr : public cocos2d::Ref
{
    ActorMgr();
    virtual ~ActorMgr();
public:
    static ActorMgr* getInstance();
    
    Player* createPlayer(Player::PlayerType type);
};

#endif /* defined(__Tone_Skipper__ActorMgr__) */
