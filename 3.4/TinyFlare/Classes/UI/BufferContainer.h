//
//  BufferContainer.h
//  TinyFlare
//
//  Created by wang haibo on 15/4/20.
//
//

#ifndef __TinyFlare__BufferContainer__
#define __TinyFlare__BufferContainer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class BufferContainer : public cocos2d::ui::Widget
{
protected:
    BufferContainer();
    virtual ~BufferContainer();
    virtual bool init() override;
public:
    static BufferContainer* create();
    
    void showAccel(float time);
    void flashAccel();
    void hideAccel();
    
    void showMulti(float time);
    void flashMulti();
    void hideMulti();
    
    void showProtected(float time);
    void flashProtected();
    void hideProtected();
    
    void showTime(float time);
    void flashTime();
    void hideTime();
private:
    cocos2d::Node*     m_pAccelIcon;
    cocos2d::Node*     m_pMultiIcon;
    cocos2d::Node*     m_pProtectedIcon;
    cocos2d::Node*     m_pTimeIcon;
    
    int                m_nCurrentShowNum;
    cocos2d::Size      m_SizeBound;
};

#endif /* defined(__TinyFlare__BufferContainer__) */
