//
//  MainUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__ShopUI__
#define __MazeJump__ShopUI__

#include "cocos2d.h"
#include "BaseUI.h"
class ShopUI : public BaseUI
{
protected:
    ShopUI();
    virtual ~ShopUI();
    virtual bool init();
public:
    virtual void onEnter();
    virtual void onExit();
    
    static ShopUI* create();
    void onBack(Ref* ref);
    void onBuyGold(Ref* ref);
    void onBuyHeart(Ref* ref);
    void onBuyRemoveAds(Ref* ref);
    void onRestore(Ref* ref);
    
    void onBuyCoin1(Ref* ref);
    void onBuyCoin2(Ref* ref);
    void onBuyCoin3(Ref* ref);
    void onBuyCoin4(Ref* ref);
    void onBuyCoin5(Ref* ref);
private:
    cocos2d::Layer* productLayer;
     cocos2d::Layer* goldProductLayer;

};

#endif /* defined(__MazeJump__ShopUI__) */
