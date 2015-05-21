//
//  StoreEventHandler.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/5/19.
//
//

#include "StoreEventHandler.h"
#include "CCStoreInfo.h"
#include "TinyFlareAssets.h"
#include "NativeBridge.h"
#include "UtilityHelper.h"

#define TAG "StoreEventHandler >>>"
USING_NS_CC;

using namespace soomla;

StoreEventHandler::StoreEventHandler() {
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_BILLING_NOT_SUPPORTED, CC_CALLBACK_1(StoreEventHandler::onBillingNotSupported, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_BILLING_SUPPORTED, CC_CALLBACK_1(StoreEventHandler::onBillingSupported, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_CURRENCY_BALANCE_CHANGED, CC_CALLBACK_1(StoreEventHandler::onCurrencyBalanceChanged, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED, CC_CALLBACK_1(StoreEventHandler::onGoodBalanceChanged, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_GOOD_EQUIPPED, CC_CALLBACK_1(StoreEventHandler::onGoodEquipped, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_GOOD_UNEQUIPPED, CC_CALLBACK_1(StoreEventHandler::onGoodUnEquipped, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_GOOD_UPGRADE, CC_CALLBACK_1(StoreEventHandler::onGoodUpgrade, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_ITEM_PURCHASE_STARTED, CC_CALLBACK_1(StoreEventHandler::onItemPurchaseStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_ITEM_PURCHASED, CC_CALLBACK_1(StoreEventHandler::onItemPurchased, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_FAILED, CC_CALLBACK_1(StoreEventHandler::onMarketItemsRefreshFailed, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_STARTED, CC_CALLBACK_1(StoreEventHandler::onMarketItemsRefreshStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESHED, CC_CALLBACK_1(StoreEventHandler::onMarketItemsRefreshed, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_PURCHASE, CC_CALLBACK_1(StoreEventHandler::onMarketPurchase, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_PURCHASE_CANCELED, CC_CALLBACK_1(StoreEventHandler::onMarketPurchaseCancelled, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_PURCHASE_STARTED, CC_CALLBACK_1(StoreEventHandler::onMarketPurchaseStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_PURCHASE_VERIFICATION, CC_CALLBACK_1(StoreEventHandler::onMarketPurchaseVerification, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_RESTORE_TRANSACTION_FINISHED, CC_CALLBACK_1(StoreEventHandler::onRestoreTransactionsFinished, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_RESTORE_TRANSACTION_STARTED, CC_CALLBACK_1(StoreEventHandler::onMarketItemsRefreshStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_SOOMLA_STORE_INITIALIZED, CC_CALLBACK_1(StoreEventHandler::onSoomlaStoreInitialized, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_UNEXPECTED_ERROR_IN_STORE, CC_CALLBACK_1(StoreEventHandler::onUnexpectedErrorInStore, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_IAB_SERVICE_STARTED, CC_CALLBACK_1(StoreEventHandler::onIabServiceStarted, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_IAB_SERVICE_STOPPED, CC_CALLBACK_1(StoreEventHandler::onIabServiceStopped, this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_MARKET_REFUND, CC_CALLBACK_1(StoreEventHandler::onMarketRefund, this));
}

void StoreEventHandler::onBillingNotSupported(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "BillingNotSupported");
}

void StoreEventHandler::onBillingSupported(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "BillingSupported");
}

void StoreEventHandler::onCurrencyBalanceChanged(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCVirtualCurrency *currency = dynamic_cast<CCVirtualCurrency *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_CURRENCY));
    __Integer *balance = dynamic_cast<__Integer *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_BALANCE));
    __Integer *amountAdded = dynamic_cast<__Integer *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_AMOUNT_ADDED));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("CurrencyBalanceChanged: %s %d %d",
                                                            currency->getItemId()->getCString(),
                                                            balance->getValue(),
                                                            amountAdded->getValue())->getCString());
}

void StoreEventHandler::onGoodBalanceChanged(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_GOOD));
    __Integer *balance = dynamic_cast<__Integer *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_BALANCE));
    __Integer *amountAdded = dynamic_cast<__Integer *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_AMOUNT_ADDED));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("GoodBalanceChanged: %s %d %d",
                                                            good->getItemId()->getCString(),
                                                            balance->getValue(),
                                                            amountAdded->getValue())->getCString());
}

void StoreEventHandler::onGoodEquipped(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCEquippableVG *equippable = dynamic_cast<CCEquippableVG *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_EQUIPPABLEVG));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("GoodEquipped: %s", equippable->getItemId()->getCString())->getCString());
}

void StoreEventHandler::onGoodUnEquipped(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCEquippableVG *equippable = dynamic_cast<CCEquippableVG *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_EQUIPPABLEVG));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("GoodUnEquipped: %s", equippable->getItemId()->getCString())->getCString());
}

void StoreEventHandler::onGoodUpgrade(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCVirtualGood *good = dynamic_cast<CCVirtualGood *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_GOOD));
    CCUpgradeVG *upgrade = dynamic_cast<CCUpgradeVG *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_UPGRADEVG));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("GoodUpgrade: %s with upgrade %s", good->getItemId()->getCString(),
                                                            upgrade->getItemId()->getCString())->getCString());
}

void StoreEventHandler::onItemPurchased(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_DEVELOPERPAYLOAD));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("ItemPurchased: %s %s",
                                                            purchasable->getItemId()->getCString(),
                                                            payload->getCString())->getCString());
    NativeBridge::getInstance()->hideIndicatorView();
}

void StoreEventHandler::onItemPurchaseStarted(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("ItemPurchaseStarted: %s", purchasable->getItemId()->getCString())->getCString());
    NativeBridge::getInstance()->showIndicatorView();
}

void StoreEventHandler::onMarketPurchaseCancelled(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketPurchaseCancelled: %s", purchasable->getItemId()->getCString())->getCString());
    NativeBridge::getInstance()->hideIndicatorView();
}

void StoreEventHandler::onMarketPurchase(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    __String *token = dynamic_cast<__String *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_TOKEN));
    __String *payload = dynamic_cast<__String *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_DEVELOPERPAYLOAD));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketPurchase: %s token: %s payload: %s",
                                                            purchasable->getItemId()->getCString(),
                                                            token->getCString(),
                                                            payload->getCString())->getCString());
    
    // Android ONLY
    __String *originalJSON = dynamic_cast<__String *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_ORIGINAL_JSON));
    if (originalJSON != NULL) {
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketPurchase: Original JSON %s", originalJSON->getCString())->getCString());
    }
    __String *signature = dynamic_cast<__String *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_SIGNATURE));
    if (signature != NULL) {
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketPurchase: Signature %s", signature->getCString())->getCString());
    }
    __String *userId = dynamic_cast<__String *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_USER_ID));
    if (userId != NULL) {
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketPurchase: User ID %s", userId->getCString())->getCString());
    }
}

void StoreEventHandler::onMarketPurchaseStarted(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketPurchaseStarted: %s", purchasable->getItemId()->getCString())->getCString());
}

void StoreEventHandler::onMarketPurchaseVerification(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    CCPurchasableVirtualItem *purchasable = dynamic_cast<CCPurchasableVirtualItem *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_PURCHASABLE));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketPurchaseVerification: %s", purchasable->getItemId()->getCString())->getCString());
}

void StoreEventHandler::onRestoreTransactionsStarted(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "RestoreTransactionsStarted");
    NativeBridge::getInstance()->showIndicatorView();
}

void StoreEventHandler::onRestoreTransactionsFinished(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    __Bool *success = dynamic_cast<__Bool *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_SUCCESS));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("RestoreTransactionsFinished: %s", success ? "YES" : "NO")->getCString());
    NativeBridge::getInstance()->hideIndicatorView();
}

void StoreEventHandler::onUnexpectedErrorInStore(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    __String *errorMessage = dynamic_cast<__String *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_ERROR_MESSAGE));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("UnexpectedErrorInStore: %s", errorMessage->getCString())->getCString());
    
    if(errorMessage->getCString() == NULL || strlen(errorMessage->getCString()) == 0)
        MessageBox(errorMessage->getCString(), UtilityHelper::getLocalString("NET_ERROR").c_str());
    else
        MessageBox(errorMessage->getCString(), "");
    NativeBridge::getInstance()->hideIndicatorView();
}

void StoreEventHandler::onSoomlaStoreInitialized(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "onSoomlaStoreInitialized");
}

void StoreEventHandler::onMarketItemsRefreshed(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "onMarketItemsRefreshed");
    
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    __Array *marketItems = dynamic_cast<__Array *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_MARKET_ITEMS));
    
    Ref *object;
    CCARRAY_FOREACH(marketItems, object) {
        CCMarketItem *marketItem = dynamic_cast<CCMarketItem *>(object);
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("Market Item: %s %s",
                                                                marketItem->getProductId()->getCString(),
                                                                marketItem->getMarketPriceAndCurrency()->getCString())->getCString());
    }
}

void StoreEventHandler::onMarketItemsRefreshStarted(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "MarketItemsRefreshStarted");
}

void StoreEventHandler::onMarketItemsRefreshFailed(EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)(event->getUserData());
    __String *errorMessage = dynamic_cast<__String *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_ERROR_MESSAGE));
    CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("MarketItemsRefreshFailed %s", errorMessage->getCString())->getCString());
}

void StoreEventHandler::onMarketRefund(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "MarketRefund");
}

void StoreEventHandler::onIabServiceStarted(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "IabServiceStarted");
}

void StoreEventHandler::onIabServiceStopped(EventCustom *event) {
    CCSoomlaUtils::logDebug(TAG, "IabServiceStopped");
}
