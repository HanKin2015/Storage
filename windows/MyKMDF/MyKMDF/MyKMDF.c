#include <fltKernel.h>
#include <wdf.h>
#include <wdfdriver.h>
#include <wdfrequest.h>

#define MYWDF_KDEVICE L"\\Device\\MyWDF_Device"//�豸���ƣ������ں�ģʽ�µ���������ʹ��
#define MYWDF_LINKNAME L"\\DosDevices\\MyWDF_LINK"//�������ӣ������û�ģʽ�µĳ������ʹ����������豸��

typedef struct
{
	WDFQUEUE _DefaultQueue;
	char _Buffer[100];
}DEVICE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE(DEVICE_CONTEXT);

/* f149fe88-f6cc-47e3-8594-e2aab6e03bdf */
DEFINE_GUID(GUID_DEVCLASS_MYUNIQUEID,
	0xf149fe88, 0xf6cc, 0x47e3, 0x85, 0x94, 0xe2, 0xaa, 0xb6, 0xe0, 0x3b, 0xdf);

//�����ص�
static EVT_WDF_DRIVER_UNLOAD EvtDriverUnload;
EVT_WDF_DEVICE_FILE_CREATE EvtDeviceFileCreate;
EVT_WDF_FILE_CLOSE EvtFileClose;

static EVT_WDF_IO_QUEUE_IO_DEFAULT EvtIoPDPControlDevice;

//�������
NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS status;
	WDF_OBJECT_ATTRIBUTES object_attribs;

	//�����������
	WDF_DRIVER_CONFIG cfg;	//����������
	WDFDRIVER drv = NULL;	//wdf framework ��������

	//�豸�������
	PWDFDEVICE_INIT DeviceInit = NULL;
	UNICODE_STRING ustring;
	WDF_FILEOBJECT_CONFIG f_cfg;
	WDFDEVICE control_device;
	PDEVICE_OBJECT dev = NULL;
	DEVICE_CONTEXT* dev_ctx = NULL;

	//IO QUEUE���
	WDF_IO_QUEUE_CONFIG qcfg;

	KdPrint(("DriverEntry [start]\n"));

	//��ʼ��WDF_DRIVER_CONFIG
	WDF_DRIVER_CONFIG_INIT(
		&cfg,
		NULL				//���ṩAddDevice����
	);

	cfg.DriverInitFlags = WdfDriverInitNonPnpDriver;  //ָ����pnp����
	cfg.DriverPoolTag = (ULONG)'PEPU';
	cfg.EvtDriverUnload = EvtDriverUnload;				//ָ��ж�غ���

	//����һ��framework����������WDF�������棬WdfDriverCreate�Ǳ���Ҫ���õġ�
	//framework������������������wdf����ĸ����󣬻��仰˵framework����������wdf�������Ķ��㣬��û�и������ˡ�
	status = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &cfg, &drv);
	if (!NT_SUCCESS(status))
	{
		goto DriverEntry_Complete;
	}

	KdPrint(("Create wdf driver object successfully\n"));

	//����һ���豸

	//��Ҫ����һ���ڴ�WDFDEVICE_INIT,����ڴ��ڴ����豸��ʱ����õ���
	DeviceInit = WdfControlDeviceInitAllocate(drv, &SDDL_DEVOBJ_SYS_ALL_ADM_RWX_WORLD_RW_RES_R);
	if (DeviceInit == NULL)
	{
		status = STATUS_INSUFFICIENT_RESOURCES;
		goto DriverEntry_Complete;
	}

	//�����豸�����֣��ں�ģʽ�£���������: L"\\Device\\MyWDF_Device"
	RtlInitUnicodeString(&ustring, MYWDF_KDEVICE);

	//���豸���ִ���device_init��
	status = WdfDeviceInitAssignName(DeviceInit, &ustring);

	//���豸��������GUID
	WdfDeviceInitSetDeviceClass(
		DeviceInit,
		&GUID_DEVCLASS_MYUNIQUEID
	);

	if (!NT_SUCCESS(status))
	{
		goto DriverEntry_Complete;
	}

	KdPrint(("Device name Unicode string: %wZ (this name can only be used by other kernel mode code, like other drivers)\n", &ustring));

	//����FILEOBJECT�����ļ�������FILECREATE,FILECLOSE�ص���
	WDF_FILEOBJECT_CONFIG_INIT(&f_cfg, EvtDeviceFileCreate, EvtFileClose, NULL);

	//��FILEOBJECT�����ô���device_init��
	WdfDeviceInitSetFileObjectConfig(DeviceInit, &f_cfg, WDF_NO_OBJECT_ATTRIBUTES);

	//��ʼ���豸����
	//WDF_OBJECT_ATTRIBUTES_INIT(&object_attribs);

	//���豸������������һ��DEVICE_CONTEXT,��WDF_OBJECT_ATTRIBUTES_INIT��ȣ�WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE
	//�����һ���ڴ沢�Ҵ���WDF_OBJECT_ATTRIBUTES���� (object_attribs.ContextTypeInfo)��DEVICE_CONEXT�Ǹ��Զ���ṹ��
	WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&object_attribs, DEVICE_CONTEXT);

	//����ǰ�洴����device_init������һ���豸. (control device)
	status = WdfDeviceCreate(&DeviceInit, &object_attribs, &control_device);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("create device failed\n"));
		goto DriverEntry_Complete;
	}

	//�õ��豸��������
	dev_ctx = WdfObjectGetTypedContext(control_device, DEVICE_CONTEXT);
	RtlZeroMemory(dev_ctx, sizeof(DEVICE_CONTEXT));

	//����IO queue

	//��ʼ��IO QUEUE CONFIG, WdfIoQueueDispatchParallel��˼��
	//The framework presents requests to the driver's request handlers as soon as the requests are available. 
	WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&qcfg, WdfIoQueueDispatchParallel);
	qcfg.PowerManaged = WdfFalse;  //��pnp�����������Դ����
	qcfg.EvtIoDefault = EvtIoPDPControlDevice;

	//���豸control_device����IO QUEUE
	status = WdfIoQueueCreate(control_device, &qcfg, WDF_NO_OBJECT_ATTRIBUTES, &dev_ctx->_DefaultQueue);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("Create IoQueue failed, %x\n", status));
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

	WdfControlFinishInitializing(control_device);	//�����豸��ɡ�

	/*******************************************
	��������Ǿͳɹ�������һ��control device��
	control device �ǲ�֧��png��power�ģ���������Ҳ����Ҫ�ֹ���ɾ����
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

//����������һ���򵥵Ĺ��ܣ���WRITE���������д���豸�����ģ�Ȼ����READ���������ʱ�򣬽��豸��������������ݶ����������Ҵ���READ�����������塣
static VOID EvtIoPDPControlDevice(WDFQUEUE Queue, WDFREQUEST Request)
{
	WDF_REQUEST_PARAMETERS Params;
	WDFREQUEST req;
	NTSTATUS status;
	WDFDEVICE  hDevice;
	DEVICE_CONTEXT* dev_ctx = NULL;

	//buffer
	char* in_buf = NULL;
	char* out_buf = NULL;

	//��WDFREQUEST�����ȡ����
	WDF_REQUEST_PARAMETERS_INIT(&Params);
	WdfRequestGetParameters(Request, &Params);

	KdPrint(("EvtIoPDPControlDevice, type: %x\n", Params.Type));

	//��ȡinput���壬���request������WdfRequestTypeRead����ô�ͷ���STATUS_INVALID_DEVICE_REQUEST
	//��ΪWdfRequestTypeRead���͵�Requestû��input buffer��ֻ��outputbuffer��
	status = WdfRequestRetrieveInputBuffer(Request, 10, &in_buf, NULL);

	KdPrint(("Get input buffer, ret: %x, buffer: %x", status, in_buf));

	//��ȡoutput���壬�����WdfRequestTypeWrite����û��������壬��Ϊwriteֻ�����뻺�塣
	status = WdfRequestRetrieveOutputBuffer(Request, 10, &out_buf, NULL);

	KdPrint(("Get output buffer, ret: %x, buffer: %x", status, out_buf));

	//��ȡQueue�������豸����
	hDevice = WdfIoQueueGetDevice(Queue);

	//��ȡ�豸�����������
	dev_ctx = WdfObjectGetTypedContext(hDevice, DEVICE_CONTEXT);

	KdPrint(("Get the context of current device, %x", dev_ctx));


	switch (Params.Type)
	{
	case WdfRequestTypeRead:
		{
			if (out_buf != NULL)
			{
				out_buf[0] = '1';

				KdPrint(("write the data in context buffer into READ request\n"));

				//���豸���������������д��Read����Ļ�������
				RtlCopyMemory(out_buf, dev_ctx->_Buffer, 10);

				WdfRequestCompleteWithInformation(Request, STATUS_SUCCESS, 10);
			}
		}
		break;
	case WdfRequestTypeWrite:
	{
		if (in_buf != NULL)
		{
			KdPrint(("input buffer, first element: %c\n", in_buf[0]));

			//��write���������д���豸������
			RtlCopyMemory(dev_ctx->_Buffer, in_buf, 10);

			WdfRequestComplete(Request, STATUS_SUCCESS);
		}
	}
	break;
	default:
		WdfRequestComplete(Request, STATUS_SUCCESS);
		break;
	}
}