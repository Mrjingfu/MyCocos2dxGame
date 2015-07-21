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
    static DecoratorLayer* create(const std::string& modelFile, const cocos2d::Color4F& fogColor);
    
    virtual bool init(const std::string& modelFile, const cocos2d::Color4F& fogColor);
};

#endif /* defined(__MazeJump__DecoratorLayer__) */
