//
//  SdkBoxManager.cpp
//  MazeJump
//
//  Created by wang haibo on 15/8/20.
//
//

#include "SdkBoxManager.h"
#include "GameConst.h"
#include "NativeBridge.h"
#include "storage/local-storage/LocalStorage.h"
#include "AudioEngine.h"
USING_NS_CC;
using namespace experimental;

SdkBoxManager* g_pSdkBoxManagerInstance = nullptr;
SdkBoxManager* SdkBoxManager::getInstance()
{
    if( g_pSdkBoxManagerInstance == nullptr )
        g_pSdkBoxManagerInstance = new SdkBoxManager();
    
    return g_pSdkBoxManagerInstance;
}
SdkBoxManager::SdkBoxManager()
{
}
SdkBoxManager::~SdkBoxManager()
{
}
#pragma mark IAP
void SdkBoxManager::registerIAPListener()
{
    ///初始化sdkbox iap
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
void SdkBoxManager::purchase(const std::string& productName)
{
    sdkbox::IAP::purchase(productName);
    NativeBridge::getInstance()->showIndicatorView();
}
void SdkBoxManager::restore()
{
    sdkbox::IAP::restore();
    //NativeBridge::getInstance()->showIndicatorView();
}
std::vector<sdkbox::Product> SdkBoxManager::getProducts() const
{
    return _products;
}
void SdkBoxManager::onSuccess(const sdkbox::Product& p)
{
    CCLOG("Purchase Success: %s", p.id.c_str());
    NativeBridge::getInstance()->hideIndicatorView();
    int currentGold = Value(localStorageGetItem(USER_GOLD_NUM)).asInt();
    if (p.name == PURCHASE_ID1) {
        currentGold += Value(localStorageGetItem(PURCHASE_ID1)).asInt();
        localStorageSetItem(USER_GOLD_NUM, Value(currentGold).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PURCHASE_GOLD_OK);
        AudioEngine::play2d("pickupgold.wav");
    }
    else if (p.name == PURCHASE_ID2) {
        currentGold += Value(localStorageGetItem(PURCHASE_ID2)).asInt();
        localStorageSetItem(USER_GOLD_NUM, Value(currentGold).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PURCHASE_GOLD_OK);
        AudioEngine::play2d("pickupgold.wav");
    }
    else if (p.name == PURCHASE_ID3) {
        currentGold += Value(localStorageGetItem(PURCHASE_ID3)).asInt();
        localStorageSetItem(USER_GOLD_NUM, Value(currentGold).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PURCHASE_GOLD_OK);
        AudioEngine::play2d("pickupgold.wav");
    }
    else if (p.name == PURCHASE_ID4) {
        currentGold += Value(localStorageGetItem(PURCHASE_ID4)).asInt();
        localStorageSetItem(USER_GOLD_NUM, Value(currentGold).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PURCHASE_GOLD_OK);
        AudioEngine::play2d("pickupgold.wav");
    }
    else if (p.name == PURCHASE_ID5) {
        currentGold += Value(localStorageGetItem(PURCHASE_ID5)).asInt();
        localStorageSetItem(USER_GOLD_NUM, Value(currentGold).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PURCHASE_GOLD_OK);
        AudioEngine::play2d("pickupgold.wav");
    }
    else if (p.name == PURCHASE_ID6) {
        CCLOG("Remove Ads");
        localStorageSetItem("RemoveAds", "true");
        NativeBridge::getInstance()->hideAdsView();
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PURCHASE_REMOVEADS_OK);
        AudioEngine::play2d("mazejump_sucess.wav", false, 0.5f);
    }
}
void SdkBoxManager::onFailure(const sdkbox::Product& p, const std::string& msg)
{
    CCLOG("Purchase Failed: %s", msg.c_str());
    NativeBridge::getInstance()->hideIndicatorView();
    AudioEngine::play2d("mazejump_failed.wav",false, 0.5f);
}
void SdkBoxManager::onCanceled(const sdkbox::Product& p)
{
    CCLOG("Purchase Canceled: %s", p.id.c_str());
    NativeBridge::getInstance()->hideIndicatorView();
    AudioEngine::play2d("mazejump_failed.wav",false, 0.5f);
}
void SdkBoxManager::onRestored(const sdkbox::Product& p)
{
    CCLOG("Purchase Restored: %s", p.name.c_str());
    NativeBridge::getInstance()->hideIndicatorView();
    if (p.name == PURCHASE_ID6) {
        CCLOG("Remove Ads");
        localStorageSetItem("RemoveAds", "true");
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PURCHASE_REMOVEADS_OK);
        AudioEngine::play2d("mazejump_sucess.wav", false, 0.5f);
    }
}
void SdkBoxManager::onProductRequestSuccess(const std::vector<sdkbox::Product>& products)
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
void SdkBoxManager::onProductRequestFailure(const std::string& msg)
{
    CCLOG("Fail to request products!");
    sdkbox::IAP::refresh();
}

#pragma mark GoogleAnalytics
void SdkBoxManager::registerGoogleAnalytics()
{
    sdkbox::PluginGoogleAnalytics::init();
    sdkbox::PluginGoogleAnalytics::enableAdvertisingTracking(true);
}
void SdkBoxManager::logScreen(std::string title)
{
    sdkbox::PluginGoogleAnalytics::logScreen(title);
}
void SdkBoxManager::logEvent(std::string eventCategory, std::string eventAction, std::string eventLabel, int value)
{
    sdkbox::PluginGoogleAnalytics::logEvent(eventCategory, eventAction, eventLabel, value);
}
void SdkBoxManager::logException(std::string exceptionDescription, bool isFatal)
{
    sdkbox::PluginGoogleAnalytics::logException(exceptionDescription, isFatal);
}
void SdkBoxManager::logTiming(std::string timingCategory, int timingInterval, std::string timingName, std::string timingLabel)
{
    sdkbox::PluginGoogleAnalytics::logTiming(timingCategory, timingInterval, timingName, timingLabel);
}
void SdkBoxManager::logSocial(std::string socialNetwork, std::string socialAction, std::string socialTarget)
{
    sdkbox::PluginGoogleAnalytics::logSocial(socialNetwork, socialAction, socialTarget);
}