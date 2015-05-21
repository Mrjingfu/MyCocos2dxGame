
var PrevSoomla = Soomla;
Soomla = new function () {

  var Soomla = _.extend(PrevSoomla, {Models: {}}); // merge with binding instance

  Soomla.DEBUG = false;

  var declareClass = Soomla.declareClass = function (ClassName, fields, parentClass) {
    var Clazz = function () {
      return _.extend(parentClass ? parentClass() : {}, fields ? fields : {}, {
        className: ClassName
      });
    };
    Clazz.create = function (values) {
      return _.defaults(values ? _.omit(values, "className") : {}, Clazz());
    };

    return Clazz;
  };

  /**
   * VirtualItem
   */
  var VirtualItem = Soomla.Models.VirtualItem = declareClass("VirtualItem", {
    name: "",
    description: "",
    itemId: null
  });

  /**
   * VirtualCategory
   */
  var VirtualCategory = Soomla.Models.VirtualCategory = declareClass("VirtualCategory", {
    name: "",
    goods_itemIds: null
  });

  /**
   * MarketItem
   */
  var MarketItem = Soomla.Models.MarketItem = declareClass("MarketItem", {
    productId: null,
    consumable: null,
    price: null,
    marketPrice: null,
    marketTitle: null,
    marketDescription: null
  });
  MarketItem.Consumable = {
    NONCONSUMABLE: 0,
    CONSUMABLE: 1,
    SUBSCRIPTION: 2
  };

  var PURCHASE_TYPE = {
    MARKET: "market",
    VI: "virtualItem"
  };

  /**
   * PurchasableVirtualItem
   */
  var PurchasableVirtualItem = Soomla.Models.PurchasableVirtualItem = declareClass("PurchasableVirtualItem", {
    purchasableItem: null
  }, VirtualItem);

  /**
   * NonConsumableItem
   */
  var NonConsumableItem = Soomla.Models.NonConsumableItem = declareClass("NonConsumableItem", {

  }, PurchasableVirtualItem);

  /**
   * VirtualCurrency
   */
  var VirtualCurrency = Soomla.Models.VirtualCurrency = declareClass("VirtualCurrency", {
  }, VirtualItem);

  /**
   * VirtualCurrencyPack
   */
  var VirtualCurrencyPack = Soomla.Models.VirtualCurrencyPack = declareClass("v", {
    currency_amount: 0,
    currency_itemId: null
  }, PurchasableVirtualItem);

  /**
   * VirtualGood
   */
  var VirtualGood = Soomla.Models.VirtualGood = declareClass("VirtualGood", {
  }, PurchasableVirtualItem);

  /**
   * LifetimeVG
   */
  var LifetimeVG = Soomla.Models.LifetimeVG = declareClass("LifetimeVG", {
  }, VirtualGood);

  /**
   * EquippableVG
   */
  var EquippableVG = Soomla.Models.EquippableVG = declareClass("EquippableVG", {
    equipping: null
  }, LifetimeVG);
  EquippableVG.EquippingModel = {
    LOCAL: "local",
    CATEGORY: "category",
    GLOBAL: "global"
  };

  /**
   * SingleUseVG
   */
  var SingleUseVG = Soomla.Models.SingleUseVG = declareClass("SingleUseVG", {
  }, VirtualGood);

  /**
   * SingleUsePackVG
   */
  var SingleUsePackVG = Soomla.Models.SingleUsePackVG = declareClass("SingleUsePackVG", {
    good_itemId: null,
    good_amount: null
  }, VirtualGood);

  /**
   * UpgradeVG
   */
  var UpgradeVG = Soomla.Models.UpgradeVG = declareClass("UpgradeVG", {
    good_itemId: null,
    prev_itemId: null,
    next_itemId: null
  }, VirtualGood);

  /**
   * PurchaseType
   */
  var PurchaseType = Soomla.Models.PurchaseType = declareClass("PurchaseType", {
    purchaseType: null
  });

  /**
   * PurchaseWithMarket
   */
  var PurchaseWithMarket = Soomla.Models.PurchaseWithMarket = declareClass("PurchaseWithMarket", {
    purchaseType: PURCHASE_TYPE.MARKET,
    marketItem: null
  }, PurchaseType);

  PurchaseWithMarket.createWithMarketItem = function(productId, price) {
    var marketItem = MarketItem.create({
      productId: productId,
      consumable: MarketItem.Consumable.CONSUMABLE,
      price: price
    });
    return PurchaseWithMarket.create({marketItem: marketItem});
  };

  /**
   * PurchaseWithVirtualItem
   */
  var PurchaseWithVirtualItem = Soomla.Models.PurchaseWithVirtualItem = declareClass("PurchaseWithVirtualItem", {
    purchaseType: PURCHASE_TYPE.VI,
    pvi_itemId: null,
    pvi_amount: null
  }, PurchaseType);

  function extractModel(retParams) {
    var retValue = retParams.return;
    var className = retValue.className;
    var item = retValue.item;
    item.className = className;
    return item;
  }

  function extractCollection(retParams) {
    var retArray = retParams.return;

    var result = [];
    for (var i = 0; i < retArray.length; i++) {
      result.push(extractModel({
        return: retArray[i]
      }));
    }
    return result;
  }

  /**
   * StoreInfo
   */
  var StoreInfo = Soomla.StoreInfo = declareClass("StoreInfo", {
    init: function(storeAssets) {
      callNative({
        method: "CCStoreAssets::init",
        version: storeAssets.version,
        storeAssets: storeAssets
      });
      return true;
    },
    getItemByItemId: function(itemId) {
      var retParams = callNative({
        method: "CCStoreInfo::getItemByItemId",
        itemId: itemId
      });
      return extractModel(retParams);
    },
    getPurchasableItemWithProductId: function(productId) {
      var retParams = callNative({
        method: "CCStoreInfo::getPurchasableItemWithProductId",
        productId: productId
      });
      return extractModel(retParams);
    },
    getCategoryForVirtualGood: function(goodItemId) {
      var retParams = callNative({
        method: "CCStoreInfo::getCategoryForVirtualGood",
        goodItemId: goodItemId
      });
      return extractModel(retParams);
    },
    getFirstUpgradeForVirtualGood: function(goodItemId) {
      var retParams = callNative({
        method: "CCStoreInfo::getFirstUpgradeForVirtualGood",
        goodItemId: goodItemId
      });
      return extractModel(retParams);
    },
    getLastUpgradeForVirtualGood: function(goodItemId) {
      var retParams = callNative({
        method: "CCStoreInfo::getLastUpgradeForVirtualGood",
        goodItemId: goodItemId
      });
      return extractModel(retParams);
    },
    getUpgradesForVirtualGood: function(goodItemId) {
      var retParams = callNative({
        method: "CCStoreInfo::getUpgradesForVirtualGood",
        goodItemId: goodItemId
      });

      return extractCollection(retParams);
    },
    getVirtualCurrencies: function() {
      var retParams = callNative({
        method: "CCStoreInfo::getVirtualCurrencies"
      });
      return extractCollection(retParams);
    },
    getVirtualGoods: function() {
      var retParams = callNative({
        method: "CCStoreInfo::getVirtualGoods"
      });
      return extractCollection(retParams);
    },
    getVirtualCurrencyPacks: function() {
      var retParams = callNative({
        method: "CCStoreInfo::getVirtualCurrencyPacks"
      });
      return extractCollection(retParams);
    },
    getNonConsumableItems: function() {
      var retParams = callNative({
        method: "CCStoreInfo::getNonConsumableItems"
      });
      return extractCollection(retParams);
    },
    getVirtualCategories: function() {
      var retParams = callNative({
        method: "CCStoreInfo::getVirtualCategories"
      });
      return extractCollection(retParams);
    }
  });

  StoreInfo.createShared = function(storeAssets) {
    var ret = new StoreInfo();
    if (ret.init(storeAssets)) {
      Soomla.storeInfo = ret;
    } else {
      Soomla.storeInfo = null;
    }
  };

  var IStoreAssets = Soomla.IStoreAssets = declareClass("IStoreAssets", {
    categories: [],
    currencies: [],
    currencyPacks: [],
    goods: {
      singleUse: [],
      lifetime: [],
      equippable: [],
      goodUpgrades: [],
      goodPacks: []
    },
    nonConsumables: [],
    version: 1
  });

  /**
   * EventHandler
   */
  var EventHandler = Soomla.EventHandler = declareClass("EventHandler", {
    onBillingNotSupported: function() {},
    onBillingSupported: function() {},
    onCurrencyBalanceChanged: function(virtualCurrency, balance, amountAdded) {},
    onGoodBalanceChanged: function(virtualGood, balance, amountAdded) {},
    onGoodEquipped: function(equippableVG) {},
    onGoodUnEquipped: function(equippableVG) {},
    onGoodUpgrade: function(virtualGood, upgradeVG) {},
    onItemPurchased: function(purchasableVirtualItem) {},
    onItemPurchaseStarted: function(purchasableVirtualItem) {},
    onMarketPurchaseCancelled: function(purchasableVirtualItem) {},
    onMarketPurchase: function(purchasableVirtualItem, receiptUrl) {},
    onMarketPurchaseStarted: function(purchasableVirtualItem) {},
    onMarketPurchaseVerification: function(purchasableVirtualItem) {},
    onRestoreTransactionsStarted: function() {},
    onRestoreTransactionsFinished: function(success) {},
    onUnexpectedErrorInStore: function() {},
    onStoreControllerInitialized: function() {},
    onMarketItemsRefreshed: function() {},
    // For Android only
    onMarketRefund: function(purchasableVirtualItem) {},
    onIabServiceStarted: function() {},
    onIabServiceStopped: function() {}
  });

  /**
   * Root definitions
   */
  Soomla.eventHandlers = [];
  Soomla.addEventHandler = Soomla.on = function (eventHandler) {
    Soomla.eventHandlers.push(eventHandler);
  };
  Soomla.removeEventHandler = Soomla.off = function (eventHandler) {
    var idx = Soomla.eventHandlers.indexOf(eventHandler);
    Soomla.eventHandlers.splice(idx, 1);
  };
  Soomla.easyNDKCallBack = function (parameters) {
    parameters = JSON.parse(parameters);
    try {
      var methodName = parameters.method || "";
      if (methodName == "CCEventHandler::onBillingNotSupported") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onBillingNotSupported) {
            eventHandler.onBillingNotSupported();
          }
        });
      }
      else if (methodName == "CCEventHandler::onBillingSupported") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onBillingSupported) {
            eventHandler.onBillingSupported();
          }
        });
      }
      else if (methodName == "CCEventHandler::onCurrencyBalanceChanged") {
        var virtualCurrency = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onCurrencyBalanceChanged) {
            eventHandler.onCurrencyBalanceChanged(virtualCurrency, parameters.balance, parameters.amountAdded);
          }
        });
      }
      else if (methodName == "CCEventHandler::onGoodBalanceChanged") {
        var virtualGood = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onGoodBalanceChanged) {
            eventHandler.onGoodBalanceChanged(virtualGood, parameters.balance, parameters.amountAdded);
          }
        });
      }
      else if (methodName == "CCEventHandler::onGoodEquipped") {
        var equippableVG = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onGoodEquipped) {
            eventHandler.onGoodEquipped(equippableVG);
          }
        });
      }
      else if (methodName == "CCEventHandler::onGoodUnEquipped") {
        var equippableVG = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onGoodUnEquipped) {
            eventHandler.onGoodUnEquipped(equippableVG);
          }
        });
      }
      else if (methodName == "CCEventHandler::onGoodUpgrade") {
        var virtualGood = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        var upgradeVG = Soomla.storeInfo.getItemByItemId(parameters.vguItemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onGoodUpgrade) {
            eventHandler.onGoodUpgrade(virtualGood, upgradeVG);
          }
        });
      }
      else if (methodName == "CCEventHandler::onItemPurchased") {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onItemPurchased) {
            eventHandler.onItemPurchased(purchasableVirtualItem);
          }
        });
      }
      else if (methodName == "CCEventHandler::onItemPurchaseStarted") {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onItemPurchaseStarted) {
            eventHandler.onItemPurchaseStarted(purchasableVirtualItem);
          }
        });
      }
      else if (methodName == "CCEventHandler::onMarketPurchaseCancelled") {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onMarketPurchaseCancelled) {
            eventHandler.onMarketPurchaseCancelled(purchasableVirtualItem);
          }
        });
      }
      else if (methodName == "CCEventHandler::onMarketPurchase") {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        var token = parameters.token;
        var payload = parameters.payload;
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onMarketPurchase) {
            eventHandler.onMarketPurchase(purchasableVirtualItem, token, payload);
          }
        });
      }
      else if (methodName == "CCEventHandler::onMarketPurchaseStarted") {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onMarketPurchaseCancelled) {
            eventHandler.onMarketPurchaseCancelled(purchasableVirtualItem);
          }
        });
      }
      else if (methodName == "CCEventHandler::onMarketItemsRefreshed") {
        var marketItems = parameters.marketItems;
        _.forEach(marketItems, function(marketItem) {
          var productId = marketItem.productId;
          var marketPrice = marketItem.market_price;
          var marketTitle = marketItem.market_title;
          var marketDescription = marketItem.market_desc;

          var pvi = Soomla.storeInfo.getPurchasableItemWithProductId(productId);

          var purchaseWithMarket = pvi.purchaseType;
          var mi = purchaseWithMarket.marketItem;

          mi.marketPrice        = marketPrice;
          mi.marketTitle        = marketTitle;
          mi.marketDescription  = marketDescription;
        });

        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onMarketPurchaseCancelled) {
            eventHandler.onMarketItemsRefreshed();
          }
        });
      }
      else if (methodName == "CCEventHandler::onMarketPurchaseVerification") {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onMarketPurchaseVerification) {
            eventHandler.onMarketPurchaseVerification(purchasableVirtualItem);
          }
        });
      }
      else if (methodName == "CCEventHandler::onRestoreTransactionsFinished") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onRestoreTransactionsFinished) {
            eventHandler.onRestoreTransactionsFinished(parameters.success);
          }
        });
      }
      else if (methodName == "CCEventHandler::onRestoreTransactions") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onRestoreTransactionsStarted) {
            eventHandler.onRestoreTransactionsStarted();
          }
        });
      }
      else if (methodName == "CCEventHandler::onUnexpectedErrorInStore") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onUnexpectedErrorInStore) {
            eventHandler.onUnexpectedErrorInStore();
          }
        });
      }
      else if (methodName == "CCEventHandler::onStoreControllerInitialized") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onStoreControllerInitialized) {
            eventHandler.onStoreControllerInitialized();
          }
        });
      }
      //  Android specific
      else if (methodName == "CCEventHandler::onMarketRefund") {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onMarketRefund) {
            eventHandler.onMarketRefund(purchasableVirtualItem);
          }
        });
      }
      else if (methodName == "CCEventHandler::onIabServiceStarted") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onIabServiceStarted) {
            eventHandler.onIabServiceStarted();
          }
        });
      }
      else if (methodName == "CCEventHandler::onIabServiceStopped") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onIabServiceStopped) {
            eventHandler.onIabServiceStopped();
          }
        });
      }
    } catch (e) {
      logError("easyNDKCallBack: " + e.message);
    }
  };
  // put it into global context
  easyNDKCallBack = function(params) {
    Soomla.easyNDKCallBack.call(Soomla, params);
  };

  /**
   * StoreController
   */
  var StoreController = Soomla.StoreController = declareClass("StoreController", {
    SOOMLA_AND_PUB_KEY_DEFAULT: "YOUR GOOGLE PLAY PUBLIC KEY",
    SOOMLA_ONLY_ONCE_DEFAULT: "SET ONLY ONCE",
    init: function(storeAssets, storeParams) {

      // Redundancy checking. Most JS libraries don't do this. I hate it when they don't do this. Do this.
      var fields = ["customSecret", "soomSec", "androidPublicKey", "SSV"];
      var wrongParams = _.omit(storeParams, fields);
      if (wrongParams.length > 0) {
        logDebug("WARNING!! Possible typo in member of storeParams: " + wrongParams);
      }

      storeParams = _.pick(storeParams, fields);
      storeParams.customSecret      = storeParams.customSecret || "";
      storeParams.soomSec           = storeParams.soomSec || "";
      storeParams.androidPublicKey  = storeParams.androidPublicKey || "";

      if (storeParams.customSecret.length == 0 || storeParams.soomSec.length == 0) {
        logError("SOOMLA/COCOS2DX MISSING customSecret or soomSec !!! Stopping here !!");
        return false;
      }

      if (storeParams.customSecret == this.SOOMLA_ONLY_ONCE_DEFAULT || storeParams.soomSec == this.SOOMLA_ONLY_ONCE_DEFAULT) {
        logError("SOOMLA/COCOS2DX You have to change customSecret and soomSec !!! Stopping here !!");
        return false;
      }

      if (storeParams.androidPublicKey.length == 0) {
        logError("SOOMLA/COCOS2DX MISSING publickKey !!! Stopping here !!");
        return false;
      }

      if (storeParams.androidPublicKey == this.SOOMLA_AND_PUB_KEY_DEFAULT) {
        logError("SOOMLA/COCOS2DX You have to change android publicKey !!! Stopping here !!");
        return false;
      }

      callNative({
        method: "CCStoreController::setAndroidPublicKey",
        androidPublicKey: storeParams.androidPublicKey
      });
      callNative({
        method: "CCStoreController::setSoomSec",
        soomSec: storeParams.soomSec
      });
      callNative({
        method: "CCStoreController::setSSV",
        ssv: storeParams.SSV
      });

      StoreInfo.createShared(storeAssets);

      callNative({
        method: "CCStoreController::init",
        customSecret: storeParams.customSecret,
        androidPublicKey: storeParams.androidPublicKey
      });

      return true;
    },
    buyMarketItem: function(productId, payload) {
      callNative({
        method: "CCStoreController::buyMarketItem",
        productId: productId,
        payload: payload
      });
    },
    restoreTransactions: function() {
      callNative({
        method: "CCStoreController::restoreTransactions"
      });
    },
    refreshInventory: function() {
      callNative({
        method: "CCStoreController::refreshInventory"
      });
    },
    // TODO: For iOS only
    transactionsAlreadyRestored: function() {
      var retParams = callNative({
        method: "CCStoreController::transactionsAlreadyRestored"
      });
      return retParams.return;
    },
    refreshMarketItemsDetails: function() {
      callNative({
        method: "CCStoreController::refreshMarketItemsDetails"
      });
    },
    // TODO: For Android only
    startIabServiceInBg: function() {
      callNative({
        method: "CCStoreController::startIabServiceInBg"
      });
    },
    // TODO: For Android only
    stopIabServiceInBg: function() {
      callNative({
        method: "CCStoreController::stopIabServiceInBg"
      });
    }
  });

  StoreController.createShared = function(storeAssets, storeParams) {
    var ret = new StoreController();
    if (ret.init(storeAssets, storeParams)) {
      Soomla.storeController = ret;
    } else {
      Soomla.storeController = null;
    }
  };

  var StoreInventory = Soomla.StoreInventory = declareClass("StoreInventory", {
    buyItem: function(itemId) {
      callNative({
        method: "CCStoreInventory::buyItem",
        itemId: itemId
      });
    },
    getItemBalance: function(itemId) {
      var retParams = callNative({
        method: "CCStoreInventory::getItemBalance",
        itemId: itemId
      });
      return retParams.return;
    },
    giveItem: function(itemId, amount) {
      callNative({
        method: "CCStoreInventory::giveItem",
        itemId: itemId,
        amount: amount
      });
    },
    takeItem: function(itemId, amount) {
      callNative({
        method: "CCStoreInventory::takeItem",
        itemId: itemId,
        amount: amount
      });
    },
    equipVirtualGood: function(itemId) {
      callNative({
        method: "CCStoreInventory::equipVirtualGood",
        itemId: itemId
      });
    },
    unEquipVirtualGood: function(itemId) {
      callNative({
        method: "CCStoreInventory::unEquipVirtualGood",
        itemId: itemId
      });
    },
    isVirtualGoodEquipped: function(itemId) {
      var retParams = callNative({
        method: "CCStoreInventory::isVirtualGoodEquipped",
        itemId: itemId
      });
      return retParams.return;
    },
    getGoodUpgradeLevel: function(goodItemId) {
      var retParams = callNative({
        method: "CCStoreInventory::getGoodUpgradeLevel",
        goodItemId: goodItemId
      });
      return retParams.return;
    },
    getGoodCurrentUpgrade: function(goodItemId) {
      var retParams = callNative({
        method: "CCStoreInventory::getGoodCurrentUpgrade",
        goodItemId: goodItemId
      });
      return retParams.return;
    },
    upgradeGood: function(goodItemId) {
      callNative({
        method: "CCStoreInventory::upgradeGood",
        goodItemId: goodItemId
      });
    },
    removeGoodUpgrades: function(goodItemId) {
      callNative({
        method: "CCStoreInventory::removeGoodUpgrades",
        goodItemId: goodItemId
      });
    },
    nonConsumableItemExists: function(nonConsItemId) {
      var retParams = callNative({
        method: "CCStoreInventory::nonConsumableItemExists",
        nonConsItemId: nonConsItemId
      });
      return retParams.return;
    },
    addNonConsumableItem: function(nonConsItemId) {
      callNative({
        method: "CCStoreInventory::addNonConsumableItem",
        nonConsItemId: nonConsItemId
      });
    },
    removeNonConsumableItem: function(nonConsItemId) {
      callNative({
        method: "CCStoreInventory::removeNonConsumableItem",
        nonConsItemId: nonConsItemId
      });
    }
  });

  Soomla.storeInventory = StoreInventory.create();

  function SoomlaException(code, message) {
    this.name = "SoomlaException";
    this.code = code || 0;
    this.message = (message || "");
  }
  SoomlaException.prototype = Error.prototype;
  SoomlaException.CODE = {
    ITEM_NOT_FOUND: -1,
    INSUFFICIENT_FUNDS: -2,
    NOT_ENOUGH_GOODS: -3,
    OTHER: -4
  };

  var callNative = function (params) {
    var jsonString = Soomla.CCSoomlaNdkBridge.callNative(JSON.stringify(params));
    var result = JSON.parse(jsonString);

    if (!result.success) {
      throw new SoomlaException(result.code, result.info);
    }
    return result.result;
  };

  var logDebug = Soomla.logDebug = function (output) {
    if (Soomla.DEBUG) {
      cc.log("DEBUG: " + output);
    }
  };

  var logError = Soomla.logError = function (output) {
    cc.log("ERROR: " + output);
  };

  var dumpError = Soomla.dumpError = function (e) {
    return e + " : " + JSON.stringify(e);
  };

  return Soomla
};
