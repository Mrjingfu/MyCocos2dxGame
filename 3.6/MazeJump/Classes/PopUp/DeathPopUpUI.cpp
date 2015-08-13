//
//  DeathPopUpUI.cpp
//
//
//
//

#include "DeathPopUpUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

DeathPopUpUI* DeathPopUpUI::create()
{
    DeathPopUpUI *pRet = new(std::nothrow) DeathPopUpUI();
    if (pRet )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

DeathPopUpUI::DeathPopUpUI()
{
}
DeathPopUpUI::~DeathPopUpUI()
{
}
void DeathPopUpUI::onEnter()
{
    BasePopUpUI::onEnter();
    init();
}
void DeathPopUpUI::onExit()
{
    BasePopUpUI::onExit();
}
bool DeathPopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /960.0f;

    
    
    
    return true;
}
