//
//  EnemiesGeneratorHelper.h
//  Geometry-Wars
//
//  Created by wang haibo on 15/3/11.
//
//

#ifndef __Geometry_Wars__EnemiesGeneratorHelper__
#define __Geometry_Wars__EnemiesGeneratorHelper__

#include "cocos2d.h"
#include "Enemies.h"
class EnemiesGeneratorHelper
{
public:
    static cocos2d::Vec2 getRandomPosLeftOutOfScreen(const cocos2d::Vec2& playerPos);
    static cocos2d::Vec2 getRandomPosRightOutOfScreen(const cocos2d::Vec2& playerPos);
    static cocos2d::Vec2 getRandomPosTopOutOfScreen(const cocos2d::Vec2& playerPos);
    static cocos2d::Vec2 getRandomPosBottomOutOfScreen(const cocos2d::Vec2& playerPos);
    static cocos2d::Vec2 getRandomPosOutOfScreen(const cocos2d::Vec2& playerPos);
    
    static cocos2d::Vec2 getRandomPosLeftInScreen(const cocos2d::Vec2& playerPos);
    static cocos2d::Vec2 getRandomPosRightInScreen(const cocos2d::Vec2& playerPos);
    static cocos2d::Vec2 getRandomPosTopInScreen(const cocos2d::Vec2& playerPos);
    static cocos2d::Vec2 getRandomPosBottomInScreen(const cocos2d::Vec2& playerPos);
    static cocos2d::Vec2 getRandomPosInScreen(const cocos2d::Vec2& playerPos);
    
    static cocos2d::Vec2 getRandomPosOutScreenInBoundRect(const cocos2d::Vec2& playerPos, const cocos2d::Rect& boundRect);
    static cocos2d::Vec2 getRandomPosInScreenInBoundRect(const cocos2d::Vec2& playerPos, const cocos2d::Rect& boundRect);
};

#endif /* defined(__Geometry_Wars__EnemiesGeneratorHelper__) */
