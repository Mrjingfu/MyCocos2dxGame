#include "AppDelegate.h"
#include "LogoScene.h"
#include "SimpleAudioEngine.h"
#include "ArchiveManager.h"
#include "SdkBoxManager.hpp"
#include "NativeBridge.h"
#include "EventConst.h"
USING_NS_CC;
using namespace CocosDenshion;

static cocos2d::Size designResolutionSize = cocos2d::Size(320, 480);
static cocos2d::Size smallResolutionSize = cocos2d::Size(640, 960);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(768, 1024);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1536, 2048);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
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

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Voxel_Explorer", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Voxel_Explorer");
#endif
        director->setOpenGLView(glview);
    }
    
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    SdkBoxManager::getInstance()->registerGoogleAnalytics();
    NativeBridge::getInstance()->initAdmob();
#endif

    std::vector<std::string> searchPaths;
    searchPaths.push_back("lang");
    searchPaths.push_back("data");
    searchPaths.push_back("models");
    searchPaths.push_back("textures");
    searchPaths.push_back("shaders");
    searchPaths.push_back("ui");
    searchPaths.push_back("fonts");
    searchPaths.push_back("sounds");
    searchPaths.push_back("musics");
    searchPaths.push_back("particle2d");
    searchPaths.push_back("particle3d/materials");
    searchPaths.push_back("particle3d/scripts");
    searchPaths.push_back("particle3d/textures");
    searchPaths.push_back("sam");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
#if COCOS2D_DEBUG
    // turn on display FPS
    director->setDisplayStats(true);
#else
    // turn off display FPS
    director->setDisplayStats(false);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    
    CCLOG("visible width:%f height:%f",director->getVisibleSize().width,director->getVisibleSize().height);
    CCLOG("Frame width:%f height:%f",glview->getFrameSize().width,glview->getFrameSize().height);
    CCLOG("origin x:%f y:%f",director->getVisibleOrigin().x,director->getVisibleOrigin().y);
    float iScalage = designResolutionSize.width / glview->getFrameSize().width ;
    float ihight = iScalage * glview->getFrameSize().height;
    CCLOG(" [%0.2f][%0.2f]" , iScalage ,ihight);
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, ihight, ResolutionPolicy::SHOW_ALL);
    cocos2d::Size frameSize = glview->getFrameSize();
//    // if the frame's height is larger than the height of medium size.
//    if (frameSize.height > mediumResolutionSize.height)
//    {        
//        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
//    }
//    // if the frame's height is larger than the height of small size.
//    else if (frameSize.height > smallResolutionSize.height)
//    {        
//        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
//    }
//    // if the frame's height is smaller than the height of medium size.
//    else
//    {        
//        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
//    }
//    if (frameSize.height > smallResolutionSize.height)
//    {
//        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
//    }
//    director->setContentScaleFactor(frameSize.width/designResolutionSize.height);

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = LogoScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GAME_PAUSE);
    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseAllEffects();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    
    ArchiveManager::getInstance()->saveGame();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
