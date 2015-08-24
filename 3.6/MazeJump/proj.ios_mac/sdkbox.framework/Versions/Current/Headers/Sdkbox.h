/****************************************************************************

 Copyright (c) 2014-2015 Chukong Technologies

 ****************************************************************************/

#ifndef _CC_SDKBOX_H_
#define _CC_SDKBOX_H_

#include <string>

namespace sdkbox
{
    class Sdkbox
    {
    public:

        // @brief initialize all services
        static void init();

        // @brief set encrypt key
        static void setKey(const std::string& key);

        // @brief set project type lua,js or cpp, cpp is default
        static void setProjectType(const std::string& type);

        // @brief get sdkbox version string
        static const char* getVersion();
    };

    namespace device
    {
        const char* getAdvertisingIdentifier();
        bool isAdvertisingTrackingEnabled();
    }
}

#endif//_CC_SDKBOX_H_