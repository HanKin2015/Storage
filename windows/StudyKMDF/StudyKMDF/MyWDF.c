#include <fltKernel.h>
#include <wdf.h>
#include <wdfdriver.h>
#include <wdfrequest.h>

#define MYWDF_KDEVICE  L"\\Device\\MyWDF_Device"	//设备名称，其他内核模式下的驱动可以使用
#define MYWDF_LINKNAME L"\\DosDevices\\MyWDF_LINK"	//符号连接，这样用户模式下的程序可以使用这个驱动设备。

//声明回调
static EVT_WDF_DRIVER_UNLOAD EvtDriverUnload;
EVT_WDF_DEVICE_FILE_CREATE EvtDeviceFileCreate;
EVT_WDF_FILE_CLOSE EvtFileClose;

//加载驱动程序后调用的第一个驱动程序提供的例程，负责初始化驱动程序
NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS status;
	WDF_OBJECT_ATTRIBUTES object_attribs;

	//驱动对象相关
	WDF_DRIVER_CONFIG cfg;	//驱动的配置
	WDFDRIVER drv = NULL;	//wdf framework 驱动对象

	//设备对象相关
	PWDFDEVICE_INIT device_init = NULL;
	UNICODE_STRING ustring;
	WDF_FILEOBJECT_CONFIG f_cfg;
	WDFDEVICE control_device;

	//error C2220: 警告被视为错误 - 没有生成“object”文件
	//PDEVICE_OBJECT dev = NULL;

	KdPrint(("DriverEntry [start]\n"));


	//初始化WDF_DRIVER_CONFIG
	WDF_DRIVER_CONFIG_INIT(
		&cfg,
		NULL				//不提供AddDevice函数
	);
	cfg.DriverInitFlags = WdfDriverInitNonPnpDriver;	//指定非pnp驱动
	cfg.DriverPoolTag = (ULONG)'PEPU';
	cfg.EvtDriverUnload = EvtDriverUnload;				//指定卸载函数

	//几乎任何一个WDF驱动一开始就要创建一个framework的驱动对象，这个对象是所有其他对象的parent对象。
	//创建一个framework驱动对象，在WDF程序里面，WdfDriverCreate是必须要调用的。
	//framework驱动对象是其他所有wdf对象的父对象，换句话说framework驱动对象是wdf对象树的顶点，它没有父对象了。
	status = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &cfg, &drv);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("Create wdf driver object failed\n"));
		goto DriverEntry_Complete;
	}

	KdPrint(("Create wdf driver object successfully\n"));


	//创建一个设备

	//先要分配一块内存WDFDEVICE_INIT,这块内存在创建设备的时候会用到。
	device_init = WdfControlDeviceInitAllocate(drv, &SDDL_DEVOBJ_SYS_ALL_ADM_RWX_WORLD_RW_RES_R);
	if (device_init == NULL)
	{
		KdPrint(("WdfControlDeviceInitAllocate failed\n"));
		status = STATUS_INSUFFICIENT_RESOURCES;
		goto DriverEntry_Complete;
	}

	//创建设备的名字，内核模式下，名字类似: L"\\Device\\MyWDF_Device"
	RtlInitUnicodeString(&ustring, MYWDF_KDEVICE);

	//将设备名字存入device_init中
	status = WdfDeviceInitAssignName(device_init, &ustring);

	if (!NT_SUCCESS(status))
	{
		KdPrint(("WdfDeviceInitAssignName failed\n"));
		goto DriverEntry_Complete;
	}

	KdPrint(("Device name Unicode string: %wZ (this name can only be used by other kernel mode code, like other drivers)\n", &ustring));

	//当用户模式的代码调用CreateFile和CloseHandle的时候，这2个回调会被调用
	//配置FILEOBJECT配置文件，设置FILECREATE,FILECLOSE回调。
	WDF_FILEOBJECT_CONFIG_INIT(&f_cfg, EvtDeviceFileCreate, EvtFileClose, NULL);

	//将FILEOBJECT的设置存入device_init中
	WdfDeviceInitSetFileObjectConfig(device_init, &f_cfg, WDF_NO_OBJECT_ATTRIBUTES);

	//初始化设备属性
	WDF_OBJECT_ATTRIBUTES_INIT(&object_attribs);

	//根据前面创建的device_init来创建一个设备. (control device)
	status = WdfDeviceCreate(&device_init, &object_attribs, &control_device);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("create device failed\n"));
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

	WdfControlFinishInitializing(control_device);//创建设备完成。

	/*******************************************
	到这里，我们就成功创建了一个control device。
	control device 是不支持png和power的，而且我们也不需要手工去删除。
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
