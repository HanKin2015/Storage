valgrind --leak-check=full --show-reachable=yes --trace-children=yes   ./a.out

如果没有任何问题显示是这样：
```
[root@ubuntu0006:~/cmake] #valgrind --leak-check=full --show-reachable=yes --trace-children=yes   ./a.out
==8109== Memcheck, a memory error detector
==8109== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==8109== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==8109== Command: ./a.out
==8109==
0x52052f0 = 5
==8109==
==8109== HEAP SUMMARY:
==8109==     in use at exit: 0 bytes in 0 blocks
==8109==   total heap usage: 4 allocs, 4 frees, 5,676 bytes allocated
==8109==
==8109== All heap blocks were freed -- no leaks are possible
==8109==
==8109== For counts of detected and suppressed errors, rerun with: -v
==8109== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

更多详情见：D:\Github\GitBook\gitbook\C++\valgrind.md