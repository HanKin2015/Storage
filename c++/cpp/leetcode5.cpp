/*******************************************************************************
* 文 件 名: leetcode5.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.06
* 修改日期：2025.08.06
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.length();

        string ans = "";

        // 奇数
        for (int i = 0; i < len; ++i) {
            for (int j = 0; ; ++j) {
                if (i - j < 0 || i + j >= len || s[i - j] != s[i + j]) {
                    int cur_len = (j - 1) * 2 + 1;
                    if (cur_len > ans.length()) {
                        ans = s.substr(i - (j - 1), cur_len);
                    }
                    break;
                }
            }
        }

        // 偶数
        for (int i = 0; i < len; ++i) {
            for (int j = 0; ; ++j) {
                if (i - j < 0 || i + 1 + j >= len || s[i - j] != s[i + 1 + j]) {
                    int cur_len = (j - 1) * 2 + 2;
                    if (cur_len > ans.length()) {
                        ans = s.substr(i - (j - 1), cur_len);
                    }
                    break;
                }
            }
        }

        return ans;
    }
};

int main()
{
    cout << (new Solution())->longestPalindrome("ababa") << endl;
    return 0;
}