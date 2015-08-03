//
//  DeathUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__DeathUI__
#define __MazeJump__DeathUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class DeathUI : public cocos2d::ui::Layout
{
protected:
    DeathUI();
    virtual ~DeathUI();
    virtual bool init() override;
public:
    static DeathUI* create();


};

#endif /* defined(__MazeJump__DeathUI__) */
