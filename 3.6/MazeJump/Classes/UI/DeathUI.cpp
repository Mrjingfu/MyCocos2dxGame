//
//  DeathUI.cpp
//
//
//
//

#include "DeathUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

DeathUI* DeathUI::create()
{
    DeathUI *pRet = new(std::nothrow) DeathUI();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

DeathUI::DeathUI()
{
}
DeathUI::~DeathUI()
{
}
bool DeathUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /960.0f;

    
    return true;
}
