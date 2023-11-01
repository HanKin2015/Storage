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

//����������
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
	**func: ��ȡ�����������豸�����á��ӿںͶ˵�
	**return: ����0�ɹ�������ֵʧ��
	**/
	int get_descriptors();

	/**
	**func: ��������ת����json��ʽ
	**object: json����
	**allocator: json������
	**messagejson: json document����
	**desc_type: ����������(�豸�����á��ӿڡ��˵�)
	**status: �Ƿ���������ȡ������Ϣ
	**/
	void descriptor_convert_json(Value &object, Document::AllocatorType &allocator,
		int desc_type, bool status);

	/**
	**func: ���˺��ӱ����Դ���usb�豸����: hub, ����, ������
	**vid: �豸��������idVendor
	**pid: �豸��������idProduct
	**/
	bool filter_built_in_devices(int vid, int pid);

	/**
	**func: json��ʽд���ļ���
	**vid: json��document����
	**/
	void json_write_to_file(Document &document);

	/**
	**func: ��ȡ�豸����
	**product_index: ��Ʒ�ַ�������
	**/
	void get_device_name(uint16_t vid, uint16_t pid, uint8_t product_index);

private:
	libusb_context *m_context;
	struct libusb_device **m_devs;
	struct libusb_device_descriptor m_dev_desc;    //�豸������
	struct libusb_config_descriptor *m_conf_desc;    //����������
	const struct libusb_interface_descriptor *m_iface_desc;    //�ӿ�������
	const struct libusb_endpoint_descriptor *m_ep_desc;    //�˵�������
	FILE *m_outfile;  //����ļ���
	std::string m_device_name;
};

#endif
