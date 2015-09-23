//
//  RegionSlider.h
//  Tone_Skipper
//
//  Created by 创李 on 15/9/22.
//
//

#ifndef __Tone_Skipper__RegionSlider__
#define __Tone_Skipper__RegionSlider__

#include "ui/CocosGUI.h"
class RegionSlider:public cocos2d::ui::Slider
{
    RegionSlider();
    
public:
    static RegionSlider* create();
    static RegionSlider* create(const std::string& barTextureName,
                          const std::string& normalBallTextureName,
                          TextureResType resType = TextureResType::LOCAL);
    virtual ~RegionSlider();
    void setTouchRegionSize(cocos2d::Size _size);
private:
    virtual bool hitTest(const cocos2d::Vec2 &pt) override;
    cocos2d::Size m_touchSize;

    
};

#endif /* defined(__Tone_Skipper__RegionSlider__) */
