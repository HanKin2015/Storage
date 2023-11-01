// device_helper.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "device_helper.h"
#include <string.h>
#include <vector>
#include <sys/stat.h>

#define INFO(fmt, ...) printf("[INFO][device_helper](%s|%d)" fmt, __func__, __LINE__, ##__VA_ARGS__)
#define DEBUG(fmt, ...) printf("[DEBUG][device_helper](%s|%d)" fmt, __func__, __LINE__, ##__VA_ARGS__)
#define WARN(fmt, ...) printf("[WARN][device_helper](%s|%d)" fmt, __func__, __LINE__, ##__VA_ARGS__)
#define ERROR(fmt, ...) printf("[ERROR][device_helper](%s|%d)" fmt, __func__, __LINE__, ##__VA_ARGS__)

#define COMMAND_LINE_PARAMETERS 3   //命令行参数必须是2个，第二个参数是文件存储路径
#define MAX_FILE_PATH_NAME 4096     //最长路径名
#define DEV_NAME_MAX_LENGTH 256     //最长文件名
#define PRODUCT "product"           //设备名称标签

//盒子内置的USB设备如hub、网卡以及声卡等
const int g_client_built_in_device[][2]{
	{ 0x0bda, 0x0411 },{ 0x1d6b, 0x0003 },{ 0x0bda, 0x5411 },
	{ 0x1d6b, 0x0002 },{ 0x1d6b, 0x0001 },{ 0x0424, 0x2514 },
	{ 0x05e3, 0x0610 },{ 0x0438, 0x7900 },{ 0x0bda, 0x8152 }
};

device_helper::device_helper(std::string file_path) :
	m_context(NULL),
	m_devs(NULL),
	m_conf_desc(NULL),
	m_iface_desc(NULL),
	m_ep_desc(NULL),
	m_device_name("null")
{
	memset(&m_dev_desc, 0, sizeof(m_dev_desc));
	m_outfile = fopen(file_path.c_str(), "w");
	if (!m_outfile) {
		ERROR("open m_outfile handle failed!\n");
	}
}

device_helper::~device_helper()
{
	if (m_conf_desc != NULL) {
		libusb_free_config_descriptor(m_conf_desc);
		m_conf_desc = NULL;
	}
	if (m_devs		!= NULL) {
		libusb_free_device_list(m_devs, 1);
		m_devs = NULL;
	}
	if (m_context != NULL) {
		libusb_exit(m_context);
		m_context = NULL;
	}
	m_iface_desc = NULL;
	m_ep_desc = NULL;
	fclose(m_outfile);
}

bool device_helper::filter_built_in_devices(int vid, int pid)
{
	int num = sizeof(g_client_built_in_device) / sizeof(g_client_built_in_device[0]);
	for (int i = 0; i < num; ++i) {
		if (vid == g_client_built_in_device[i][0] && pid == g_client_built_in_device[i][1]) {
			INFO("0x%04x:0x%04x built-in device.\n", vid, pid);
			return false;
		}
	}
	return true;
}

void device_helper::descriptor_convert_json(Value &object, Document::AllocatorType &allocator,
	int desc_type, bool status)
{
	Value product_str;
	switch (desc_type) {
	case DEVICE_DESCRIPTOR:
		if (!status) {
			object.AddMember("device_descriptor", StringRef("error"), allocator);
			break;
		}
		object.AddMember("bLength", m_dev_desc.bLength, allocator);
		object.AddMember("bDescriptorType", m_dev_desc.bDescriptorType, allocator);
		object.AddMember("bcdUSB", m_dev_desc.bcdUSB, allocator);
		object.AddMember("bDeviceClass", m_dev_desc.bDeviceClass, allocator);
		object.AddMember("bDeviceSubClass", m_dev_desc.bDeviceSubClass, allocator);
		object.AddMember("bDeviceProtocol", m_dev_desc.bDeviceProtocol, allocator);
		object.AddMember("bMaxPacketSize0", m_dev_desc.bMaxPacketSize0, allocator);
		object.AddMember("idVendor", m_dev_desc.idVendor, allocator);
		object.AddMember("idProduct", m_dev_desc.idProduct, allocator);
		object.AddMember("bcdDevice", m_dev_desc.bcdDevice, allocator);
		object.AddMember("iManufacturer", m_dev_desc.iManufacturer, allocator);
		object.AddMember("iProduct", m_dev_desc.iProduct, allocator);
		object.AddMember("iSerialNumber", m_dev_desc.iSerialNumber, allocator);
		object.AddMember("bNumConfigurations", m_dev_desc.bNumConfigurations, allocator);
		product_str.SetString(m_device_name.c_str(), m_device_name.length(), allocator);
		object.AddMember("product", product_str, allocator);
		break;
	case CONFIG_DESCRIPTOR:
		if (!status) {
			object.AddMember("config_descriptor", StringRef("error"), allocator);
			break;
		}
		object.AddMember("bLength", m_conf_desc->bLength, allocator);
		object.AddMember("bDescriptorType", m_conf_desc->bDescriptorType, allocator);
		object.AddMember("wTotalLength", m_conf_desc->wTotalLength, allocator);
		object.AddMember("bNumInterfaces", m_conf_desc->bNumInterfaces, allocator);
		object.AddMember("bConfigurationValue", m_conf_desc->bConfigurationValue, allocator);
		object.AddMember("iConfiguration", m_conf_desc->iConfiguration, allocator);
		object.AddMember("bmAttributes", m_conf_desc->bmAttributes, allocator);
		object.AddMember("MaxPower", m_conf_desc->MaxPower, allocator);
		break;
	case INTERFACE_DESCRIPTOR:
		object.AddMember("bLength", m_iface_desc->bLength, allocator);
		object.AddMember("bDescriptorType", m_iface_desc->bDescriptorType, allocator);
		object.AddMember("bInterfaceNumber", m_iface_desc->bInterfaceNumber, allocator);
		object.AddMember("bAlternateSetting", m_iface_desc->bAlternateSetting, allocator);
		object.AddMember("bNumEndpoints", m_iface_desc->bNumEndpoints, allocator);
		object.AddMember("bInterfaceClass", m_iface_desc->bInterfaceClass, allocator);
		object.AddMember("bInterfaceSubClass", m_iface_desc->bInterfaceSubClass, allocator);
		object.AddMember("bInterfaceProtocol", m_iface_desc->bInterfaceProtocol, allocator);
		object.AddMember("iInterface", m_iface_desc->iInterface, allocator);
		break;
	case ENDPOINT_DESCRIPTOR:
		object.AddMember("bLength", m_ep_desc->bLength, allocator);
		object.AddMember("bDescriptorType", m_ep_desc->bDescriptorType, allocator);
		object.AddMember("bEndpointAddress", m_ep_desc->bEndpointAddress, allocator);
		object.AddMember("bmAttributes", m_ep_desc->bmAttributes, allocator);
		object.AddMember("wMaxPacketSize", m_ep_desc->wMaxPacketSize, allocator);
		object.AddMember("bInterval", m_ep_desc->bInterval, allocator);
		object.AddMember("bRefresh", m_ep_desc->bRefresh, allocator);
		object.AddMember("bSynchAddress", m_ep_desc->bSynchAddress, allocator);
		break;
	default:
		ERROR("ERROR descriptor!");
	}
}

void device_helper::json_write_to_file(Document &document)
{
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string message = buffer.GetString();
	message += "\n";
	if (m_outfile) {
		int ret = fwrite(message.c_str(), sizeof(char), message.length(), m_outfile);
		if (ret < 0) {
			ERROR("write to file failed.\n");
		}
	}
	else {
		ERROR("m_outfile stream invalid, write file failed!\n");
		return;
	}
}

int device_helper::get_descriptors()
{
	int ret = libusb_init(&m_context);
	if (ret != LIBUSB_SUCCESS) {
		ERROR("Failed to init libusb error %d", ret);
		return ret;
	}

	int dev_cnt = (int)libusb_get_device_list(m_context, &m_devs);
	if (dev_cnt < 0 || m_devs == NULL) {
		WARN("libusb get device list fail, error %d", dev_cnt);
		return -1;
	}
	Document messagejson;
	messagejson.SetObject();
	Document::AllocatorType &allocator = messagejson.GetAllocator();
	Value dev_list(kArrayType);
	bool is_hub_device = false;
	for (int dev_idx = 0; dev_idx < dev_cnt; ++dev_idx) {
		Value dev_obj(kObjectType);
		ret = libusb_get_device_descriptor(m_devs[dev_idx], &m_dev_desc);
		if (ret < 0) {
			(void)descriptor_convert_json(dev_obj, allocator, DEVICE_DESCRIPTOR, false);
			ERROR("failed to get device descriptor\n");
			continue;
		}
		if (!filter_built_in_devices(m_dev_desc.idVendor, m_dev_desc.idProduct)) {
			continue;
		}
		(void)get_device_name(m_dev_desc.idVendor, m_dev_desc.idProduct, m_dev_desc.iProduct);
		(void)descriptor_convert_json(dev_obj, allocator, DEVICE_DESCRIPTOR, true);
		dev_list.PushBack(dev_obj, allocator);

		int config_cnt = m_dev_desc.bNumConfigurations;
		Value conf_list(kArrayType);
		for (int conf_idx = 0; conf_idx < config_cnt; ++conf_idx) {
			Value conf_obj(kObjectType);
			ret = libusb_get_config_descriptor(m_devs[dev_idx], conf_idx, &m_conf_desc);
			if (ret != LIBUSB_SUCCESS) {
				(void)descriptor_convert_json(conf_obj, allocator, CONFIG_DESCRIPTOR, false);
				ERROR("could not read config descriptor: error %d", ret);
				continue;
			}
			(void)descriptor_convert_json(conf_obj, allocator, CONFIG_DESCRIPTOR, true);
			conf_list.PushBack(conf_obj, allocator);

			int iface_cnt = m_conf_desc->bNumInterfaces;
			Value iface_list(kArrayType);
			for (int iface_idx = 0; iface_idx < iface_cnt; ++iface_idx) {
				m_iface_desc = &(m_conf_desc->interface[iface_idx].altsetting[0]);
				if (m_iface_desc->bInterfaceClass == 0x09) {
					WARN("[%04x:%04x] this is a hub device\n", m_dev_desc.idVendor, m_dev_desc.idProduct);
					is_hub_device = true;
				}
				Value iface_obj(kObjectType);
				(void)descriptor_convert_json(iface_obj, allocator, INTERFACE_DESCRIPTOR, true);
				iface_list.PushBack(iface_obj, allocator);

				int ep_cnt = m_iface_desc->bNumEndpoints;
				Value ep_list(kArrayType);
				for (int ep_idx = 0; ep_idx < ep_cnt; ++ep_idx) {
					Value ep_obj(kObjectType);
					m_ep_desc = &(m_iface_desc->endpoint[ep_idx]);
					(void)descriptor_convert_json(ep_obj, allocator, ENDPOINT_DESCRIPTOR, true);
					ep_list.PushBack(ep_obj, allocator);
				}
				iface_list.PushBack(ep_list, allocator);
			}
			conf_list.PushBack(iface_list, allocator);
		}
		if (is_hub_device) {
			dev_list.PopBack();
		} else {
			dev_list.PushBack(conf_list, allocator);
		}
	}
	messagejson.AddMember("device_list", dev_list, allocator);
	(void)json_write_to_file(messagejson);
	return 0;
}

void device_helper::get_device_name(uint16_t vid, uint16_t pid, uint8_t product_index)
{
	unsigned char dev_name[DEV_NAME_MAX_LENGTH];
	memset(dev_name, 0, sizeof(dev_name));
	int r = 0;
	libusb_device_handle *dev_handle = NULL;

	INFO("[%04x:%04x] product_index %d\n", vid, pid, product_index);
	if (product_index == 0) {
		WARN("device name is null!\n");
	} else {
		dev_handle = libusb_open_device_with_vid_pid(m_context, vid, pid);
		if (dev_handle == NULL) {
			ERROR("libusb_open_device_with_vid_pid failed\n");
			return;
		}

		INFO("[%04x:%04x] product_index %d\n", vid, pid, product_index);
		//r = libusb_open(dev, &dev_handle);
		if (r < 0) {
			ERROR("libusb_open failed\n");
			return;
		}
		r = libusb_get_string_descriptor_ascii(dev_handle, product_index, dev_name, DEV_NAME_MAX_LENGTH);
		m_device_name = (char *)dev_name;
		libusb_close(dev_handle);
		dev_handle = NULL;
	}
	return;
}

int main(int argc, char *argv[])
{
	if (argc != COMMAND_LINE_PARAMETERS) {
		ERROR("params are not three!\n");
		return -1;
	}
	std::string file_path = "";

	if (strcmp(argv[1], "-p") == 0)
	{
		printf("file path: %s\n", argv[2]);
		if (strlen(argv[2]) > MAX_FILE_PATH_NAME) {
			printf("invalid file path name!");
			return -1;
		}
		file_path = argv[2];
	}
	if (file_path.empty()) {
		ERROR("file path is empty!\n");
		return -1;
	}
	device_helper device_obj(file_path);
	int ret = device_obj.get_descriptors();
	if (ret != 0) {
		ERROR("get descriptors failed!\n");
	}
	return 0;
}


