/**
* @描述   dump data到txt文件和jpg文件
* @param  data 数据
* @param  len  数据长度
* @return 无
*/
static int s_uvc_dump_idx = 0;
static void uvc_dump_file(uint8_t *data, int len)
{
	assert(data);
	assert(len > 0);

	char txt_file_name[100] = { 0 };
	char jpg_file_name[100] = { 0 };
	FILE *txt_fp = NULL;
	FILE *jpg_fp = NULL;
	int i = 0;

	s_uvc_dump_idx++;
	UVC_LOGI("s_uvc_dump_idx: %d, uvc data len: %d", s_uvc_dump_idx, len);

	(void)snprintf(txt_file_name, 100, "/sf/data/local/txt_file_%d.txt", s_uvc_dump_idx);
	(void)snprintf(jpg_file_name, 100, "/sf/data/local/jpg_file_%d.jpg", s_uvc_dump_idx);
	txt_fp = fopen(txt_file_name, "w");
	jpg_fp = fopen(jpg_file_name, "wb");
	if (txt_fp == NULL || jpg_fp == NULL) {
		UVC_LOGE("fopen file failed!");
		return;
	}

	for (i = 1; i <= len; i++) {
		//100个数据换行
		(void)fprintf(txt_fp, "%02x%c", data[i-1], i % 100 ? ' ' : '\n');
	}
	(void)fwrite((void *)data, 1, len, jpg_fp);

	fflush(txt_fp);
	fclose(txt_fp);
	txt_fp = NULL;
	fflush(jpg_fp);
	fclose(jpg_fp);
	jpg_fp = NULL;
	return;
}