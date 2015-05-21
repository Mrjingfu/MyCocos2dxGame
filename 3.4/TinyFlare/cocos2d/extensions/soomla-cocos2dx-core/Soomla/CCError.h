/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#ifndef __CCError_H_
#define __CCError_H_

#include "cocos2d.h"

namespace soomla {

    class CCError : public cocos2d::Ref {
    public:
        static CCError *createWithObject(cocos2d::Ref *obj);
        static void tryFillError(CCError **error, cocos2d::Ref *obj, const char *tag = NULL);
        const char *getInfo() {return mInfo.c_str();};
    private:
		/**
		   Extra information about what went wrong
		 */
        std::string mInfo;

        CCError():
            mInfo("") {}

        bool init(std::string &errorInfo);
    };
};


#endif //__CCError_H_
