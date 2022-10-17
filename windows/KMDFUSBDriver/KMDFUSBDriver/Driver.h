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
#include <usb.h>
#include <usbdlib.h>
#include <wdfusb.h>
#include <wdfobject.h>

#include "device.h"
#include "queue.h"
#include "trace.h"
#include "Log.h"

EXTERN_C_START

//
// WDFDRIVER Events
//

DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD KMDFUSBDriverEvtDeviceAdd;
EVT_WDF_OBJECT_CONTEXT_CLEANUP KMDFUSBDriverEvtDriverContextCleanup;

#define DEVICE_NAME_LEN    128
#define MAX_PATH           1024
typedef struct
{
	WDFUSBDEVICE    UsbDevice;
	unsigned short  vendor;
	unsigned short  product;
	BOOLEAN         IsInit;
	WCHAR           DeviceName[DEVICE_NAME_LEN];
	PDEVICE_OBJECT  PhyDevice;
	int             ConfigSize;
	unsigned char  *ConfigData;
	int             DeviceSize;
	unsigned char  *DeviceData;
}CAMERA_EXTENSION, *PCAMERA_EXTENSION;
WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(CAMERA_EXTENSION, GetExtension)

/**
* @描述  卸载驱动
* @param Driver USB设备驱动
* @return 无
*/
static VOID KMDFUSBDriverUnload(IN WDFDRIVER Driver);

/**
* 标准的驱动Unload
*/
VOID KMDFUSBFilterDriverUnload(IN PDRIVER_OBJECT DriverObject);
EXTERN_C_END
