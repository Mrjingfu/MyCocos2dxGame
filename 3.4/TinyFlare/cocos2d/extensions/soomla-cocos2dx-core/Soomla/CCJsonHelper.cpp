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

#include "CCJsonHelper.h"

USING_NS_CC;
using namespace std;

Ref *CCJsonHelper::getCCObjectFromJson(json_t *obj) {
    if (obj == NULL) {
        return NULL;
    }

    if (json_is_object(obj)) {
        __Dictionary *dictionary = __Dictionary::create();

        const char *key;
        json_t *value;

        void *iter = json_object_iter(obj);
        while (iter) {
            key = json_object_iter_key(iter);
            value = json_object_iter_value(iter);

            dictionary->setObject(CCJsonHelper::getCCObjectFromJson(value), string(key));

            iter = json_object_iter_next(obj, iter);
        }

        return dictionary;
    }
    else if (json_is_array(obj)) {
        size_t sizeArray = json_array_size(obj);
        __Array *array = __Array::createWithCapacity(sizeArray);

        for (unsigned int i = 0; i < sizeArray; i++) {
            array->addObject(CCJsonHelper::getCCObjectFromJson(json_array_get(obj, i)));
        }

        return array;
    }
    else if (json_is_boolean(obj)) {
        __Bool *ccBool = __Bool::create(json_is_true(obj));
        return ccBool;
    }
    else if (json_is_integer(obj)) {
        json_int_t intVal = json_integer_value(obj);

        __Integer *__Integer = __Integer::create((int) intVal);
        return __Integer;
    }
    else if (json_is_real(obj)) {
        double realVal = json_real_value(obj);

        __Double *ccDouble = __Double::create(realVal);
        return ccDouble;
    }
    else if (json_is_string(obj)) {
        stringstream str;
        str << json_string_value(obj);

        __String *__String = __String::create(str.str());
        return __String;
    }
    else if (json_is_null(obj)) {
        return __String::create("");
    }
    else {
        CC_ASSERT(false);
        return NULL;
    }
}

json_t*CCJsonHelper::getJsonFromCCObject(Ref* obj) {
    if (dynamic_cast<__Dictionary *>(obj)) {
        __Dictionary *mainDict = (__Dictionary *) obj;
        __Array *allKeys = mainDict->allKeys();
        json_t *jsonDict = json_object();

        if (allKeys == NULL ) return jsonDict;
        for (unsigned int i = 0; i < allKeys->count(); i++) {
            const char *key = ((__String *) allKeys->getObjectAtIndex(i))->getCString();
            json_object_set_new(jsonDict,
                    key,
                    CCJsonHelper::getJsonFromCCObject(mainDict->objectForKey(key)));
        }

        return jsonDict;
    }
    else if (dynamic_cast<__Array *>(obj)) {
        __Array *mainArray = (__Array *) obj;
        json_t *jsonArray = json_array();

        for (unsigned int i = 0; i < mainArray->count(); i++) {
            json_array_append_new(jsonArray,
                    CCJsonHelper::getJsonFromCCObject(mainArray->getObjectAtIndex(i)));
        }

        return jsonArray;
    }
    else if (dynamic_cast<__String *>(obj)) {
        __String *mainString = (__String *) obj;
        json_t *jsonString = json_string(mainString->getCString());

        return jsonString;
    }
    else if (dynamic_cast<__Integer *>(obj)) {
        __Integer *mainInteger = (__Integer *) obj;
        json_t *jsonInt = json_integer(mainInteger->getValue());

        return jsonInt;
    }
    else if (dynamic_cast<__Double *>(obj)) {
        __Double *mainDouble = (__Double *) obj;
        json_t *jsonReal = json_real(mainDouble->getValue());

        return jsonReal;
    }
    else if (dynamic_cast<__Float *>(obj)) {
        __Float *mainFloat = (__Float *) obj;
        json_t *jsonString = json_real(mainFloat->getValue());

        return jsonString;
    }
    else if (dynamic_cast<__Bool *>(obj)) {
        __Bool *mainBool = (__Bool *) obj;
        json_t *jsonBoolean = json_boolean(mainBool->getValue());

        return jsonBoolean;
    }
    else {
        CC_ASSERT(false);
        return NULL;
    }
}
