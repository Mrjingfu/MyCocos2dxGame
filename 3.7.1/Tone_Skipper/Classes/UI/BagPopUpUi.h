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


class CustomScrollView;
class BagPopUpUi:public PopupUILayer
{
public:
    BagPopUpUi();
    virtual ~BagPopUpUi();
    CREATE_FUNC(BagPopUpUi);
    void addEvents() override;
    void updateItemRow(int row);
    void onClose(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
private:
    void onScrollEvent(Ref*, cocos2d::ui::ScrollView::EventType);
    cocos2d::Vec2 getItemVec(int col,int row);
    cocos2d::ui::ScrollView* m_pCustomScrollView;
    cocos2d::Vector<cocos2d::ui::ImageView*> testImgs;
    cocos2d::Vec2 m_pTouch;
    void initItems();
    void initBackground();
    int m_pCol;
    int m_pRow;
    int m_pCellSize;
    bool m_pIsScrolling;
    
};


#endif /* defined(__Tone_Skipper__BagPopUpUi__) */

