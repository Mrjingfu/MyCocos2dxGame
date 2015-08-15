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
#include "RoleManager.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

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

    m_itemNormalImg = ui::ImageView::create(_roleImg);
    setContentSize(m_itemNormalImg->getContentSize()*scale);
    m_itemNormalImg->setPosition(Vec2(getContentSize().width*0.5,getContentSize().height*0.5));
    addChild(m_itemNormalImg);
    
    m_itemLockImg = ui::ImageView::create("character_mask.png");
    m_itemLockImg->setPosition(Vec2(getContentSize().width*0.5,getContentSize().height*0.5));
    addChild(m_itemLockImg);
    m_itemLockImg->setVisible(!m_isLock);
    setAnchorPoint(Vec2(0.5, 0.5));

    
    return true;
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
    m_currentRoleItem = nullptr;
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
    m_popupBgLayer = ui::ImageView::create("panel_characterlist.png");
    m_popupBgLayer->setPosition(Vec2(m_popupBgLayer->getContentSize().width*0.5*scale, size.height*0.7));
    m_popupBgLayer->setScale(scale);
    m_dialogLayer->addChild(m_popupBgLayer);
    
    
    ui::ListView* uiListView = ui::ListView::create();
    uiListView->setAnchorPoint(Vec2(0.5,0.5));
    uiListView->setContentSize(m_popupBgLayer->getContentSize()*scale);
    uiListView->setPosition(Vec2(m_popupBgLayer->getContentSize().width*0.5*scale+20*scale, size.height*0.7));
    uiListView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    uiListView->setTouchEnabled(true);
    uiListView->setBounceEnabled(true);
    uiListView->setBackGroundImageScale9Enabled(true);
    uiListView->setItemsMargin(25*scale);
    uiListView->setGravity(cocos2d::ui::ListView::Gravity::CENTER_VERTICAL);
    uiListView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(RolePopUpUI::selectedItemEvent, this));
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
        roleItem->setScale(scale);
        uiListView->pushBackCustomItem(roleItem);
        
    }
    
    ui::Button* backButton = ui::Button::create("btn_scrollback_normal.png","btn_scrollback_pressed.png");
    backButton->setScale(scale);
    backButton->setPosition(Vec2(backButton->getContentSize().width*0.5*scale, size.height*0.557));
    m_dialogLayer->addChild(backButton);
    
     m_lockLayer = Layer::create();
    m_dialogLayer->addChild(m_lockLayer);
    m_lockLayer->setPosition(Vec2(size.width, 0));
    ui::Button* m_lockButton = ui::Button::create(UtilityHelper::getLocalString("UI_ROLE_BTN_LOCK_NORMAL"),UtilityHelper::getLocalString("UI_ROLE_BTN_LOCK_PRESSED"));
    m_lockButton->setScale(scale);
    m_lockButton->setPosition(Vec2(size.width-m_lockButton->getContentSize().width*0.5*scale, size.height*0.557));
    m_lockLayer->addChild(m_lockButton);
    
    m_lockTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()).asString());
    m_lockTv->setPosition(Vec2(size.width-60*scale, size.height*0.557));
    m_lockTv->setScale(scale*0.5);
    m_lockLayer->addChild(m_lockTv);
    
    
     backButton->addClickEventListener(CC_CALLBACK_1(RolePopUpUI::onBack, this));
     m_lockButton->addClickEventListener(CC_CALLBACK_1(RolePopUpUI::onLock, this));
    return true;
}
void RolePopUpUI::selectedItemEvent(cocos2d::Ref *sender, cocos2d::ui::ListView::EventType type)
{
    if (m_isNowShowLockBtn) {
        return;
    }
    if (type == cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END) {
        cocos2d::ui::ListView* listView = static_cast<cocos2d::ui::ListView*>(sender);
        RoleItem* item = static_cast<RoleItem*>(listView->getItem(listView->getCurSelectedIndex()));
        if (m_currentRoleItem) {
            if (item->getRoleId() == m_currentRoleItem->getRoleId()) {
                return;
            }
        }
        m_currentRoleItem = item;
        m_isNowShowLockBtn = true;
        if (!m_currentRoleItem->getIsLock()) {
            if (m_isShowLockBtn) {
                hideLockButton(CC_CALLBACK_0(RolePopUpUI::onHideShowLockCall,this,m_currentRoleItem->getPrice()));
            }else
            {
                showLockButton(m_currentRoleItem->getPrice());
            }
        }else{
            hideLockButton();
        }
    }
}
void RolePopUpUI::showLockButton(int price)
{
    if (m_lockTv) {
        m_lockTv->setString(Value(price).asString());
    }
    if (m_lockLayer) {
        cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.3,Vec2::ZERO);
         CallFunc* callFunc1 = CallFunc::create(CC_CALLBACK_0(RolePopUpUI::onShowLockEnd,this));
        m_lockLayer->runAction(Sequence::create(EaseSineOut::create(moveTo),callFunc1, NULL));
        
    }
    
}
void RolePopUpUI::hideLockButton(const std::function<void()> &endfunc)
{

    auto size = Director::getInstance()->getVisibleSize();
    if (m_lockLayer) {
        cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.3,Vec2(size.width, 0));
        CallFunc* callFunc1 = CallFunc::create(CC_CALLBACK_0(RolePopUpUI::onHideLockEnd,this));
        if (endfunc) {
            CallFunc* callFunc2 = CallFunc::create(endfunc);
            m_lockLayer->runAction(Sequence::create(EaseSineOut::create(moveTo),callFunc1,callFunc2,NULL));
        }else
        {
           m_lockLayer->runAction(Sequence::create(moveTo,callFunc1, NULL));
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
    m_isShowLockBtn = true;
}
void RolePopUpUI::onHideShowLockCall(int price)
{
    showLockButton(price);
}
void RolePopUpUI::onBack(cocos2d::Ref *Ref)
{
    UIManager::getInstance()->hidePopUp();
}
void RolePopUpUI::onLock(cocos2d::Ref *ref)
{
    if (m_currentRoleItem) {
        
        int goldNum = Value(localStorageGetItem(USER_GOLD_NUM)).asInt();
        if (goldNum >= m_currentRoleItem->getPrice()) {
            localStorageSetItem(USER_GOLD_NUM, Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()-m_currentRoleItem->getPrice()).asString());
            m_currentRoleItem->setLock(true);
            CCLOG("currentRoleId:%s isLock:%d",m_currentRoleItem->getRoleId().c_str(),m_currentRoleItem->getIsLock());
            RoleManager::getInstance()->updateRoleLock(m_currentRoleItem->getRoleId(), m_currentRoleItem->getIsLock());
        }else
        {
            UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
            UIManager::getInstance()->showPopUp(false);
        }
        
    }
}

