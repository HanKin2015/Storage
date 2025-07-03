```
[root@ubuntu0006:~] #cppcheck static_scanning_tool.cpp
Checking static_scanning_tool.cpp...
[static_scanning_tool.cpp:75]: (error) Memory leak: p
[static_scanning_tool.cpp:75]: (error) Memory leak: q
[static_scanning_tool.cpp:75]: (error) Resource leak: fp
[static_scanning_tool.cpp:68]: (error) Mismatching allocation and deallocation: str

[root@ubuntu0006:~] #cppcheck static_scanning_tool.cpp --enable=all
Checking static_scanning_tool.cpp...
[static_scanning_tool.cpp:58]: (style) Variable 's' is assigned a value that is never used.
[static_scanning_tool.cpp:61]: (style) Variable 'p' is allocated memory that is never used.
[static_scanning_tool.cpp:64]: (style) Variable 'q' is assigned a value that is never used.
[static_scanning_tool.cpp:67]: (style) Variable 'str' is allocated memory that is never used.
[static_scanning_tool.cpp:71]: (style) Variable 'fp' is assigned a value that is never used.
[static_scanning_tool.cpp:74]: (style) Variable 'fd' is assigned a value that is never used.
[static_scanning_tool.cpp:31]: (warning) Member variable 'Animal::m_hight' is not initialized in the constructor.
[static_scanning_tool.cpp:31]: (warning) Member variable 'Animal::m_type' is not initialized in the constructor.
[static_scanning_tool.cpp:31]: (warning) Member variable 'Animal::m_color' is not initialized in the constructor.
[static_scanning_tool.cpp:48]: (style) Unused private function: 'Animal::get_color'
[static_scanning_tool.cpp:75]: (error) Memory leak: p
[static_scanning_tool.cpp:75]: (error) Memory leak: q
[static_scanning_tool.cpp:75]: (error) Resource leak: fp
[static_scanning_tool.cpp:68]: (error) Mismatching allocation and deallocation: str
[static_scanning_tool.cpp:22]: (style) The function 'get_age' is never used.
[static_scanning_tool.cpp:48]: (style) The function 'get_color' is never used.
[static_scanning_tool.cpp:34]: (style) The function 'get_hight' is never used.
[static_scanning_tool.cpp:41]: (style) The function 'get_type' is never used.
(information) Cppcheck cannot find all the include files (use --check-config for details)
```