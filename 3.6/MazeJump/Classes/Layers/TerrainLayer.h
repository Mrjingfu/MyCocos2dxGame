//
//  TerrainLayer.h
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#ifndef __MazeJump__TerrainLayer__
#define __MazeJump__TerrainLayer__

#include "cocos2d.h"
#include "GroundCell.h"
#include "Arrow.h"
#include "Player.h"
class TerrainLayer : public cocos2d::Layer
{
    TerrainLayer();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static TerrainLayer* create();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
protected:
    // 处理输入
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
private:
};

#endif /* defined(__MazeJump__TerrainLayer__) */
