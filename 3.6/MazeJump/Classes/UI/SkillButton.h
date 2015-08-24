//
//  SkillButton.h
//  MazeJump
//
//  Created by wang haibo on 15/8/12.
//
//

#ifndef __MazeJump__SkillButton__
#define __MazeJump__SkillButton__

#include "HueSprite.h"
class SkillButton : public cocos2d::Node
{
    SkillButton();
public:
    static SkillButton* create(const std::string& btnTex, const std::string& maskTex, const std::string& colorTex);
    
    bool init(const std::string& btnTex, const std::string& maskTex, const std::string& colorTex);
    
    virtual void onEnter();
    virtual void onExit();
    
private:
    void onRainbowColumnValueChange(cocos2d::EventCustom* sender);
    void onRainbowRowValueChange(cocos2d::EventCustom* sender);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
private:
    cocos2d::Node*          m_pRootNode;
    HueSprite*              m_pBtnSprite;
    cocos2d::Sprite*        m_pMaskSprite;
    cocos2d::Sprite*        m_pColorSprite;
    cocos2d::Sprite*        m_pStepSprite;
    cocos2d::ProgressTimer*     m_pProgressTimer;
    float                   m_fCurrentRainbowValue;
    bool                    m_bTouchEnable;
};

#endif /* defined(__MazeJump__SkillButton__) */
