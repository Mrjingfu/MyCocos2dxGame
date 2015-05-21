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



#include "CCSoomlaUtils.h"
#include "cocos2d.h"

namespace soomla {
    void CCSoomlaUtils::logDebug(const char *tag, const char *message) {
        if (SOOMLA_DEBUG) {
            cocos2d::log("%s %s", tag, message);
        }
    }
    void CCSoomlaUtils::logError(const char *tag, const char *message) {
        CCLOGERROR("%s %s", tag, message);
    }

    void CCSoomlaUtils::logException(char const *tag, CCError *error) {
        CC_ASSERT(error);
        cocos2d::log("%s Soomla error: %s", tag, error->getInfo());
    }

    bool CCSoomlaUtils::isNullOrEmpty(cocos2d::__String *str) {
        return ((str == NULL) || (str->length() == 0));
    }
};
