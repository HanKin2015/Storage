#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <setupapi.h>
#include <initguid.h>
#include <usbiodef.h>
#include <usbioctl.h>
#include <winioctl.h>
#include <usb.h>
#include <strsafe.h>
#include <hidsdi.h>
#include <usbuser.h>
#include "usbdesc.h"
#include "cJSON.h"

// 定义GUID_DEVINTERFACE_HID宏
DEFINE_GUID(GUID_DEVINTERFACE_HID, 0x4D1E55B2, 0xF16F, 0x11CF, 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30);

#define INFO(fmt, ...) printf("[INFO][device_helper](%s|%d)" fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#define DEBUG(fmt, ...) printf("[DEBUG][device_helper](%s|%d)" fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#define WARN(fmt, ...) printf("[WARN][device_helper](%s|%d)" fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#define ERR(fmt, ...) printf("[ERROR][device_helper](%s|%d)" fmt "\n", __func__, __LINE__, ##__VA_ARGS__)

//*****************************************************************************
// D E F I N E S
//*****************************************************************************
#define NUM_STRING_DESC_TO_GET 32
#define MAX_DEVICE_PROP 200
#define MAX_DRIVER_KEY_NAME 256
#define ALLOC(dwBytes) GlobalAlloc(GPTR,(dwBytes))
#define FREE(hMem)  GlobalFree((hMem))

ULONG TotalDevicesConnected;
BOOL gDoConfigDesc;

typedef struct _DEVICE_GUID_LIST {
	HDEVINFO   DeviceInfo;
	LIST_ENTRY ListHead;
} DEVICE_GUID_LIST, *PDEVICE_GUID_LIST;

typedef struct _DEVICE_INFO_NODE {
	HDEVINFO                         DeviceInfo;
	LIST_ENTRY                       ListEntry;
	SP_DEVINFO_DATA                  DeviceInfoData;
	SP_DEVICE_INTERFACE_DATA         DeviceInterfaceData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA DeviceDetailData;
	PSTR                             DeviceDescName;
	ULONG                            DeviceDescNameLength;
	PSTR                             DeviceDriverName;
	ULONG                            DeviceDriverNameLength;
	DEVICE_POWER_STATE               LatestDevicePowerState;
} DEVICE_INFO_NODE, *PDEVICE_INFO_NODE;

//
//  BOOLEAN
//  IsListEmpty(
//      PLIST_ENTRY ListHead
//      );
//
#define IsListEmpty(ListHead) \
    ((ListHead)->Flink == (ListHead))

//
//  PLIST_ENTRY
//  RemoveHeadList(
//      PLIST_ENTRY ListHead
//      );
//
#define RemoveHeadList(ListHead) \
    (ListHead)->Flink;\
    {RemoveEntryList((ListHead)->Flink)}

//
//  VOID
//  RemoveEntryList(
//      PLIST_ENTRY Entry
//      );
//
#define RemoveEntryList(Entry) {\
    PLIST_ENTRY _EX_Blink;\
    PLIST_ENTRY _EX_Flink;\
    _EX_Flink = (Entry)->Flink;\
    _EX_Blink = (Entry)->Blink;\
    _EX_Blink->Flink = _EX_Flink;\
    _EX_Flink->Blink = _EX_Blink;\
    }

//
//  VOID
//  InsertTailList(
//      PLIST_ENTRY ListHead,
//      PLIST_ENTRY Entry
//      );
//
#define InsertTailList(ListHead,Entry) {\
    PLIST_ENTRY _EX_Blink;\
    PLIST_ENTRY _EX_ListHead;\
    _EX_ListHead = (ListHead);\
    _EX_Blink = _EX_ListHead->Blink;\
    (Entry)->Flink = _EX_ListHead;\
    (Entry)->Blink = _EX_Blink;\
    _EX_Blink->Flink = (Entry);\
    _EX_ListHead->Blink = (Entry);\
    }

FORCEINLINE
VOID
InitializeListHead(
	_Out_ PLIST_ENTRY ListHead
)
{
	ListHead->Flink = ListHead->Blink = ListHead;
}

//
// A collection of device properties. The device can be hub, host controller or usb device
//
typedef struct _USB_DEVICE_PNP_STRINGS
{
	PCHAR DeviceId;
	PCHAR DeviceDesc;
	PCHAR HwId;
	PCHAR Service;
	PCHAR DeviceClass;
	PCHAR PowerState;
} USB_DEVICE_PNP_STRINGS, *PUSB_DEVICE_PNP_STRINGS;

//
// Structures assocated with TreeView items through the lParam.  When an item
// is selected, the lParam is retrieved and the structure it which it points
// is used to display information in the edit control.
//
typedef enum _USBDEVICEINFOTYPE
{
	HostControllerInfo,
	RootHubInfo,
	ExternalHubInfo,
	DeviceInfo
} USBDEVICEINFOTYPE, *PUSBDEVICEINFOTYPE;

typedef struct _USBHOSTCONTROLLERINFO
{
	USBDEVICEINFOTYPE                   DeviceInfoType;
	LIST_ENTRY                          ListEntry;
	PCHAR                               DriverKey;
	ULONG                               VendorID;
	ULONG                               DeviceID;
	ULONG                               SubSysID;
	ULONG                               Revision;
	USB_POWER_INFO                      USBPowerInfo[6];
	BOOL                                BusDeviceFunctionValid;
	ULONG                               BusNumber;
	USHORT                              BusDevice;
	USHORT                              BusFunction;
	PUSB_CONTROLLER_INFO_0              ControllerInfo;
	PUSB_DEVICE_PNP_STRINGS             UsbDeviceProperties;
} USBHOSTCONTROLLERINFO, *PUSBHOSTCONTROLLERINFO;

//
// Structure used to build a linked list of String Descriptors
// retrieved from a device.
//
typedef struct _STRING_DESCRIPTOR_NODE
{
	struct _STRING_DESCRIPTOR_NODE *Next;
	UCHAR                           DescriptorIndex;
	USHORT                          LanguageID;
	USB_STRING_DESCRIPTOR           StringDescriptor[1];
} STRING_DESCRIPTOR_NODE, *PSTRING_DESCRIPTOR_NODE;

typedef struct _USBROOTHUBINFO
{
	USBDEVICEINFOTYPE                   DeviceInfoType;
	PUSB_NODE_INFORMATION               HubInfo;
	PUSB_HUB_INFORMATION_EX             HubInfoEx;
	PCHAR                               HubName;
	PUSB_PORT_CONNECTOR_PROPERTIES      PortConnectorProps;
	PUSB_DEVICE_PNP_STRINGS             UsbDeviceProperties;
	PDEVICE_INFO_NODE                   DeviceInfoNode;
	PUSB_HUB_CAPABILITIES_EX            HubCapabilityEx;

} USBROOTHUBINFO, *PUSBROOTHUBINFO;

typedef struct _USBEXTERNALHUBINFO
{
	USBDEVICEINFOTYPE                      DeviceInfoType;
	PUSB_NODE_INFORMATION                  HubInfo;
	PUSB_HUB_INFORMATION_EX                HubInfoEx;
	PCHAR                                  HubName;
	PUSB_NODE_CONNECTION_INFORMATION_EX    ConnectionInfo;
	PUSB_PORT_CONNECTOR_PROPERTIES         PortConnectorProps;
	PUSB_DESCRIPTOR_REQUEST                ConfigDesc;
	PUSB_DESCRIPTOR_REQUEST                BosDesc;
	PSTRING_DESCRIPTOR_NODE                StringDescs;
	PUSB_NODE_CONNECTION_INFORMATION_EX_V2 ConnectionInfoV2; // NULL if root HUB
	PUSB_DEVICE_PNP_STRINGS                UsbDeviceProperties;
	PDEVICE_INFO_NODE                      DeviceInfoNode;
	PUSB_HUB_CAPABILITIES_EX               HubCapabilityEx;
} USBEXTERNALHUBINFO, *PUSBEXTERNALHUBINFO;

// HubInfo, HubName may be in USBDEVICEINFOTYPE, so they can be removed
typedef struct
{
	USBDEVICEINFOTYPE                      DeviceInfoType;
	PUSB_NODE_INFORMATION                  HubInfo;          // NULL if not a HUB
	PUSB_HUB_INFORMATION_EX                HubInfoEx;        // NULL if not a HUB
	PCHAR                                  HubName;          // NULL if not a HUB
	PUSB_NODE_CONNECTION_INFORMATION_EX    ConnectionInfo;   // NULL if root HUB
	PUSB_PORT_CONNECTOR_PROPERTIES         PortConnectorProps;
	PUSB_DESCRIPTOR_REQUEST                ConfigDesc;       // NULL if root HUB
	PUSB_DESCRIPTOR_REQUEST                BosDesc;          // NULL if root HUB
	PSTRING_DESCRIPTOR_NODE                StringDescs;
	PUSB_NODE_CONNECTION_INFORMATION_EX_V2 ConnectionInfoV2; // NULL if root HUB
	PUSB_DEVICE_PNP_STRINGS                UsbDeviceProperties;
	PDEVICE_INFO_NODE                      DeviceInfoNode;
	PUSB_HUB_CAPABILITIES_EX               HubCapabilityEx;  // NULL if not a HUB
} USBDEVICEINFO, *PUSBDEVICEINFO;

//
// DEVNODE.C
//
PUSB_DEVICE_PNP_STRINGS
DriverNameToDeviceProperties(
	_In_reads_bytes_(cbDriverName) PCHAR   DriverName,
	_In_ size_t                       cbDriverName
);

VOID FreeDeviceProperties(
	_In_ PUSB_DEVICE_PNP_STRINGS *ppDevProps
);

BOOL
AreThereStringDescriptors(
	PUSB_DEVICE_DESCRIPTOR          DeviceDesc,
	PUSB_CONFIGURATION_DESCRIPTOR   ConfigDesc
);

PSTRING_DESCRIPTOR_NODE
GetAllStringDescriptors(
	HANDLE                          hHubDevice,
	ULONG                           ConnectionIndex,
	PUSB_DEVICE_DESCRIPTOR          DeviceDesc,
	PUSB_CONFIGURATION_DESCRIPTOR   ConfigDesc
);

PSTRING_DESCRIPTOR_NODE
GetStringDescriptor(
	HANDLE  hHubDevice,
	ULONG   ConnectionIndex,
	UCHAR   DescriptorIndex,
	USHORT  LanguageID
);

HRESULT
GetStringDescriptors(
	_In_ HANDLE                         hHubDevice,
	_In_ ULONG                          ConnectionIndex,
	_In_ UCHAR                          DescriptorIndex,
	_In_ ULONG                          NumLanguageIDs,
	_In_reads_(NumLanguageIDs) USHORT  *LanguageIDs,
	_In_ PSTRING_DESCRIPTOR_NODE        StringDescNodeHead
);

PCHAR GetDriverKeyName(
	HANDLE  Hub,
	ULONG   ConnectionIndex
);

PUSB_DESCRIPTOR_REQUEST
GetConfigDescriptor(
	HANDLE  hHubDevice,
	ULONG   ConnectionIndex,
	UCHAR   DescriptorIndex
);

_Success_(return == TRUE)
BOOL
GetDeviceProperty(
	_In_    HDEVINFO         DeviceInfoSet,
	_In_    PSP_DEVINFO_DATA DeviceInfoData,
	_In_    DWORD            Property,
	_Outptr_ LPTSTR         *ppBuffer
);

//*****************************************************************************
// L O C A L    F U N C T I O N    P R O T O T Y P E S
//*****************************************************************************

VOID
EnumerateHostControllers();

VOID
EnumerateHostController(
	HANDLE                   hHCDev,
	_Inout_ PCHAR            leafName,
	_In_    HANDLE           deviceInfo,
	_In_    PSP_DEVINFO_DATA deviceInfoData
);

VOID
EnumerateHub(
	_In_reads_(cbHubName) PCHAR                     HubName,
	_In_ size_t                                     cbHubName,
	_In_opt_ PUSB_NODE_CONNECTION_INFORMATION_EX    ConnectionInfo,
	_In_opt_ PUSB_NODE_CONNECTION_INFORMATION_EX_V2 ConnectionInfoV2,
	_In_opt_ PUSB_PORT_CONNECTOR_PROPERTIES         PortConnectorProps,
	_In_opt_ PUSB_DESCRIPTOR_REQUEST                ConfigDesc,
	_In_opt_ PUSB_DESCRIPTOR_REQUEST                BosDesc,
	_In_opt_ PSTRING_DESCRIPTOR_NODE                StringDescs,
	_In_opt_ PUSB_DEVICE_PNP_STRINGS                DevProps
);

VOID
EnumerateHubPorts(
	HANDLE      hHubDevice,
	ULONG       NumPorts
);

PCHAR GetExternalHubName(
	HANDLE  Hub,
	ULONG   ConnectionIndex
);

#define COMMAND_LINE_PARAMETERS 3			//命令行参数必须是2个，第二个参数是文件存储路径
#define MAX_FILE_PATH_NAME		4096		//json文件路径长度
#define DEV_NAME_MAX_LENGTH		256			//设备名称长度
#define PRODUCT					"product"	//设备名称标签

// 把描述符转换成json格式
VOID DescriptorConvertJson(VOID *desc, UCHAR descType, cJSON *descListObj);

// json格式写到文件中
VOID GetDescriptors(PUSB_DEVICE_DESCRIPTOR DeviceDesc,
					PUSB_CONFIGURATION_DESCRIPTOR ConfigDesc);

// 设备名称
CHAR gDeviceName[DEV_NAME_MAX_LENGTH];

// 输出文件流
FILE *gOutFileFp;
