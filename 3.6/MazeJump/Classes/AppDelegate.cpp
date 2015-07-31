#include "AppDelegate.h"
#include "LogoScene.h"
#include "SimpleAudioEngine.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;
using namespace CocosDenshion;
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
    localStorageFree();
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
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    std::vector<std::string> searchPaths;
    searchPaths.push_back("maps");
    searchPaths.push_back("lang");
    searchPaths.push_back("fonts");
    searchPaths.push_back("music");
    searchPaths.push_back("sounds");
    searchPaths.push_back("shaders");
    searchPaths.push_back("particles");
    searchPaths.push_back("textures");
    searchPaths.push_back("models");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    //load database
    std::string path = FileUtils::getInstance()->getWritablePath() + "userdata.db";
    CCLOG("path:%s",path.c_str());
    localStorageInit(path);
#if COCOS2D_DEBUG
    //resetUserDataTable();
    printUserTataTable();
#endif
    //
    
    //director->setClearColor(Color4F(153.0f/255.0f, 204.0f/255.0f, 1.0f, 1.0f));
    //director->setClearColor(Color4F(0.8f, 0.8f, 0.8f, 1.0f));

#if COCOS2D_DEBUG
    // turn on display FPS
    director->setDisplayStats(true);
#else
    // turn off display FPS
    director->setDisplayStats(false);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

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

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
void AppDelegate::resetUserDataTable()
{
    localStorageSetItem("MaxReachDifficultLevel", "0");
    localStorageSetItem("LastReachDifficultLevel", "0");
    localStorageSetItem("UserHeartNum", "0");
    localStorageSetItem("UserGoldNum", "0");
}
void AppDelegate::printUserTataTable()
{
    CCLOG("MaxReachDifficultLevel : %s", localStorageGetItem("MaxReachDifficultLevel").c_str());
    CCLOG("LastReachDifficultLevel : %s", localStorageGetItem("LastReachDifficultLevel").c_str());
    CCLOG("UserHeartNum : %s", localStorageGetItem("UserHeartNum").c_str());
    CCLOG("UserGoldNum : %s", localStorageGetItem("UserGoldNum").c_str());
}