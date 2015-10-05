//
//  CustomScrollView.h
//  Tone_Skipper
//
//  Created by 创李 on 15/9/22.
//
//

#ifndef __Tone_Skipper__BagScrollView__
#define __Tone_Skipper__BagScrollView__

#include "ui/CocosGUI.h"
class CustomScrollView:public cocos2d::ui::ScrollView
{
    CustomScrollView();
public:
    static CustomScrollView* create();
    virtual ~CustomScrollView();
    virtual void setCameraMask(unsigned short mask, bool applyChildren = true) override;

};
#endif /* defined(__Tone_Skipper__BagScrollView__) */
