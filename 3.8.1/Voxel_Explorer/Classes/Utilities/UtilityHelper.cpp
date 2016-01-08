//
//  UtilityHelper.cpp
//  
//
//  Created by wang haibo on 15/7/2.
//
//

#include "UtilityHelper.h"
USING_NS_CC;

std::string UtilityHelper::getLocalString(const std::string& key)
{
    return  getLocalStringForPlist(key, "chinese.plist", "english.plist");
}

std::string UtilityHelper::getLocalStringForUi(const std::string& key)
{
    return  getLocalStringForPlist(key, "ui_chinese.plist", "ui_english.plist");
}
std::string UtilityHelper::getLocalStringForPlist(const std::string &key, const std::string cn_plist,const std::string en_plist)
{
    ValueMap dict;
    LanguageType lt= Application::getInstance()->getCurrentLanguage();
    switch (lt) {
        case LanguageType::CHINESE:
            dict = FileUtils::getInstance()->getValueMapFromFile(cn_plist);
            CCASSERT(!dict.empty(), "cannot create dictionary");
            break;
            
        default:
            dict = FileUtils::getInstance()->getValueMapFromFile(en_plist);
            CCASSERT(!dict.empty(), "cannot create dictionary");
            break;
    }
    
    Value ret = dict[key];
    
    return ret.asString();
}
void UtilityHelper::getLineForText(cocos2d::ui::Text*  tempText,std::string& str)
{
    std::string retultStr;
    if (!tempText ||str.empty())
        return ;
    
    std::vector<std::string> tempVec;
    std::vector<std::string> CharVec;
     for (int i=0; i<str.length(); )
     {
         char ch = str.at(i);
         int count = getCharUtf8Count(ch);
         
         std::string subStr =  str.substr(i,count);
         CharVec.push_back(subStr);
         i+=count;
     }
    int current = 0;
    std::string patterStr ="？。，““；";
    for (int i=0; i<CharVec.size(); i++)
    {
            if (CharVec[i]=="？"||CharVec[i]=="。"||
                CharVec[i]=="，"||CharVec[i]=="；"||
                CharVec[i]==" "||CharVec[i]=="“"||CharVec[i]=="“")
            {
                std::string charStr;
                for (int j=current; j<=i; j++)
                {
                    charStr.append(CharVec[j]);
                }
                current = i+1;
                tempVec.push_back(charStr);
            }
        
        if (i==CharVec.size()-1) {
            std::string charStr;
            for (int j=current; j<=i; j++)
            {
                charStr.append(CharVec[j]);
            }
            current = i;
            tempVec.push_back(charStr);
        }
        
    }
    
    CCASSERT(tempText->getParent(), "tempText is not parent" );
    
    float parentWidth = tempText->getParent()->getContentSize().width-10;
    
    float textWidthSum = 0.0f;
    for (int i =0; i<tempVec.size(); i++) {
        
        tempText->setString(tempVec[i]);
        cocos2d::Size textSize = tempText->getContentSize()* tempText->getScale();
        textWidthSum+=textSize.width;
        if (textWidthSum >= parentWidth){
            if (i==0) {
                tempVec[i].append("\n");
            }else
            {
                tempVec[i-1].append("\n");
                --i;
            }
            textWidthSum = 0.0f;
            
        }
    }
    str.clear();
    for (int i =0; i<tempVec.size(); i++)
    {
        str.append(tempVec[i]);
    }
    
}
cocos2d::Size UtilityHelper::getSingleStrFontSize(cocos2d::ui::Text* tempText,std::string str)
{
     cocos2d::Size tempSize = cocos2d::Size::ZERO;
    if (str.empty())
        return tempSize;
    std::vector<std::string > tempVec = getStringCount(str);
    std::vector<cocos2d::Size>  sizeWidthVec;
    
    
    for (int i =0; i<tempVec.size(); i++) {
        std::string tempStr = tempVec[i];
        tempText->setString(tempStr);
        cocos2d::Size textSize = tempText->getContentSize()*tempText->getScale();
//        CCLOG("width:%f height:%f",textSize.width,textSize.height);
        sizeWidthVec.push_back(textSize);
        
    }
 
    //取最小字体大小  测试之后看要不要做中英文 中文取最大字体 英文取最小字体
   
    std::sort(sizeWidthVec.begin(), sizeWidthVec.end(),[](cocos2d::Size a, cocos2d::Size b) {
        return a.width < b.width;
    });
     auto end = std::unique(sizeWidthVec.begin(), sizeWidthVec.end(),[](cocos2d::Size a, cocos2d::Size b){
        return a.width ==b.width;
    });
    sizeWidthVec.erase(end, sizeWidthVec.end());
    tempSize =  sizeWidthVec.at(sizeWidthVec.size()/2);
    
    
    return tempSize;
}
std::vector<std::string> UtilityHelper::getStringCount(std::string str )
{
    std::vector<std::string > tempVec;
    
    if (str.empty() ) {
        return tempVec;
    }
    
    //1.将字符串中英文切割存放到列表
    std::string tempStr;
    for (int i=0; i<str.length(); ) {
        //判断当前字符有几个字节
        int count = getCharUtf8Count(str.at(i));

        std::string subStr =  str.substr(i,count);
        //三个字节算一个字
        if (count >0 && count <3 ) {
            if (tempStr.length() >=3 ) {
                tempVec.push_back(tempStr);
                tempStr.clear();
            }
            tempStr.append(subStr);
        }else{
            if (!tempStr.empty()) {
                tempVec.push_back(tempStr);
                tempStr.clear();
            }
            tempVec.push_back(subStr);
        }
        i+=count;
        if (i==str.length() && !tempStr.empty()) {
            tempVec.push_back(tempStr);
            tempStr.clear();
        }

    }
    return tempVec;
}
int UtilityHelper::getLineStr(std::string &str, int length)
{
    if (str.empty() ||length<=0) {
        return 0;
    }
    if (str.length() < length) {
        return 0;
    }

    std::string resultStr;
    std::vector<std::string > str_vec;
    std::vector<std::string > tempVec = getStringCount(str);
 
    if (tempVec.size() <=length) {
        std::string tempStr;
        for (int i=0; i<tempVec.size(); i++) {
            tempStr.append(tempVec[i]);
        }
        str_vec.push_back(tempStr);
    }else{
        int tempCount = (int)tempVec.size()/length;
        for (int i =0; i< tempCount; i++)
        {
            std::string tempStr;
            for(int j=i*length;j<length*(i+1);j++)
            {
                tempStr.append(tempVec[j]);
            }
             str_vec.push_back(tempStr);
        }
         std::string tempStr;
        for (int i =length*tempCount; i< tempVec.size(); i++)
        {
            tempStr.append(tempVec[i]);
        }
        str_vec.push_back(tempStr);
    }
   
    for (unsigned int i = 0;i<str_vec.size();++i)
    {
        resultStr.append(str_vec.at(i)).append("\n");
    }
        resultStr.pop_back();
    str = resultStr;
    return str_vec.size();
}
int UtilityHelper::getCharUtf8Count(unsigned char ch)
{
    int resultsize = 1;
    if(ch < 0x80) {
        resultsize = 1;
    }
    else if(ch < 0xc2)
    {
        resultsize = 2;
    }
    else if(ch < 0xe0)
    {
        resultsize = 2;
    }
    else if(ch < 0xf0)
    {
        resultsize = 3;
    }
    else if(ch < 0xf8)
    {
        resultsize = 4;
    }
    else if (ch < 0xfc)
    {
        resultsize = 5;
    }
    else if (ch < 0xfe)
    {
        resultsize = 6;
    }
    else
        resultsize = 7;

//    if (ch >= 0x00 && ch <= 0x7f)//说明最高位为'0'，这意味着utf8编码只有1个字节！
//    {
//
//        resultsize = 1;
//    }
//    else if ((ch & 0xe0)== 0xc0)//只保留最高三位，看最高三位是不是110，如果是则意味着utf8编码有2个字节！
//    {
//        
//        resultsize = 2;
//    }
//    else if ((ch & (0xf0))== 0xe0)//只保留最高四位，看最高三位是不是1110，如果是则意味着utf8编码有3个字节！
//    {
//        
//        resultsize = 3;
//    }
    return resultsize;
}
void UtilityHelper::getHexDigest(const unsigned char* md5, int len, std::string& hexStr)
{
    char* hex = new char[len*2+1];
    hex[len*2] =  '\0';
    
    int i;
    static const char HEX_CHARS[]="0123456789abcdef";
    for (i=0;i<len;i++)
    {
        hex[i+i] = HEX_CHARS[md5[i] >> 4];
        hex[i+i+1] = HEX_CHARS[md5[i] & 0x0f];
    }
    hexStr = std::string(hex, 2*len);
    CC_SAFE_DELETE_ARRAY(hex);
}

void UtilityHelper::screenshot(const std::string& fileName,const std::function<void(const std::string&)>& callback)
{
    Image::Format format;
    //进行后缀判断
    if(std::string::npos != fileName.find_last_of(".")){
        auto extension = fileName.substr(fileName.find_last_of("."),fileName.length());
        if (!extension.compare(".png")) {
            format = Image::Format::PNG;
        } else if(!extension.compare(".jpg")) {
            format = Image::Format::JPG;
        } else{
            CCLOGWARN("cocos2d: the image can only be saved as JPG or PNG format");
            return;
        }
    } else {
        CCLOGWARN("cocos2d: the image can only be saved as JPG or PNG format");
        return ;
    }
    //获取屏幕尺寸，初始化一个空的渲染纹理对象
    cocos2d::Size winSize = Director::getInstance()->getWinSize();
    auto renderTexture = RenderTexture::create(winSize.width, winSize.height, Texture2D::PixelFormat::RGBA8888);
    //清空并开始获取
    renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    //遍历场景节点对象，填充纹理到RenderTexture中
    Director::getInstance()->getRunningScene()->visit();
    //结束获取
    renderTexture->end();
    //保存文件
    renderTexture->saveToFile(fileName , format);
    //使用schedule在下一帧中调用callback函数
    auto fullPath = FileUtils::getInstance()->getWritablePath() + fileName;
    auto scheduleCallback = [&,fullPath,callback](float dt){
        callback(fullPath);
    };
    auto _schedule = Director::getInstance()->getRunningScene()->getScheduler();
    _schedule->schedule(scheduleCallback, Director::getInstance(), 0.0f,0,0.0f, false, "screenshot");
}

bool UtilityHelper::checkCircleIntersectWithSegment(const Vec2& center, float radius, const Vec2& start, const Vec2& end)
{
    bool ret = false;
    Vec2 d = (end - start).getNormalized();
    Vec2 e = center - start;
    
    float a = e.dot(d);
    
    float a2 = a*a;
    float e2 = center.distanceSquared(start);
    float r2 = radius*radius;
    
    if ((r2 + a2) < e2)
        ret = false;
    else
    {
        Vec2 v1 = (start - center).getNormalized();
        Vec2 v2 = (end - center).getNormalized();
        float f = v1.dot(v2);
        if(f > 0)
            ret = false;
        else
            ret = true;
    }
    ////这个判断算法只是粗略检测，当两点之间距离是小于半径2倍时会穿透。
    return ret;
}
void UtilityHelper::getCameraToViewportRay(Camera* camera,const Vec2& screenPoint, Ray* outRay)
{
    if(!camera)
        outRay = nullptr;
    else
    {
        auto size = Director::getInstance()->getWinSize();
        float screenX = screenPoint.x / size.width;
        float screenY = screenPoint.y / size.height;
        
        float nx = (2.0f * screenX) -1.0f;
        float ny = (2.0f * screenY) -1.0f;
        
        Vec4 nearPoint(nx, ny, -1.0f, 1.0f);
        Vec4 midPoint(nx, ny, 0.0f, 1.0f);
        
        
        Vec4 origin, target;
        camera->getViewProjectionMatrix().getInversed().transformVector(nearPoint, &origin);
        camera->getViewProjectionMatrix().getInversed().transformVector(midPoint, &target);
        if(origin.w > 0.0f)
        {
            origin.x /= origin.w;
            origin.y /= origin.w;
            origin.z /= origin.w;
            origin.w = 1.0f;
        }
        if(target.w > 0.0f)
        {
            target.x /= target.w;
            target.y /= target.w;
            target.z /= target.w;
            target.w = 1.0f;
        }
        Vec3 dir = Vec3(target.x - origin.x, target.y - origin.y, target.z - origin.z);
        dir.normalize();
        outRay->set(Vec3(origin.x, origin.y, origin.z), dir);
    }

}
Node* UtilityHelper::seekNodeByTag(Node* root, int tag){
    if (!root)
    {
        return nullptr;
    }
    if (root->getTag() == tag)
    {
        return root;
    }
    const auto& arrayRootChildren = root->getChildren();
    ssize_t length = arrayRootChildren.size();
    for (ssize_t i=0;i<length;i++)
    {
        Node* child = dynamic_cast<Node*>(arrayRootChildren.at(i));
        if (child)
        {
            Node* res = seekNodeByTag(child,tag);
            if (res != nullptr)
            {
                return res;
            }
        }
    }
    return nullptr;
}


Node* UtilityHelper::seekNodeByName(Node* root, const std::string& name)
{
    if (!root)
    {
        return nullptr;
    }
    if (root->getName() == name)
    {
        return root;
    }
    const auto& arrayRootChildren = root->getChildren();
    for (auto& subWidget : arrayRootChildren)
    {
        Node* child = dynamic_cast<Node*>(subWidget);
        if (child)
        {
            Node* res = seekNodeByName(child,name);
            if (res != nullptr)
            {
                return res;
            }
        }
    }
    return nullptr;
}
Color3B UtilityHelper::randomColor(int minSum, int minDelta)
{
    int r, g, b, min, max;
    while (true) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        r = arc4random_uniform(255);
        g = arc4random_uniform(255);
        b = arc4random_uniform(255);
#else
        r = arc4random() % 256;
        g = arc4random() % 256;
        b = arc4random() % 256;
#endif
        min = MIN(MIN(r, g), b);
        max = MAX(MAX(r, g), b);
        if (max-min < minDelta) continue;
        if (r+g+b < minSum) continue;
        break;
    }
    return Color3B(r, g, b);
}
Color3B UtilityHelper::randomRedColor()
{
    int r = cocos2d::random(252, 255);
    int g = cocos2d::random(132, 200);
    int b = g;
    return Color3B(r,g,b);
}
Color3B UtilityHelper::randomOrangeColor()
{
    int r = cocos2d::random(252, 255);
    int g = cocos2d::random(200, 238);
    int b = g-cocos2d::random(40, 50);
    return Color3B(r,g,b);
}
Color3B UtilityHelper::randomYellowColor()
{
    int r = cocos2d::random(252, 255);
    int g = cocos2d::random(252, 255);
    int b = cocos2d::random(103, 203);
    return Color3B(r,g,b);
}
Color3B UtilityHelper::randomGreenColor()
{
    int r = cocos2d::random(200, 234);
    int g = cocos2d::random(238, 252);
    int b = r-cocos2d::random(40, 50);
    return Color3B(r,g,b);
}
Color3B UtilityHelper::randomCyanColor()
{
    int g = cocos2d::random(238, 250);
    int b = cocos2d::random(252, 255);
    int r = g - cocos2d::random(40, 50);
    return Color3B(r,g,b);
}
Color3B UtilityHelper::randomBlueColor()
{
    int g = cocos2d::random(186, 230);
    int b = cocos2d::random(252, 255);
    int r = g - cocos2d::random(40, 50);
    return Color3B(r,g,b);
}
Color3B UtilityHelper::randomPurpleColor()
{
    int r = cocos2d::random(209, 240);
    int g = r -cocos2d::random(40, 50);
    int b = cocos2d::random(252, 255);
    return Color3B(r,g,b);
}
float UtilityHelper::InvSqrt (float x)
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1); // 计算第一个近似根
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x); // 牛顿迭代法
    return x;
}
