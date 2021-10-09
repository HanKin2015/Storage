//#include "csv.hpp"
#include "log.hpp"
#include <errno.h>
#include <string.h>

int read_csv(const char *file_path)
{
    const int buffer_size = 100;
    char buffer[buffer_size + 1];

    FILE *fp = fopen(file_path, "r");

    while (fgets(buffer, buffer_size, fp) != NULL ) {
        LOGH("%s", buffer);
    }
    return 0;
}

int main(int argc, char *argv[])
{
	string current_path = "./";
	string file_name = "test.csv";

	const char *file_path = (current_path + file_name).data();
	LOGH("file_path = %s", file_path);

	FILE *fp = fopen(file_path, "w");
	if (fp == NULL) {
		LOGH("fopen error! err=%u, %s", errno, strerror(errno));
	}
	fprintf(fp, "%s,%s,%s\n", "name", "sex", "age");
    fprintf(fp, "%s,%s,%d\n", "hejian", "male", 22);
    fprintf(fp, "%s,%s,%d\n", "xubing", "female", 23);
	fclose(fp);


	read_csv(file_path);
	return 0;
}
