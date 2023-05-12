LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := remount_usbhid_driver
LOCAL_SRC_FILES := remount_usbhid_driver.c
LOCAL_SHARED_LIBRARIES := libusb1.0

include $(BUILD_EXECUTABLE)

