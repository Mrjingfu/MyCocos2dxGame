//
//  GroundLosePopUpUI.cpp
//
//
//
//

#include "GroundLosePopUpUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

GroundLosePopUpUI* GroundLosePopUpUI::create()
{
    GroundLosePopUpUI *pRet = new(std::nothrow) GroundLosePopUpUI();
    if (pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

GroundLosePopUpUI::GroundLosePopUpUI()
{
}
GroundLosePopUpUI::~GroundLosePopUpUI()
{
}
void GroundLosePopUpUI::onEnter()
{
    BasePopUpUI::onEnter();
    init();
}
void GroundLosePopUpUI::onExit()
{
    BasePopUpUI::onExit();
}
bool GroundLosePopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;

    
    return true;
}
