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

#ifndef __CCAggregateReward_H_
#define __CCAggregateReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCCoreConsts.h"
#include "CCReward.h"

namespace soomla {
    class CCAggregateReward : public CCReward {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__Array *, mRewards, Rewards, CCCoreConsts::JSON_REWARDS);
    public:
        CCAggregateReward() : CCReward(), mRewards(NULL) {
        };

        virtual bool init(
                cocos2d::__String *id,
                cocos2d::__String *name,
                cocos2d::__Array *rewards,
                CCSchedule *schedule = NULL);

        virtual bool initWithDictionary(cocos2d::__Dictionary *dict);

        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCAggregateReward();
    };
}

#endif //__CCAggregateReward_H_
