// 1.修改全局变量或对象状态
int global_value = 0;
void increment()
{
    global_value++;  // 修改全局变量，产生副作用
}

// 2.输入 / 输出操作
void print_number(int x)
{
    std::cout << x;  // 打印到控制台，产生副作用
}

// 3.文件系统操作
void write_to_file(const std::string& data)
{
    std::ofstream file("output.txt");
    file << data;  // 写入文件，产生副作用
}

// 4.修改传入的参数
void add_one(int& x)
{
    x++;  // 修改引用参数，产生副作用
}

// 5.随机数生成
int generate_random()
{
    return rand();  // 返回随机数，每次调用结果不同
}