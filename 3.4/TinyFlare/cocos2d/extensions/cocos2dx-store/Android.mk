LOCAL_PATH := $(call my-dir)

# cocos2dx-store
include $(CLEAR_VARS)

COCOS2D_JAVASCRIPT = $(filter %-DCOCOS2D_JAVASCRIPT,$(APP_CPPFLAGS))

#$(call __ndk_warning,COCOS2D_JAVASCRIPT: "$(COCOS2D_JAVASCRIPT)")
#$(call __ndk_warning,APP_CPPFLAGS: "$(APP_CPPFLAGS)")

LOCAL_MODULE := cocos2dx_store_static
LOCAL_MODULE_FILENAME := libcocos2dxstore

STORE_SRC_LIST := $(wildcard $(LOCAL_PATH)/Soomla/*.cpp)
STORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/NativeImpl/*.cpp)
STORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/PurchaseTypes/*.cpp)
STORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/data/*.cpp)
STORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/domain/*.cpp)
STORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/domain/virtualCurrencies/*.cpp)
STORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/domain/virtualGoods/*.cpp)
STORE_SRC_LIST += $(wildcard $(LOCAL_PATH)/Soomla/rewards/*.cpp)

LOCAL_SRC_FILES := $(STORE_SRC_LIST:$(LOCAL_PATH)/%=%)


ifneq '$(COCOS2D_JAVASCRIPT)' ''
LOCAL_SRC_FILES +=  \
        Soomla/jsb/jsb_soomla.cpp \
        Soomla/jsb/JSBinding.cpp
endif

LOCAL_C_INCLUDES := $(LOCAL_PATH)/Soomla
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/data
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/domain
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/domain/virtualCurrencies
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/domain/virtualGoods
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/jsb
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/PurchaseTypes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/NativeImpl
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Soomla/rewards
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../lib \
        $(LOCAL_PATH)/../../../bindings/manual

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_soomla_common_static

ifneq '$(COCOS2D_JAVASCRIPT)' ''
LOCAL_WHOLE_STATIC_LIBRARIES += spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += scriptingcore-spidermonkey
endif

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/data
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/domain
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/domain/virtualCurrencies
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/domain/virtualGoods
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/jsb
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/PurchaseTypes
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/Soomla/rewards

include $(BUILD_STATIC_LIBRARY)

$(call import-module,extensions/soomla-cocos2dx-core)

ifneq '$(COCOS2D_JAVASCRIPT)' ''
$(call import-module,external/spidermonkey/prebuilt/android)
$(call import-module,bindings)
endif
