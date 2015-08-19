//
//  StoreListener.h
//  MazeJump
//
//  Created by wang haibo on 15/8/19.
//
//

#ifndef __MazeJump__StoreListener__
#define __MazeJump__StoreListener__

#include "cocos2d.h"
#include "PluginIAP/PluginIAP.h"
class StoreListener : public cocos2d::Ref, public sdkbox::IAPListener
{
    StoreListener();
    ~StoreListener();
public:
    static StoreListener* getInstance();
    void registerStoreListener();
    
    void purchase(const std::string& productName);
    void restore();
    std::vector<sdkbox::Product> getProducts() const;
    
    virtual void onSuccess(const sdkbox::Product& p) override;
    
    virtual void onFailure(const sdkbox::Product& p, const std::string& msg) override;

    virtual void onCanceled(const sdkbox::Product& p) override;
    
    virtual void onRestored(const sdkbox::Product& p) override;
    
    virtual void onProductRequestSuccess(const std::vector<sdkbox::Product>& products) override;
    
    virtual void onProductRequestFailure(const std::string& msg) override;
    
private:
    std::vector<sdkbox::Product> _products;
};

#endif /* defined(__MazeJump__StoreListener__) */
