//
//  GameLose.cpp
//
//
//
//

#include "GameLose.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

GameLose* GameLose::create()
{
    GameLose *pRet = new(std::nothrow) GameLose();
    if (pRet&& pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

GameLose::GameLose()
{
}
GameLose::~GameLose()
{
}

bool GameLose::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /960.0f;

    
    return true;
}
