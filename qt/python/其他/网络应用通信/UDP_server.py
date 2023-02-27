import sys
from PyQt5.QtCore import Qt, QTimer, QDateTime
from PyQt5.QtNetwork import QUdpSocket, QHostAddress
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QLabel, QVBoxLayout

class Server(QWidget):

    def __init__(self):
        super(Server, self).__init__()

        # 1
        self.sock = QUdpSocket(self)

        # 2
        self.label = QLabel('0', self)
        self.label.setAlignment(Qt.AlignCenter)
        self.btn = QPushButton('Start Server', self)
        self.btn.clicked.connect(self.start_stop_slot)

        self.v_layout = QVBoxLayout()
        self.v_layout.addWidget(self.label)
        self.v_layout.addWidget(self.btn)
        self.setLayout(self.v_layout)

        # 3
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.send_data_slot)

    def start_stop_slot(self):
        if not self.timer.isActive():
            self.btn.setText('Stop Server')
            self.timer.start(1000)
        else:
            self.btn.setText('Start Server')
            self.timer.stop()

    def send_data_slot(self):
        message = QDateTime.currentDateTime().toString()
        self.label.setText(message)

        datagram = message.encode()
        #self.sock.writeDatagram(datagram, QHostAddress.LocalHost, 6666)
        self.sock.writeDatagram(datagram, QHostAddress("172.22.192.97"), 6666)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    demo = Server()
    demo.show()
    sys.exit(app.exec_())