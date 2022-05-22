#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    TCHAR *szBuffer=_T("Good morning to you and to you !");
    TCHAR *szFind=_T("you");
    TCHAR *pFind = _tcsstr(szBuffer, szFind);
    return 0;
}
