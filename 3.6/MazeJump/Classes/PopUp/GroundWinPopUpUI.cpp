//
//  GroundWinPopUpUI.cpp
//
//
//
//

#include "GroundWinPopUpUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

GroundWinPopUpUI* GroundWinPopUpUI::create()
{
    GroundWinPopUpUI *pRet = new(std::nothrow) GroundWinPopUpUI();
    if (pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

GroundWinPopUpUI::GroundWinPopUpUI()
{
}
GroundWinPopUpUI::~GroundWinPopUpUI()
{
}

void GroundWinPopUpUI::onEnter()
{
    BasePopUpUI::onEnter();
    init();
}
void GroundWinPopUpUI::onExit()
{
    BasePopUpUI::onExit();
}
bool GroundWinPopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /640.0f;

    
    return true;
}
