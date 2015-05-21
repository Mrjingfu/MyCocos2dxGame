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

#include "CCDomain.h"
#include "CCDomainHelper.h"
#include "CCCoreConsts.h"

cocos2d::__Array *soomla::CCDomain::getDomainsFromDictArray(cocos2d::__Array *dictArray) {
    return CCDomainHelper::getInstance()->getDomainsFromDictArray(dictArray);
}

cocos2d::__Array *soomla::CCDomain::getDictArrayFromDomains(cocos2d::__Array *domainArray) {
    return CCDomainHelper::getInstance()->getDictArrayFromDomains(domainArray);
}

cocos2d::__Dictionary *soomla::CCDomain::putTypeData(cocos2d::__Dictionary *dict, const char *type) {
    dict->setObject(cocos2d::__String::create(type), CCCoreConsts::JSON_JSON_TYPE);
    return dict;
}
