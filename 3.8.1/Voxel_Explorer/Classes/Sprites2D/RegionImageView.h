//
//  RegionButton.h
//  MazeJump
//
//
//

#ifndef __MazeJump__RegionImageView__
#define __MazeJump__RegionImageView__

#include "ui/CocosGUI.h"
class RegionImageView : public cocos2d::ui::ImageView
{
    RegionImageView();
public:
    static RegionImageView* create();
    static RegionImageView* create(const std::string& imageFileName, TextureResType texType = TextureResType::LOCAL);
    virtual ~RegionImageView();
    void setTouchRegionSize(cocos2d::Size _size);
private:
    virtual bool hitTest(const cocos2d::Vec2 &pt, const cocos2d::Camera* camera, cocos2d::Vec3 *p) const override;
    cocos2d::Size m_regionTouchSize;
};

#endif /* defined(__MazeJump__RegionImageView__) */
