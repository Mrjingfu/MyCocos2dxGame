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

#ifndef __CCReward_H_
#define __CCReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCDomain.h"
#include "CCCoreConsts.h"
#include "CCSchedule.h"
#include "CCSoomlaEntity.h"

namespace soomla {
    class CCReward : public CCSoomlaEntity {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(CCSchedule *, mSchedule, Schedule, CCCoreConsts::JSON_SCHEDULE);
    public:
        CCReward() : CCSoomlaEntity(), mSchedule(NULL) {
        };

        virtual bool init(cocos2d::__String *id, cocos2d::__String *name, CCSchedule *schedule = NULL);

        virtual bool initWithDictionary(cocos2d::__Dictionary *dict);

        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCReward();

    public:
        virtual bool take();
        virtual bool give();
        bool isOwned();
        
        static void addReward(CCReward *reward);
        static CCReward *getReward(cocos2d::__String *id);

    protected:
        virtual bool takeInner() = 0;
        virtual bool giveInner() = 0;
        
    private:
        static cocos2d::__Dictionary *rewardsMap;
    };
}

#endif //__CCReward_H_
