/****************************************************************************

 Copyright (c) 2014-2015 Chukong Technologies

 ****************************************************************************/

#ifndef _CC_SDKBOX_H_
#define _CC_SDKBOX_H_

#define SDKBOX_VERSION_STR  "sdkbox V1.5.2.6"

namespace sdkbox {

    void init( const char* application_token, const char* application_key );
    void init( const char* application_token, const char* application_key, bool debug );
    void setProjectType(const char* project_type);
    
    void sessionStart();
    void sessionEnd();
}

#endif//_CC_SDKBOX_H_
