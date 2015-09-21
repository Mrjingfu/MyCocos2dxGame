//
//  BagPopUpUi.h
//  Tone_Skipper
//
//  Created by 创李 on 15/9/21.
//
//

#ifndef __Tone_Skipper__BagPopUpUi__
#define __Tone_Skipper__BagPopUpUi__

#include "GameConfig.h"
#include "PopupUILayer.h"


#define CELL_PT(COL,ROW) (cocos2d::Vec2(ROW*CELL_SIZE+CELL_SIZE/2,COL*CELL_SIZE+CELL_SIZE/2))
#define MAX_COL 6
#define MAX_ROW 5
#define CELL_SIZE 32
class BagPopUpUi:public PopupUILayer
{
public:
    BagPopUpUi();
    virtual ~BagPopUpUi();
    CREATE_FUNC(BagPopUpUi);
    void addEvents() override;
    void onClose(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
private:
    cocos2d::Vector<cocos2d::ui::ImageView*> m_pItemBgs;
    
};


#endif /* defined(__Tone_Skipper__BagPopUpUi__) */

