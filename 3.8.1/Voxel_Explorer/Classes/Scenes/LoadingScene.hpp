//
//  LoadingScene.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 16/1/13.
//
//

#ifndef LoadingScene_hpp
#define LoadingScene_hpp

#include "cocos2d.h"

struct LoadingIndicator {
    pthread_mutex_t     m_Mutex;
    bool                m_bDone;
    void*               m_pContext;
};

class LoadingScene : public cocos2d::Layer
{
    LoadingScene(void);
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    
    CREATE_FUNC(LoadingScene);
    bool getLoadingIndicator();
    void setLoadingIndicator(bool flag);
protected:
    virtual void handleSwitchScene();
private:
    void checkFinished(float dt);
    
private:
    LoadingIndicator    m_LoadingIndicator;
};

#endif /* LoadingScene_hpp */
