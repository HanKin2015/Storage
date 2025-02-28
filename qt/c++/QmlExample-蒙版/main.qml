import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: true
    width: Screen.width
    height: Screen.height
    color: "black"
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.WindowTransparentForInput

    Text {
        id: text
        text: "这是一个蒙版"
        font.pixelSize: 30
        color: "white"
        anchors.centerIn: parent
    }
}
