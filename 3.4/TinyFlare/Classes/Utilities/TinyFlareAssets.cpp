//
//  TinyFlareAssets.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/5/19.
//
//

#include "TinyFlareAssets.h"
#include "CCVirtualCurrency.h"
#include "CCVirtualCurrencyPack.h"
#include "CCPurchaseWithMarket.h"
#include "CCVirtualGood.h"
#include "CCLifetimeVG.h"
#include "UtilityHelper.h"
USING_NS_CC;
using namespace soomla;

TinyFlareAssets* TinyFlareAssets::create()
{
    TinyFlareAssets* assets = new (std::nothrow) TinyFlareAssets();
    if (assets && assets->init())
    {
        assets->autorelease();
        return assets;
    }
    CC_SAFE_DELETE(assets);
    return nullptr;
}

TinyFlareAssets::TinyFlareAssets():
m_pCurrencies(NULL),
m_pGoods(NULL),
m_pCurrencyPacks(NULL),
m_pCategories(NULL)
{}

TinyFlareAssets::~TinyFlareAssets()
{
    CC_SAFE_RELEASE(m_pCurrencies);
    CC_SAFE_RELEASE(m_pGoods);
    CC_SAFE_RELEASE(m_pCurrencyPacks);
    CC_SAFE_RELEASE(m_pCategories);
}


bool TinyFlareAssets::init()
{
    CCVirtualCurrency* stardustCurrency = CCVirtualCurrency::create(
                                                                     String::create(UtilityHelper::getLocalString("STARDUST")),
                                                                 String::create(""),
                                                                 String::create(STARDUST_ITEM_ID)
                                                                 );
    
    CCVirtualCurrencyPack* thousandStardustPack = CCVirtualCurrencyPack::create(
                                                                         String::create(UtilityHelper::getLocalString("THOUSAND_STARDUST")),
                                                                         String::create(UtilityHelper::getLocalString("THOUSAND_STARDUST_DESC")),
                                                                         String::create(THOUSAND_STARDUST_ITEM_ID),
                                                                         Integer::create(1000),
                                                                         String::create(STARDUST_ITEM_ID),
                                                                         CCPurchaseWithMarket::create(String::create(THOUSAND_STARDUST_PACK_PRODUCT_ID), Double::create(0.99))
                                                                         );
    
    CCVirtualGood *noAdsGood = CCLifetimeVG::create(
                                                    __String::create(UtilityHelper::getLocalString("NO_ADS")),
                                                    __String::create(UtilityHelper::getLocalString("NO_ADS_DESC")),
                                                    __String::create(NO_ADS_ITEM_ID),
                                                    CCPurchaseWithMarket::createWithMarketItem(CCMarketItem::create(
                                                                                                                    __String::create(NO_ADS_PRODUCT_ID),
                                                                                                                    __Integer::create(CCMarketItem::NONCONSUMABLE), CCDouble::create(0.99))
                                                                                               )
                                                    );
    
    m_pCurrencies = __Array::create(stardustCurrency, NULL);
    m_pCurrencies->retain();
    
    m_pCurrencyPacks = __Array::create(thousandStardustPack, NULL);
    m_pCurrencyPacks->retain();
    
    m_pGoods = __Array::create(noAdsGood, NULL);
    m_pGoods->retain();
    
    return true;
}

int TinyFlareAssets::getVersion()
{
    return 0;
}

__Array* TinyFlareAssets::getCurrencies()
{
    return m_pCurrencies;
}

__Array* TinyFlareAssets::getGoods()
{
    return m_pGoods;
}

__Array* TinyFlareAssets::getCurrencyPacks()
{
    return m_pCurrencyPacks;
}

__Array* TinyFlareAssets::getCategories()
{
    return m_pCategories;
}