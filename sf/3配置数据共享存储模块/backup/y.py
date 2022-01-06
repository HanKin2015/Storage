import socket_library
import threading

def start_socket_thread():
    my_socket = self_socket_library()
    socket_thread = threading.Thread(target=my_socket.recv_message, args=('127.0.0.1', 21893,))
    socket_thread.setDaemon(True)
    socket_thread.start()
    return True
    
class self_socket_library(socket_library.socket_library):
    def parse_msg(self, pid, msg):
        print("okokokoo")

if __name__=='__main__':
    #start_socket_thread()
    my_socket = self_socket_library()
    my_socket.send_message('127.0.0.1', 21893, 'haha')
    input('等待输入')