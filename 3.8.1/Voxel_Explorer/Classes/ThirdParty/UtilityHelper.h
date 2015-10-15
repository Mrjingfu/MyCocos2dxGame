//
//  UtilityHelper.h
//
//
//  Created by wang haibo on 15/7/2.
//
//

#ifndef __TinyFlare__UtilityHelper__
#define __TinyFlare__UtilityHelper__

#include "cocos2d.h"

class UtilityHelper
{
public:
    static std::string getLocalString(const char* key);
    static void screenshot(const std::string& fileName,const std::function<void(const std::string&)>& callback);
    static bool checkCircleIntersectWithSegment(const cocos2d::Vec2& center, float radius, const cocos2d::Vec2& start, const cocos2d::Vec2& end);
    static void getCameraToViewportRay(cocos2d::Camera* camera, const cocos2d::Vec2& screenPoint, cocos2d::Ray* outRay);
    static void getHexDigest(const unsigned char* md5, int len, std::string& hexStr);
    
    
    static cocos2d::Color3B randomColor(int minSum = 650, int minDelta = 10);
    
    static cocos2d::Color3B randomRedColor();
    static cocos2d::Color3B randomOrangeColor();
    static cocos2d::Color3B randomYellowColor();
    static cocos2d::Color3B randomGreenColor();
    static cocos2d::Color3B randomCyanColor();
    static cocos2d::Color3B randomBlueColor();
    static cocos2d::Color3B randomPurpleColor();
};

#endif /* defined(__TinyFlare__UtilityHelper__) */
