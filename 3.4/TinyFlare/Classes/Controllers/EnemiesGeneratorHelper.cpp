//
//  EnemiesGeneratorHelper.cpp
//  Geometry-Wars
//
//  Created by wang haibo on 15/3/11.
//
//

#include "EnemiesGeneratorHelper.h"
USING_NS_CC;

Vec2 EnemiesGeneratorHelper::getRandomPosLeftOutOfScreen(const cocos2d::Vec2& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorWidth = cocos2d::random(0.0f, 100.0f);
    float x = playerPos.x -(size.width*0.5f + generatorWidth);
    float y = playerPos.y +(size.height*0.5f*CCRANDOM_MINUS1_1());
    return Vec2(x, y);
}
Vec2 EnemiesGeneratorHelper::getRandomPosRightOutOfScreen(const cocos2d::Vec2& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorWidth = cocos2d::random(0.0f, 100.0f);
    float x = playerPos.x + (size.width*0.5f + generatorWidth);
    float y = playerPos.y + (size.height*0.5f*CCRANDOM_MINUS1_1());
    return Vec2(x, y);
}
Vec2 EnemiesGeneratorHelper::getRandomPosTopOutOfScreen(const cocos2d::Vec2& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorHeight = cocos2d::random(0.0f, 100.0f);
    float x = playerPos.x + (size.width*0.5f*CCRANDOM_MINUS1_1());
    float y = playerPos.y + (size.height*0.5f + generatorHeight);
    return Vec2(x, y);
}
Vec2 EnemiesGeneratorHelper::getRandomPosBottomOutOfScreen(const cocos2d::Vec2& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorHeight = cocos2d::random(0.0f, 100.0f);
    float x = playerPos.x + (size.width*0.5f*CCRANDOM_MINUS1_1());
    float y = playerPos.y - (size.height*0.5f + generatorHeight);
    return Vec2(x, y);
}
Vec2 EnemiesGeneratorHelper::getRandomPosOutOfScreen(const cocos2d::Vec2& playerPos)
{
    Vec2 ret;
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

Vec2 EnemiesGeneratorHelper::getRandomPosLeftInScreen(const cocos2d::Vec2& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorWidth = cocos2d::random(0.0f, size.height*0.1f);
    float x = playerPos.x - (size.width*0.5f - generatorWidth);
    float y = playerPos.y + (size.height*0.5f*CCRANDOM_MINUS1_1());
    return Vec2(x, y);
}
Vec2 EnemiesGeneratorHelper::getRandomPosRightInScreen(const cocos2d::Vec2& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorWidth = cocos2d::random(0.0f, size.height*0.1f);
    float x = playerPos.x + (size.width*0.5f - generatorWidth);
    float y = playerPos.y + (size.height*0.5f*CCRANDOM_MINUS1_1());
    return Vec2(x, y);
}
Vec2 EnemiesGeneratorHelper::getRandomPosTopInScreen(const cocos2d::Vec2& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorHeight = cocos2d::random(0.0f, size.height*0.1f);
    float x = playerPos.x + (size.width*0.5f*CCRANDOM_MINUS1_1());
    float y = playerPos.y + (size.height*0.5f - generatorHeight);
    return Vec2(x, y);
}
Vec2 EnemiesGeneratorHelper::getRandomPosBottomInScreen(const cocos2d::Vec2& playerPos)
{
    Size size = Director::getInstance()->getWinSize();
    float generatorHeight = cocos2d::random(0.0f, size.height*0.1f);
    float x = playerPos.x + (size.width*0.5f*CCRANDOM_MINUS1_1());
    float y = playerPos.y - (size.height*0.5f - generatorHeight);
    return Vec2(x, y);
}
Vec2 EnemiesGeneratorHelper::getRandomPosInScreen(const cocos2d::Vec2& playerPos)
{
    Vec2 ret;
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

Vec2 EnemiesGeneratorHelper::getRandomPosOutScreenInBoundRect(const cocos2d::Vec2& playerPos, const cocos2d::Rect& boundRect)
{
    Vec2 ret = getRandomPosOutOfScreen(playerPos);
    if(boundRect.containsPoint(ret))
        return ret;
    if(ret.x <= boundRect.getMinX() + 100.0f)
        ret.x += 2*(boundRect.getMinX() + 150.0f - ret.x);
    if(ret.x >= boundRect.getMaxX() - 100.0f)
        ret.x -= 2*(ret.x - boundRect.getMaxX() + 150.0f);
    if(ret.y <= boundRect.getMinY() + 100.0f)
        ret.y += 2*(boundRect.getMinY() + 150.0f - ret.y);
    if(ret.y >= boundRect.getMaxY() - 100.0f)
        ret.y -= 2*(ret.y - boundRect.getMaxY() + 150.0f);
    return ret;
}
Vec2 EnemiesGeneratorHelper::getRandomPosInScreenInBoundRect(const cocos2d::Vec2& playerPos, const cocos2d::Rect& boundRect)
{
    Vec2 ret = getRandomPosInScreen(playerPos);
    if(boundRect.containsPoint(ret))
        return ret;
    if(ret.x <= boundRect.getMinX() + 100.0f)
        ret.x += 2*(boundRect.getMinX() + 100.0f - ret.x);
    if(ret.x >= boundRect.getMaxX() - 100.0f)
        ret.x -= 2*(ret.x - boundRect.getMaxX() + 100.0f);
    if(ret.y <= boundRect.getMinY() + 100.0f)
        ret.y += 2*(boundRect.getMinY() + 100.0f - ret.y);
    if(ret.y >= boundRect.getMaxY() - 100.0f)
        ret.y -= 2*(ret.y - boundRect.getMaxY() + 100.0f);
    return ret;
}