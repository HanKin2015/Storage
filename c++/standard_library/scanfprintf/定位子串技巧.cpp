#include <iostream>
#include <cstdio>
#include <string.h>
#include <string>

int main()
{
    std::string line="frame: 1000 91  95    charger/Charge_19.png";
    
    int disp_time = 0, min_level = 0, max_level = 0, start = 0, end = 0;
    // %n 不计入返回值：sscanf 的返回值是成功赋值的变量个数。这里 %n 和 %*s 都不算赋值，所以只统计了3个 %d
    // 匹配frame前面的空格没有作用
	// 读取一个字符串（以空白分隔），但 * 表示赋值抑制——匹配并跳过它，不存储到任何变量
    size_t ret = sscanf(line.c_str(), " frame: %d %d %d %n%*s%n",
                &disp_time, &min_level, &max_level, &start, &end);
    printf("ret %ld %d %d %d end %d start %d\n", ret, disp_time, min_level, max_level, end, start);
    std::string image_file = "";
    image_file.assign(&line[start], end - start);
    printf("image_file %s\n", image_file.c_str());
    return 0;
}
/*
hejian@android-PowerEdge-R120:~/hj$ ./a.out
ret 3 1000 91 95 end 43 start 22
image_file charger/Charge_19.png
*/