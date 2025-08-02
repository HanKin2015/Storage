#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool doesValidArrayExist(vector<int>& derived) {
        int n = derived.size();

        // 看首位为0行不行通
        int cur = 0;
        for (int i = 1; i < n; ++i) {
            if (derived[i - 1] == 1) {  // cur值变
                cur = !cur;
                cout << 'd' << cur << endl;
            }
        }
        cout << cur << endl;
        if ((cur ^ 0) == derived[n - 1]) return true;

        // 看首位为1行不行通
        cur = 1;
        for (int i = 1; i < n; ++i) {
            if (derived[i - 1] == 1) {  // cur值变
                cur = !cur;
            }
        }
        if ((cur ^ 1) == derived[n - 1]) return true;

        return false;
    }
};

int main()
{
    std::string str = "hello";
    std::cout << str.size() << std::endl;
    std::cout << str.length() << std::endl;

    return 0;
}
