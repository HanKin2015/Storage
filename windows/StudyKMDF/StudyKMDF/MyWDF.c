#include <fltKernel.h>
#include <wdf.h>
#include <wdfdriver.h>
#include <wdfrequest.h>

#define MYWDF_KDEVICE  L"\\Device\\MyWDF_Device"	//�豸���ƣ������ں�ģʽ�µ���������ʹ��
#define MYWDF_LINKNAME L"\\DosDevices\\MyWDF_LINK"	//�������ӣ������û�ģʽ�µĳ������ʹ����������豸��

//�����ص�
static EVT_WDF_DRIVER_UNLOAD EvtDriverUnload;
EVT_WDF_DEVICE_FILE_CREATE EvtDeviceFileCreate;
EVT_WDF_FILE_CLOSE EvtFileClose;

//���������������õĵ�һ�����������ṩ�����̣������ʼ����������
NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS status;
	WDF_OBJECT_ATTRIBUTES object_attribs;

	//�����������
	WDF_DRIVER_CONFIG cfg;	//����������
	WDFDRIVER drv = NULL;	//wdf framework ��������

	//�豸�������
	PWDFDEVICE_INIT device_init = NULL;
	UNICODE_STRING ustring;
	WDF_FILEOBJECT_CONFIG f_cfg;
	WDFDEVICE control_device;

	//error C2220: ���汻��Ϊ���� - û�����ɡ�object���ļ�
	//PDEVICE_OBJECT dev = NULL;

	KdPrint(("DriverEntry �[[start]\n"));


	//��ʼ��WDF_DRIVER_CONFIG
	WDF_DRIVER_CONFIG_INIT(
		&cfg,
		NULL				//���ṩAddDevice����
	);
	cfg.DriverInitFlags = WdfDriverInitNonPnpDriver;	//ָ����pnp����
	cfg.DriverPoolTag = (ULONG)'PEPU';
	cfg.EvtDriverUnload = EvtDriverUnload;				//ָ��ж�غ���

	//�����κ�һ��WDF����һ��ʼ��Ҫ����һ��framework��������������������������������parent����
	//����һ��framework����������WDF�������棬WdfDriverCreate�Ǳ���Ҫ���õġ�
	//framework������������������wdf����ĸ����󣬻��仰˵framework����������wdf�������Ķ��㣬��û�и������ˡ�
	status = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &cfg, &drv);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("Create wdf driver object failed\n"));
		goto DriverEntry_Complete;
	}

	KdPrint(("Create wdf driver object successfully\n"));


	//����һ���豸

	//��Ҫ����һ���ڴ�WDFDEVICE_INIT,����ڴ��ڴ����豸��ʱ����õ���
	device_init = WdfControlDeviceInitAllocate(drv, &SDDL_DEVOBJ_SYS_ALL_ADM_RWX_WORLD_RW_RES_R);
	if (device_init == NULL)
	{
		KdPrint(("WdfControlDeviceInitAllocate failed\n"));
		status = STATUS_INSUFFICIENT_RESOURCES;
		goto DriverEntry_Complete;
	}

	//�����豸�����֣��ں�ģʽ�£���������: L"\\Device\\MyWDF_Device"
	RtlInitUnicodeString(&ustring, MYWDF_KDEVICE);

	//���豸���ִ���device_init��
	status = WdfDeviceInitAssignName(device_init, &ustring);

	if (!NT_SUCCESS(status))
	{
		KdPrint(("WdfDeviceInitAssignName failed\n"));
		goto DriverEntry_Complete;
	}

	KdPrint(("Device name Unicode string: %wZ (this name can only be used by other kernel mode code, like other drivers)\n", &ustring));

	//���û�ģʽ�Ĵ������CreateFile��CloseHandle��ʱ����2���ص��ᱻ����
	//����FILEOBJECT�����ļ�������FILECREATE,FILECLOSE�ص���
	WDF_FILEOBJECT_CONFIG_INIT(&f_cfg, EvtDeviceFileCreate, EvtFileClose, NULL);

	//��FILEOBJECT�����ô���device_init��
	WdfDeviceInitSetFileObjectConfig(device_init, &f_cfg, WDF_NO_OBJECT_ATTRIBUTES);

	//��ʼ���豸����
	WDF_OBJECT_ATTRIBUTES_INIT(&object_attribs);

	//����ǰ�洴����device_init������һ���豸. (control device)
	status = WdfDeviceCreate(&device_init, &object_attribs, &control_device);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("create device failed\n"));
		goto DriverEntry_Complete;
	}

	//�����������ӣ������û�ģʽ�µĳ������ʹ���������������Ǳ���ģ���Ȼ�û�ģʽ�µĳ����ܷ�������豸��
	RtlInitUnicodeString(&ustring, MYWDF_LINKNAME);
	status = WdfDeviceCreateSymbolicLink(control_device, &ustring);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("Failed to create Link\n"));
		goto DriverEntry_Complete;
	}

	KdPrint(("Create symbolic link successfully, %wZ (user mode code should use this name, like in CreateFile())\n", &ustring));

	WdfControlFinishInitializing(control_device);//�����豸��ɡ�

	/*******************************************
	��������Ǿͳɹ�������һ��control device��
	control device �ǲ�֧��png��power�ģ���������Ҳ����Ҫ�ֹ�ȥɾ����
	��Ϊframework�������ɾ������MSDN

	If your driver creates control device objects but does not create framework device objects that support PnP and power management,
	the driver does not have to delete the control device objects.

	In this case, the framework deletes the control device objects after the driver's EvtDriverUnload callback function returns.

	����ϸ�ڿ�MSDN,��
	http://msdn.microsoft.com/en-us/library/windows/hardware/ff545424(v=vs.85).aspx
	*******************************************/


	KdPrint(("Create device object successfully\n"));
	KdPrint(("DriverEntry succeeds [end]\n"));

DriverEntry_Complete:
	return status;
}

//����ж��
static VOID EvtDriverUnload(WDFDRIVER Driver)
{
	KdPrint(("unload driver\n"));
	KdPrint(("Doesn't need to clean up the devices, since we only have control device here\n"));
}/* EvtDriverUnload */

VOID EvtDeviceFileCreate(__in WDFDEVICE Device, __in WDFREQUEST Request, __in WDFFILEOBJECT FileObject)
{
	KdPrint(("EvtDeviceFileCreate"));
	WdfRequestComplete(Request, STATUS_SUCCESS);
}

VOID EvtFileClose(__in  WDFFILEOBJECT FileObject)
{
	KdPrint(("EvtFileClose"));
}
