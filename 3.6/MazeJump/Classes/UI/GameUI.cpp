//
//  GameUI.cpp
//
//
//
//

#include "GameUI.h"

USING_NS_CC;

GameUI* GameUI::create()
{
    GameUI *pRet = new(std::nothrow) GameUI();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

GameUI::GameUI()
{
    

}
GameUI::~GameUI()
{
}

bool GameUI::init()
{
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /960.0f;
    
    
    

    return true;
}
