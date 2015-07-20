//
//  DecoratorLayer.h
//  MazeJump
//
//  Created by wang haibo on 15/7/20.
//
//

#ifndef __MazeJump__DecoratorLayer__
#define __MazeJump__DecoratorLayer__

#include "cocos2d.h"

class DecoratorLayer : public cocos2d::Layer
{
    DecoratorLayer();
public:
    virtual bool init();
    
    CREATE_FUNC(DecoratorLayer);
};

#endif /* defined(__MazeJump__DecoratorLayer__) */
