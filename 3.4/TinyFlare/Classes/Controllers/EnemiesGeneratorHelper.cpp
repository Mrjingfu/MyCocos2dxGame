//
//  EnemiesGeneratorHelper.cpp
//  Geometry-Wars
//
//  Created by wang haibo on 15/3/11.
//
//

#include "EnemiesGeneratorHelper.h"
USING_NS_CC;

Vec3 EnemiesGeneratorHelper::getRandomPosLeftOutOfScreen(const cocos2d::Vec3& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorWidth = cocos2d::random(0.0f, 100.0f);
    float x = playerPos.x -(size.width*0.5f + generatorWidth);
    float y = playerPos.y +(size.height*0.5f*CCRANDOM_MINUS1_1());
    float z = playerPos.z;
    return Vec3(x, y, z);
}
Vec3 EnemiesGeneratorHelper::getRandomPosRightOutOfScreen(const cocos2d::Vec3& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorWidth = cocos2d::random(0.0f, 100.0f);
    float x = playerPos.x + (size.width*0.5f + generatorWidth);
    float y = playerPos.y + (size.height*0.5f*CCRANDOM_MINUS1_1());
    float z = playerPos.z;
    return Vec3(x, y, z);
}
Vec3 EnemiesGeneratorHelper::getRandomPosTopOutOfScreen(const cocos2d::Vec3& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorHeight = cocos2d::random(0.0f, 100.0f);
    float x = playerPos.x + (size.width*0.5f*CCRANDOM_MINUS1_1());
    float y = playerPos.y + (size.height*0.5f + generatorHeight);
    float z = playerPos.z;
    return Vec3(x, y, z);
}
Vec3 EnemiesGeneratorHelper::getRandomPosBottomOutOfScreen(const cocos2d::Vec3& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorHeight = cocos2d::random(0.0f, 100.0f);
    float x = playerPos.x + (size.width*0.5f*CCRANDOM_MINUS1_1());
    float y = playerPos.y - (size.height*0.5f + generatorHeight);
    float z = playerPos.z;
    return Vec3(x, y, z);
}
Vec3 EnemiesGeneratorHelper::getRandomPosOutOfScreen(const cocos2d::Vec3& playerPos)
{
    Vec3 ret;
    int rand = cocos2d::random(1, 4);
    switch (rand) {
        case 1:
            ret = getRandomPosLeftOutOfScreen(playerPos);
            break;
        case 2:
            ret = getRandomPosRightOutOfScreen(playerPos);
            break;
        case 3:
            ret = getRandomPosTopOutOfScreen(playerPos);
            break;
        case 4:
            ret = getRandomPosBottomOutOfScreen(playerPos);
            break;
        default:
            break;
    }
    return ret;
}

Vec3 EnemiesGeneratorHelper::getRandomPosLeftInScreen(const cocos2d::Vec3& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorWidth = cocos2d::random(0.0f, size.height*0.3f);
    float x = playerPos.x - (size.width*0.5f - generatorWidth);
    float y = playerPos.y + (size.height*0.5f*CCRANDOM_MINUS1_1());
    float z = playerPos.z;
    return Vec3(x, y, z);
}
Vec3 EnemiesGeneratorHelper::getRandomPosRightInScreen(const cocos2d::Vec3& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorWidth = cocos2d::random(0.0f, size.height*0.3f);
    float x = playerPos.x + (size.width*0.5f - generatorWidth);
    float y = playerPos.y + (size.height*0.5f*CCRANDOM_MINUS1_1());
    float z = playerPos.z;
    return Vec3(x, y, z);
}
Vec3 EnemiesGeneratorHelper::getRandomPosTopInScreen(const cocos2d::Vec3& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorHeight = cocos2d::random(0.0f, size.height*0.3f);
    float x = playerPos.x + (size.width*0.5f*CCRANDOM_MINUS1_1());
    float y = playerPos.y + (size.height*0.5f - generatorHeight);
    float z = playerPos.z;
    return Vec3(x, y, z);
}
Vec3 EnemiesGeneratorHelper::getRandomPosBottomInScreen(const cocos2d::Vec3& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorHeight = cocos2d::random(0.0f, size.height*0.3f);
    float x = playerPos.x + (size.width*0.5f*CCRANDOM_MINUS1_1());
    float y = playerPos.y - (size.height*0.5f - generatorHeight);
    float z = playerPos.z;
    return Vec3(x, y, z);
}
Vec3 EnemiesGeneratorHelper::getRandomPosInScreen(const cocos2d::Vec3& playerPos)
{
    Vec3 ret;
    int rand = cocos2d::random(1, 4);
    switch (rand) {
        case 1:
            ret = getRandomPosLeftInScreen(playerPos);
            break;
        case 2:
            ret = getRandomPosRightInScreen(playerPos);
            break;
        case 3:
            ret = getRandomPosTopInScreen(playerPos);
            break;
        case 4:
            ret = getRandomPosBottomInScreen(playerPos);
            break;
        default:
            break;
    }
    return ret;
}