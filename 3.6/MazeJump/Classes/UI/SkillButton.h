//
//  SkillButton.h
//  MazeJump
//
//  Created by wang haibo on 15/8/12.
//
//

#ifndef __MazeJump__SkillButton__
#define __MazeJump__SkillButton__

#include "cocos2d.h"

class SkillButton : public cocos2d::Node
{
    SkillButton();
public:
    static SkillButton* create(const std::string& btnTex, const std::string& maskTex);
    
    bool init(const std::string& btnTex, const std::string& maskTex);
    
    virtual void onEnter();
    virtual void onExit();
    
private:
    void onRainbowValueChange(cocos2d::EventCustom* sender);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
private:
    cocos2d::Sprite*        m_pBtnSprite;
    cocos2d::Sprite*        m_pMaskSprite;
    cocos2d::ProgressTimer*     m_pProgressTimer;
    int                     m_nCurrentRainbowValue;
    bool                    m_bTouchEnable;
};

#endif /* defined(__MazeJump__SkillButton__) */
