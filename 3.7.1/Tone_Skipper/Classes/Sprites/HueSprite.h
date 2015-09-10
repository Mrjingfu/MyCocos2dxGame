//
//  HueSprite.h
//  MazeJump
//
//  Created by wang haibo on 15/8/12.
//
//

#ifndef __MazeJump__HueSprite__
#define __MazeJump__HueSprite__

#include "cocos2d.h"

class HueSprite: public cocos2d::Sprite
{
public:
    static HueSprite* create(const std::string& filename);
    static HueSprite* create(const std::string& filename, const cocos2d::Rect& rect);
    
    static HueSprite* createWithTexture(cocos2d::Texture2D *texture);
    static HueSprite* createWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect& rect, bool rotated=false);
    
    static HueSprite* createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame);
    static HueSprite* createWithSpriteFrameName(const std::string& spriteFrameName);
    
    float getHue();
    void setHue(float hue);
    
    virtual cocos2d::Rect getBoundingBox() const;
    
protected:
    float _hue;
    GLfloat _mat[3][3];
    
    bool initWithTexture(cocos2d::Texture2D *texture);
    bool initWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect& rect);
    virtual bool initWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect &rect, bool rotated);
    virtual bool initWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame);
    
    void setupDefaultSettings();
    void initShader();
    const GLchar* shaderBody();
    virtual void updateColor();
    void updateColorMatrix();
    void updateAlpha();
    GLfloat getAlpha();
    
    void hueUniformCallback(cocos2d::GLProgram *p, cocos2d::Uniform *u);
};

#endif /* defined(__MazeJump__HueSprite__) */
