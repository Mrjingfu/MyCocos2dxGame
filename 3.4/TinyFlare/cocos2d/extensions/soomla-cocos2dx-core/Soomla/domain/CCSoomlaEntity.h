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

#ifndef __CCSoomlaEntity_H_
#define __CCSoomlaEntity_H_

#include "cocos2d.h"
#include "CCDomain.h"
#include "CCCoreConsts.h"
#include "CCSoomlaMacros.h"

namespace soomla {
    class CCSoomlaEntity: public CCDomain {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String*, mId, Id, CCCoreConsts::JSON_ITEM_ITEM_ID);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String*, mName, Name, CCCoreConsts::JSON_ITEM_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String*, mDescription, Description, CCCoreConsts::JSON_ITEM_DESCRIPTION);
    public:
        CCSoomlaEntity(): mId(NULL), mName(NULL), mDescription(NULL) {}

        virtual bool init(cocos2d::__String *id, cocos2d::__String *name = NULL, cocos2d::__String *description = NULL);
        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual ~CCSoomlaEntity();

        /**
        * Converts this `CCSoomlaEntity` to a `CCDictionary`.
        * @return `CCDictionary` representation of this `CCSoomlaEntity`.
        */
        virtual cocos2d::__Dictionary* toDictionary();

        virtual char const * getType() const = 0;

        virtual bool equals(cocos2d::Ref *obj) const;

        virtual CCSoomlaEntity *clone(const char *newId);
    };
}


#endif //__CCSoomlaEntity_H_
