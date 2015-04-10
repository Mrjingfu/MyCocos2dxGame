//
//  EncrytionUtility.h
//  TinyFlare
//
//  Created by wang haibo on 14-8-22.
//
//

#ifndef __TinyFlare__EncrytionUtility__
#define __TinyFlare__EncrytionUtility__

#include "GameConst.h"
class EncrytionUtility
{
public:
    static bool     getBoolForKey(const char* pKey);
    static bool     getBoolForKey(const char* pKey, bool defaultValue);
    static int      getIntegerForKey(const char* pKey);
    static int      getIntegerForKey(const char* pKey, int defaultValue);
    static float    getFloatForKey(const char* pKey);
    static float    getFloatForKey(const char* pKey, float defaultValue);
    static double       getDoubleForKey(const char* pKey);
    static double       getDoubleForKey(const char* pKey, double defaultValue);
    static std::string  getStringForKey(const char* pKey);
    static std::string  getStringForKey(const char* pKey, const std::string & defaultValue);
    

    static void    setBoolForKey(const char* pKey, bool value);
    static void    setIntegerForKey(const char* pKey, int value);
    static void    setFloatForKey(const char* pKey, float value);
    static void    setDoubleForKey(const char* pKey, double value);
    static void    setStringForKey(const char* pKey, const std::string & value);
    
    static bool strXor(std::string& stream, int begin, int end, const char* secret);
};

#endif /* defined(__SuperLife__EncrytionUtility__) */
