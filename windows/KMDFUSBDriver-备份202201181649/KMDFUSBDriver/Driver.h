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

#include "device.h"
#include "queue.h"
#include "trace.h"

EXTERN_C_START

//
// WDFDRIVER Events
//

DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD KMDFUSBDriverEvtDeviceAdd;
EVT_WDF_OBJECT_CONTEXT_CLEANUP KMDFUSBDriverEvtDriverContextCleanup;

typedef struct _KMDF_USB_DRIVER_DEVICE {
	//fido �����豸����
	DEVICE_OBJECT * fido;
	//pdo �����豸����
	DEVICE_OBJECT * pdo;
	//lowerFdo �²㹦���豸����
	DEVICE_OBJECT * lowerFdo;
	//removeLock IO��
	IO_REMOVE_LOCK removeLock;
}KMDF_USB_DRIVER_DEVICE;

/**
* �豸ָ���ȡ�豸���ͻص�
* @param	DriverObject	 ��������ָ��
* @param	DriverObject	 �豸ָ��
* @retval	STATUS_SUCCESS	�ɹ�
* @retval	����			ʧ��
*/
NTSTATUS KMDFUSBDriverAddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT pdo);

/**
* ��׼������Unload
*/
VOID KMDFUSBDriverUnload(IN PDRIVER_OBJECT DriverObject);

/**
* �ǹ��������޸Ŀ��С��Ϣ������Skip
* @param	fido			�豸ָ��
* @param	irp				irp����
* @retval	STATUS_SUCCESS	�ɹ�
* @retval	����			ʧ��
*/
NTSTATUS KMDFUSBDriverDispatch(IN PDEVICE_OBJECT fido, IN PIRP irp);

/**
* �����޸Ŀ��С��Ϣ
* @param	fido	�豸ָ��
* @param	irp		irp����
* @retval	STATUS_SUCCESS	�ɹ�
* @retval	����			ʧ��
*/
NTSTATUS KMDFUSBDriverDispatchForPnp(IN PDEVICE_OBJECT fido, IN PIRP irp);

/**
* �豸ָ���ȡ�豸���ͻص�
* @param	pdo	 �豸ָ��
* @retval	�����豸����
*/
ULONG GetDeviceTypeToUse(PDEVICE_OBJECT pdo);

EXTERN_C_END
