/* getvideoinfo.cpp : 定义控制台应用程序的入口点。

	作者：
	日期：
	作用：获取视频设备的分辨率

	使用方法：
		控制台输出：
		比如：
			devicename:USB 视频设备 && resolution:2592*1944,640*480,320*240,2048*1536,1280*1024,1024*768,1600*1200,
			devicename:USB 视频设备 && resolution:640*480,352*288,320*240,176*144,160*120,


	20180806更新：
		增加mokinername与格式输出

		控制台输出：
			devicename:UDS CamScanner && MonikerName:@device:pnp:\\?\usb#vid_0c45&pid_6366&mi_00#8&183af011&0&0000#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global && resolution:MEDIASUBTYPE_MJPG-3264*2448,2592*1944,2048*1536,1920*1080,1600*1200,1280*960,1280*720,1024*768,800*600,640*480,320*240,3264*2448,MEDIASUBTYPE_YUY2-3264*2448,2592*1944,2048*1536,1920*1080,1600*1200,1280*960,1280*720,1024*768,800*600,640*480,320*240,3264*2448,
			devicename:USB CAM2 && MonikerName:@device:pnp:\\?\usb#vid_1b17&pid_6684&mi_00#8&6daf276&0&0000#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global && resolution:MEDIASUBTYPE_YUY2-640*480,352*288,320*240,176*144,160*120,MEDIASUBTYPE_MJPG-640*480,352*288,320*240,176*144,160*120,800*600,1280*960,1600*1200,MEDIASUBTYPE_YUY2-1600*1200,1280*960,800*600,640*480,352*288,320*240,176*144,160*120,MEDIASUBTYPE_MJPG-1600*1200,1280*960,800*600,640*480,352*288,320*240,176*144,160*120,

	20180921更新：
		优化分辨率输出个数，合并格式的相同分辨率

		控制台输出：
			devicename:MICROTEK H-Screen && MonikerName:@device:pnp:\\?\usb#vid_05da&pid_f066&mi_00#9&ee6f894&0&0000#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global && MEDIASUBTYPE_MJPG-3264*244
			8,2592*1944,2048*1536,1920*1080,1600*1200,1280*960,1280*720,1024*768,800*600,640*480,320*240, && MEDIASUBTYPE_YUY2-3264*2448,2592*1944,2048*1536,1920*1080,1600*1200,1280*960,1280*7
			20,1024*768,800*600,640*480,320*240,
			devicename:USB Camera && MonikerName:@device:pnp:\\?\usb#vid_0c45&pid_0591&mi_00#a&387a50c1&0&0000#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global && MEDIASUBTYPE_MJPG-2592*1944,2048
			*1536,1920*1080,1600*1200,1280*720,1024*768,800*600,640*480, && MEDIASUBTYPE_YUY2-2592*1944,2048*1536,1920*1080,1600*1200,1280*720,1024*768,800*600,640*480,

	20190104更新：
		分辨率分为捕获与静态，只获取捕获，根据pinInfo.achName
		devicename:Nantian Camera 8913 && MonikerName:@device:pnp:\\?\usb#vid_1dfc&pid_8813&mi_00#6&1f942fca&0&0000#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global && MEDIASUBTYPE_MJPG-1600*1200,
		devicename:Microstar 5M Scanner 2.9 && MonikerName:@device:pnp:\\?\usb#vid_0ac8&pid_3370&mi_00#6&6a386e7&0&0000#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global && MEDIASUBTYPE_YUY2-2592*1944,640*480,320*240,176*144,160*120,2048*1536,1280*720,1920*1080,
			
			
*/


#include "stdafx.h"
#pragma comment(lib, "Strmiids.lib")  
#include <dshow.h>  
#include <vector>  
#include <iostream>  
#include <locale>
using namespace std;

#define MAX_FRIENDLY_NAME_LENGTH    128
#define MAX_MONIKER_NAME_LENGTH     256  
  
typedef struct _TDeviceName  
{  
    WCHAR FriendlyName[MAX_FRIENDLY_NAME_LENGTH];   //设备友好名
    WCHAR MonikerName[MAX_MONIKER_NAME_LENGTH];     //设备Moniker名
} TDeviceName;  



int GuidToString(const GUID &guid, char* buffer){  
    int buf_len = 64;  
    _snprintf(  
        buffer,  
        buf_len,  
        "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",  
        guid.Data1, guid.Data2, guid.Data3,  
        guid.Data4[0], guid.Data4[1],  
        guid.Data4[2], guid.Data4[3],  
        guid.Data4[4], guid.Data4[5],  
        guid.Data4[6], guid.Data4[7]);  
    return 0;  
}  
  
int GetMajorType(GUID guid, char* buffer) {  
    memset(buffer, 0, 256);  
    if (guid == MEDIATYPE_Video) {  
        //_snprintf(buffer, 256, "MEDIATYPE_Video");  
        return 0;  
    }  
    if (guid == MEDIATYPE_Audio) {  
        _snprintf(buffer, 256, "MEDIATYPE_Audio");  
        return 0;  
    }  
    if (guid == MEDIASUBTYPE_RGB24) {  
        _snprintf(buffer, 256, "MEDIATYPE_Stream");  
        return 0;  
    }  
    return -1;  
}

int GetSubType(GUID guid, char* buffer) {  
    memset(buffer, 0, 256);  
    if( guid == MEDIASUBTYPE_YUY2){  
		//printf("MEDIASUBTYPE_YUY2");
        _snprintf(buffer, 256, "MEDIASUBTYPE_YUY2");  
        return 0;  
    }  
    if (guid == MEDIASUBTYPE_MJPG) {  
		//printf("MEDIASUBTYPE_MJPG");
        _snprintf(buffer, 256, "MEDIASUBTYPE_MJPG");  
        return 0;  
    }  
    if (guid == MEDIASUBTYPE_RGB24) {  
		//printf("MEDIASUBTYPE_RGB24");
        _snprintf(buffer, 256, "MEDIASUBTYPE_RGB24");  
        return 0;  
    }  
    return -1;  
}  
  
int GetFormatType(GUID guid, char* buffer) {  
    memset(buffer, 0, 256);  
    if (guid == FORMAT_VideoInfo) {  
        _snprintf(buffer, 256, "FORMAT_VideoInfo");  
        return 0;  
    }  
    if (guid == FORMAT_VideoInfo2) {  
        _snprintf(buffer, 256, "FORMAT_VideoInfo2");  
        return 0;  
    }  
    return -1;  
}  

int DsGetOptionDevice(IMoniker* pMoniker,TDeviceName& name) {  
    //USES_CONVERSION;  
    HRESULT hr = NULL;  
    IBaseFilter *pFilter;  
    hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, (void**)&pFilter);  
    if (!pFilter) {  
        return -1;  
    }  
    IEnumPins * pinEnum = NULL;  
    IPin * pin = NULL;  
    if (FAILED(pFilter->EnumPins(&pinEnum))) {  
        pinEnum->Release();  
        return -1;  
    }  
    pinEnum->Reset();  
    ULONG pinFetched = 0; 
	//初始化变量
	char mjpg_resolution[256] = "";
	char yuy2_resolution[256] = "";
    while (SUCCEEDED(pinEnum->Next(1, &pin, &pinFetched)) && pinFetched) {  
        if (!pin) {  
            continue;  
        }  
        PIN_INFO pinInfo;  
        if (FAILED(pin->QueryPinInfo(&pinInfo))) {  
            continue;  
        }  
        if (pinInfo.dir != PINDIR_OUTPUT) {  
            continue;  
        }  

		//分辨率分为捕获与静态，只获取捕获，根据pinInfo.achName
		wchar_t *achname_str = L"捕获";
		int achname_str_comp;
		achname_str_comp = wcscmp(achname_str, pinInfo.achName);
		
		if (achname_str_comp == 0) {
			

			IEnumMediaTypes *mtEnum = NULL;  
			AM_MEDIA_TYPE   *mt = NULL;  
			if (FAILED(pin->EnumMediaTypes(&mtEnum)))  
				break;  
			mtEnum->Reset();  
			ULONG mtFetched = 0;  
		
			while (SUCCEEDED(mtEnum->Next(1, &mt, &mtFetched)) && mtFetched) {  
				char majorbuf[256];           
				if ( GetMajorType(mt->majortype, majorbuf) != 0) {  
					GuidToString(mt->majortype, majorbuf);  
				}  
				char subtypebuf[256];  
				if (GetSubType(mt->subtype, subtypebuf) != 0) {  
					GuidToString(mt->subtype, subtypebuf);  
				}                     
				char formatbuf[256];  
				if (GetFormatType(mt->formattype, formatbuf) != 0) {  
					GuidToString(mt->formattype, formatbuf);               
				}  


				BITMAPINFOHEADER* bmi = NULL;  
				int avgTime;  
				if (mt->formattype == FORMAT_VideoInfo) {  
					if ( mt->cbFormat >= sizeof(VIDEOINFOHEADER)){                      
						VIDEOINFOHEADER *pVih = reinterpret_cast<VIDEOINFOHEADER*>( mt->pbFormat);  
						bmi = &( pVih->bmiHeader );  
						avgTime = pVih->AvgTimePerFrame;
					
						//判断格式
						int is_mjpg;
						int is_yuy2;
						is_mjpg = strcmp("MEDIASUBTYPE_MJPG", subtypebuf);
						is_yuy2 = strcmp("MEDIASUBTYPE_YUY2", subtypebuf);
						if (is_mjpg == 0) {
							//字符串拼接
							char width[256];
							char height[256];
							char mjpg_resolution_tmp[256]="";
							strcat(mjpg_resolution_tmp, itoa(bmi->biWidth, width, 10));
							strcat(mjpg_resolution_tmp, "*");
							strcat(mjpg_resolution_tmp, itoa(bmi->biHeight, height, 10));
							strcat(mjpg_resolution_tmp, ",");

							//只拼接不存在的字符串
							char *str1 = mjpg_resolution;
							char *str2 = mjpg_resolution_tmp;
							char *pl;
							pl = strstr(str1, str2);
							if (pl == NULL) strcat(mjpg_resolution, mjpg_resolution_tmp);
						}

						if (is_yuy2 == 0) {
							//字符串拼接
							char width[256];
							char height[256];
							char yuy2_resolution_tmp[256]="";
							strcat(yuy2_resolution_tmp, itoa(bmi->biWidth, width, 10));
							strcat(yuy2_resolution_tmp, "*");
							strcat(yuy2_resolution_tmp, itoa(bmi->biHeight, height, 10));
							strcat(yuy2_resolution_tmp, ",");

							//只拼接不存在的字符串
							char *str1 = yuy2_resolution;
							char *str2 = yuy2_resolution_tmp;
							char *pl;
							pl = strstr(str1, str2);
							if (pl == NULL) strcat(yuy2_resolution, yuy2_resolution_tmp);
						}

					}  
				}

			} 

		}
        pin->Release();
	}
	if (strcmp("", mjpg_resolution) != 0) printf(" && MEDIASUBTYPE_MJPG-%s", mjpg_resolution);
	if (strcmp("", yuy2_resolution) != 0) printf(" && MEDIASUBTYPE_YUY2-%s", yuy2_resolution);
	printf("\n");	// 显示完分辨率，换行进行下一个设备信息显示
	return 0;
}  


// 入口函数
int _tmain(int argc, _TCHAR* argv[])
{  
    TDeviceName name;  
    HRESULT hr;  
  
    // 初始化
    std::vector<TDeviceName> vectorDevices;  
    vectorDevices.clear();  
  
    // 初始化COM
    hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);  
    if (FAILED(hr))  
    {  
        return hr;  
    }  
  
    // 创建系统设备枚举器实例
    ICreateDevEnum *pSysDevEnum = NULL;  
    hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void **)&pSysDevEnum);  
    if (FAILED(hr))  
    {  
        CoUninitialize();  
        return hr;  
    }  
  
    // 获取设备类枚举器
    IEnumMoniker *pEnumCat = NULL;  
    hr = pSysDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnumCat, 0);  
    if (hr == S_OK)  
    {  
        // 枚举设备名称
        IMoniker *pMoniker = NULL;  
        ULONG cFetched;  
        while (pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)  
        {  
            IPropertyBag *pPropBag;  
            hr = pMoniker->BindToStorage(NULL, NULL, IID_IPropertyBag, (void **)&pPropBag);  
            if (SUCCEEDED(hr))  
            {  
                // 获取设备友好名
                VARIANT varName;  
                VariantInit(&varName);  
                hr = pPropBag->Read(L"FriendlyName", &varName, NULL);  
                if (SUCCEEDED(hr))  
                {  
                    StringCchCopy(name.FriendlyName, MAX_FRIENDLY_NAME_LENGTH, varName.bstrVal);  
					locale loc( "chs" );    
					wcout.imbue( loc );
					printf("devicename:");
                    std::wcout << name.FriendlyName;
					
                    // 获取设备Moniker名
                    LPOLESTR pOleDisplayName = reinterpret_cast<LPOLESTR>(CoTaskMemAlloc(MAX_MONIKER_NAME_LENGTH * 2));  
                    if (pOleDisplayName != NULL)  
                    {  
                        hr = pMoniker->GetDisplayName(NULL, NULL, &pOleDisplayName);  
                        if (SUCCEEDED(hr))  
                        {  
                            StringCchCopy(name.MonikerName, MAX_MONIKER_NAME_LENGTH, pOleDisplayName);
							locale loc( "chs" );    
							wcout.imbue( loc );
							printf(" && ");
							printf("MonikerName:");
							std::wcout << name.MonikerName;

							//printf(" && ");
							//printf("resolution:");
							DsGetOptionDevice( pMoniker, name ); 
                            vectorDevices.push_back(name);
							
                        }  
						
                        CoTaskMemFree(pOleDisplayName);  
                    }  
                }  
				
                VariantClear(&varName);  
                pPropBag->Release();  
            }  
            pMoniker->Release();  
        } // End for While    
        pEnumCat->Release();  
    } else {
		printf("no video device was found");
	}
    pSysDevEnum->Release();  
    CoUninitialize();  
}






