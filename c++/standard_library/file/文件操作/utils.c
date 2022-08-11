unsigned long get_filesize(const char* filename) {
	long ret;
	FILE* fp;
	assert(filename != NULL);
	fp = fopen(filename,"rb");
	if(fp ==NULL) {
		printf("The file is not loaded successfully!\n");
		return 0;
	}
	fseek(fp ,0L ,SEEK_END );
	ret = ftell(fp);
	fclose(fp);
	return ret;
}

#ifdef WIN32
int get_filelist(const char* dir ,const char* pattern ,char** filelist) {
	static char to_search[FILEPATH_LEN];
	long handle; //用于查找的句柄
	struct _finddata_t fileinfo; //文件信息的结构体
	unsigned index = 0;

	sprintf(to_search ,"%s/%s" ,dir ,pattern);
	handle =_findfirst(to_search,&fileinfo); //第一次查找
	if(-1 == handle)
		return -1;

	// 第一个文件名
	// printf("%s\n",fileinfo.name); //打印出找到的文件的文件名
	filelist[index] = (char*) malloc(FILEPATH_LEN);
	// strcpy(filelist[index] ,fileinfo.name);
	sprintf(filelist[index], "%s/%s" ,dir ,fileinfo.name);
	index++;

	while(!_findnext(handle,&fileinfo)) //循环查找其他符合的文件，知道找不到其他的为止
	{
		// printf("%s\n",fileinfo.name);
		filelist[index] = (char*) malloc(FILEPATH_LEN);
		// strcpy(filelist[index] ,fileinfo.name);
		sprintf(filelist[index], "%s/%s" ,dir ,fileinfo.name);
		index++;

		if (index == MAX_FILECOUNT)
			break;
	}
	_findclose(handle); //别忘了关闭句柄
	return index;
}


unsigned get_filelist_dfs(const char* dir ,const char* pattern ,char** filelist) {
	static char to_search[FILEPATH_LEN];
	struct _finddata_t fileinfo; //文件信息的结构体
	static unsigned index = 0;
	long handle;
	sprintf(to_search ,"%s/%s" ,dir ,pattern);

	handle = _findfirst(to_search, &fileinfo);
	if  (handle == -1L) {
		printf("can not match the folder path");
		return 0;
	}

	do {
		if (fileinfo.attrib & _A_SUBDIR) {
			if ((strcmp(fileinfo.name, "." ) != 0 ) &&(strcmp(fileinfo.name, ".." ) != 0)) {
				char subpath[100];
				sprintf(subpath ,"%s/%s" ,dir ,fileinfo.name);
				get_filelist_dfs(subpath, pattern ,filelist);
			}
		} else {
			filelist[index] = (char*) malloc(FILEPATH_LEN);
			// strcpy(filelist[index] ,fileinfo.name);
			sprintf(filelist[index], "%s/%s" ,dir ,fileinfo.name);
			index++;
		}
	} while (_findnext(handle, &fileinfo) == 0);

	_findclose(handle);
	return index;
}
#else

unsigned get_filelist(const char* dir ,const char* pattern ,char** filelist) {
	struct dirent *ptr;
	unsigned index = 0;
	DIR *dir_;
	dir_ = opendir(dir);
	while ((ptr = readdir(dir_)) != NULL) {
		//跳过'.'和'..'两个目录
		if(ptr->d_name[0] == '.')
			continue;
		filelist[index] = (char*) malloc(FILEPATH_LEN);
		sprintf(filelist[index],"%s/%s" ,dir ,ptr->d_name);

		index++;

		if (index == MAX_FILECOUNT)
			break;
	}
	closedir(dir_);
	return index;
}

#endif

void log2file(const char* filename ,const char* fmt ,...) {
#if 0
	return;
#else
	FILE* fout = fopen(filename ,"a+");
	static char buf[MAX_MSG_SIZE];
	va_list ap;
	memset(buf, 0, MAX_MSG_SIZE);

	va_start(ap, fmt);
	vsnprintf(buf, MAX_MSG_SIZE-1, fmt, ap);
	va_end(ap);

	fprintf(fout ,"%s\n" ,buf);
	fclose(fout);
#endif
}
