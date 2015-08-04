//
//  GameWin.cpp
//
//
//
//

#include "GameWin.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

GameWin* GameWin::create()
{
    GameWin *pRet = new(std::nothrow) GameWin();
    if (pRet )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

GameWin::GameWin()
{
}
GameWin::~GameWin()
{
}
void GameWin::onEnter()
{
    BaseUI::onEnter();
    init();
}
void GameWin::onExit()
{
    BaseUI::onExit();
}

bool GameWin::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /960.0f;

    
    return true;
}
