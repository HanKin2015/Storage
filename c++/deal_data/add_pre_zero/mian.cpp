#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ostringstream>
using namespace std;

int main()
{
    ostringstream os;
    uint32_t i = 0;
    os << "hejian data_: 0x" << std::hex << (uint64_t)data_ << " ";
    os << "len_: 0x" << std::hex << (uint32_t)len_ << " ";

    for (i = 0 ; i < len_ ; i++)
        os <<  std::hex << " 0x" <<(uint32_t)(data_[i]);
