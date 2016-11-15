LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/BackgroundLayer.cpp \
                   ../../Classes/BaseLayer.cpp \
                   ../../Classes/BaseObject.cpp \
                   ../../Classes/Bloomb.cpp \
                   ../../Classes/Bullet.cpp \
                   ../../Classes/Cannon.cpp \
                   ../../Classes/CircleBy.cpp \
                   ../../Classes/CurveBy.cpp \
                   ../../Classes/CutDown.cpp \
                   ../../Classes/Fish.cpp \
                   ../../Classes/FishLayer.cpp \
                   ../../Classes/GameData.cpp \
                   ../../Classes/GameHelper.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/Gold.cpp \
                   ../../Classes/Lightting.cpp \
                   ../../Classes/LoadingLayer.cpp \
                   ../../Classes/MenuLayer.cpp \
                   ../../Classes/Net.cpp \
                   ../../Classes/PaymentLayer.cpp \
                   ../../Classes/PayNodeFirst.cpp \
                   ../../Classes/PayNodeSecond.cpp \
                   ../../Classes/RotateWithAction.cpp \
                   ../../Classes/SettingLayer.cpp \
                   ../../Classes/Task.cpp
                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
