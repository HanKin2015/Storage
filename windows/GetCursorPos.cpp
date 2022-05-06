#include <iostream>
#include <windows.h>
#define WINVER 0x0600

int main()
{
    POINT p, pNext;
    GetCursorPos(&p);
    GetPhysicalCursorPos(&pNext);
    std::cout << p.x << "," << p.y << std::endl;
    SetCursorPos(p.x + 30, p.y + 30);
    GetCursorPos(&pNext);
    std::cout << pNext.x << "," << pNext.y << std::endl;

    POINT last_cursor = {0, 0}, current_cursor;
    while (true)
    {
        GetCursorPos(&current_cursor);
        if (current_cursor.x != last_cursor.x && current_cursor.y != last_cursor.y)
        {
            std::cout << current_cursor.x << "," << current_cursor.y << std::endl;
            //last_cursor.x = current_cursor.x;
            //last_cursor.y = current_cursor.y;
            last_cursor = current_cursor;
        }
    }
    return 0;
}
