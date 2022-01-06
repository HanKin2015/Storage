import socket_library
import threading

def start_socket_thread(socket_handle):
    socket_thread = threading.Thread(target=socket_handle.recv_message, args=('127.0.0.1', 21893,))
    socket_thread.setDaemon(True)
    socket_thread.start()
    return True

x = 10

class self_socket_library(socket_library.socket_library):
    def parse_msg(self, pid, msg):
        print("okokokoo")
        global x
        x += 100

if __name__=='__main__':
    start_socket_thread()
    input('等待输入')
    print(x)