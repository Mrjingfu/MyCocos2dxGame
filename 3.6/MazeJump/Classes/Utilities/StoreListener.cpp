//
//  StoreListener.cpp
//  MazeJump
//
//  Created by wang haibo on 15/8/19.
//
//

#include "StoreListener.h"
#include "GameConst.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

StoreListener* g_pStoreListenerInstance = nullptr;
StoreListener* StoreListener::getInstance()
{
    if( g_pStoreListenerInstance == nullptr )
        g_pStoreListenerInstance = new StoreListener();
    
    return g_pStoreListenerInstance;
}
StoreListener::StoreListener()
{
}
StoreListener::~StoreListener()
{
}
void StoreListener::registerStoreListener()
{
    ///初始化sdkbox
#if COCOS2D_DEBUG
    sdkbox::IAP::setDebug(true);
#endif
    localStorageSetItem("coin_package1", "450");
    localStorageSetItem("coin_package2", "1500");
    localStorageSetItem("coin_package3", "2500");
    localStorageSetItem("coin_package4", "6000");
    localStorageSetItem("coin_package5", "12500");
    sdkbox::IAP::setListener(this);
    sdkbox::IAP::init();
}
void StoreListener::purchase(const std::string& productName)
{
    sdkbox::IAP::purchase(productName);
}
void StoreListener::restore()
{
    sdkbox::IAP::restore();
}
std::vector<sdkbox::Product> StoreListener::getProducts() const
{
    return _products;
}
void StoreListener::onSuccess(const sdkbox::Product& p)
{
    int currentGold = Value(localStorageGetItem(USER_GOLD_NUM)).asInt();
    if (p.name == PURCHASE_ID1) {
        currentGold += Value(localStorageGetItem(PURCHASE_ID1)).asInt();
        localStorageSetItem(USER_GOLD_NUM, Value(currentGold).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PURCHASE_GOLD_OK);
    }
    else if (p.name == PURCHASE_ID2) {
        currentGold += Value(localStorageGetItem(PURCHASE_ID2)).asInt();
        localStorageSetItem(USER_GOLD_NUM, Value(currentGold).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PURCHASE_GOLD_OK);
    }
    else if (p.name == PURCHASE_ID3) {
        currentGold += Value(localStorageGetItem(PURCHASE_ID3)).asInt();
        localStorageSetItem(USER_GOLD_NUM, Value(currentGold).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PURCHASE_GOLD_OK);
    }
    else if (p.name == PURCHASE_ID4) {
        currentGold += Value(localStorageGetItem(PURCHASE_ID4)).asInt();
        localStorageSetItem(USER_GOLD_NUM, Value(currentGold).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PURCHASE_GOLD_OK);
    }
    else if (p.name == PURCHASE_ID5) {
        currentGold += Value(localStorageGetItem(PURCHASE_ID5)).asInt();
        localStorageSetItem(USER_GOLD_NUM, Value(currentGold).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PURCHASE_GOLD_OK);
    }
    else if (p.name == PURCHASE_ID6) {
        CCLOG("Remove Ads");
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PURCHASE_REMOVEADS_OK);
    }
    
    CCLOG("Purchase Success: %s", p.id.c_str());
    
}

void StoreListener::onFailure(const sdkbox::Product& p, const std::string& msg)
{
    CCLOG("Purchase Failed: %s", msg.c_str());
}

void StoreListener::onCanceled(const sdkbox::Product& p)
{
    CCLOG("Purchase Canceled: %s", p.id.c_str());
}

void StoreListener::onRestored(const sdkbox::Product& p)
{
    CCLOG("Purchase Restored: %s", p.name.c_str());
    if (p.name == PURCHASE_ID6) {
        CCLOG("Remove Ads");
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PURCHASE_REMOVEADS_OK);
    }
}

void StoreListener::onProductRequestSuccess(const std::vector<sdkbox::Product>& products)
{
    CCLOG("Request product success!");
    _products = products;
#if COCOS2D_DEBUG
    for (int i=0; i < _products.size(); i++)
    {
        CCLOG("IAP: ========= IAP Item =========");
        CCLOG("IAP: Name: %s", _products[i].name.c_str());
        CCLOG("IAP: ID: %s", _products[i].id.c_str());
        CCLOG("IAP: Title: %s", _products[i].title.c_str());
        CCLOG("IAP: Desc: %s", _products[i].description.c_str());
        CCLOG("IAP: Price: %s", _products[i].price.c_str());
        CCLOG("IAP: Price Value: %f", _products[i].priceValue);
    }
#endif
}

void StoreListener::onProductRequestFailure(const std::string& msg)
{
    CCLOG("Fail to request products!");
}