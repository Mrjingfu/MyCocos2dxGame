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

#ifndef __CCRandomReward_H_
#define __CCRandomReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCAggregateReward.h"

namespace soomla {
    class CCRandomReward : public CCAggregateReward {
        CC_SYNTHESIZE_RETAIN(CCReward *, mLastGivenReward, LastGivenReward);
    public:
        CCRandomReward() : CCAggregateReward(), mLastGivenReward(NULL) {
        };

        static CCRandomReward *create(
                cocos2d::__String *id,
                cocos2d::__String *name,
                cocos2d::__Array *rewards,
                CCSchedule *schedule
        );

        SL_CREATE_WITH_DICTIONARY(CCRandomReward);

        virtual ~CCRandomReward();

        virtual const char *getType() const;

    protected:
        virtual bool takeInner();

        virtual bool giveInner();
    };
}

#endif //__CCRandomReward_H_
