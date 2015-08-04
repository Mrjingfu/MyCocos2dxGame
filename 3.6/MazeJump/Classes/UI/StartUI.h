//
//  StartUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__StartUI__
#define __MazeJump__StartUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BaseUI.h"
class StartUI : public cocos2d::ui::Layout
{
protected:
    StartUI();
    virtual ~StartUI();
    virtual bool init(BaseUI* baseUi) ;
public:
    static StartUI* create(BaseUI* baseUi);
    void onPlayGame(Ref* ref);
    void onResumeGame(Ref* ref);
private:
    BaseUI* m_baseUi;

};

#endif /* defined(__MazeJump__StartUI__) */
