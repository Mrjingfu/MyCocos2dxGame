#include "checkMD5.h"
#include "cocos2d.h"
#include "md5.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
using namespace cocos2d;
using namespace std;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "MD5String.h"
#else
#define STR_MD5         ""
#endif

#define FILE_NAME       "classes.dex"

std::string getCurMD5Str()
{
    static char szTemp[48] = {0};
	if (szTemp[0])
	{
		return string(szTemp);
	}
    unsigned char* buffer = NULL;
    ssize_t  bufSize = 0;
    std::string strRet = "";
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string fullPath = getApkPath();
    CCLOG("full path is %s", fullPath.c_str());
    buffer = FileUtils::getInstance()->getFileDataFromZip(fullPath.c_str(), FILE_NAME, &bufSize);
    lutil_md5_data(buffer, (unsigned long)bufSize, szTemp);
    strRet = szTemp;
    // add by xiaochen
    char* mix_key = "ap9abmacde9856c";
    strRet += mix_key;
    lutil_md5_data((unsigned char*)(strRet.c_str()), strRet.length(), szTemp);
    strRet = szTemp;
    // ...
    
    CC_SAFE_DELETE_ARRAY(buffer);
#else
    CCFileData data(FILE_NAME, "rb");
    buffer  = data.getBuffer();
    bufSize = data.getSize();
    lutil_md5_data(buffer, bufSize, szTemp);
    strRet = szTemp;
#endif
    return strRet;
}

bool getBooleanForKey()
{
    bool bRet = true;

    do 
    {
        std::string strMD5 = STR_MD5;
        CCLOG("Record md5 string is : %s", strMD5.c_str());
        if (strMD5.length() <= 0)
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            MessageBox("MD5 string is empty! PLZ ensure it's in debug mode!", "Debug");
#endif
            break;
        }

        std::string curMD5 = getCurMD5Str();
        CCLOG("current md5 string is : %s", curMD5.c_str());
        if (0 != curMD5.compare(strMD5))
        {
            bRet = false;
        }
    } while (0);
 
    return bRet;
}

bool getBooleanForKey(bool defaultValue)
{
    bool bRet = true;
    
    if (defaultValue)
        return true;

    do 
    {
        std::string strMD5 = STR_MD5;
        CCLOG("Record md5 string is : %s", strMD5.c_str());
        if (strMD5.length() <= 0)
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            MessageBox("MD5 string is empty! PLZ ensure it's in debug mode!", "Debug");
#endif
            break;
        }

        std::string curMD5 = getCurMD5Str();
        CCLOG("current md5 string is : %s", curMD5.c_str());
        if (0 != curMD5.compare(strMD5))
        {
            bRet = false;
        }
    } while (0);

    return bRet;
}
