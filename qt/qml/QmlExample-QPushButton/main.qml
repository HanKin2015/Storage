import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import com.example.myclass 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Hello QML"

    MyClass {
        id: myClass
    }

    Button {
        text: "Click Me"
        anchors.centerIn: parent
        onClicked: {
            console.log("Button clicked!")
        }
    }
}
