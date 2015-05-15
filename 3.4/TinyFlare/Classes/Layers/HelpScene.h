//
//  HelpScene.h
//  TinyFlare
//
//  Created by wang haibo on 15/5/14.
//
//

#ifndef __TinyFlare__HelpScene__
#define __TinyFlare__HelpScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class HelpScene : public cocos2d::Layer
{
    HelpScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelpScene);
private:
    cocos2d::ui::Layout*    m_pHelpInfoUI;
};

#endif /* defined(__TinyFlare__HelpScene__) */
