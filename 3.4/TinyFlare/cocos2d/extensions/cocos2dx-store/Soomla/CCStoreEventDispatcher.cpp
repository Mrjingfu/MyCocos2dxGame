

#include "CCStoreEventDispatcher.h"
#include "CCSoomlaEventDispatcher.h"
#include "CCError.h"
#include "CCStoreInfo.h"
#include "CCSoomlaUtils.h"
#include "CCPurchaseWithMarket.h"
#include "CCNdkBridge.h"
#include "CCStoreInventory.h"

namespace soomla {

    USING_NS_CC;

    static CCStoreEventDispatcher *s_SharedInstance = NULL;

    CCStoreEventDispatcher *CCStoreEventDispatcher::getInstance() {
        if (!s_SharedInstance) {
            s_SharedInstance = new CCStoreEventDispatcher();
            s_SharedInstance->init();
        }

        return s_SharedInstance;
    }

    bool CCStoreEventDispatcher::init() {

        CCSoomlaEventDispatcher *eventDispatcher = CCSoomlaEventDispatcher::getInstance();

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_BILLING_NOT_SUPPORTED,
                [this](__Dictionary *parameters) {
                    this->onBillingNotSupported();
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_BILLING_SUPPORTED,
                [this](__Dictionary *parameters) {
                    this->onBillingSupported();
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_CURRENCY_BALANCE_CHANGED,
                [this](__Dictionary *parameters) {
                    __String *itemId = (__String *)(parameters->objectForKey("itemId"));
                    __Integer *balance = (__Integer *)(parameters->objectForKey("balance"));
                    __Integer *amountAdded = (__Integer *)(parameters->objectForKey("amountAdded"));
                    CCError *error = NULL;
                    CCVirtualCurrency *virtualCurrency =
                            dynamic_cast<CCVirtualCurrency *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_CURRENCY_BALANCE_CHANGED, error);
                        return;
                    }
                    CC_ASSERT(virtualCurrency);
                    this->onCurrencyBalanceChanged(virtualCurrency, balance->getValue(), amountAdded->getValue());
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED,
                [this](__Dictionary *parameters) {
                    __String *itemId = (__String *)(parameters->objectForKey("itemId"));
                    __Integer *balance = (__Integer *)(parameters->objectForKey("balance"));
                    __Integer *amountAdded = (__Integer *)(parameters->objectForKey("amountAdded"));
                    CCError *error = NULL;
                    CCVirtualGood *virtualGood =
                            dynamic_cast<CCVirtualGood *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED, error);
                        return;
                    }
                    CC_ASSERT(virtualGood);
                    this->onGoodBalanceChanged(virtualGood, balance->getValue(), amountAdded->getValue());
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_GOOD_EQUIPPED,
                [this](__Dictionary *parameters) {
                    __String *itemId = (__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCEquippableVG *equippableVG =
                            dynamic_cast<CCEquippableVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_GOOD_EQUIPPED, error);
                        return;
                    }
                    CC_ASSERT(equippableVG);
                    this->onGoodEquipped(equippableVG);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_GOOD_UNEQUIPPED,
                [this](__Dictionary *parameters) {
                    __String *itemId = (__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCEquippableVG *equippableVG =
                            dynamic_cast<CCEquippableVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_GOOD_UNEQUIPPED, error);
                        return;
                    }
                    CC_ASSERT(equippableVG);
                    this->onGoodUnEquipped(equippableVG);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_GOOD_UPGRADE,
                [this](__Dictionary *parameters) {
                    __String *itemId = (__String *)(parameters->objectForKey("itemId"));
                    __String *vguItemId = (__String *)(parameters->objectForKey("vguItemId"));

                    CCError *error;

                    error = NULL;
                    CCVirtualGood *virtualGood =
                            dynamic_cast<CCVirtualGood *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_GOOD_UPGRADE, error);
                        return;
                    }
                    CC_ASSERT(virtualGood);

                    error = NULL;
                    CCUpgradeVG *upgradeVG =
                            dynamic_cast<CCUpgradeVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(vguItemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_GOOD_UPGRADE, error);
                        return;
                    }
                    CC_ASSERT(upgradeVG);
                    this->onGoodUpgrade(virtualGood, upgradeVG);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_ITEM_PURCHASED,
                [this](__Dictionary *parameters) {
                    __String *itemId = (__String *)(parameters->objectForKey("itemId"));
                    __String *payload = (__String *)(parameters->objectForKey("payload"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem =
                            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_ITEM_PURCHASED, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onItemPurchased(purchasableVirtualItem, payload);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_ITEM_PURCHASE_STARTED,
                [this](__Dictionary *parameters) {
                    __String *itemId = (__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(
                            CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_ITEM_PURCHASE_STARTED, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onItemPurchaseStarted(purchasableVirtualItem);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_PURCHASE_CANCELED,
                [this](__Dictionary *parameters) {
                    __String *itemId = (__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem =
                            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_PURCHASE_CANCELED, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onMarketPurchaseCancelled(purchasableVirtualItem);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_PURCHASE,
                [this](__Dictionary *parameters) {
                    __String *itemId = (__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem =
                            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_PURCHASE, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    __String *token = (__String *)(parameters->objectForKey("token"));
                    __String *payload = (__String *)(parameters->objectForKey("payload"));
                    __String *originalJson = (__String *)(parameters->objectForKey("originalJson"));
                    __String *signature = (__String *)(parameters->objectForKey("signature"));
                    __String *userId = (__String *)(parameters->objectForKey("userId"));
                    this->onMarketPurchase(purchasableVirtualItem, token, payload, originalJson, signature, userId);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_PURCHASE_STARTED,
                [this](__Dictionary *parameters) {
                    __String *itemId = (__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(
                            CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_PURCHASE_STARTED, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onMarketPurchaseStarted(purchasableVirtualItem);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_PURCHASE_STARTED,
                [this](__Dictionary *parameters) {
                    __String *itemId = (__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem =
                            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_PURCHASE_STARTED, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onMarketPurchaseStarted(purchasableVirtualItem);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESHED,
                [this](__Dictionary *parameters) {
                    __Array *marketItemDicts = (__Array *)(parameters->objectForKey("marketItems"));
                    __Array *marketItems = __Array::create();
                    __Array *virtualItems = __Array::create();

                    CCError *error = NULL;
                    __Dictionary *marketItem = NULL;
                    for (unsigned int i = 0; i < marketItemDicts->count(); i++) {
                        marketItem = dynamic_cast<__Dictionary *>(marketItemDicts->getObjectAtIndex(i));
                        CC_ASSERT(marketItem);
                        __String *productId = dynamic_cast<__String *>(marketItem->objectForKey("productId"));
                        __String *marketPrice = dynamic_cast<__String *>(marketItem->objectForKey("marketPrice"));
                        __String *marketTitle = dynamic_cast<__String *>(marketItem->objectForKey("marketTitle"));
                        __String *marketDescription = dynamic_cast<__String *>(marketItem->objectForKey("marketDesc"));
                        __String *marketCurrencyCode = dynamic_cast<__String *>(marketItem->objectForKey("marketCurrencyCode"));
                        __Integer *marketPriceMicros = dynamic_cast<__Integer *>(marketItem->objectForKey("marketPriceMicros"));

                        CCPurchasableVirtualItem *pvi = CCStoreInfo::sharedStoreInfo()->getPurchasableItemWithProductId(
                                productId->getCString(), &error);
                        if (error) {
                            CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESHED, error);
                            return;
                        }
                        CC_ASSERT(pvi);

                        CCPurchaseWithMarket *purchaseWithMarket = dynamic_cast<CCPurchaseWithMarket *>(pvi->getPurchaseType());
                        CC_ASSERT(purchaseWithMarket);
                        CCMarketItem *mi = purchaseWithMarket->getMarketItem();
                        mi->setMarketPriceAndCurrency(marketPrice);
                        mi->setMarketTitle(marketTitle);
                        mi->setMarketDescription(marketDescription);
                        mi->setMarketCurrencyCode(marketCurrencyCode);
                        mi->setMarketPriceMicros(marketPriceMicros);

                        marketItems->addObject(mi);
                        virtualItems->addObject(pvi);
                    }
                    
                    if (virtualItems->count() > 0) {
                        // no need to save to DB since it's already saved in native
                        // before this event is received
                        CCStoreInfo::sharedStoreInfo()->saveItems(virtualItems, false);
                    }

                    this->onMarketItemsRefreshed(marketItems);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_STARTED,
                [this](__Dictionary *parameters) {
                    this->onMarketItemsRefreshStarted();
                });
        
        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_FAILED,
                [this](__Dictionary *parameters) {
                    __String *errorMessage = (__String *)(parameters->objectForKey("errorMessage"));
                    this->onMarketItemsRefreshFailed(errorMessage);
                });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_PURCHASE_VERIFICATION,
                [this](__Dictionary *parameters) {
                    __String *itemId = (__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem =
                            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_PURCHASE_VERIFICATION, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onMarketPurchaseVerification(purchasableVirtualItem);
               });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_RESTORE_TRANSACTION_FINISHED,
                [this](__Dictionary *parameters) {
                    __Bool *success = (__Bool *)(parameters->objectForKey("success"));
                    this->onRestoreTransactionsFinished(success->getValue());
               });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_RESTORE_TRANSACTION_STARTED,
                [this](__Dictionary *parameters) {
                    this->onRestoreTransactionsStarted();
               });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_UNEXPECTED_ERROR_IN_STORE,
                [this](__Dictionary *parameters) {
                    __String *errorMessage = (__String *)(parameters->objectForKey("errorMessage"));
                    this->onUnexpectedErrorInStore(errorMessage);
               });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_SOOMLA_STORE_INITIALIZED,
                [this](__Dictionary *parameters) {
                    this->onSoomlaStoreInitialized();
               });

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_MARKET_REFUND,
                [this](__Dictionary *parameters) {
                    __String *itemId = (__String *)(parameters->objectForKey("itemId"));
                    CCError *error = NULL;
                    CCPurchasableVirtualItem *purchasableVirtualItem =
                            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &error));
                    if (error) {
                        CCSoomlaUtils::logException(CCStoreConsts::EVENT_MARKET_REFUND, error);
                        return;
                    }
                    CC_ASSERT(purchasableVirtualItem);
                    this->onMarketRefund(purchasableVirtualItem);
               });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_IAB_SERVICE_STARTED,
                [this](__Dictionary *parameters) {
                    this->onIabServiceStarted();
               });

        eventDispatcher->registerEventHandler(CCStoreConsts::EVENT_IAB_SERVICE_STOPPED,
                [this](__Dictionary *parameters) {
                    this->onIabServiceStopped();
               });
#endif
        return true;
    }

    void CCStoreEventDispatcher::onBillingNotSupported() {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_BILLING_NOT_SUPPORTED);
    }

    void CCStoreEventDispatcher::onBillingSupported() {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_BILLING_SUPPORTED);
    }

    void CCStoreEventDispatcher::onCurrencyBalanceChanged(CCVirtualCurrency *virtualCurrency, int balance, int amountAdded) {
        CCStoreInventory::sharedStoreInventory()->refreshOnCurrencyBalanceChanged(virtualCurrency, balance, amountAdded);
        
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(virtualCurrency, CCStoreConsts::DICT_ELEMENT_CURRENCY);
        eventDict->setObject(__Integer::create(balance), CCStoreConsts::DICT_ELEMENT_BALANCE);
        eventDict->setObject(__Integer::create(amountAdded), CCStoreConsts::DICT_ELEMENT_AMOUNT_ADDED);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_CURRENCY_BALANCE_CHANGED, eventDict);
    }

    void CCStoreEventDispatcher::onGoodBalanceChanged(CCVirtualGood *virtualGood, int balance, int amountAdded) {
        CCStoreInventory::sharedStoreInventory()->refreshOnGoodBalanceChanged(virtualGood, balance, amountAdded);
        
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(virtualGood, CCStoreConsts::DICT_ELEMENT_GOOD);
        eventDict->setObject(__Integer::create(balance), CCStoreConsts::DICT_ELEMENT_BALANCE);
        eventDict->setObject(__Integer::create(amountAdded), CCStoreConsts::DICT_ELEMENT_AMOUNT_ADDED);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED, eventDict);
    }

    void CCStoreEventDispatcher::onGoodEquipped(CCEquippableVG *equippableVG) {
        CCStoreInventory::sharedStoreInventory()->refreshOnGoodEquipped(equippableVG);
        
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(equippableVG, CCStoreConsts::DICT_ELEMENT_EQUIPPABLEVG);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_GOOD_EQUIPPED, eventDict);
    }

    void CCStoreEventDispatcher::onGoodUnEquipped(CCEquippableVG *equippableVG) {
        CCStoreInventory::sharedStoreInventory()->refreshOnGoodUnEquipped(equippableVG);
        
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(equippableVG, CCStoreConsts::DICT_ELEMENT_EQUIPPABLEVG);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_GOOD_UNEQUIPPED, eventDict);
    }

    void CCStoreEventDispatcher::onGoodUpgrade(CCVirtualGood *virtualGood, CCUpgradeVG *upgradeVG) {
        CCStoreInventory::sharedStoreInventory()->refreshOnGoodUpgrade(virtualGood, upgradeVG);
        
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(virtualGood, CCStoreConsts::DICT_ELEMENT_GOOD);
        eventDict->setObject(upgradeVG, CCStoreConsts::DICT_ELEMENT_UPGRADEVG);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_GOOD_UPGRADE, eventDict);
    }

    void CCStoreEventDispatcher::onItemPurchased(CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::__String *payload) {
        onItemPurchased(purchasableVirtualItem, payload, false);
    }

    void CCStoreEventDispatcher::onItemPurchased(CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::__String *payload, bool alsoPush) {
        if (payload == NULL) {
            payload = __String::create("");
        }
        
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        eventDict->setObject(payload, CCStoreConsts::DICT_ELEMENT_DEVELOPERPAYLOAD);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_ITEM_PURCHASED, eventDict);

        if (alsoPush) {
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            
            __Dictionary *params = __Dictionary::create();
            params->setObject(__String::create("CCStoreEventDispatcher::pushOnItemPurchased"), "method");
            params->setObject(purchasableVirtualItem->getItemId(), "itemId");
            params->setObject(payload, "payload");
            CCNdkBridge::callNative (params, NULL);
            
            #endif
        }
    }

    void CCStoreEventDispatcher::onItemPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem) {
        onItemPurchaseStarted(purchasableVirtualItem, false);
    }

    void CCStoreEventDispatcher::onItemPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem, bool alsoPush) {
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_ITEM_PURCHASE_STARTED, eventDict);

        if (alsoPush) {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            
            __Dictionary *params = __Dictionary::create();
            params->setObject(__String::create("CCStoreEventDispatcher::pushOnItemPurchaseStarted"), "method");
            params->setObject(purchasableVirtualItem->getItemId(), "itemId");
            CCNdkBridge::callNative (params, NULL);
            
        #endif
        }
    }

    void CCStoreEventDispatcher::onMarketPurchaseCancelled(CCPurchasableVirtualItem *purchasableVirtualItem) {
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_PURCHASE_CANCELED, eventDict);
    }

    void CCStoreEventDispatcher::onMarketPurchase(CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::__String *token, cocos2d::__String *payload, cocos2d::__String *originalJson,
                                                  cocos2d::__String *signature, cocos2d::__String *userId) {
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        eventDict->setObject(token, CCStoreConsts::DICT_ELEMENT_TOKEN);
        eventDict->setObject(payload, CCStoreConsts::DICT_ELEMENT_DEVELOPERPAYLOAD);
        if (originalJson != NULL) {
            eventDict->setObject(originalJson, CCStoreConsts::DICT_ELEMENT_ORIGINAL_JSON);
        }
        
        if (signature != NULL) {
            eventDict->setObject(signature, CCStoreConsts::DICT_ELEMENT_SIGNATURE);
        }
        
        if (userId != NULL) {
            eventDict->setObject(userId, CCStoreConsts::DICT_ELEMENT_USER_ID);
        }
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_PURCHASE, eventDict);
    }

    void CCStoreEventDispatcher::onMarketPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem) {
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_PURCHASE_STARTED, eventDict);
    }

    void CCStoreEventDispatcher::onMarketPurchaseVerification(CCPurchasableVirtualItem *purchasableVirtualItem) {
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_PURCHASE_VERIFICATION, eventDict);
    }

    void CCStoreEventDispatcher::onRestoreTransactionsFinished(bool success) {
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(__Bool::create(success), CCStoreConsts::DICT_ELEMENT_SUCCESS);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_RESTORE_TRANSACTION_FINISHED, eventDict);
    }

    void CCStoreEventDispatcher::onRestoreTransactionsStarted() {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_RESTORE_TRANSACTION_STARTED);
    }

    void CCStoreEventDispatcher::onUnexpectedErrorInStore(cocos2d::__String *errorMessage) {
        onUnexpectedErrorInStore(errorMessage, false);
    }

    void CCStoreEventDispatcher::onUnexpectedErrorInStore(cocos2d::__String *errorMessage, bool alsoPush) {
        if (errorMessage == NULL) {
            errorMessage = __String::create("");
        }
        
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(errorMessage, CCStoreConsts::DICT_ELEMENT_ERROR_MESSAGE);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_UNEXPECTED_ERROR_IN_STORE, eventDict);

        if (alsoPush) {
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                        
            __Dictionary *params = __Dictionary::create();
            params->setObject(__String::create("CCStoreEventDispatcher::pushOnUnexpectedErrorInStore"), "method");
            params->setObject(errorMessage, "errorMessage");
            CCNdkBridge::callNative (params, NULL);
            
            #endif
        }
    }

    void CCStoreEventDispatcher::onSoomlaStoreInitialized() {
        onSoomlaStoreInitialized(false);
    }

    void CCStoreEventDispatcher::onSoomlaStoreInitialized(bool alsoPush) {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_SOOMLA_STORE_INITIALIZED);

        CCStoreInventory::sharedStoreInventory()->refreshLocalInventory();

        if (alsoPush) {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            
            __Dictionary *params = __Dictionary::create();
            params->setObject(__String::create("CCStoreEventDispatcher::pushOnSoomlaStoreInitialized"), "method");
            CCNdkBridge::callNative (params, NULL);
            
        #endif
        }
    }

    void CCStoreEventDispatcher::onMarketItemsRefreshed(cocos2d::__Array *marketItems) {
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(marketItems, CCStoreConsts::DICT_ELEMENT_MARKET_ITEMS);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESHED, eventDict);
    }

    void CCStoreEventDispatcher::onMarketItemsRefreshStarted() {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_STARTED);
    }

    void CCStoreEventDispatcher::onMarketItemsRefreshFailed(cocos2d::__String *errorMessage) {
        if (errorMessage == NULL) {
            errorMessage = __String::create("");
        }
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(errorMessage, CCStoreConsts::DICT_ELEMENT_ERROR_MESSAGE);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_FAILED, eventDict);
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void CCStoreEventDispatcher::onMarketRefund(CCPurchasableVirtualItem *purchasableVirtualItem) {
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(purchasableVirtualItem, CCStoreConsts::DICT_ELEMENT_PURCHASABLE);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_MARKET_REFUND, eventDict);
    }

    void CCStoreEventDispatcher::onIabServiceStarted() {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_IAB_SERVICE_STARTED);
    }

    void CCStoreEventDispatcher::onIabServiceStopped() {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCStoreConsts::EVENT_IAB_SERVICE_STOPPED);
    }
#endif

}
