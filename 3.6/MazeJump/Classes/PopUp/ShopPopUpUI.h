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

public:
    typedef enum {
        SHOP_GOLD = 0,
        SHOP_NORMAL,
    } ShopType;
    virtual void onEnter() override;
    virtual void onExit() override;
    static ShopPopUpUI* create();

    void onBuyGold(Ref* ref);
    void onBuyHeart(Ref* ref);
    void onBuyRemoveAds(Ref* ref);
    void onRestore(Ref* ref);
    void onRole(Ref* ref);
    void onBackShop(Ref* ref);
    
    
    void onProuuctSucessEvent(cocos2d::EventCustom* sender);
    void onRemoveAdaSucessEvent(cocos2d::EventCustom* sender);
    void onProduct(Ref* Ref,const std::string& productId);
    
    void setShopDisplay(ShopType type);
protected:
    ShopPopUpUI();
    virtual ~ShopPopUpUI();
    virtual bool init();
private:
    cocos2d::ui::Button* adsBuyBtn;
    cocos2d::Layer* productLayer;
    cocos2d::Layer* goldProductLayer;
    cocos2d::ui::Text* tipTv;
    cocos2d::ui::Text* heartTv;
    cocos2d::ui::Text* goldTv;
    ShopType m_shopType;
    bool m_isOnGold;
};

#endif /* defined(__MazeJump__ShopUI__) */
