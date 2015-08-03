//
//  MainUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__ShopUI__
#define __MazeJump__ShopUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class ShopUI : public cocos2d::ui::Layout
{
protected:
    ShopUI();
    virtual ~ShopUI();
    virtual bool init() override;
public:
    static ShopUI* create();


};

#endif /* defined(__MazeJump__ShopUI__) */
