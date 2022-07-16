很是郁闷，在34行进行cout输出后程序不崩溃，不输出就崩溃。

打印完整的字符串后发现原来是没有结束符。

增加memset初始化后解决。


```
[root@ubuntu0006:/media/hankin/vdb/TransferStation/rapid] #g++ rapid_example.cpp -g
[root@ubuntu0006:/media/hankin/vdb/TransferStation/rapid] #./a.out
<?xml version="1.0" encoding="utf-8" ?>
<Conf>
        <color>
                <red>0.1</red>
                <green>0.1</green>
                <blue>0.1</blue>
                <alpha>1.0</alpha>
        </color>
        <size>
                <x>640</x>
                <y>480</y>
        </size>
        <mode fullscreen="false">screen mode</mode>
        <USBDeviceMap>
                <WhiteList>
                        <Dev ID="1234:4321" Desc="keyborad"/>
                        <Dev ID="1bC4:4321" Desc="ukey"/>
                        <Dev ID="AF34:4Ym1" Desc="iphone"/>
                </WhiteList>
                <BlackList>
                        <Dev ID="af34:ge21" Desc="mouce"/>
                        <Dev ID="GTFD:dser" Desc="display"/>
                </BlackList>
        </USBDeviceMap>
</Conf>

alpha>
        <a
---------------------------
<?xml version="1.0" encoding="utf-8" ?>
<Conf>
        <color>
                <red>0.1</red>
                <green>0.1</green>
                <blue>0.1</blue>
                <alpha>1.0</alpha>
        </color>
        <size>
                <x>640</x>
                <y>480</y>
        </size>
        <mode fullscreen="false">screen mode</mode>
        <USBDeviceMap>
                <WhiteList>
                        <Dev ID="1234:4321" Desc="keyborad"/>
                        <Dev ID="1bC4:4321" Desc="ukey"/>
                        <Dev ID="AF34:4Ym1" Desc="iphone"/>
                </WhiteList>
                <BlackList>
                        <Dev ID="af34:ge21" Desc="mouce"/>
                        <Dev ID="GTFD:dser" Desc="display"/>
                </BlackList>
        </USBDeviceMap>
</Conf>

alpha>
        <a
---------------------------
terminate called after throwing an instance of 'rapidxml::parse_error'
  what():  expected <
已放弃

(gdb) bt
Python Exception <class 'ImportError'> cannot import name '_remove_dead_weakref':
#0  0x00007ffff74aa438 in __GI_raise (sig=sig@entry=6) at ../sysdeps/unix/sysv/linux/raise.c:54
#1  0x00007ffff74ac03a in __GI_abort () at abort.c:89
Python Exception <class 'NameError'> Installation error: gdb.execute_unwinders function is missing:
#2  0x00007ffff7ae484d in __gnu_cxx::__verbose_terminate_handler() () from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
Python Exception <class 'NameError'> Installation error: gdb.execute_unwinders function is missing:
#3  0x00007ffff7ae26b6 in ?? () from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
Python Exception <class 'NameError'> Installation error: gdb.execute_unwinders function is missing:
#4  0x00007ffff7ae2701 in std::terminate() () from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
Python Exception <class 'NameError'> Installation error: gdb.execute_unwinders function is missing:
#5  0x00007ffff7ae2919 in __cxa_throw () from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
Python Exception <class 'NameError'> Installation error: gdb.execute_unwinders function is missing:
Python Exception <class 'NameError'> Installation error: gdb.execute_unwinders function is missing:
#6  0x00000000004027ce in rapidxml::xml_document<char>::parse<200> (this=0x7ffffffee1f0, text=0x61f0ef "alpha>\n\t<\241") at rapidxml/rapidxml.hpp:1408
Python Exception <class 'NameError'> Installation error: gdb.execute_unwinders function is missing:
#7  0x0000000000401eca in parse_confxml (confxml=0x61eee0 "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n<Conf") at rapid_example.cpp:51
Python Exception <class 'NameError'> Installation error: gdb.execute_unwinders function is missing:
#8  0x0000000000402331 in main (argc=1, argv=0x7fffffffe3f8) at rapid_example.cpp:89
```









