#include "AppDelegate.h"
#include "Logo.h"
#include "SimpleAudioEngine.h"
#include "GameController.h"
#include "Cocos2dxStore.h"
#include "GameConst.h"
#include "TinyFlareAssets.h"
#include "EncrytionUtility.h"
USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {
    m_pHandler = nullptr;
}

AppDelegate::~AppDelegate() 
{
    CC_SAFE_DELETE(m_pHandler);
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    m_pHandler = new StoreEventHandler();
    soomla::CCSoomla::initialize(PACKAGE_NAME);
    
    TinyFlareAssets *assets = TinyFlareAssets::create();
    
    __Dictionary *storeParams = __Dictionary::create();
    storeParams->setObject(__String::create(ANDROID_PUBLIC_KEY), "androidPublicKey");
    storeParams->setObject(__Bool::create(true), "testPurchases");
    storeParams->setObject(__Bool::create(false), "SSV");
    
    soomla::CCSoomlaStore::initialize(assets, storeParams);
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    std::vector<std::string> searchPaths;
    searchPaths.push_back("stages");
    searchPaths.push_back("lang");
    searchPaths.push_back("fonts");
    searchPaths.push_back("music");
    searchPaths.push_back("sounds");
    searchPaths.push_back("shaders");
    searchPaths.push_back("particles");
    searchPaths.push_back("textures");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    Director::getInstance()->getTextureCache()->addImage("mask.png");
    Director::getInstance()->getTextureCache()->addImage("mask2.png");
    Director::getInstance()->getTextureCache()->addImage("noise.png");
    Director::getInstance()->getTextureCache()->addImage("noise2.png");
    
    SimpleAudioEngine::getInstance()->preloadEffect("btnclick.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("explodeEffect.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("explodeEffect2.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("Laser_Shot21.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("Laser_Shot23.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("Pickup_GemBells11.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("Pickup_GemBells14.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("Pickup_Speed02.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("Pickup_Speed03.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("LaserRifle_Shot04.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("LaserRifle_Shot06.wav");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Flux1.mp3");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Flux2.mp3");
    
#if COCOS2D_DEBUG
    // turn on display FPS
    director->setDisplayStats(true);
#endif
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = Logo::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeAllEffects();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    
    GameController::getInstance()->pause();
    GameController::getInstance()->setToShowAds();
}
