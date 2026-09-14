[10356856@LIN-EB1ACC025D1 hj]$ g++ 条件变量例子.cpp -lthread
/usr/bin/ld: 找不到 -lthread
collect2: 错误：ld 返回 1
[10356856@LIN-EB1ACC025D1 hj]$ g++ 条件变量例子.cpp -pthread
[10356856@LIN-EB1ACC025D1 hj]$ ./a.out
主线程启动，开始每秒打印...
主线程计数：监控线程启动，开始检查文件: status
1
主线程计数: 2
主线程计数: 3
主线程计数: 4
主线程计数: 5
主线程计数: 6
主线程计数: 7
主线程计数: 8
主线程计数: 9
主线程计数: 10
主线程计数: 11
主线程计数: 12
主线程计数: 13
主线程计数: 14
主线程计数: 15
主线程计数: 16
主线程计数: 17
主线程计数: 18
主线程计数: 19
主线程计数: 20
主线程计数: 21
检测到 status 文件存在，通知主线程停止
监控线程退出
主线程收到停止信号，提前结束等待
主线程正常退出
程序结束
[10356856@LIN-EB1ACC025D1 hj]$ cat 条件变量例子.cpp
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
class FileMonitor {
private:
std::mutex mMonitorLock;
std::condition_variable mMonitorCv;
bool mStopRequested;
std::string mStatusFileName;
public:
FileMonitor (const std::string& filename)
: mStopRequested (false), mStatusFileName (filename) {}
// 主线程运行的函数：每秒打印一次，可被文件事件中断
void runMainThread () {
std::cout << "主线程启动，开始每秒打印...\n";
for (int counter = 1; !shouldStop (); counter++) {
std::cout << "主线程计数:" << counter << std::endl;

// 等待 1 秒，但如果被 notify 则会提前醒来
std::unique_lockstd::mutex lock (mMonitorLock);
if (mMonitorCv.wait_for (lock, std::chrono::seconds (1),
[this]{ return mStopRequested; })) {
std::cout << "主线程收到停止信号，提前结束等待 \n";
break;
}
//wait_for 超时后继续循环
}

std::cout << "主线程正常退出 \n";
}
// 子线程运行的函数：持续检查 status 文件
void monitorFileThread () {
std::cout << "监控线程启动，开始检查文件:" << mStatusFileName << "\n";

while (!mStopRequested) {
// 检查文件是否存在
std::ifstream file (mStatusFileName);
if (file.good ()) {
std::cout << "检测到 status 文件存在，通知主线程停止 \n";

std::lock_guardstd::mutex lock (mMonitorLock);
mStopRequested = true;
mMonitorCv.notify_all ();  // 通知所有等待的线程
break;
}

// 每隔 500 毫秒检查一次
std::this_thread::sleep_for (std::chrono::milliseconds (500));
}

std::cout << "监控线程退出 \n";
}

private:
// 线程安全的停止检查
bool shouldStop () {
std::lock_guardstd::mutex lock (mMonitorLock);
return mStopRequested;
}
};
int main () {
FileMonitor monitor ("status");  // 监控当前目录下的 "status" 文件

// 启动监控线程
std::thread fileThread (&FileMonitor::monitorFileThread, &monitor);

// 在主线程中运行主要逻辑
monitor.runMainThread ();

// 等待监控线程结束
fileThread.join ();

std::cout << "程序结束 \n";
return 0;

}
[10356856@LIN-EB1ACC025D1 hj]$ g++ --help
用法：g++ [选项] 文件...
选项：
-pass-exit-codes         在某一阶段退出时返回其中最高的错误码。
--help                   显示此帮助说明。
--target-help            显示目标机器特定的命令行选项。
--help={common|optimizers|params|target|warnings|[^]{joined|separate|undocumented}}[,...]。
显示特定类型的命令行选项。
（使用‘-v --help’显示子进程的命令行参数）。
--version                显示编译器版本信息。
-dumpspecs               显示所有内建 spec 字符串。
-dumpversion             显示编译器的版本号。
-dumpmachine             显示编译器的目标处理器。
-print-search-dirs       显示编译器的搜索路径。
-print-libgcc-file-name  显示编译器伴随库的名称。
-print-file-name=< 库 >    显示 < 库 > 的完整路径。
-print-prog-name=< 程序 >  显示编译器组件 < 程序 > 的完整路径。
-print-multiarch         显示目标的标准 GNU 三元组（被用于库路径的一部分）。
-print-multi-directory   显示不同版本 libgcc 的根目录。
-print-multi-lib         显示命令行选项和多个版本库搜索路径间的映射。
-print-multi-os-directory 显示操作系统库的相对路径。
-print-sysroot           显示目标库目录。
-print-sysroot-headers-suffix 显示用于寻找头文件的 sysroot 后缀。
-Wa,< 选项 >               将逗号分隔的 < 选项 > 传递给汇编器。
-Wp,< 选项 >               将逗号分隔的 < 选项 > 传递给预处理器。
-Wl,< 选项 >               将逗号分隔的 < 选项 > 传递给链接器。
-Xassembler < 参数 >       将 < 参数 > 传递给汇编器。
-Xpreprocessor < 参数 >    将 < 参数 > 传递给预处理器。
-Xlinker < 参数 >          将 < 参数 > 传递给链接器。
-save-temps              不删除中间文件。
-save-temps=< 参数 >       不删除中间文件。
-no-canonical-prefixes   生成其他 gcc 组件的相对路径时不生成规范化的
前缀。
-pipe                    使用管道代替临时文件。
-time                    为每个子进程计时。
-specs=< 文件 >            用 < 文件 > 的内容覆盖内建的 specs 文件。
-std=< 标准 >              假定输入源文件遵循给定的标准。
--sysroot=< 目录 >         将 < 目录 > 作为头文件和库文件的根目录。
-B < 目录 >                将 < 目录 > 添加到编译器的搜索路径中。
-v                       显示编译器调用的程序。
-###                     与 -v 类似，但选项被引号括住，并且不执行命令。
-E                       仅作预处理，不进行编译、汇编或链接。
-S                       编译到汇编语言，不进行汇编和链接，
-c                       编译、汇编到目标代码，不进行链接。
-o < 文件 >                输出到 < 文件 >。
-pie                     Create a dynamically linked position independent
executable.
-shared                  生成一个共享库。
-x < 语言 >                指定其后输入文件的语言。
允许的语言包括：c、c++、assembler、none
‘none’意味着恢复默认行为，即根据文件的扩展名猜测
源文件的语言。
以 -g、-f、-m、-O、-W 或 --param 开头的选项将由 g++ 自动传递给其调用的
不同子进程。若要向这些进程传递其他选项，必须使用 -W < 字母 > 选项。
报告程序缺陷的步骤请参见：
[http://bugzilla.redhat.com/bugzilla](http://bugzilla.redhat.com/bugzilla).