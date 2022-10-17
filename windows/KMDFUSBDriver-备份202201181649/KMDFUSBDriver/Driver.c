/*++

Module Name:

    driver.c

Abstract:

    This file contains the driver entry points and callbacks.

Environment:

    Kernel-mode Driver Framework

--*/

#include "driver.h"
#include "driver.tmh"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, GetDeviceTypeToUse)
#pragma alloc_text (PAGE, KMDFUSBDriverDispatch)
#pragma alloc_text (PAGE, KMDFUSBDriverDispatchForPnp)
#pragma alloc_text (PAGE, KMDFUSBDriverEvtDeviceAdd)
#pragma alloc_text (PAGE, KMDFUSBDriverUnload)

#endif


NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT  DriverObject,
    _In_ PUNICODE_STRING RegistryPath
    )
/*++

Routine Description:
    DriverEntry initializes the driver and is the first routine called by the
    system after the driver is loaded. DriverEntry specifies the other entry
    points in the function driver, such as EvtDevice and DriverUnload.

Parameters Description:

    DriverObject - represents the instance of the function driver that is loaded
    into memory. DriverEntry must initialize members of DriverObject before it
    returns to the caller. DriverObject is allocated by the system before the
    driver is loaded, and it is released by the system after the system unloads
    the function driver from memory.

    RegistryPath - represents the driver specific path in the Registry.
    The function driver can use the path to store driver related data between
    reboots. The path does not store hardware instance specific data.

Return Value:

    STATUS_SUCCESS if successful,
    STATUS_UNSUCCESSFUL otherwise.

--*/
{
	KdPrint(("hejian 6 %s:%d", __FUNCTION__, __LINE__));

	UNREFERENCED_PARAMETER(RegistryPath);
	if (NULL == DriverObject)
	{
		KdPrint(("Parameter is null"));
		return STATUS_UNSUCCESSFUL;
	}

	//所有设备都会走的流程
	DriverObject->DriverUnload = KMDFUSBDriverUnload;
	DriverObject->DriverExtension->AddDevice = KMDFUSBDriverAddDevice;

	//IRP_MJ_MAXIMUM_FUNCTION
	int nMajorSize = ARRAYSIZE(DriverObject->MajorFunction);
	KdPrint(("hejian %s:%d nMajorSize:%d", __FUNCTION__, __LINE__, nMajorSize));

	//这些消息都不需要处理给下层驱动
	for (int i = 0; i < nMajorSize; i++)
	{
		DriverObject->MajorFunction[i] = KMDFUSBDriverDispatch;
	}

	//IRP_MJ_PNP：即插即用管理，处理这个消息修改块大小
	DriverObject->MajorFunction[IRP_MJ_PNP] = KMDFUSBDriverDispatchForPnp;

	KdPrint(("hejian %s:%d", __FUNCTION__, __LINE__));
    return STATUS_SUCCESS;
}

NTSTATUS
KMDFUSBDriverEvtDeviceAdd(
    _In_    WDFDRIVER       Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
    )
/*++
Routine Description:

    EvtDeviceAdd is called by the framework in response to AddDevice
    call from the PnP manager. We create and initialize a device object to
    represent a new instance of the device.

Arguments:

    Driver - Handle to a framework driver object created in DriverEntry

    DeviceInit - Pointer to a framework-allocated WDFDEVICE_INIT structure.

Return Value:

    NTSTATUS

--*/
{
	KdPrint(("hejian %s:%d", __FUNCTION__, __LINE__));

    NTSTATUS status;

    UNREFERENCED_PARAMETER(Driver);

    PAGED_CODE();

    status = KMDFUSBDriverCreateDevice(DeviceInit);

    return status;
}

VOID
KMDFUSBDriverEvtDriverContextCleanup(
    _In_ WDFOBJECT DriverObject
    )
/*++
Routine Description:

    Free all the resources allocated in DriverEntry.

Arguments:

    DriverObject - handle to a WDF Driver object.

Return Value:

    VOID.

--*/
{
	KdPrint(("hejian %s:%d", __FUNCTION__, __LINE__));

    UNREFERENCED_PARAMETER(DriverObject);

    PAGED_CODE ();
}

//驱动卸载
VOID KMDFUSBDriverUnload(IN PDRIVER_OBJECT pDriverObject)
{
	KdPrint(("hejian %s:%d", __FUNCTION__, __LINE__));
}

//获取设备类型
ULONG GetDeviceTypeToUse(PDEVICE_OBJECT pdo)
{
	KdPrint(("hejian %s:%d", __FUNCTION__, __LINE__));

	if (NULL == pdo)
	{
		KdPrint(("Parameter is null"));
		return FILE_DEVICE_UNKNOWN;
	}

	//获取顶层设备指针
	PDEVICE_OBJECT ldo = IoGetAttachedDeviceReference(pdo);
	PAGED_CODE();

	if (NULL == ldo)
	{
		KdPrint(("ldo is null"));
		return FILE_DEVICE_UNKNOWN;
	}

	ULONG devtype = ldo->DeviceType;
	(VOID)ObDereferenceObject(ldo);
	return devtype;
}

//设备是否支持
NTSTATUS IsSupportedDevice(__in PDEVICE_OBJECT pdo)
{
	KdPrint(("hejian %s:%d", __FUNCTION__, __LINE__));

	if (NULL == pdo)
	{
		KdPrint(("Parameter is null"));
		return STATUS_UNSUCCESSFUL;
	}
	return STATUS_SUCCESS;
}

//创建设备
NTSTATUS KMDFUSBDriverAddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT pdo)
{
	KdPrint(("hejian %s:%d", __FUNCTION__, __LINE__));

	if (NULL == DriverObject || NULL == pdo)
	{
		KdPrint(("Parameter is null"));
		return STATUS_UNSUCCESSFUL;
	}

	NTSTATUS status = STATUS_SUCCESS;
	DEVICE_OBJECT *fido = NULL;

	PAGED_CODE();
	//根据驱动对象和设备类型创建设备
	status = IoCreateDevice(DriverObject,
		sizeof(KMDF_USB_DRIVER_DEVICE),
		NULL,
		GetDeviceTypeToUse(pdo),
		0,
		FALSE,
		&fido);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("IoCreateDevice failed"));
		return status;
	}
	if (NULL == fido)
	{
		KdPrint(("fido is null"));
		return STATUS_UNSUCCESSFUL;
	}

	//DeviceExtension指向驱动的扩展，使用RemoveLock防止奔溃
	KMDF_USB_DRIVER_DEVICE *sfdisk = (KMDF_USB_DRIVER_DEVICE*)fido->DeviceExtension;
	if (NULL == sfdisk)
	{
		KdPrint(("sfdisk is null"));
		return STATUS_UNSUCCESSFUL;
	}

	(VOID)IoInitializeRemoveLock(&sfdisk->removeLock, 0, 0, 0);
	sfdisk->fido = fido;
	sfdisk->pdo = pdo;

	//判断设备是否开启加速
	if (STATUS_SUCCESS != IsSupportedDevice(pdo))
	{
		KdPrint(("Device not support speed up"));
		status = STATUS_DEVICE_REMOVED;
		return status;
	}

	//将设备添加到设备栈
	sfdisk->lowerFdo = IoAttachDeviceToDeviceStack(fido, pdo);
	if (NULL == sfdisk->lowerFdo)
	{
		KdPrint(("IoAttachDeviceToDeviceStack failed, lowerFdo is null"));
		status = STATUS_DEVICE_REMOVED;
		if (sfdisk->lowerFdo)
			(VOID)IoDetachDevice(sfdisk->lowerFdo);
		(VOID)IoDeleteDevice(fido);
		return status;
	}

	//DO_DIRECT_IO 常用于传输大块的讲求速度的数据。DO_BUFFERED_IO常用于传输小块的，慢速的数据
	fido->Flags |= sfdisk->lowerFdo->Flags & (DO_DIRECT_IO | DO_BUFFERED_IO | DO_POWER_PAGABLE);
	//在初始化设备对象之后到从例程返回之前清除 DO_DEVICE_INITIALIZING
	fido->Flags &= ~DO_DEVICE_INITIALIZING;

	return status;
}

NTSTATUS KMDFUSBDriverDispatch(IN DEVICE_OBJECT *fido, IN PIRP irp)
{
	KdPrint(("hejian %s:%d", __FUNCTION__, __LINE__));

	if (NULL == fido || NULL == irp)
	{
		KdPrint(("Parameter is null"));
		return STATUS_UNSUCCESSFUL;
	}

	//DeviceExtension指向驱动的扩展
	NTSTATUS status = STATUS_SUCCESS;
	return status;
}

NTSTATUS KMDFUSBDriverDispatchForPnp(IN PDEVICE_OBJECT fido, IN PIRP irp)
{
	KdPrint(("hejian %s:%d", __FUNCTION__, __LINE__));

	if (NULL == fido || NULL == irp)
	{
		KdPrint(("Parameter is null"));
		return STATUS_UNSUCCESSFUL;
	}

	//获取当前IRP栈位置
	NTSTATUS status = STATUS_SUCCESS;
	return status;
}
