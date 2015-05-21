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

#include "CCSchedule.h"
#include "CCSoomlaUtils.h"

#define TAG "SOOMLA Schedule"

namespace soomla {
    CCSchedule::CCDateTimeRange *CCSchedule::CCDateTimeRange::create(timeval start, timeval end) {
        CCDateTimeRange *ret = new CCDateTimeRange();
        if (ret->init(start, end)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }
        return ret;
    }

    bool CCSchedule::CCDateTimeRange::init(timeval start, timeval end) {
        mStart = start;
        mEnd = end;

        return true;
    }

    bool CCSchedule::CCDateTimeRange::initWithDictionary(cocos2d::__Dictionary *dict) {
        Ref *ref;
        time_t seconds;

        ref = dict->objectForKey(CCCoreConsts::JSON_SCHE_RANGE_START);
        CC_ASSERT(ref && dynamic_cast<cocos2d::__Double *>(ref));
        cocos2d::__Double *startMs = dynamic_cast<cocos2d::__Double *>(ref);

        // convert ms to timeval
        seconds = (time_t) (startMs->getValue() / 1000);
        this->mStart.tv_sec = seconds;
        this->mStart.tv_usec = (suseconds_t)((startMs->getValue() - 1000 * seconds) * 1000);

        ref = dict->objectForKey(CCCoreConsts::JSON_SCHE_RANGE_END);
        CC_ASSERT(ref && dynamic_cast<cocos2d::__Double *>(ref));
        cocos2d::__Double *endMs = dynamic_cast<cocos2d::__Double *>(ref);

        // convert ms to timeval
        seconds = (time_t) (endMs->getValue() / 1000);
        this->mStart.tv_sec = seconds;
        this->mStart.tv_usec = (suseconds_t)((endMs->getValue() - 1000 * seconds) * 1000);

        return true;
    }

    CCSchedule::CCDateTimeRange::~CCDateTimeRange() {

    }

    cocos2d::__Dictionary *CCSchedule::CCDateTimeRange::toDictionary() {
        cocos2d::__Dictionary *dict = cocos2d::__Dictionary::create();

        double ms;

        ms = 1000 * mStart.tv_sec + mStart.tv_usec / 1000.0f;
        dict->setObject(cocos2d::__Double::create(ms), CCCoreConsts::JSON_SCHE_RANGE_START);

        ms = 1000 * mEnd.tv_sec + mEnd.tv_usec / 1000.0f;
        dict->setObject(cocos2d::__Double::create(ms), CCCoreConsts::JSON_SCHE_RANGE_END);

        return this->putTypeData(dict, CCCoreConsts::JSON_JSON_TYPE_DATE_TIME_RANGE);
    }

    CCSchedule *CCSchedule::create(cocos2d::__Integer *requiredRecurrence, cocos2d::__Array *timeRanges, cocos2d::__Integer *activationLimit) {
        CCSchedule *ret = new CCSchedule();
        if (ret->init(requiredRecurrence, timeRanges, activationLimit)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }
        return ret;
    }

    CCSchedule *CCSchedule::create(cocos2d::__Integer *activationLimit) {
        return CCSchedule::create(cocos2d::__Integer::create(CCSchedule::Recurrence::NONE), NULL, activationLimit);
    }

    CCSchedule *CCSchedule::create(cocos2d::__Integer *requiredRecurrence, timeval start, timeval end, cocos2d::__Integer *activationLimit) {
        cocos2d::__Array *timeRanges = cocos2d::__Array::create();
        timeRanges->addObject(CCDateTimeRange::create(start, end));
        return CCSchedule::create(requiredRecurrence, timeRanges, activationLimit);
    }

    CCSchedule *CCSchedule::createAnyTimeOnce() {
        return CCSchedule::create(cocos2d::__Integer::create(1));
    }

    CCSchedule *CCSchedule::createAnyTimeLimited(int activationLimit) {
        return CCSchedule::create(cocos2d::__Integer::create(activationLimit));
    }

    CCSchedule *CCSchedule::createAnyTimeUnLimited() {
        return CCSchedule::create(cocos2d::__Integer::create(0));
    }

    bool CCSchedule::init(cocos2d::__Integer *requiredRecurrence, cocos2d::__Array *timeRanges, cocos2d::__Integer *activationLimit) {
        setRequiredRecurrence(requiredRecurrence);
        setTimeRanges(timeRanges);
        setActivationLimit(activationLimit);

        return true;
    }

    bool CCSchedule::initWithDictionary(cocos2d::__Dictionary *dict) {
        fillRequiredRecurrenceFromDict(dict);
        fillTimeRangesFromDict(dict);
        fillActivationLimitFromDict(dict);

        return true;
    }

    CCSchedule::~CCSchedule() {
        CC_SAFE_RELEASE(mRequiredRecurrence);
        CC_SAFE_RELEASE(mTimeRanges);
        CC_SAFE_RELEASE(mActivationLimit);
    }

    cocos2d::__Dictionary *CCSchedule::toDictionary() {
        cocos2d::__Dictionary *dict = cocos2d::__Dictionary::create();

        putRequiredRecurrenceToDict(dict);
        putTimeRangesToDict(dict);
        putActivationLimitToDict(dict);

        return this->putTypeData(dict, CCCoreConsts::JSON_JSON_TYPE_SCHEDULE);
    }

    bool CCSchedule::approve(int activationTimes) {

        struct timeval now;
        gettimeofday(&now, NULL);

        if (mActivationLimit && mActivationLimit->getValue() < 1 && (mTimeRanges == NULL || mTimeRanges->count() == 0)) {
            CCSoomlaUtils::logDebug(TAG, "There's no activation limit and no TimeRanges. APPROVED!");
            return true;
        }

        if (mActivationLimit && mActivationLimit->getValue() > 0 && activationTimes >= mActivationLimit->getValue()) {
            CCSoomlaUtils::logDebug(TAG, "Activation limit exceeded.");
            return false;
        }

        if ((mTimeRanges == NULL || mTimeRanges->count() == 0)) {
            CCSoomlaUtils::logDebug(TAG, "We have an activation limit that was not reached. Also, we don't have any time ranges. APPROVED!");
            return true;
        }


        // NOTE: From this point on ... we know that we didn't reach the activation limit AND we have TimeRanges.
        //		 We'll just make sure the time ranges and the Recurrence copmlies.

        Ref *ref;
        CCDateTimeRange *dateTimeRange;

        CCARRAY_FOREACH(mTimeRanges, ref) {
                dateTimeRange = dynamic_cast<CCDateTimeRange *>(ref);
                CC_ASSERT(dateTimeRange);
                if (!timercmp(&now, &dateTimeRange->mStart, <) && !timercmp(&now, &dateTimeRange->mEnd, >)) {
                    CCSoomlaUtils::logDebug(TAG, "We are just in one of the time spans, it can't get any better then that. APPROVED!");
                    return true;
                }
            }

        // we don't need to continue if RequiredRecurrence is NONE
        if (mRequiredRecurrence->getValue() == Recurrence::NONE) {
            return false;
        }

        tm *ptm;

        ptm = localtime(&now.tv_sec);
        tm nowTm = *ptm;

        CCARRAY_FOREACH(mTimeRanges, ref) {
                dateTimeRange = dynamic_cast<CCDateTimeRange *>(ref);

                ptm = localtime(&dateTimeRange->mStart.tv_sec);
                tm begTm = *ptm;

                ptm = localtime(&dateTimeRange->mEnd.tv_sec);
                tm endTm = *ptm;

                if (nowTm.tm_min >= begTm.tm_min && nowTm.tm_min <= endTm.tm_min) {
                    CCSoomlaUtils::logDebug(TAG, "Now is in one of the time ranges' minutes span.");

                    if (mRequiredRecurrence->getValue() == Recurrence::EVERY_HOUR) {
                        CCSoomlaUtils::logDebug(TAG, "It's a EVERY_HOUR recurrence. APPROVED!");
                        return true;
                    }

                    if (nowTm.tm_hour >= begTm.tm_hour && nowTm.tm_hour <= endTm.tm_hour) {
                        CCSoomlaUtils::logDebug(TAG, "Now is in one of the time ranges' hours span.");

                        if (mRequiredRecurrence->getValue() == Recurrence::EVERY_DAY) {
                            CCSoomlaUtils::logDebug(TAG, "It's a EVERY_DAY recurrence. APPROVED!");
                            return true;
                        }

                        if (nowTm.tm_wday >= begTm.tm_wday && nowTm.tm_wday <= endTm.tm_wday) {
                            CCSoomlaUtils::logDebug(TAG, "Now is in one of the time ranges' day-of-week span.");

                            if (mRequiredRecurrence->getValue() == Recurrence::EVERY_WEEK) {
                                CCSoomlaUtils::logDebug(TAG, "It's a EVERY_WEEK recurrence. APPROVED!");
                                return true;
                            }

                            if (nowTm.tm_mday >= begTm.tm_mday && nowTm.tm_mday <= endTm.tm_mday) {
                                CCSoomlaUtils::logDebug(TAG, "Now is in one of the time ranges' days span.");

                                if (mRequiredRecurrence->getValue() == Recurrence::EVERY_MONTH) {
                                    CCSoomlaUtils::logDebug(TAG, "It's a EVERY_MONTH recurrence. APPROVED!");
                                    return true;
                                }
                            }
                        }
                    }
                }
            }

        return false;
    }
}
