LOCAL_PATH := $(call my-dir)

# cocos2dx-soomla-common
include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_soomla_common_static
LOCAL_MODULE_FILENAME := libcocos2dxsoomlacommon

CORE_SRC_LIST := $(wildcard $(LOCAL_PATH)/Soomla/*.cpp)
CORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/domain/*.cpp)
CORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/data/*.cpp)
CORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/rewards/*.cpp)
CORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/NativeImpl/*.cpp)

LOCAL_SRC_FILES := $(CORE_SRC_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/Soomla
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/data
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/domain
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/rewards
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/NativeImpl

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += jansson_static


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/data
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/domain
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/rewards
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/NativeImpl

include $(BUILD_STATIC_LIBRARY)

$(call import-module,external/jansson)
