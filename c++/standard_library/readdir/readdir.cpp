/**
 * read_dir_links: grabs links in a specific directory
 * @sysdir: sysfs directory to read
 * returns list of link names with success and NULL with error.
 */
struct dlist *read_dir_links(const char *path)
{
	DIR *dir = NULL;
	struct dirent *dirent = NULL;
	char file_path[SYSFS_PATH_MAX], *linkname;
	struct dlist *linklist = NULL;

	if (!path) {
		errno = EINVAL;
		return NULL;
	}
	dir = opendir(path);
	if (!dir) {
		dprintf("Error opening directory %s\n", path);
		return NULL;
	}
	while ((dirent = readdir(dir)) != NULL) {
		if (0 == strcmp(dirent->d_name, "."))
			 continue;
		if (0 == strcmp(dirent->d_name, ".."))
			continue;
		memset(file_path, 0, SYSFS_PATH_MAX);
		safestrcpy(file_path, path);
		safestrcat(file_path, "/");
		safestrcat(file_path, dirent->d_name);
		if (!sysfs_path_is_link(file_path)) {
			if (!linklist) {
				linklist = dlist_new_with_delete
					(SYSFS_NAME_LEN, sysfs_del_name);
				if (!linklist) {
					dprintf("Error creating list\n");
					closedir(dir);
					return NULL;
				}
			}
			linkname = (char *)calloc(1, SYSFS_NAME_LEN);
			safestrcpymax(linkname, dirent->d_name, SYSFS_NAME_LEN);
			dlist_unshift_sorted(linklist, linkname, sort_char);
		}
	}
	closedir(dir);
	return linklist;
}

/**
 * read_dir_subdirs: grabs subdirs in a specific directory
 * @sysdir: sysfs directory to read
 * returns list of directory names with success and NULL with error.
 */
struct dlist *read_dir_subdirs(const char *path)
{
	DIR *dir = NULL;
	struct dirent *dirent = NULL;
	char file_path[SYSFS_PATH_MAX], *dir_name;
	struct dlist *dirlist = NULL;

	if (!path) {
		errno = EINVAL;
		return NULL;
	}
	dir = opendir(path);
	if (!dir) {
		dprintf("Error opening directory %s\n", path);
		return NULL;
	}
	while ((dirent = readdir(dir)) != NULL) {
		if (0 == strcmp(dirent->d_name, "."))
			 continue;
		if (0 == strcmp(dirent->d_name, ".."))
			continue;
		memset(file_path, 0, SYSFS_PATH_MAX);
		safestrcpy(file_path, path);
		safestrcat(file_path, "/");
		safestrcat(file_path, dirent->d_name);
		if (!sysfs_path_is_dir(file_path)) {
			if (!dirlist) {
				dirlist = dlist_new_with_delete
					(SYSFS_NAME_LEN, sysfs_del_name);
				if (!dirlist) {
					dprintf("Error creating list\n");
					closedir(dir);
					return NULL;
				}
			}
			dir_name = (char *)calloc(1, SYSFS_NAME_LEN);
			safestrcpymax(dir_name, dirent->d_name, SYSFS_NAME_LEN);
			dlist_unshift_sorted(dirlist, dir_name, sort_char);
		}
	}
	closedir(dir);
	return dirlist;
}

