#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int ReadFile(const char* file_path, vector<char*> &data);
int WriteFile(const char* file_path, vector<char*> data);

#endif // COMMON_H
