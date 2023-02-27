import sys
from PyQt5.QtNetwork import QUdpSocket, QHostAddress
from PyQt5.QtWidgets import QApplication, QWidget, QTextBrowser, QVBoxLayout


class Client(QWidget):

    def __init__(self):
        super(Client, self).__init__()

        # 1
        self.sock = QUdpSocket(self)
        #self.sock.bind(QHostAddress.LocalHost, 6666)
        self.sock.bind(QHostAddress.Any, 6666)
        self.sock.readyRead.connect(self.read_data_slot)
        
        # 2
        self.browser = QTextBrowser(self)

        self.layout = QVBoxLayout()
        self.layout.addWidget(self.browser)
        self.setLayout(self.layout)

    def read_data_slot(self):
        while self.sock.hasPendingDatagrams():
            datagram, host, port = self.sock.readDatagram(
                self.sock.pendingDatagramSize()
            )

            messgae = 'Date time: {}\nHost: {}\nPort: {}\n\n'.format(datagram.decode(), host.toString(), port)
            self.browser.append(messgae)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    demo = Client()
    demo.show()
    sys.exit(app.exec_())