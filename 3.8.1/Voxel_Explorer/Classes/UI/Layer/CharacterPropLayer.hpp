//
//  CharacterPropLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#ifndef CharacterPropLayer_hpp
#define CharacterPropLayer_hpp

#include "WrapperUILayer.h"
class TGridView;
class BaseMonster;

class CharacterPropLayer :public WrapperUILayer {
protected:
    CharacterPropLayer();
public:
    virtual ~CharacterPropLayer();
    virtual bool initUi() override;
    virtual bool addEvents() override;
    virtual void refreshUIView()override;
private:
    virtual void updateCharacterBuff() = 0;
    virtual void updateCharacterProp() = 0;
protected:
   
    TGridView*               m_pCharacterBufferList;
    cocos2d::ui::LoadingBar* m_pCharacterHpBar;
    cocos2d::ui::Text*       m_pCharacterCurHp;
    cocos2d::ui::Text*       m_pCharacterMaxHp;
    cocos2d::ui::LoadingBar* m_pCharacterMpBar;
    cocos2d::ui::Text*       m_pCharacterCurMp;
    cocos2d::ui::Text*       m_pCharacterMaxMp;
    cocos2d::ui::Text*       m_pCharacterLevel;
    cocos2d::ui::Text*       m_pCharacterName;
    cocos2d::ui::ImageView*  m_pCharacterIcon;
    cocos2d::ui::ImageView*  m_pCharacterIconFrame;
};




#endif /* CharacterPropLayer_hpp */
