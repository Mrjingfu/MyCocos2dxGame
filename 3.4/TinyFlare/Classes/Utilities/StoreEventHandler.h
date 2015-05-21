//
//  StoreEventHandler.h
//  TinyFlare
//
//  Created by wang haibo on 15/5/19.
//
//

#ifndef __TinyFlare__StoreEventHandler__
#define __TinyFlare__StoreEventHandler__

#include "cocos2d.h"
#include "Cocos2dxStore.h"

class StoreEventHandler {
public:
    
    StoreEventHandler();
    
    virtual void onBillingNotSupported(cocos2d::EventCustom *event);
    
    virtual void onBillingSupported(cocos2d::EventCustom *event);
    
    virtual void onCurrencyBalanceChanged(cocos2d::EventCustom *event);
    
    virtual void onGoodBalanceChanged(cocos2d::EventCustom *event);
    
    virtual void onGoodEquipped(cocos2d::EventCustom *event);
    
    virtual void onGoodUnEquipped(cocos2d::EventCustom *event);
    
    virtual void onGoodUpgrade(cocos2d::EventCustom *event);
    
    virtual void onItemPurchased(cocos2d::EventCustom *event);
    
    virtual void onItemPurchaseStarted(cocos2d::EventCustom *event);
    
    virtual void onMarketPurchaseCancelled(cocos2d::EventCustom *event);
    
    virtual void onMarketPurchase(cocos2d::EventCustom *event);
    
    virtual void onMarketPurchaseStarted(cocos2d::EventCustom *event);
    
    virtual void onMarketPurchaseVerification(cocos2d::EventCustom *event);
    
    virtual void onRestoreTransactionsStarted(cocos2d::EventCustom *event);
    
    virtual void onRestoreTransactionsFinished(cocos2d::EventCustom *event);
    
    virtual void onUnexpectedErrorInStore(cocos2d::EventCustom *event);
    
    virtual void onSoomlaStoreInitialized(cocos2d::EventCustom *event);
    
    virtual void onMarketItemsRefreshed(cocos2d::EventCustom *event);
    
    virtual void onMarketItemsRefreshStarted(cocos2d::EventCustom *event);
    
    virtual void onMarketItemsRefreshFailed(cocos2d::EventCustom *event);
    
    // Android Only
    virtual void onMarketRefund(cocos2d::EventCustom *event);
    virtual void onIabServiceStarted(cocos2d::EventCustom *event);
    virtual void onIabServiceStopped(cocos2d::EventCustom *event);
};

#endif /* defined(__TinyFlare__StoreEventHandler__) */
