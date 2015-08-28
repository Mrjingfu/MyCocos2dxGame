//
//  RegionButton.h
//  MazeJump
//
//
//

#ifndef __MazeJump__RegionButton__
#define __MazeJump__RegionButton__

#include "ui/CocosGUI.h"
class RegionButton : public cocos2d::ui::Button
{
    RegionButton();
    virtual ~RegionButton();
public:
    static RegionButton* create(const std::string& normalImage,
                          const std::string& selectedImage = "",
                          const std::string& disableImage = "",
                          TextureResType texType = TextureResType::LOCAL);
    void setTouchRegionSize(cocos2d::Size _size);
private:
    virtual bool hitTest(const cocos2d::Vec2 &pt) override;
    cocos2d::Size m_touchSize;
};

#endif /* defined(__MazeJump__RegionButton__) */
