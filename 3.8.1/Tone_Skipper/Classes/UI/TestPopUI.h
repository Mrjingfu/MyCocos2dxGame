//
//  TestPopUI.h
//  Tone_Skipper
//
//  Created by 创李 on 15/9/18.
//
//

#ifndef __Tone_Skipper__TestPopUI__
#define __Tone_Skipper__TestPopUI__

#include "PopupUILayer.h"

class TestPopUI:public PopupUILayer
{
public:
    CREATE_FUNC(TestPopUI)
    TestPopUI();
    virtual ~TestPopUI();
    void addEvents() override;
    virtual bool init();
    void onCancel(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
};

#endif /* defined(__Tone_Skipper__TestPopUI__) */
