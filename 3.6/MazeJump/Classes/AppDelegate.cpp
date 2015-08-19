#include "AppDelegate.h"
#include "LogoScene.h"
#include "AudioEngine.h"
#include "GameConst.h"
#include "UIManager.h"
#include "storage/local-storage/LocalStorage.h"
#include "GameCenterController.h"
USING_NS_CC;
using namespace experimental;
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
    searchPaths.push_back("Particle3D");
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
    std::string defualutRole = localStorageGetItem(USER_DEFAULT_ROLE_ID);
    if (defualutRole.length()<=0) {
        localStorageSetItem(USER_DEFAULT_ROLE_ID, "role_girl1");
    }
    
#if COCOS2D_DEBUG
    //resetUserDataTable();
    printUserTataTable();
#endif
    //
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    GameCenterController::getInstance()->registerGameCenterController();
#endif
    
    
    //director->setClearColor(Color4F(153.0f/255.0f, 204.0f/255.0f, 1.0f, 1.0f));
    //director->setClearColor(Color4F(0.8f, 0.8f, 0.8f, 1.0f));

#if COCOS2D_DEBUG
    // turn on display FPS
    director->setDisplayStats(true);
#else
    // turn off display FPS
    director->setDisplayStats(true);
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
    if (UIManager::getInstance()->getGameId() == UIManager::UI_GAME) {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GAME_PAUSE);
    }
    
    // if you use SimpleAudioEngine, it must be pause
    AudioEngine::pauseAll();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    AudioEngine::resumeAll();
}
void AppDelegate::resetUserDataTable()
{
    localStorageSetItem(USER_MAX_LEVEL, "0");
    localStorageSetItem(USER_LAST_LEVEL, "0");
    localStorageSetItem(USER_HEART_NUM, "0");
    localStorageSetItem(USER_GOLD_NUM, "0");
}
void AppDelegate::printUserTataTable()
{
    CCLOG("%s : %s", USER_MAX_LEVEL.c_str(),localStorageGetItem(USER_MAX_LEVEL).c_str());
    CCLOG("%s : %s", USER_LAST_LEVEL.c_str(),localStorageGetItem(USER_LAST_LEVEL).c_str());
    CCLOG("%s : %s", USER_HEART_NUM.c_str(),localStorageGetItem(USER_HEART_NUM).c_str());
    CCLOG("%s : %s", USER_GOLD_NUM.c_str(),localStorageGetItem(USER_GOLD_NUM).c_str());
}