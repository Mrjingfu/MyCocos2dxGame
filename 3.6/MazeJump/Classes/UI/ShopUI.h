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
    ShopUI(const std::string& tip);
    virtual ~ShopUI();
    virtual bool init();
public:

    virtual void onEnter();
    virtual void onExit();
    
    static ShopUI* create(const std::string& tip);
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
    void updateUserData();
    void onProduct(const std::string& productId);
    void setTips(const std::string& tipkey);
private:
    cocos2d::Layer* productLayer;
    cocos2d::Layer* goldProductLayer;
    std:: string m_tip;
    cocos2d::ui::Text* tipTv;
    cocos2d::ui::Text* heartTv;
    cocos2d::ui::Text* goldTv;
};

#endif /* defined(__MazeJump__ShopUI__) */
