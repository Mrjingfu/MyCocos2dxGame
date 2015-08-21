//
//  RolePopUpUI.cpp
//
//
//
//

#include "RolePopUpUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MenuScene.h"
#include "UIManager.h"
#include "ShopPopUpUI.h"
#include "RoleManager.h"
#include "storage/local-storage/LocalStorage.h"
#include "AudioEngine.h"
USING_NS_CC;
using namespace experimental;
RoleItem::RoleItem()
{
    m_isLock = false;

}
RoleItem::~RoleItem()
{


}
RoleItem* RoleItem::create(std::string _roleId, int preice, std::string _roleImg, std::string _rolModel, bool _isLock, std::string _roleSound)
{
    RoleItem *pRet = new(std::nothrow) RoleItem();
    if (pRet && pRet->init(_roleId,preice,_roleImg,_rolModel,_isLock,_roleSound))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}
bool RoleItem::init(std::string _roleId, int preice, std::string _roleImg, std::string _rolModel, bool _isLock, std::string _roleSound)
{
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;

    m_isLock = _isLock;
    m_roleId = _roleId;
    m_roleModel = _roleImg;
    m_roleSound = _roleSound;
    m_price = preice;
    m_itemNormal = cocos2d::ui::ImageView::create(_roleImg);
    setContentSize(m_itemNormal->getContentSize());
    m_itemNormal->setPosition(Vec2(getContentSize().width*0.5,getContentSize().height*0.5));
    addChild(m_itemNormal);
    setSelectColor(false);
    
    if (!strcmp(m_roleId.c_str(), localStorageGetItem(USER_DEFAULT_ROLE_ID).c_str()) ) {
      
        setSelectColor(true);
    }
    if (!m_isLock) {
        setSelectColor(true);
    }
    
    
    m_itemLockImg = cocos2d::ui::ImageView::create("character_mask.png");
    m_itemLockImg->setPosition(Vec2(getContentSize().width*0.5,getContentSize().height*0.5));
    addChild(m_itemLockImg);
    m_itemLockImg->setVisible(!m_isLock);
    setAnchorPoint(Vec2(0.5, 0.5));

    
    return true;
}
void RoleItem::setSelectColor(bool isSelect)
{
    if (isSelect)
    {
        m_itemNormal->setColor(Color3B(255, 255, 255));
    }else
    {
        m_itemNormal->setColor(Color3B(159, 168, 187));
    }
    
}
void RoleItem::setLock(bool _isLock)
{
    m_isLock = _isLock;
    if (m_itemLockImg) {
       m_itemLockImg->setVisible(!m_isLock);
    }
}

RolePopUpUI* RolePopUpUI::create()
{
    RolePopUpUI *pRet = new(std::nothrow) RolePopUpUI();
    if (pRet )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

RolePopUpUI::RolePopUpUI()
{
    m_lockTv = nullptr;
    m_lockLayer = nullptr;
    m_isShowLockBtn = false;
    m_isNowShowLockBtn = false;
    m_cureentSelectIteml = nullptr;
    m_currentNotLockRoleItem = nullptr;
    m_isLockHideShow = false;
}
RolePopUpUI::~RolePopUpUI()
{
}
void RolePopUpUI::onEnter()
{
    BasePopUpUI::onEnter();
    init();
    if (UIManager::getInstance()->getGameId() == UIManager::UI_MAIN) {
        UIManager::getInstance()->showInfo(true);
        
    }
}
void RolePopUpUI::onExit()
{
    BasePopUpUI::onExit();
    if (UIManager::getInstance()->getGameId() == UIManager::UI_MAIN) {
        UIManager::getInstance()->showInfo(false);
        
    }
}
bool RolePopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    m_maskLayerBg->setVisible(false);
    m_popupBgLayer = cocos2d::ui::ImageView::create("panel_characterlist.png");
    m_popupBgLayer->setScale(scale);
    m_popupBgLayer->setPosition(Vec2(m_popupBgLayer->getContentSize().width*0.5*scale, size.height*0.7));

    m_dialogLayer->addChild(m_popupBgLayer);
    
    
    cocos2d::ui::ListView* uiListView = cocos2d::ui::ListView::create();
    uiListView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    uiListView->setContentSize(cocos2d::Size(m_popupBgLayer->getContentSize().width-20*scale, m_popupBgLayer->getContentSize().height));
    uiListView->setPosition(Vec2(m_popupBgLayer->getContentSize().width*0.5*scale+10*scale, size.height*0.7));
    uiListView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
    uiListView->setTouchEnabled(true);
    uiListView->setBounceEnabled(true);
    uiListView->setBackGroundImageScale9Enabled(true);
    uiListView->setItemsMargin(5*scale);
    uiListView->setScale(scale);
    uiListView->setGravity(cocos2d::ui::ListView::Gravity::CENTER_VERTICAL);
    uiListView->addEventListener((cocos2d::ui::ListView::ccListViewCallback)CC_CALLBACK_2(RolePopUpUI::selectedItemEvent, this));
    m_dialogLayer->addChild(uiListView);

    
    ValueMap roleMap = RoleManager::getInstance()->getRoleMap();
    for(std::unordered_map<std::string, Value>::iterator roteIt = roleMap.begin(); roteIt!=roleMap.end();roteIt++)
    {
        std::string keyStr = roteIt->first;
        Value roleValue = roteIt->second;
        std::string roleModel = RoleManager::getInstance()->getRoleModel(keyStr);
        std::string roleImg = RoleManager::getInstance()->getRoleImg(keyStr);
        std::string roleSound = RoleManager::getInstance()->getRoleSound(keyStr);
        int rolePrice = RoleManager::getInstance()->getRolePrice(keyStr);
        bool roleLock = RoleManager::getInstance()->getRoleLock(keyStr);
        CCLOG("roleModel:%s,roleImg:%s,roleSound:%s,rolePrice:%d,roleLock:%d",roleModel.c_str(),roleImg.c_str(),roleSound.c_str(),rolePrice,roleLock);
        RoleItem* roleItem = RoleItem::create(keyStr, rolePrice, roleImg, roleModel, roleLock, roleSound);
        roleItem->setTouchEnabled(true);
        uiListView->pushBackCustomItem(roleItem);
        if (!strcmp(keyStr.c_str(), localStorageGetItem(USER_DEFAULT_ROLE_ID).c_str())) {
            m_cureentSelectIteml = roleItem;
        }
        
    }
    
    cocos2d::ui::Button* backButton = cocos2d::ui::Button::create("btn_scrollback_normal.png","btn_scrollback_pressed.png");
    backButton->setScale(scale);
    backButton->setPosition(Vec2(backButton->getContentSize().width*0.5*scale, size.height*0.55));
    m_dialogLayer->addChild(backButton);
    
    m_lockLayer = Layer::create();
    m_dialogLayer->addChild(m_lockLayer);
    
    m_lockLayer->setPosition(Vec2(size.width, 0));
    cocos2d::ui::Button* m_lockButton = cocos2d::ui::Button::create(UtilityHelper::getLocalString("UI_ROLE_BTN_LOCK_NORMAL"),UtilityHelper::getLocalString("UI_ROLE_BTN_LOCK_PRESSED"));
    m_lockButton->setScale(scale);
    m_lockButton->setPosition(Vec2(size.width-m_lockButton->getContentSize().width*0.5*scale, size.height*0.557));
    m_lockLayer->addChild(m_lockButton);
    
    m_lockTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()).asString());
    m_lockTv->setPosition(Vec2(size.width-60*scale, size.height*0.55));
    m_lockTv->setScale(scale);
    m_lockLayer->addChild(m_lockTv);
    
    
     backButton->addClickEventListener(CC_CALLBACK_1(RolePopUpUI::onBack, this));
     m_lockButton->addClickEventListener(CC_CALLBACK_1(RolePopUpUI::onUnLock, this));
    return true;
}

void RolePopUpUI::selectedItemEvent(cocos2d::Ref *sender, cocos2d::ui::ListView::EventType type)
{
    
    if (type == cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END) {

        
        CCLOG("m_isNowShowLockBtn:%d",m_isNowShowLockBtn);
        if (m_isNowShowLockBtn)
            return;
        if (m_isLockHideShow)
            return;
        
        UIManager::getInstance()->playBtnSound();
        cocos2d::ui::ListView* listView = static_cast<cocos2d::ui::ListView*>(sender);
        RoleItem* item = static_cast<RoleItem*>(listView->getItem(listView->getCurSelectedIndex()));
        

        if (m_currentNotLockRoleItem) {
            CCLOG("item:%s notLock:%s select:%s",item->getRoleId().c_str(),m_currentNotLockRoleItem->getRoleId().c_str(),m_cureentSelectIteml->getRoleId().c_str());
        }else
        {
            CCLOG("item:%s notLock is null,select:%s",item->getRoleId().c_str(),m_cureentSelectIteml->getRoleId().c_str());
        }
        
        if (m_currentNotLockRoleItem && item->getRoleId() == m_currentNotLockRoleItem->getRoleId())
            return;
        
        if (!item->getIsLock())
        {
             m_currentNotLockRoleItem = item;
            
            if (m_isShowLockBtn) {
                m_isLockHideShow = true;
                hideLockButton(CC_CALLBACK_0(RolePopUpUI::onHideShowLockCall,this,m_currentNotLockRoleItem->getPrice()));
            }
            else
            {
                m_isNowShowLockBtn = true;
                showLockButton(m_currentNotLockRoleItem->getPrice());
            }
            localStorageSetItem(USER_SELECT_ROLE_ID, m_currentNotLockRoleItem->getRoleId());
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_CHARACTER_MODEL_CHANGE);
            
        }else
        {
            m_currentNotLockRoleItem = nullptr;
            if (m_cureentSelectIteml && m_cureentSelectIteml->getRoleId() != item->getRoleId())
            {
                m_cureentSelectIteml->setSelectColor(false);
                m_cureentSelectIteml = item;
                m_cureentSelectIteml->setSelectColor(true);
            }
            hideLockButton();
            localStorageSetItem(USER_SELECT_ROLE_ID, m_cureentSelectIteml->getRoleId());
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_CHARACTER_MODEL_CHANGE);

        }

    }
}
void RolePopUpUI::showLockButton(int price)
{
    stopActionByTag(SHOW_ACTION);
    if (m_lockTv) {
        m_lockTv->setString(Value(price).asString());
    }
    if (m_lockLayer) {
        cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.2,Vec2::ZERO);
         CallFunc* callFunc1 = CallFunc::create(CC_CALLBACK_0(RolePopUpUI::onShowLockEnd,this));
        Sequence* action = Sequence::create(EaseSineOut::create(moveTo),callFunc1, NULL);
        action->setTag(SHOW_ACTION);
        m_lockLayer->runAction(action);
        
    }
    
}
void RolePopUpUI::hideLockButton(const std::function<void()> &endfunc)
{
    stopActionByTag(HIDE_ACTION);
    auto size = Director::getInstance()->getVisibleSize();
    if (m_lockLayer) {
        cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.2,Vec2(size.width, 0));
        CallFunc* callFunc1 = CallFunc::create(CC_CALLBACK_0(RolePopUpUI::onHideLockEnd,this));
        if (endfunc) {
            CallFunc* callFunc2 = CallFunc::create(endfunc);
            Sequence* action = Sequence::create(EaseSineOut::create(moveTo),callFunc1,callFunc2,NULL);
            action->setTag(HIDE_ACTION);
            m_lockLayer->runAction(action);
        }else
        {
            Sequence* action = Sequence::create(moveTo,callFunc1, NULL);
            action->setTag(HIDE_ACTION);
            m_lockLayer->runAction(action);
        }
        
    }
}
void RolePopUpUI::onHideLockEnd()
{
    m_isNowShowLockBtn =false;
    m_isShowLockBtn = false;
}
void RolePopUpUI::onShowLockEnd()
{
    m_isNowShowLockBtn = false;
    m_isLockHideShow =false;
    m_isShowLockBtn = true;
}
void RolePopUpUI::onHideShowLockCall(int price)
{
    showLockButton(price);
}
void RolePopUpUI::onBack(cocos2d::Ref *Ref)
{
    if (m_cureentSelectIteml ) {
        
        localStorageSetItem(USER_DEFAULT_ROLE_ID, m_cureentSelectIteml->getRoleId());
        localStorageSetItem(USER_SELECT_ROLE_ID, m_cureentSelectIteml->getRoleId());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_CHARACTER_MODEL_CHANGE);
    }
    
    UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->hidePopUp();
}
void RolePopUpUI::onUnLock(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playBtnSound();
    if (m_currentNotLockRoleItem) {
        
        int goldNum = Value(localStorageGetItem(USER_GOLD_NUM)).asInt();
        if (goldNum >= m_currentNotLockRoleItem->getPrice()) {
            localStorageSetItem(USER_GOLD_NUM, Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()-m_currentNotLockRoleItem->getPrice()).asString());
            m_currentNotLockRoleItem->setLock(true);
            m_currentNotLockRoleItem->setSelectColor(true);
            if (m_cureentSelectIteml) {
                m_cureentSelectIteml->setSelectColor(false);
            }
            m_cureentSelectIteml = m_currentNotLockRoleItem;
            CCLOG("currentRoleId:%s isLock:%d",m_currentNotLockRoleItem->getRoleId().c_str(),m_currentNotLockRoleItem->getIsLock());
            RoleManager::getInstance()->updateRoleLock(m_currentNotLockRoleItem->getRoleId(), m_currentNotLockRoleItem->getIsLock());
            hideLockButton();
            
        }else
        {
            UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
            ShopPopUpUI* shopPopUp = static_cast<ShopPopUpUI*>(UIManager::getInstance()->getPopUpUI(BasePopUpUI::POPUP_SHOP));
            if (shopPopUp) {
                shopPopUp->setShopDisplay(ShopPopUpUI::SHOP_GOLD);
            }
            UIManager::getInstance()->showPopUp(false);
        }
        
    }
}

