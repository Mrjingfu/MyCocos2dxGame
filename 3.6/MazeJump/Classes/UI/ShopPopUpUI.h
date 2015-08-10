//
//  MainUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__ShopUI__
#define __MazeJump__ShopUI__

#include "cocos2d.h"
#include "BasePopUpUI.h"
class ShopPopUpUI : public BasePopUpUI
{
protected:
    ShopPopUpUI();
    virtual ~ShopPopUpUI();
    virtual bool init();
public:

    
    static ShopPopUpUI* create();

    void onBuyGold(Ref* ref);
    void onBuyHeart(Ref* ref);
    void onBuyRemoveAds(Ref* ref);
    void onRestore(Ref* ref);
    
    void onBuyCoin1(Ref* ref);
    void onBuyCoin2(Ref* ref);
    void onBuyCoin3(Ref* ref);
    void onBuyCoin4(Ref* ref);
    void onBuyCoin5(Ref* ref);

    void onProduct(const std::string& productId);
private:
    cocos2d::Layer* productLayer;
    cocos2d::Layer* goldProductLayer;
    cocos2d::ui::Text* tipTv;
    cocos2d::ui::Text* heartTv;
    cocos2d::ui::Text* goldTv;
};

#endif /* defined(__MazeJump__ShopUI__) */
