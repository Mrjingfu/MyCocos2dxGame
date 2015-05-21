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

#include "CCCoreEventDispatcher.h"
#include "CCDomainFactory.h"
#include "CCSoomlaEventDispatcher.h"
#include "CCCoreConsts.h"

namespace soomla {

    USING_NS_CC;

    static CCCoreEventDispatcher *s_SharedInstance = NULL;

    CCCoreEventDispatcher *CCCoreEventDispatcher::getInstance() {
        if (!s_SharedInstance) {
            s_SharedInstance = new CCCoreEventDispatcher();
            s_SharedInstance->init();
        }

        return s_SharedInstance;
    }

    bool CCCoreEventDispatcher::init() {
        
        CCSoomlaEventDispatcher *eventDispatcher = CCSoomlaEventDispatcher::getInstance();

        eventDispatcher->registerEventHandler(CCCoreConsts::EVENT_REWARD_GIVEN,
                [this](__Dictionary *parameters) {
                    __String *rewardId = dynamic_cast<__String *>(parameters->objectForKey(CCCoreConsts::DICT_ELEMENT_REWARD));
                    CC_ASSERT(rewardId);
                    CCReward *reward  = CCReward::getReward(rewardId);
                    CC_ASSERT(reward);
                    this->onRewardGivenEvent(reward);
                });
        eventDispatcher->registerEventHandler(CCCoreConsts::EVENT_REWARD_TAKEN,
                [this](__Dictionary *parameters) {
                    __String *rewardId = dynamic_cast<__String *>(parameters->objectForKey(CCCoreConsts::DICT_ELEMENT_REWARD));
                    CC_ASSERT(rewardId);
                    CCReward *reward  = CCReward::getReward(rewardId);
                    CC_ASSERT(reward);
                    this->onRewardTakenEvent(reward);
                });
        eventDispatcher->registerEventHandler(CCCoreConsts::EVENT_CUSTOM,
              [this](__Dictionary *parameters) {
                  __String *name = dynamic_cast<__String *>(parameters->objectForKey(CCCoreConsts::DICT_ELEMENT_NAME));
                  CC_ASSERT(name);
                  __Dictionary *extra = dynamic_cast<__Dictionary *>(parameters->objectForKey(CCCoreConsts::DICT_ELEMENT_EXTRA));
                  CC_ASSERT(extra);
                  this->onCustomEvent(name, extra);
              });

        return true;
    }

    void CCCoreEventDispatcher::onRewardGivenEvent(CCReward *reward) {
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(reward, CCCoreConsts::DICT_ELEMENT_REWARD);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCCoreConsts::EVENT_REWARD_GIVEN, eventDict);
    }

    void CCCoreEventDispatcher::onRewardTakenEvent(CCReward *reward) {
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(reward, CCCoreConsts::DICT_ELEMENT_REWARD);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCCoreConsts::EVENT_REWARD_TAKEN, eventDict);
    }

    void CCCoreEventDispatcher::onCustomEvent(cocos2d::__String *name, cocos2d::__Dictionary *extra) {
        __Dictionary *eventDict = __Dictionary::create();
        eventDict->setObject(name, CCCoreConsts::DICT_ELEMENT_NAME);
        eventDict->setObject(extra, CCCoreConsts::DICT_ELEMENT_EXTRA);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CCCoreConsts::EVENT_CUSTOM, eventDict);
    }
}
