#!/usr/bin/env python3
import bisect
import collections
import sys
from PyQt5.QtCore import (QByteArray, QDataStream, QDate, QReadWriteLock, QThread,QIODevice, Qt)
from PyQt5.QtWidgets import (QApplication, QMessageBox, QPushButton)
from PyQt5.QtNetwork import (QAbstractSocket,QHostAddress, QTcpServer, QTcpSocket)

PORT = 9407
SIZEOF_UINT16 = 2
MAX_BOOKINGS_PER_DAY = 5

# Key = date, value = list of room IDs
Bookings = collections.defaultdict(list)


def printBookings():
  for key in sorted(Bookings):
    print(key, Bookings[key])
  print()


class Thread(QThread):

  lock = QReadWriteLock()

  def __init__(self, socketId, parent):
    super(Thread, self).__init__(parent)
    self.socketId = socketId


  def run(self):
    socket = QTcpSocket()
    if not socket.setSocketDescriptor(self.socketId):
      #self.emit(SIGNAL("error(int)"), socket.error())
      self.error.connect(socket.error)
      return
    while socket.state() == QAbstractSocket.ConnectedState:
      nextBlockSize = 0
      stream = QDataStream(socket)
      stream.setVersion(QDataStream.Qt_5_7)
      if (socket.waitForReadyRead() and
        socket.bytesAvailable() >= SIZEOF_UINT16):
        nextBlockSize = stream.readUInt16()
      else:
        self.sendError(socket, "Cannot read client request")
        return
      if socket.bytesAvailable() < nextBlockSize:
        if (not socket.waitForReadyRead(60000) or
          socket.bytesAvailable() < nextBlockSize):
          self.sendError(socket, "Cannot read client data")
          return
      action = ""
      room = ""
      date = QDate()
      action=stream.readQString()
      if action in ("BOOK", "UNBOOK"):
        room=stream.readQString()
        stream >> date
        try:
          Thread.lock.lockForRead()
          bookings = Bookings.get(date.toPyDate())
        finally:
          Thread.lock.unlock()
        uroom = str(room)
      if action == "BOOK":
        newlist = False
        try:
          Thread.lock.lockForRead()
          if bookings is None:
            newlist = True
        finally:
          Thread.lock.unlock()
        if newlist:
          try:
            Thread.lock.lockForWrite()
            bookings = Bookings[date.toPyDate()]
          finally:
            Thread.lock.unlock()
        error = None
        insert = False
        try:
          Thread.lock.lockForRead()
          if len(bookings) < MAX_BOOKINGS_PER_DAY:
            if uroom in bookings:
              error = "Cannot accept duplicate booking"
            else:
              insert = True
          else:
            error = "{0} is fully booked".format(date.toString(Qt.ISODate))
        finally:
          Thread.lock.unlock()
        if insert:
          try:
            Thread.lock.lockForWrite()
            bisect.insort(bookings, uroom)
          finally:
            Thread.lock.unlock()
          self.sendReply(socket, action, room, date)
        else:
          self.sendError(socket, error)
      elif action == "UNBOOK":
        error = None
        remove = False
        try:
          Thread.lock.lockForRead()
          if bookings is None or uroom not in bookings:
            error = "Cannot unbook nonexistent booking"
          else:
            remove = True
        finally:
          Thread.lock.unlock()
        if remove:
          try:
            Thread.lock.lockForWrite()
            bookings.remove(uroom)
          finally:
            Thread.lock.unlock()
          self.sendReply(socket, action, room, date)
        else:
          self.sendError(socket, error)
      else:
        self.sendError(socket, "Unrecognized request")
      socket.waitForDisconnected()
      try:
        Thread.lock.lockForRead()
        printBookings()
      finally:
        Thread.lock.unlock()


  def sendError(self, socket, msg):
    reply = QByteArray()
    stream = QDataStream(reply, QIODevice.WriteOnly)
    stream.setVersion(QDataStream.Qt_5_7)
    stream.writeUInt16(0)
    stream.writeQString("ERROR")
    stream.writeQString(msg)
    stream.device().seek(0)
    stream.writeUInt16(reply.size() - SIZEOF_UINT16)
    socket.write(reply)

  def sendReply(self, socket, action, room, date):
    reply = QByteArray()
    stream = QDataStream(reply, QIODevice.WriteOnly)
    stream.setVersion(QDataStream.Qt_5_7)
    stream.writeUInt16(0)
    stream.writeQString(action)
    stream.writeQString(room)
    stream<<date
    stream.device().seek(0)
    stream.writeUInt16(reply.size() - SIZEOF_UINT16)
    socket.write(reply)

class TcpServer(QTcpServer):

  def __init__(self, parent=None):
    super(TcpServer, self).__init__(parent)


  def incomingConnection(self, socketId):
    thread = Thread(socketId, self)
    #self.connect(thread, SIGNAL("finished()"),
    #       thread, SLOT("deleteLater()"))
    thread.finished.connect(thread.deleteLater)
    thread.start()


class BuildingServicesDlg(QPushButton):

  def __init__(self, parent=None):
    super(BuildingServicesDlg, self).__init__(
        "&Close Server", parent)
    self.setWindowFlags(Qt.WindowStaysOnTopHint)

    self.loadBookings()
    self.tcpServer = TcpServer(self)
    if not self.tcpServer.listen(QHostAddress("0.0.0.0"), PORT):
      QMessageBox.critical(self, "Building Services Server","Failed to start server: {0}".format(self.tcpServer.errorString()))
      self.close()
      return

    self.clicked.connect(self.close)
    font = self.font()
    font.setPointSize(24)
    self.setFont(font)
    self.setWindowTitle("Building Services Server")


  def loadBookings(self):
    # Generate fake data
    import random

    today = QDate.currentDate()
    for i in range(10):
      date = today.addDays(random.randint(7, 60))
      for j in range(random.randint(1, MAX_BOOKINGS_PER_DAY)):
        # Rooms are 001..534 excl. 100, 200, ..., 500
        floor = random.randint(0, 5)
        room = random.randint(1, 34)
        bookings = Bookings[date.toPyDate()]
        if len(bookings) >= MAX_BOOKINGS_PER_DAY:
          continue
        bisect.insort(bookings, "{0:1d}{1:02d}".format(
               floor, room))
    printBookings()


app = QApplication(sys.argv)
form = BuildingServicesDlg()
form.show()
form.move(0, 0)
app.exec_()