//
//  TinyFlareAssets.h
//  TinyFlare
//
//  Created by wang haibo on 15/5/19.
//
//

#ifndef __TinyFlare__TinyFlareAssets__
#define __TinyFlare__TinyFlareAssets__

#include "CCStoreAssets.h"

#define STARDUST_ITEM_ID "stardust_currency"
#define THOUSAND_STARDUST_ITEM_ID "thousand_stardust_currency"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#define THOUSAND_STARDUST_PACK_PRODUCT_ID "com.wanax.geometrywars.stardustpack"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#define THOUSAND_STARDUST_PACK_PRODUCT_ID "com.wanax.geometrywars.stardust"
#endif

#define NO_ADS_ITEM_ID "no_ads"
#define NO_ADS_PRODUCT_ID "com.wanax.geometrywars.removeads"

class TinyFlareAssets: public soomla::CCStoreAssets {

    TinyFlareAssets();
    bool init();
public:
    virtual ~TinyFlareAssets();
    
    static TinyFlareAssets *create();
    
    virtual int getVersion();
    
    virtual cocos2d::__Array *getCurrencies();
    
    virtual cocos2d::__Array *getGoods();
    
    virtual cocos2d::__Array *getCurrencyPacks();
    
    virtual cocos2d::__Array *getCategories();
private:
    cocos2d::__Array*   m_pCurrencies;
    cocos2d::__Array*   m_pGoods;
    cocos2d::__Array*   m_pCurrencyPacks;
    cocos2d::__Array*   m_pCategories;
};

#endif /* defined(__TinyFlare__TinyFlareAssets__) */
