#include "AppDelegate.h"
#include "Logo.h"
#include "SimpleAudioEngine.h"
#include "GameController.h"
USING_NS_CC;
using namespace CocosDenshion;

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

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    std::vector<std::string> searchPaths;
    searchPaths.push_back("fonts");
    searchPaths.push_back("textures");
    searchPaths.push_back("particles");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    Director::getInstance()->getTextureCache()->addImage("mask.png");
    Director::getInstance()->getTextureCache()->addImage("mask2.png");
    Director::getInstance()->getTextureCache()->addImage("noise.png");
    Director::getInstance()->getTextureCache()->addImage("noise2.png");
    
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
    Director::getInstance()->stopAnimation();
    GameController::getInstance()->pause();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeAllEffects();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    
    Director::getInstance()->startAnimation();
}
