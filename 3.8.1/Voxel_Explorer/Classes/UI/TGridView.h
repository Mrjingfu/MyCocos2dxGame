


#ifndef __UIGridView_H__
#define __UIGridView_H__

#include "ui/UIScrollView.h"
#include "ui/GUIExport.h"
USING_NS_CC;
using namespace ui;

typedef enum
{
    LISTVIEW_ONSELECTEDITEM_START,
    LISTVIEW_ONSELECTEDITEM_END
}GridViewEventType;

typedef void (Ref::*SEL_ListViewEvent)(Ref*,GridViewEventType);



class CC_GUI_DLL TGridView : public ScrollView
{
 
    DECLARE_CLASS_GUI_INFO
public:
 
    enum class Gravity
    {
        LEFT,
        RIGHT,
        CENTER_HORIZONTAL,
        TOP,
        BOTTOM,
        CENTER_VERTICAL
    };

    enum class EventType
    {
        ON_SELECTED_ITEM_START,
        ON_SELECTED_ITEM_END
    };
  
    typedef std::function<void(Ref*, EventType)> ccGridViewCallback;
    

    TGridView();
 
    virtual ~TGridView();
 
    static TGridView* create();

    void setCol(int x);
    
    void setItemModel(Widget* model);

    void pushBackCustomItem(Widget* item);
   
    void insertCustomItem(Widget* item, ssize_t index);
   
    void removeLastItem();
    
    void removeItem(ssize_t index);
    
    void removeAllItems();

    
    Widget* getItem(ssize_t index)const;
    
    Vector<Widget*>& getItems();
    
    ssize_t getIndex(Widget* item) const;
    
    void setGravity(Gravity gravity);
    
    void setItemsMargin(cocos2d::Size margin);
    
    cocos2d::Size getItemsMargin()const;
    
    //override methods
    virtual void forceDoLayout()override;
    virtual void doLayout() override;
    virtual void addChild(Node* child)override;
    virtual void addChild(Node * child, int localZOrder)override;
    virtual void addChild(Node* child, int zOrder, int tag) override;
    virtual void addChild(Node* child, int zOrder, const std::string &name) override;
    virtual void removeAllChildren() override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void removeChild(Node* child, bool cleaup = true) override;
    
    ssize_t getCurSelectedIndex() const;
    
    void addEventListener(const ccGridViewCallback& callback);
    using ScrollView::addEventListener;

    virtual void setDirection(Direction dir) override;
    
    virtual std::string getDescription() const override;
    
    void requestRefreshView();

    void refreshView();

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
protected:
    
    void updateInnerContainerSize();
    void remedyLayoutParameter(Widget* item);
    
    
    virtual void onSizeChanged() override;
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;
    void selectedItemEvent(TouchEventType event);
    virtual void interceptTouchEvent(Widget::TouchEventType event,Widget* sender,Touch* touch) override;
protected:
    
    int m_pX;
    Widget* _model;
    
    Vector<Widget*> _items;
    
    Gravity _gravity;
    cocos2d::Size _itemMarginSize;

    ssize_t _curSelectedIndex;
    bool _refreshViewDirty;
  
    ccGridViewCallback _eventCallback;
};





#endif
