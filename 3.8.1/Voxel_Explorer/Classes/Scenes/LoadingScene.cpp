//
//  LoadingScene.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 16/1/13.
//
//

#include "LoadingScene.hpp"
#include "GameScene.h"
USING_NS_CC;

static void* resource_load_thread_entry(void* param)
{
    LoadingIndicator* loadingIndicator = (LoadingIndicator*)param;
    LoadingScene *scene = (LoadingScene*)loadingIndicator->m_pContext;
    
    
    ////加载资源
    
    //load done
    scene->setLoadingIndicator(true);
    return nullptr;
}
LoadingScene::LoadingScene(void)
{
}
Scene* LoadingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
bool LoadingScene::init()
{
    if ( !Layer::init() )
        return false;
    
    bool bRet = false;
    do {
        this->schedule(schedule_selector(LoadingScene::checkFinished)
                       , 0.01f);
        m_LoadingIndicator.m_bDone = false;
        m_LoadingIndicator.m_pContext = (void*)this;
        pthread_mutex_init(&m_LoadingIndicator.m_Mutex, NULL);
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_t thread;
        pthread_create(&thread, &attr, resource_load_thread_entry, &m_LoadingIndicator);
        
        bRet=true;
    } while(0);
    
    return bRet;
}

void LoadingScene::checkFinished(float dt)
{
    if (getLoadingIndicator()) {
        handleSwitchScene();
    }
}
void LoadingScene::handleSwitchScene()
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
bool LoadingScene::getLoadingIndicator()
{
    bool flag;
    pthread_mutex_lock(&m_LoadingIndicator.m_Mutex);
    flag = m_LoadingIndicator.m_bDone;
    pthread_mutex_unlock(&m_LoadingIndicator.m_Mutex);
    return flag;
}

void LoadingScene::setLoadingIndicator(bool flag)
{
    pthread_mutex_lock(&m_LoadingIndicator.m_Mutex);
    m_LoadingIndicator.m_bDone = flag;
    pthread_mutex_unlock(&m_LoadingIndicator.m_Mutex);
    return; 
}