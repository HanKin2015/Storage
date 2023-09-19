Utils：工具类; 效用; 实用工具;


# paramiko
Paramiko是一个用于SSH协议的Python库，它提供了SSH客户端和服务器的实现，可以用于远程执行命令、传输文件等操作。以下是Paramiko库的一些常用功能：

- SSH客户端连接：使用paramiko.SSHClient()类可以创建一个SSH客户端对象，然后使用connect()方法连接到远程服务器。
- 执行远程命令：使用SSH客户端对象的exec_command()方法可以在远程服务器上执行命令，并返回命令的标准输出、标准错误和退出状态码。
- 传输文件：使用SSH客户端对象的sftp()方法可以创建一个SFTP客户端对象，然后使用put()和get()方法可以上传和下载文件。
- SSH密钥认证：使用paramiko.RSAKey.from_private_key_file()方法可以加载SSH私钥文件，然后使用SSH客户端对象的connect()方法时指定私钥即可进行SSH密钥认证。
- SSH代理：使用paramiko.ProxyCommand()方法可以创建一个SSH代理对象，然后使用SSH客户端对象的connect()方法时指定代理即可进行SSH代理连接。

Paramiko库的使用需要一定的SSH协议和网络编程基础，但是它提供了非常方便的API，可以大大简化SSH连接和操作的编程工作。

# retrying
retrying是一个Python库，用于在函数执行失败时自动重试。它提供了一些装饰器和函数，可以方便地实现函数重试的逻辑。

retrying库的主要特点包括：
- 灵活的重试策略：可以通过设置stop_max_attempt_number、wait_fixed、wait_random_min等参数来控制重试的次数、间隔和随机性。
- 支持异常过滤：可以通过设置retry_on_exception参数来指定需要重试的异常类型，或者通过自定义函数来判断是否需要重试。
- 支持返回值过滤：可以通过设置retry_on_result参数来指定需要重试的返回值，或者通过自定义函数来判断是否需要重试。
- 支持日志输出：可以通过设置log_level和log_formatter参数来控制日志输出的级别和格式。

# traceback
traceback是Python标准库中的一个模块，用于打印和处理异常信息。它提供了一些函数，可以方便地获取和处理异常信息，以便进行调试和错误处理。

以下是traceback库的一些常用函数：
traceback.print_exc([limit[, file]])：打印当前异常的回溯信息到标准错误输出或指定文件中。
traceback.format_exc([limit])：返回当前异常的回溯信息字符串。
traceback.print_exception(etype, value, tb[, limit[, file]])：打印指定异常的回溯信息到标准错误输出或指定文件中。
traceback.format_exception(etype, value, tb[, limit])：返回指定异常的回溯信息字符串。
traceback.extract_tb(tb[, limit])：返回指定回溯信息中的栈帧列表。
traceback.extract_stack([f[, limit]])：返回当前调用栈中的栈帧列表。

## 又一次体现出chatgpt的智障
```
(base) D:\Users\User\Desktop>python k.py
******** starting ********
sftp connect to 172.22.65.15:22 root failed.
Traceback (most recent call last):
  File "k.py", line 39, in get_sftp_client
    self.sftp_client = paramiko.SFTPClient.from_transport(transport)
  File "C:\Users\User\anaconda3\lib\site-packages\paramiko\sftp_client.py", line 165, in from_transport
    window_size=window_size, max_packet_size=max_packet_size
  File "C:\Users\User\anaconda3\lib\site-packages\paramiko\transport.py", line 879, in open_session
    timeout=timeout,
  File "C:\Users\User\anaconda3\lib\site-packages\paramiko\transport.py", line 973, in open_channel
    window_size = self._sanitize_window_size(window_size)
  File "C:\Users\User\anaconda3\lib\site-packages\paramiko\transport.py", line 1970, in _sanitize_window_size
    return clamp_value(MIN_WINDOW_SIZE, window_size, MAX_WINDOW_SIZE)
  File "C:\Users\User\anaconda3\lib\site-packages\paramiko\util.py", line 308, in clamp_value
    return max(minimum, min(val, maximum))
TypeError: '<' not supported between instances of 'int' and 'str'

put file patrol.log to 172.22.65.15:22/media/hejian.log  failed.
Traceback (most recent call last):
  File "k.py", line 48, in put_file_to_remote
    self.sftp_client.put(local_path, remote_path)
AttributeError: 'NoneType' object has no attribute 'put'

uname: Linux ubuntu0006 4.4.0-210-generic #242-Ubuntu SMP Fri Apr 16 09:57:56 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux

process spend 0.538 s.
```
chatgpt告诉我是这个错误是由于 paramiko 库的版本不兼容所导致的。在 paramiko 2.7.2 版本中，_sanitize_window_size() 方法的参数类型已经从字符串改为整数，但是在旧版本中，该方法的参数类型仍然是字符串。

最后发现原因是port变量类型问题，需要传入是int整型。demo见：D:\Github\Storage\python\web\paramiko_example2.py










