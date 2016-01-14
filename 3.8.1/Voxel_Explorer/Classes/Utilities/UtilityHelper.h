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
#include "ui/CocosGUI.h"
class UtilityHelper
{
public:
    static std::string getAppStoreURL();
    static std::string getLocalString(const std::string& key);
    static std::string getLocalStringForUi(const std::string& key);
    static std::string getLocalStringForPlist(const std::string& key,const std::string cn_plist,const std::string en_plist);
    static void getLineForText(cocos2d::ui::Text*  tempText,std::string& str);
    static cocos2d::Size getSingleStrFontSize(cocos2d::ui::Text*  tempText,std::string str);//单个字符Size大小
    static std::vector<std::string> getStringCount(std::string str ); //字符串字节格式
    static int getLineStr(std::string& str,int length);//对字符串换行符 返回换行符个数
    static int getCharUtf8Count(unsigned char ch);
    static void screenshot(const std::string& fileName,const std::function<void(const std::string&)>& callback);
    static bool checkCircleIntersectWithSegment(const cocos2d::Vec2& center, float radius, const cocos2d::Vec2& start, const cocos2d::Vec2& end);
    static void getCameraToViewportRay(cocos2d::Camera* camera, const cocos2d::Vec2& screenPoint, cocos2d::Ray* outRay);
    static void getHexDigest(const unsigned char* md5, int len, std::string& hexStr);
    static cocos2d::Node* seekNodeByTag(cocos2d::Node* root, int tag);
    static cocos2d::Node* seekNodeByName(cocos2d::Node* root, const std::string& name);
    static cocos2d::Color3B randomColor(int minSum = 650, int minDelta = 10);
    
    static cocos2d::Color3B randomRedColor();
    static cocos2d::Color3B randomOrangeColor();
    static cocos2d::Color3B randomYellowColor();
    static cocos2d::Color3B randomGreenColor();
    static cocos2d::Color3B randomCyanColor();
    static cocos2d::Color3B randomBlueColor();
    static cocos2d::Color3B randomPurpleColor();
    
    
    static float InvSqrt (float x);
};

#endif /* defined(__TinyFlare__UtilityHelper__) */
