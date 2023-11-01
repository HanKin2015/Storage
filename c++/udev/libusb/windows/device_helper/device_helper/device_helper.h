#ifndef __DEVICE_HELPER_H__
#define __DEVICE_HELPER_H__

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "libusb.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

//描述符类型
enum descriptor_type
{
	DEVICE_DESCRIPTOR,
	CONFIG_DESCRIPTOR,
	INTERFACE_DESCRIPTOR,
	ENDPOINT_DESCRIPTOR
};

class device_helper
{
public:
	device_helper(std::string file_path);
	~device_helper();

	/**
	**func: 获取描述符包括设备、配置、接口和端点
	**return: 返回0成功，其它值失败
	**/
	int get_descriptors();

	/**
	**func: 把描述符转换成json格式
	**object: json对象
	**allocator: json索引器
	**messagejson: json document对象
	**desc_type: 描述符类型(设备、配置、接口、端点)
	**status: 是否是正常获取到了信息
	**/
	void descriptor_convert_json(Value &object, Document::AllocatorType &allocator,
		int desc_type, bool status);

	/**
	**func: 过滤盒子本身自带的usb设备，如: hub, 网卡, 声卡等
	**vid: 设备描述符的idVendor
	**pid: 设备描述符的idProduct
	**/
	bool filter_built_in_devices(int vid, int pid);

	/**
	**func: json格式写到文件中
	**vid: json的document对象
	**/
	void json_write_to_file(Document &document);

	/**
	**func: 获取设备名称
	**product_index: 产品字符串索引
	**/
	void get_device_name(uint16_t vid, uint16_t pid, uint8_t product_index);

private:
	libusb_context *m_context;
	struct libusb_device **m_devs;
	struct libusb_device_descriptor m_dev_desc;    //设备描述符
	struct libusb_config_descriptor *m_conf_desc;    //配置描述符
	const struct libusb_interface_descriptor *m_iface_desc;    //接口描述符
	const struct libusb_endpoint_descriptor *m_ep_desc;    //端点描述符
	FILE *m_outfile;  //输出文件流
	std::string m_device_name;
};

#endif
