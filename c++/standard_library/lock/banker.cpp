#include<iostream>
#include<fstream>
#include<Windows.h>
#include<queue>
using namespace std;
const int M = 100;

int pro = 0;//线程数目
int source = 0;//资源数目
queue<int> safeq;//安全序列
//安全性算法 
bool check(int available[], int max[][M], int allocation[][M], int need[][M]) {
	bool finished[100] = { false };//标记某一线程是否已经完成所有资源的借贷
	int available2[100];//可利用资源向量available 
	int max2[100][100];//最大需求矩阵max 
	int allocation2[100][100];//分配矩阵allocation 
	int need2[100][100];//需求矩阵need
	//为四个矩阵赋值
	for (int i = 0; i < pro; i++) {
		for (int j = 0; j < source; j++) {
			available2[j] = available[j];
			max2[i][j] = max[i][j];
			allocation2[i][j] = allocation[i][j];
			need2[i][j] = need[i][j];
		}
	}

	while (1) {
		int sumNeed = 0;
		for (int i = 0; i < pro; i++) {
			for (int j = 0; j < source; j++) {
				sumNeed += need2[i][j];
			}
			if (sumNeed != 0) {
				break;
			}
		}
		//如果need矩阵中所有的值都为0，即所有的需求都已经被满足
		if (sumNeed == 0) {
			return true;
		}
		//用于标记是否满足了某个线程的请求，如果都无法满足，则出现了不安全队列
		bool needflag = false;
		for (int i = 0; i < pro; i++) {
			bool flag = true;
			for (int j = 0; j < source; j++) {
				if (need2[i][j] > available2[j]) {
					flag = false;
				}
			}
			if (flag && !finished[i]) {
				needflag = true;
				safeq.push(i);
				for (int j = 0; j < source; j++) {
					allocation2[i][j] = allocation2[i][j] + need2[i][j];
					need2[i][j] = 0;
					available2[j] = available2[j] + allocation2[i][j];
					finished[i] = true;
				}

			}
			else {
				continue;
			}

		}
		if (!needflag) {
			cout << "出现了不安全序列！！\n";
			return false;
		}
	}


	return false;
}


//主函数
int main() {
	int available[100];//可利用资源向量available 
	int max[100][100];//最大需求矩阵max 
	int allocation[100][100];//分配矩阵allocation 
	int need[100][100];//需求矩阵need

	cout << "正在读取数据文件\n";
	Sleep(2000);
	ifstream inFile;
	inFile.open("banker.dat");
	if (!inFile.is_open())
		cout << "文件打开时候出错！！" << endl;
	inFile >> pro >> source;
	cout << "共有" << pro << "个线程，" << source << "种资源\n";

	if (pro >= 100 || source >= 100) {
		cout << "输入的线程或资源数目过大！！";
		exit(0);
	}

	while (!inFile.eof()) {           // 若未到文件结束一直循环

		//读入available
		for (int i = 0; i < pro; i++) {
			inFile >> available[i];
		}

		//读入max
		for (int i = 0; i < pro; i++) {
			for (int j = 0; j < source; j++) {
				inFile >> max[i][j];
			}
		}

		//读入allocation
		for (int i = 0; i < pro; i++) {
			for (int j = 0; j < source; j++) {
				inFile >> allocation[i][j];
			}
		}

		//读入need
		for (int i = 0; i < pro; i++) {
			for (int j = 0; j < source; j++) {
				need[i][j] = max[i][j] - allocation[i][j];
			}
		}
	}
	inFile.close();

	//打印提示信息
	cout << "************************************************\n";
	cout << "        操作系统实验模拟银行家算法\n";
	cout << "        作者：CSDN Carmelo_7 主页： https://blog.csdn.net/Carmelo_7?spm=1000.2115.3001.5343\n";
	cout << "************************************************\n";

	cout << "AVAILABLE:\n";
	for (int i = 0; i < pro; i++) {
		cout << available[i] << " ";
	}
	cout << "\n";
	cout << "MAX:\n";
	for (int i = 0; i < pro; i++) {
		for (int j = 0; j < source; j++) {
			cout << max[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "ALLOCATION:\n";
	for (int i = 0; i < pro; i++) {
		for (int j = 0; j < source; j++) {
			cout << allocation[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "NEED:\n";
	for (int i = 0; i < pro; i++) {
		for (int j = 0; j < source; j++) {
			cout << need[i][j] << " ";
		}
		cout << "\n";
	}
	//检查当前状态是否安全
	if (check(available, max, allocation, need) == true) {
		cout << "操作系统现有状态安全！\n" << "安全序列为：";
		while (!safeq.empty()) {
			cout << "P" << safeq.front() << " ";
			safeq.pop();
		}
	}
	else {
		cout << "操作系统现有状态不安全！\n";
		exit(0);
	}

	//线程开始请求相应的资源
	bb:
	while (true) {
		int proNo;
		int request[100];
		cout << "输入请求的线程号：";
		cin >> proNo;

		for (int i = 0; i < source; i++) {
			cout << "\n输入线程对于资源" << i << "的请求数量:\n";
			cin >> request[i];
		}
		//复制一份四个矩阵
		int available2[100];//可利用资源向量available 
		int max2[100][100];//最大需求矩阵max 
		int allocation2[100][100];//分配矩阵allocation 
		int need2[100][100];//需求矩阵need
		//为四个矩阵赋值
		for (int i = 0; i < pro; i++) {
			for (int j = 0; j < source; j++) {
				available2[j] = available[j];
				max2[i][j] = max[i][j];
				allocation2[i][j] = allocation[i][j];
				need2[i][j] = need[i][j];
			}
		}
		for (int i = 0; i < source; i++) {
			if (available2[i]<request[i]) {
				cout << "操作系统现有状态不安全！\n";
				goto bb;
			}
		}
		for (int i = 0; i < source; i++) {
			available2[i] = available2[i] - request[i];
			allocation2[proNo][i] = allocation[proNo][i]+ request[i];
			need2[proNo][i] = need[proNo][i]- request[i];
		}
		//检查接受request请求后状态是否安全
		if (check(available2, max2, allocation2, need2) == true) {
			cout << "操作系统现有状态安全！\n" << "安全序列为：";
			while (!safeq.empty()) {
				cout << "P" << safeq.front() << " ";
				safeq.pop();
			}
		}
		else {
			cout << "操作系统现有状态不安全！\n";
			exit(0);
		}

		return 0;
	}
}

