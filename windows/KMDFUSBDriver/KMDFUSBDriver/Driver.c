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
#pragma alloc_text (PAGE, KMDFUSBDriverEvtDeviceAdd)
#pragma alloc_text (PAGE, KMDFUSBDriverEvtDriverContextCleanup)
#pragma alloc_text (PAGE, KMDFUSBFilterDriverUnload)
#pragma alloc_text (PAGE, KMDFUSBDriverUnload)
#endif

/**
* @描述   驱动的MAIN入口函数
* @param  DriverObject   USB设备驱动对象
* @param  RegistryPath   注册表路径
* @return STATUS_SUCCESS 驱动加载成功，其它加载失败
*/
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
	// 注意需要添加换行符
	//KdPrint(("hejian %s:%d\n", __FUNCTION__, __LINE__));

	Info("10086");

    WDF_DRIVER_CONFIG config;
    NTSTATUS status;
    WDF_OBJECT_ATTRIBUTES attributes;

    //
    // Register a cleanup callback so that we can call WPP_CLEANUP when
    // the framework driver object is deleted during driver unload.
    //
    WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
    attributes.EvtCleanupCallback = KMDFUSBDriverEvtDriverContextCleanup;

    WDF_DRIVER_CONFIG_INIT(&config,
                           KMDFUSBDriverEvtDeviceAdd
                           );
	config.EvtDriverUnload = KMDFUSBDriverUnload;

    status = WdfDriverCreate(DriverObject,
                             RegistryPath,
                             //&attributes,	// WDF_NO_OBJECT_ATTRIBUTES
							WDF_NO_OBJECT_ATTRIBUTES,
                             &config,
                             WDF_NO_HANDLE
                             );

    if (!NT_SUCCESS(status)) {
		Err("%s:%d WdfDriverCreate failed", __FUNCTION__, __LINE__);
        return status;
    }

	Info("status:%d", status);
	return status;
}

/**
* @描述   添加设备
* @param  Driver     USB设备驱动
* @param  DeviceInit 设备初始化句柄
* @return STATUS_SUCCESS表示成功，其它表示失败
*/
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
	Info("");

	NTSTATUS status = STATUS_SUCCESS;

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
	Info("");

    UNREFERENCED_PARAMETER(DriverObject);
    PAGED_CODE ();
}

/**
* @描述  卸载驱动
* @param Driver USB设备驱动
* @return 无
*/
static VOID KMDFUSBDriverUnload(IN WDFDRIVER Driver)
{
	Info("");

	if (NULL == Driver)
	{
		Err("Entering KMDFUSBDriverUnload fail, parameter is null");
		return;
	}

	PAGED_CODE();
	Info("Entering KMDFUSBDriverUnload: Driver %8.8lX", Driver);
}

//驱动卸载
VOID KMDFUSBFilterDriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	Info("");

	if (NULL == DriverObject)
	{
		Err("Entering DriverUnload fail, parameter is null");
		return;
	}

	PAGED_CODE();
	Info("Entering DriverUnload: DriverObject %8.8lX", DriverObject);
}

