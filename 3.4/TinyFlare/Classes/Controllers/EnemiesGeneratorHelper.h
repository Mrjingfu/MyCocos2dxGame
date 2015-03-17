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
    static cocos2d::Vec3 getRandomPosLeftOutOfScreen(const cocos2d::Vec3& playerPos);
    static cocos2d::Vec3 getRandomPosRightOutOfScreen(const cocos2d::Vec3& playerPos);
    static cocos2d::Vec3 getRandomPosTopOutOfScreen(const cocos2d::Vec3& playerPos);
    static cocos2d::Vec3 getRandomPosBottomOutOfScreen(const cocos2d::Vec3& playerPos);
    static cocos2d::Vec3 getRandomPosOutOfScreen(const cocos2d::Vec3& playerPos);
    
    static cocos2d::Vec3 getRandomPosLeftInScreen(const cocos2d::Vec3& playerPos);
    static cocos2d::Vec3 getRandomPosRightInScreen(const cocos2d::Vec3& playerPos);
    static cocos2d::Vec3 getRandomPosTopInScreen(const cocos2d::Vec3& playerPos);
    static cocos2d::Vec3 getRandomPosBottomInScreen(const cocos2d::Vec3& playerPos);
    static cocos2d::Vec3 getRandomPosInScreen(const cocos2d::Vec3& playerPos);
};

#endif /* defined(__Geometry_Wars__EnemiesGeneratorHelper__) */
