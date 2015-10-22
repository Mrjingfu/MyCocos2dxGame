

#include "TGridView.h"
#include "ui/UIHelper.h"




    
IMPLEMENT_CLASS_GUI_INFO(TGridView)

TGridView::TGridView():
_model(nullptr),
_gravity(Gravity::CENTER_VERTICAL),
_itemMarginSize(cocos2d::Size::ZERO),
_curSelectedIndex(-1),
_refreshViewDirty(true),
m_pX(-1),
_eventCallback(nullptr)
{
    this->setTouchEnabled(true);
}

TGridView::~TGridView()
{

    _items.clear();
    CC_SAFE_RELEASE(_model);
}

TGridView* TGridView::create()
{
    TGridView* widget = new (std::nothrow) TGridView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool TGridView::init()
{
    if (ScrollView::init())
    {
        setLayoutType(Type::RELATIVE);
        return true;
    }
    return false;
}
void TGridView::setCol(int x)
{
    m_pX = x;

}
void TGridView::setItemModel(Widget *model)
{
    if (nullptr == model)
    {
        CCLOG("Can't set a nullptr to item model!");
        return;
    }
    CC_SAFE_RELEASE_NULL(_model);
    _model = model;
    CC_SAFE_RETAIN(_model);
}

void TGridView::updateInnerContainerSize()
{
    int y = _items.size()/m_pX;
    float totalHeight = y*_itemMarginSize.height;
    float totalWidth = m_pX* _itemMarginSize.width ;
    
    for (auto item : _items) {
        totalHeight+= item->getContentSize().height*y;
        totalWidth+=item->getContentSize().width*m_pX;
        break;
    }
//    if (_direction == Direction::HORIZONTAL && totalHeight < _contentSize.height) {
//        totalHeight = _contentSize.height;
//    }else if (_direction == Direction::VERTICAL && totalWidth < _contentSize.width)
//    {
//        totalWidth = _contentSize.width;
//    }

    setInnerContainerSize(cocos2d::Size(totalWidth, totalHeight));
    
   }
    


void TGridView::remedyLayoutParameter(Widget *item)
{
    CCASSERT(nullptr != item, "ListView Item can't be nullptr!");
    
    RelativeLayoutParameter* reLayoutParameter = (RelativeLayoutParameter*)(item->getLayoutParameter());
    bool isLayoutParameterExists = true;
    if (!reLayoutParameter)
    {
        reLayoutParameter = RelativeLayoutParameter::create();
        isLayoutParameterExists = false;
    }
//    RelativeLayoutParameter* reLayoutParameter = RelativeLayoutParameter::create();
    ssize_t itemIndex = getIndex(item);
    std::string currenName = StringUtils::format("item_%d",(int)itemIndex);
    std::string preName = StringUtils::format("item_%d",(int)itemIndex-1);
    int x = itemIndex%m_pX;
    int y = itemIndex/m_pX;
    if (itemIndex ==0) {
        reLayoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_LEFT);
        reLayoutParameter->setRelativeName(currenName );
        reLayoutParameter->setMargin(Margin(_itemMarginSize.width,_itemMarginSize.height,0.0f, 0.0f));
    }else{
        
        if (x==0) {
            //转弯
            preName = StringUtils::format("item_%d",(y-1)*m_pX);
            CCLOG("preName:%s",preName.c_str());
            reLayoutParameter->setRelativeToWidgetName(preName);
             reLayoutParameter->setRelativeName(currenName );
            reLayoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_CENTER);
            reLayoutParameter->setMargin(Margin(0.0f,_itemMarginSize.height,0.0f, 0.0f));
        }else{
            reLayoutParameter->setRelativeToWidgetName(preName);
            reLayoutParameter->setRelativeName(currenName );
            reLayoutParameter->setAlign(RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_CENTER);
            reLayoutParameter->setMargin(Margin(_itemMarginSize.width,_itemMarginSize.height,0.0f, 0.0f));

        }
        
    }


    if (!isLayoutParameterExists)
    {
        item->setLayoutParameter(reLayoutParameter);
    }
}



void TGridView::pushBackCustomItem(Widget* item)
{
    remedyLayoutParameter(item);
    addChild(item);
    _refreshViewDirty = true;
}
    
void TGridView::addChild(cocos2d::Node *child, int zOrder, int tag)
{
 
    ScrollView::addChild(child, zOrder, tag);

    Widget* widget = dynamic_cast<Widget*>(child);
    if (nullptr != widget)
    {
        _items.pushBack(widget);
    }
    
}
    
void TGridView::addChild(cocos2d::Node *child)
{
    TGridView::addChild(child, child->getLocalZOrder(), child->getName());
}

void TGridView::addChild(cocos2d::Node *child, int zOrder)
{
    TGridView::addChild(child, zOrder, child->getName());
}
 
void TGridView::addChild(Node* child, int zOrder, const std::string &name)
{
  
    ScrollView::addChild(child, zOrder, name);
    
    Widget* widget = dynamic_cast<Widget*>(child);
    if (nullptr != widget)
    {
        _items.pushBack(widget);
    }
}
    
void TGridView::removeChild(cocos2d::Node *child, bool cleaup)
{
    Widget* widget = dynamic_cast<Widget*>(child);
    if (nullptr != widget)
    {
        if (-1 != _curSelectedIndex)
        {
            auto removedIndex = getIndex(widget);
            if (_curSelectedIndex > removedIndex)
            {
                _curSelectedIndex -= 1;
            }
            else if (_curSelectedIndex == removedIndex)
            {
                _curSelectedIndex = -1;
            }
        }
        _items.eraseObject(widget);
    }
   
    ScrollView::removeChild(child, cleaup);
}
    
void TGridView::removeAllChildren()
{
    this->removeAllChildrenWithCleanup(true);
}
    
void TGridView::removeAllChildrenWithCleanup(bool cleanup)
{
    ScrollView::removeAllChildrenWithCleanup(cleanup);
    _items.clear();
    _curSelectedIndex = -1;
}

void TGridView::insertCustomItem(Widget* item, ssize_t index)
{
    if (-1 != _curSelectedIndex)
    {
        if (_curSelectedIndex >= index)
        {
            _curSelectedIndex += 1;
        }
    }
    
    _items.insert(index, item);
    ScrollView::addChild(item);

    remedyLayoutParameter(item);
    _refreshViewDirty = true;
}

void TGridView::removeItem(ssize_t index)
{
    Widget* item = getItem(index);
    if (nullptr == item)
    {
        return;
    }
    removeChild(item, true);
    
    _refreshViewDirty = true;
}

void TGridView::removeLastItem()
{
    removeItem(_items.size() -1);
}
    
void TGridView::removeAllItems()
{
    removeAllChildren();
}

Widget* TGridView::getItem(ssize_t index)const
{
    if (index < 0 || index >= _items.size())
    {
        return nullptr;
    }
    return _items.at(index);
}

Vector<Widget*>& TGridView::getItems()
{
    return _items;
}

ssize_t TGridView::getIndex(Widget *item) const
{
    if (nullptr == item)
    {
        return -1;
    }
    return _items.getIndex(item);
}

void TGridView::setGravity(Gravity gravity)
{
    if (_gravity == gravity)
    {
        return;
    }
    _gravity = gravity;
    _refreshViewDirty = true;
}

void TGridView::setItemsMargin(cocos2d::Size margin)
{
    if (_itemMarginSize.width == margin.width && margin.height ==_itemMarginSize.height)
    {
        return;
    }
    _itemMarginSize = margin;
    _refreshViewDirty = true;
}
    
cocos2d::Size TGridView::getItemsMargin()const
{
    return _itemMarginSize;
}

void TGridView::setDirection(Direction dir)
{
    switch (dir)
    {
        case Direction::NONE:
        case Direction::BOTH:
            break;
        case Direction::VERTICAL:
            setLayoutType(Type::VERTICAL);
            break;
        case Direction::HORIZONTAL:
            setLayoutType(Type::HORIZONTAL);
            break;
        default:
            return;
            break;
    }
    ScrollView::setDirection(dir);
}
    
void TGridView::requestRefreshView()
{
    _refreshViewDirty = true;
}

void TGridView::refreshView()
{
    ssize_t length = _items.size();
    for (int i=0; i<length; i++)
    {
        Widget* item = _items.at(i);
        item->setLocalZOrder(i);
        remedyLayoutParameter(item);
    }
    updateInnerContainerSize();
}
    
void TGridView::forceDoLayout()
{
    if (_refreshViewDirty)
    {
        refreshView();
        _refreshViewDirty = false;
    }

    this->_innerContainer->forceDoLayout();
}

void TGridView::doLayout()
{
    Layout::doLayout();
    
    if (_refreshViewDirty)
    {
        refreshView();
        _refreshViewDirty = false;
    }
}


    
void TGridView::addEventListener(const ccGridViewCallback& callback)
{
    _eventCallback = callback;
}
    
void TGridView::selectedItemEvent(TouchEventType event)
{
    this->retain();
    switch (event)
    {
        case TouchEventType::BEGAN:
        {
            
            if (_eventCallback) {
                _eventCallback(this,EventType::ON_SELECTED_ITEM_START);
            }
            if (_ccEventCallback)
            {
                _ccEventCallback(this, static_cast<int>(EventType::ON_SELECTED_ITEM_START));
            }
        }
        break;
        default:
        {
            
            if (_eventCallback) {
                _eventCallback(this, EventType::ON_SELECTED_ITEM_END);
            }
            if (_ccEventCallback)
            {
                _ccEventCallback(this, static_cast<int>(EventType::ON_SELECTED_ITEM_END));
            }
        }
        break;
    }
    this->release();
}
    
void TGridView::interceptTouchEvent(TouchEventType event, Widget *sender, Touch* touch)
{
    ScrollView::interceptTouchEvent(event, sender, touch);
    if (!_touchEnabled)
    {
        return;
    }
    if (event != TouchEventType::MOVED)
    {
        Widget* parent = sender;
        while (parent)
        {
            if (parent && (parent->getParent() == _innerContainer))
            {
                _curSelectedIndex = getIndex(parent);
                break;
            }
            parent = dynamic_cast<Widget*>(parent->getParent());
        }
        if (sender->isHighlighted()) {
            selectedItemEvent(event);
        }
    }
}
    
ssize_t TGridView::getCurSelectedIndex() const
{
    return _curSelectedIndex;
}

void TGridView::onSizeChanged()
{
    ScrollView::onSizeChanged();
    _refreshViewDirty = true;
}

std::string TGridView::getDescription() const
{
    return "ListView";
}

Widget* TGridView::createCloneInstance()
{
    return TGridView::create();
}

void TGridView::copyClonedWidgetChildren(Widget* model)
{
    auto& arrayItems = static_cast<TGridView*>(model)->getItems();
    for (auto& item : arrayItems)
    {
        pushBackCustomItem(item->clone());
    }
}

void TGridView::copySpecialProperties(Widget *widget)
{
    TGridView* listViewEx = dynamic_cast<TGridView*>(widget);
    if (listViewEx)
    {
        ScrollView::copySpecialProperties(widget);
        setItemModel(listViewEx->_model);
        setItemsMargin(listViewEx->_itemMarginSize);
        setGravity(listViewEx->_gravity);
        _eventCallback = listViewEx->_eventCallback;
    }
}

