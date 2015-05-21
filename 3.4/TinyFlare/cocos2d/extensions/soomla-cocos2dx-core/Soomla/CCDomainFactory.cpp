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

#include "CCDomainFactory.h"
#include "CCCoreConsts.h"

USING_NS_CC;

using namespace soomla;

static CCDomainFactory *s_SharedDomainFactory = nullptr;

CCDomainFactory *CCDomainFactory::getInstance() {
    if (!s_SharedDomainFactory) {
        s_SharedDomainFactory = new CCDomainFactory();
    }

    return s_SharedDomainFactory;
}

void CCDomainFactory::registerCreator(const char *key, std::function<soomla::CCDomain *(__Dictionary *)> creator) {
    mCreators[key] = creator;
}

CCDomain * CCDomainFactory::createWithDictionary(__Dictionary *dict) {
    Ref *typeRef = dict->objectForKey(CCCoreConsts::JSON_JSON_TYPE);
    CC_ASSERT(typeRef != nullptr);
    __String *type = dynamic_cast<__String *>(typeRef);
    CC_ASSERT(type != nullptr);

    return this->createWithDictionaryAndType(dict, type->getCString());
}

soomla::CCDomain *CCDomainFactory::createWithDictionaryAndType(__Dictionary *dict, const char *type) {
    CC_ASSERT(type);
    if (type == nullptr) {
        return nullptr;
    }

    std::function<soomla::CCDomain *(__Dictionary *)> creator = mCreators[type];
    CC_ASSERT(creator);
    if (creator == nullptr) {
        return nullptr;
    }

    return creator(dict);
}
