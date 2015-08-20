//
//  SdkBoxManager.h
//  MazeJump
//
//  Created by wang haibo on 15/8/20.
//
//

#ifndef __MazeJump__SdkBoxManager__
#define __MazeJump__SdkBoxManager__

#include "cocos2d.h"
#include "PluginIAP/PluginIAP.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
class SdkBoxManager : public cocos2d::Ref, public sdkbox::IAPListener
{
    SdkBoxManager();
    ~SdkBoxManager();
public:
    static SdkBoxManager* getInstance();
    
#pragma mark IAP
    void registerIAPListener();
    void purchase(const std::string& productName);
    void restore();
    std::vector<sdkbox::Product> getProducts() const;
    
    virtual void onSuccess(const sdkbox::Product& p) override;
    virtual void onFailure(const sdkbox::Product& p, const std::string& msg) override;
    virtual void onCanceled(const sdkbox::Product& p) override;
    virtual void onRestored(const sdkbox::Product& p) override;
    virtual void onProductRequestSuccess(const std::vector<sdkbox::Product>& products) override;
    virtual void onProductRequestFailure(const std::string& msg) override;
    
#pragma mark GoogleAnalytics
    void registerGoogleAnalytics();
    void logScreen(std::string title);
    ///example : logEvent("Achievement", "Unlocked", "Slay 10 dragons", 5);
    void logEvent(std::string eventCategory, std::string eventAction, std::string eventLabel, int value);
    void logException(std::string exceptionDescription, bool isFatal);
    void logTiming(std::string timingCategory, int timingInterval, std::string timingName, std::string timingLabel);
    void logSocial(std::string socialNetwork, std::string socialAction, std::string socialTarget);
private:
    std::vector<sdkbox::Product> _products;
};

#endif /* defined(__MazeJump__SdkBoxManager__) */
