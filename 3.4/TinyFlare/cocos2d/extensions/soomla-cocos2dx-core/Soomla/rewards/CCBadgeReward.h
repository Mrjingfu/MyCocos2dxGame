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

#ifndef __CCBadgeReward_H_
#define __CCBadgeReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCReward.h"

namespace soomla {
    class CCBadgeReward : public CCReward {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mIconUrl, IconUrl, CCCoreConsts::JSON_ICON_URL);
    public:
        CCBadgeReward() : CCReward(), mIconUrl(NULL) {
        };

        static CCBadgeReward *create(
                cocos2d::__String *id,
                cocos2d::__String *name,
                cocos2d::__String *iconUrl = NULL);

        SL_CREATE_WITH_DICTIONARY(CCBadgeReward);

        virtual bool init(
                cocos2d::__String *id,
                cocos2d::__String *name,
                cocos2d::__String *iconUrl = NULL);

        virtual bool initWithDictionary(cocos2d::__Dictionary *dict);

        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCBadgeReward();

        virtual const char *getType() const;

    protected:
        virtual bool takeInner() override;

        virtual bool giveInner() override;
    };
}

#endif //__CCBadgeReward_H_
