#include <fltKernel.h>
#include <wdf.h>
#include <wdfdriver.h>
#include <wdfrequest.h>

#define MYWDF_KDEVICE L"\\Device\\MyWDF_Device"//设备名称，其他内核模式下的驱动可以使用
#define MYWDF_LINKNAME L"\\DosDevices\\MyWDF_LINK"//符号连接，这样用户模式下的程序可以使用这个驱动设备。

typedef struct
{
	WDFQUEUE _DefaultQueue;
	char _Buffer[100];
}DEVICE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE(DEVICE_CONTEXT);

/* f149fe88-f6cc-47e3-8594-e2aab6e03bdf */
DEFINE_GUID(GUID_DEVCLASS_MYUNIQUEID,
	0xf149fe88, 0xf6cc, 0x47e3, 0x85, 0x94, 0xe2, 0xaa, 0xb6, 0xe0, 0x3b, 0xdf);

//声明回调
static EVT_WDF_DRIVER_UNLOAD EvtDriverUnload;
EVT_WDF_DEVICE_FILE_CREATE EvtDeviceFileCreate;
EVT_WDF_FILE_CLOSE EvtFileClose;

static EVT_WDF_IO_QUEUE_IO_DEFAULT EvtIoPDPControlDevice;

//驱动入口
NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS status;
	WDF_OBJECT_ATTRIBUTES object_attribs;

	//驱动对象相关
	WDF_DRIVER_CONFIG cfg;	//驱动的配置
	WDFDRIVER drv = NULL;	//wdf framework 驱动对象

	//设备对象相关
	PWDFDEVICE_INIT DeviceInit = NULL;
	UNICODE_STRING ustring;
	WDF_FILEOBJECT_CONFIG f_cfg;
	WDFDEVICE control_device;
	PDEVICE_OBJECT dev = NULL;
	DEVICE_CONTEXT* dev_ctx = NULL;

	//IO QUEUE相关
	WDF_IO_QUEUE_CONFIG qcfg;

	KdPrint(("DriverEntry [start]\n"));

	//初始化WDF_DRIVER_CONFIG
	WDF_DRIVER_CONFIG_INIT(
		&cfg,
		NULL				//不提供AddDevice函数
	);

	cfg.DriverInitFlags = WdfDriverInitNonPnpDriver;  //指定非pnp驱动
	cfg.DriverPoolTag = (ULONG)'PEPU';
	cfg.EvtDriverUnload = EvtDriverUnload;				//指定卸载函数

	//创建一个framework驱动对象，在WDF程序里面，WdfDriverCreate是必须要调用的。
	//framework驱动对象是其他所有wdf对象的父对象，换句话说framework驱动对象是wdf对象树的顶点，它没有父对象了。
	status = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &cfg, &drv);
	if (!NT_SUCCESS(status))
	{
		goto DriverEntry_Complete;
	}

	KdPrint(("Create wdf driver object successfully\n"));

	//创建一个设备

	//先要分配一块内存WDFDEVICE_INIT,这块内存在创建设备的时候会用到。
	DeviceInit = WdfControlDeviceInitAllocate(drv, &SDDL_DEVOBJ_SYS_ALL_ADM_RWX_WORLD_RW_RES_R);
	if (DeviceInit == NULL)
	{
		status = STATUS_INSUFFICIENT_RESOURCES;
		goto DriverEntry_Complete;
	}

	//创建设备的名字，内核模式下，名字类似: L"\\Device\\MyWDF_Device"
	RtlInitUnicodeString(&ustring, MYWDF_KDEVICE);

	//将设备名字存入device_init中
	status = WdfDeviceInitAssignName(DeviceInit, &ustring);

	//给设备设置类型GUID
	WdfDeviceInitSetDeviceClass(
		DeviceInit,
		&GUID_DEVCLASS_MYUNIQUEID
	);

	if (!NT_SUCCESS(status))
	{
		goto DriverEntry_Complete;
	}

	KdPrint(("Device name Unicode string: %wZ (this name can only be used by other kernel mode code, like other drivers)\n", &ustring));

	//配置FILEOBJECT配置文件，设置FILECREATE,FILECLOSE回调。
	WDF_FILEOBJECT_CONFIG_INIT(&f_cfg, EvtDeviceFileCreate, EvtFileClose, NULL);

	//将FILEOBJECT的设置存入device_init中
	WdfDeviceInitSetFileObjectConfig(DeviceInit, &f_cfg, WDF_NO_OBJECT_ATTRIBUTES);

	//初始化设备属性
	//WDF_OBJECT_ATTRIBUTES_INIT(&object_attribs);

	//在设备属性里面增加一个DEVICE_CONTEXT,跟WDF_OBJECT_ATTRIBUTES_INIT相比，WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE
	//会分配一块内存并且存入WDF_OBJECT_ATTRIBUTES里面 (object_attribs.ContextTypeInfo)。DEVICE_CONEXT是个自定义结构。
	WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&object_attribs, DEVICE_CONTEXT);

	//根据前面创建的device_init来创建一个设备. (control device)
	status = WdfDeviceCreate(&DeviceInit, &object_attribs, &control_device);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("create device failed\n"));
		goto DriverEntry_Complete;
	}

	//得到设备的上下文
	dev_ctx = WdfObjectGetTypedContext(control_device, DEVICE_CONTEXT);
	RtlZeroMemory(dev_ctx, sizeof(DEVICE_CONTEXT));

	//创建IO queue

	//初始化IO QUEUE CONFIG, WdfIoQueueDispatchParallel意思是
	//The framework presents requests to the driver's request handlers as soon as the requests are available. 
	WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&qcfg, WdfIoQueueDispatchParallel);
	qcfg.PowerManaged = WdfFalse;  //非pnp驱动，无需电源管理。
	qcfg.EvtIoDefault = EvtIoPDPControlDevice;

	//给设备control_device创建IO QUEUE
	status = WdfIoQueueCreate(control_device, &qcfg, WDF_NO_OBJECT_ATTRIBUTES, &dev_ctx->_DefaultQueue);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("Create IoQueue failed, %x\n", status));
		goto DriverEntry_Complete;
	}

	//创建符号连接，这样用户模式下的程序可以使用这个驱动。这个是必须的，不然用户模式下的程序不能访问这个设备。
	RtlInitUnicodeString(&ustring, MYWDF_LINKNAME);
	status = WdfDeviceCreateSymbolicLink(control_device, &ustring);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("Failed to create Link\n"));
		goto DriverEntry_Complete;
	}

	KdPrint(("Create symbolic link successfully, %wZ (user mode code should use this name, like in CreateFile())\n", &ustring));

	WdfControlFinishInitializing(control_device);	//创建设备完成。

	/*******************************************
	到这里，我们就成功创建了一个control device。
	control device 是不支持png和power的，而且我们也不需要手工是删除。
	因为framework会帮我们删除，看MSDN

	If your driver creates control device objects but does not create framework device objects that support PnP and power management,
	the driver does not have to delete the control device objects.

	In this case, the framework deletes the control device objects after the driver's EvtDriverUnload callback function returns.
	更多细节看MSDN,如
	http://msdn.microsoft.com/en-us/library/windows/hardware/ff545424(v=vs.85).aspx
	*******************************************/


	KdPrint(("Create device object successfully\n"));
	KdPrint(("DriverEntry succeeds [end]\n"));

DriverEntry_Complete:
	return status;
}

//驱动卸载
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

//给驱动增加一个简单的功能，将WRITE请求的数据写入设备上下文，然后当有READ请求过来的时候，将设备上下文里面的数据读出来，并且存入READ请求的输出缓冲。
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

	//从WDFREQUEST里面获取参数
	WDF_REQUEST_PARAMETERS_INIT(&Params);
	WdfRequestGetParameters(Request, &Params);

	KdPrint(("EvtIoPDPControlDevice, type: %x\n", Params.Type));

	//获取input缓冲，如果request类型是WdfRequestTypeRead，那么就返回STATUS_INVALID_DEVICE_REQUEST
	//因为WdfRequestTypeRead类型的Request没有input buffer，只有outputbuffer。
	status = WdfRequestRetrieveInputBuffer(Request, 10, &in_buf, NULL);

	KdPrint(("Get input buffer, ret: %x, buffer: %x", status, in_buf));

	//获取output缓冲，如果是WdfRequestTypeWrite，则没有输出缓冲，因为write只有输入缓冲。
	status = WdfRequestRetrieveOutputBuffer(Request, 10, &out_buf, NULL);

	KdPrint(("Get output buffer, ret: %x, buffer: %x", status, out_buf));

	//获取Queue关联的设备对象
	hDevice = WdfIoQueueGetDevice(Queue);

	//获取设备对象的上下文
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

				//将设备上下文里面的数据写入Read请求的缓冲里面
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

			//将write请求的数据写入设备上下文
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