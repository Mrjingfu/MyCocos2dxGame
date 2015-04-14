//
//  ShatterSprite.h
//  TinyFlare
//
//  Created by wang haibo on 15/4/14.
//
//

#ifndef __TinyFlare__ShatterSprite__
#define __TinyFlare__ShatterSprite__

#include "cocos2d.h"

class FragSprite : public cocos2d::Sprite
{
    friend class ShatterSprite;
protected:
    FragSprite();
public:
    static FragSprite* create();
protected:
    int         m_nRandomNumber;
};

class ShatterSprite : public cocos2d::Sprite
{
    friend class ShatterAction;
protected:
    ShatterSprite(){
        m_fGridSideLen = 5.0f;
        m_fInitalFrageScale = 2.5f;
        m_pFragBatchNode = nullptr;
    }
    virtual ~ShatterSprite(){}
    bool init(const std::string& texFileName);
public:
    static ShatterSprite* create(const std::string &texFileName);
protected:
    void createShatter();
    void resetShatter();
    void updateShatterAction(float time, float delta,float growSpeedOfTargetR);
    
protected:
    float   m_fGridSideLen;
    float   m_fInitalFrageScale;
    std::vector<std::vector<FragSprite*> >  m_GridSprite;
    cocos2d::SpriteBatchNode*   m_pFragBatchNode;
};

#endif /* defined(__TinyFlare__ShatterSprite__) */
