//
//  ShopUI.cpp
//
//
//
//

#include "ShopUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

ShopUI* ShopUI::create()
{
    ShopUI *pRet = new(std::nothrow) ShopUI();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

ShopUI::ShopUI()
{
}
ShopUI::~ShopUI()
{
}
bool ShopUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /960.0f;
    
    auto bg = LayerColor::create(Color4B(107, 223, 255,255),size.width,size.height);
    bg->setPosition(Vec2::ZERO);
    addChild(bg);
    
    
    
    return true;
}
