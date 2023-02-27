#!/usr/bin/env python3

import sys
from PyQt5.QtCore import (QByteArray, QDataStream, QDate, QIODevice,
    QRegExp, Qt)
from PyQt5.QtWidgets import (QApplication, QDateEdit, QFrame, QGridLayout,
    QHBoxLayout, QLabel, QLineEdit, QPushButton,
    QWidget)
from PyQt5.QtGui import QRegExpValidator
from PyQt5.QtNetwork import (QTcpSocket,)

MAC = True
try:
  from PyQt5.QtGui import qt_mac_set_native_menubar
except ImportError:
  MAC = False

PORT = 9407
SIZEOF_UINT16 = 2


class BuildingServicesClient(QWidget):

  def __init__(self, parent=None):
    super(BuildingServicesClient, self).__init__(parent)

    self.socket = QTcpSocket()
    self.nextBlockSize = 0
    self.request = None

    roomLabel = QLabel("&Room")
    self.roomEdit = QLineEdit()
    roomLabel.setBuddy(self.roomEdit)
    regex = QRegExp(r"[0-9](?:0[1-9]|[12][0-9]|3[0-4])")
    self.roomEdit.setValidator(QRegExpValidator(regex, self))
    self.roomEdit.setAlignment(Qt.AlignRight|Qt.AlignVCenter)
    dateLabel = QLabel("&Date")
    self.dateEdit = QDateEdit()
    dateLabel.setBuddy(self.dateEdit)
    self.dateEdit.setAlignment(Qt.AlignRight|Qt.AlignVCenter)
    self.dateEdit.setDate(QDate.currentDate().addDays(1))
    self.dateEdit.setDisplayFormat("yyyy-MM-dd")
    responseLabel = QLabel("Response")
    self.responseLabel = QLabel()
    self.responseLabel.setFrameStyle(QFrame.StyledPanel|QFrame.Sunken)

    self.bookButton = QPushButton("&Book")
    self.bookButton.setEnabled(False)
    self.unBookButton = QPushButton("&Unbook")
    self.unBookButton.setEnabled(False)
    quitButton = QPushButton("&Quit")
    if not MAC:
      self.bookButton.setFocusPolicy(Qt.NoFocus)
      self.unBookButton.setFocusPolicy(Qt.NoFocus)

    buttonLayout = QHBoxLayout()
    buttonLayout.addWidget(self.bookButton)
    buttonLayout.addWidget(self.unBookButton)
    buttonLayout.addStretch()
    buttonLayout.addWidget(quitButton)
    layout = QGridLayout()
    layout.addWidget(roomLabel, 0, 0)
    layout.addWidget(self.roomEdit, 0, 1)
    layout.addWidget(dateLabel, 0, 2)
    layout.addWidget(self.dateEdit, 0, 3)
    layout.addWidget(responseLabel, 1, 0)
    layout.addWidget(self.responseLabel, 1, 1, 1, 3)
    layout.addLayout(buttonLayout, 2, 1, 1, 4)
    self.setLayout(layout)

    self.socket.connected.connect(self.sendRequest)
    self.socket.readyRead.connect(self.readResponse)
    self.socket.disconnected.connect(self.serverHasStopped)
    #self.connect(self.socket,
    #       SIGNAL("error(QAbstractSocket::SocketError)"),
     #      self.serverHasError)
    self.socket.error.connect(self.serverHasError)
    self.roomEdit.textEdited.connect(self.updateUi)
    self.dateEdit.dateChanged.connect(self.updateUi)

    self.bookButton.clicked.connect(self.book)
    self.unBookButton.clicked.connect(self.unBook)
    quitButton.clicked.connect(self.close)

    self.setWindowTitle("Building Services")


  def updateUi(self):
    enabled = False
    if (self.roomEdit.text() and
      self.dateEdit.date() > QDate.currentDate()):
      enabled = True
    if self.request is not None:
      enabled = False
    self.bookButton.setEnabled(enabled)
    self.unBookButton.setEnabled(enabled)


  def closeEvent(self, event):
    self.socket.close()
    event.accept()


  def book(self):
    self.issueRequest("BOOK", self.roomEdit.text(),
             self.dateEdit.date())


  def unBook(self):
    self.issueRequest("UNBOOK", self.roomEdit.text(),
             self.dateEdit.date())


  def issueRequest(self, action, room, date):
    self.request = QByteArray()
    stream = QDataStream(self.request, QIODevice.WriteOnly)
    stream.setVersion(QDataStream.Qt_5_7)
    stream.writeUInt16(0)
    stream.writeQString(action)
    stream.writeQString(room)
    stream << date
    stream.device().seek(0)
    stream.writeUInt16(self.request.size() - SIZEOF_UINT16)#overwrite seek(0)
    self.updateUi()
    if self.socket.isOpen():
      self.socket.close()
    self.responseLabel.setText("Connecting to server...")
    self.socket.connectToHost("localhost", PORT)


  def sendRequest(self):
    self.responseLabel.setText("Sending request...")
    self.nextBlockSize = 0
    self.socket.write(self.request)
    self.request = None


  def readResponse(self):
    stream = QDataStream(self.socket)
    stream.setVersion(QDataStream.Qt_5_7)

    while True:
      if self.nextBlockSize == 0:
        if self.socket.bytesAvailable() < SIZEOF_UINT16:
          break
        self.nextBlockSize = stream.readUInt16()
      if self.socket.bytesAvailable() < self.nextBlockSize:
        break
      action = ""
      room = ""
      date = QDate()
      #stream >> action >> room
      action=stream.readQString()
      room=stream.readQString()
      if action != "ERROR":
        stream >> date
      if action == "ERROR":
        msg = "Error: {0}".format(room)
      elif action == "BOOK":
        msg = "Booked room {0} for {1}".format(room,date.toString(Qt.ISODate))
      elif action == "UNBOOK":
        msg = "Unbooked room {0} for {1}".format(room,date.toString(Qt.ISODate))
      self.responseLabel.setText(msg)
      self.updateUi()
      self.nextBlockSize = 0


  def serverHasStopped(self):
    self.responseLabel.setText(
        "Error: Connection closed by server")
    self.socket.close()


  def serverHasError(self, error):
    self.responseLabel.setText("Error: {0}".format(self.socket.errorString()))
    self.socket.close()


app = QApplication(sys.argv)
form = BuildingServicesClient()
form.show()
app.exec_()