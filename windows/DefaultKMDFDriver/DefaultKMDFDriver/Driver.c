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
#pragma alloc_text (PAGE, DefaultKMDFDriverEvtDeviceAdd)
#pragma alloc_text (PAGE, DefaultKMDFDriverEvtDriverContextCleanup)
#endif

/**
* @���� ����豸
* @param Driver USB�豸����
* @param  DeviceInit �豸��ʼ�����
* @return STATUS_SUCCESS��ʾ�ɹ���������ʾʧ��
*/
static NTSTATUS DeviceAdd(
	IN WDFDRIVER        Driver,
	IN PWDFDEVICE_INIT  DeviceInit)
{
	WDF_OBJECT_ATTRIBUTES        deviceAttributes;
	WDFDEVICE                    device;
	WDF_IO_QUEUE_CONFIG          ioQueueConfig;
	WDF_PNPPOWER_EVENT_CALLBACKS pnpPowerCallbacks;
	ULONG                        returnSize;
	PCAMERA_EXTENSION            extension = NULL;
	NTSTATUS                     status = STATUS_SUCCESS;

	PAGED_CODE();

	L_FORCE_TRACE("DeviceAdd enter\n");

	WDF_PNPPOWER_EVENT_CALLBACKS_INIT(&pnpPowerCallbacks);
	pnpPowerCallbacks.EvtDevicePrepareHardware = PrepareHardware;
	WdfDeviceInitSetPnpPowerEventCallbacks(DeviceInit, &pnpPowerCallbacks);

	//���Ϊ��������
	WdfFdoInitSetFilter(DeviceInit);

	//�����豸������ص�
	WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&deviceAttributes,
		CAMERA_EXTENSION);
	deviceAttributes.EvtCleanupCallback = DeviceCleanup;

	status = WdfDeviceCreate(&DeviceInit, &deviceAttributes, &device);
	if (!NT_SUCCESS(status))
	{
		L_TRACE_ERR("WdfDeviceCreate failed 0x%x\n", status);
		return status;
	};

	extension = GetExtension(device);

	extension->ConfigSize = 0;
	extension->ConfigData = NULL;
	extension->DeviceData = NULL;
	extension->DeviceSize = 0;
	extension->IsInit = FALSE;
	extension->PhyDevice = NULL;
	extension->vendor = 0;
	extension->product = 0;

	memset(extension->DeviceName, 0, sizeof(extension->DeviceName));
	return status;
}

/**
* @����  ж������
* @param Driver USB�豸����
* @return ��
*/
static VOID DriverUnload(IN WDFDRIVER Driver)
{
	L_FORCE_TRACE("DriverUnload enter...........\r\n");
	SpecialDevDelAll();
	return;
}

/**
* @����  ������MAIN��ں���
* @param DriverObject USB�豸��������
* @param  RegistryPathע���·��
* @return STATUS_SUCCESS �������سɹ�����������ʧ��
*/
NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT  DriverObject,
    _In_ PUNICODE_STRING RegistryPath
    )
{
	KdPrint(("hejian [%s:%s:%d]\n", __FILE__, __FUNCTION__, __LINE__));

    WDF_DRIVER_CONFIG     config;
	WDFDRIVER             hDriver;
    NTSTATUS              status;

	WDF_DRIVER_CONFIG_INIT(&config, DeviceAdd);
	config.EvtDriverUnload = DriverUnload;

	status = WdfDriverCreate(DriverObject,
		RegistryPath,
		WDF_NO_OBJECT_ATTRIBUTES,
		&config,
		&hDriver);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("DriverCreate failed 0x%x\n", status));
		return status;
	};

	//HelpInitDeviceKeyName(hDriver, RegistryPath);

	status = DeviceListInit();
	if (!NT_SUCCESS(status))
	{
		L_TRACE_ERR("Init failed 0x%x\n", status);
	};

	//�����豸����
	SpecialDevInit();
	SpecialDevStaticAdd();
	HelpUpdatePoliyFromReg();

	status = CreateControlDevice(hDriver);
	if (!NT_SUCCESS(status))
	{
		L_TRACE_ERR("CreateDevice failed 0x%x\n", status);
	}
    return status;
}

NTSTATUS
DefaultKMDFDriverEvtDeviceAdd(
    _In_    WDFDRIVER       Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
    )
{
	KdPrint(("hejian [%s:%s:%d]\n", __FILE__, __FUNCTION__, __LINE__));

    NTSTATUS status;

    UNREFERENCED_PARAMETER(Driver);

    PAGED_CODE();

    status = DefaultKMDFDriverCreateDevice(DeviceInit);
    return status;
}

VOID
DefaultKMDFDriverEvtDriverContextCleanup(
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
	KdPrint(("hejian [%s:%s:%d]\n", __FILE__, __FUNCTION__, __LINE__));

    UNREFERENCED_PARAMETER(DriverObject);

    PAGED_CODE ();
}
