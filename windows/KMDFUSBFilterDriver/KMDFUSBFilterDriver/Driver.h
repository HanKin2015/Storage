/*++

Module Name:

    driver.h

Abstract:

    This file contains the driver definitions.

Environment:

    Kernel-mode Driver Framework

--*/

#define INITGUID

#include <ntddk.h>
#include <wdf.h>
#include <usbspec.h>
#include <usb.h>
#include <wdfusb.h>

#include "device.h"
#include "queue.h"
#include "trace.h"
#include "Log.h"

EXTERN_C_START

//
// WDFDRIVER Events
//

DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD KMDFUSBFilterDriverEvtDeviceAdd;
EVT_WDF_OBJECT_CONTEXT_CLEANUP KMDFUSBFilterDriverEvtDriverContextCleanup;

typedef struct _KMDF_USB_DRIVER_DEVICE {
	//fido 功能设备对象
	DEVICE_OBJECT * fido;
	//pdo 物理设备对象
	DEVICE_OBJECT * pdo;
	//lowerFdo 下层功能设备对象
	DEVICE_OBJECT * lowerFdo;
	//removeLock IO锁
	IO_REMOVE_LOCK removeLock;
}KMDF_USB_DRIVER_DEVICE;

/**
* 设备指针获取设备类型回调
* @param	DriverObject	 驱动对象指针
* @param	DriverObject	 设备指针
* @retval	STATUS_SUCCESS	成功
* @retval	其他			失败
*/
NTSTATUS KMDFUSBFilterDriverAddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT pdo);

/**
* 标准的驱动Unload
*/
VOID KMDFUSBFilterDriverUnload(IN PDRIVER_OBJECT DriverObject);

/**
* 非过滤驱动修改块大小消息在这里Skip
* @param	fido			设备指针
* @param	irp				irp请求
* @retval	STATUS_SUCCESS	成功
* @retval	其他			失败
*/
NTSTATUS KMDFUSBFilterDriverDispatch(IN PDEVICE_OBJECT fido, IN PIRP irp);

/**
* 处理修改块大小消息
* @param	fido	设备指针
* @param	irp		irp请求
* @retval	STATUS_SUCCESS	成功
* @retval	其他			失败
*/
NTSTATUS KMDFUSBFilterDriverDispatchForPnp(IN PDEVICE_OBJECT fido, IN PIRP irp);

/**
* 设备指针获取设备类型回调
* @param	pdo	 设备指针
* @retval	返回设备类型
*/
ULONG GetDeviceTypeToUse(PDEVICE_OBJECT pdo);

//保存修改块大小设备信息的结构体
typedef struct _SF_STOR_FILTER_DEVICE {
	//fido 功能设备对象
	DEVICE_OBJECT * fido;
	//pdo 物理设备对象
	DEVICE_OBJECT * pdo;
	//lowerFdo 下层功能设备对象
	DEVICE_OBJECT * lowerFdo;
	//removeLock IO锁
	IO_REMOVE_LOCK removeLock;
}SF_STOR_FILTER_DEVICE;

EXTERN_C_END
