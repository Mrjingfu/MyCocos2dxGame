//
//  HelpInfoUI.h
//  TinyFlare
//
//  Created by wang haibo on 15/5/14.
//
//

#ifndef __TinyFlare__HelpInfoUI__
#define __TinyFlare__HelpInfoUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
class HelpInfoUI : public cocos2d::ui::Layout,  public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
    HelpInfoUI();
    virtual ~HelpInfoUI();
    virtual bool init() override;
public:
    static HelpInfoUI* create();
    
    cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
    cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
    void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
protected:
    void pressPreviousBtn(Ref* p,TouchEventType eventType);
    void pressNextBtn(Ref* p,TouchEventType eventType);
    void pressExitBtn(Ref* p,TouchEventType eventType);
    
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event);
private:
    cocos2d::ui::Button*                    m_pPreviousBtn;
    cocos2d::ui::Button*                    m_pNextBtn;
    cocos2d::ui::Button*                    m_pExitBtn;
    cocos2d::extension::TableView*          m_pTableView;
    int                                     m_nCurrentPage;
};

#endif /* defined(__TinyFlare__HelpInfoUI__) */
