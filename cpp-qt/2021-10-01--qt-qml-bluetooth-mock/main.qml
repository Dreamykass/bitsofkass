import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    //    id: appwindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    StackView {
        id: stackView
        initialItem: "initial.qml"
        anchors.fill: parent
    }

    // current state debug on screen
    Item {
        Label {
            id: current_state_debug_label
            x: 100
            y: 100
            font.pixelSize: 20
            text: "???"
        }
        Timer {
            interval: 250
            running: true
            repeat: true
            onTriggered: {
                var cs = backend.getCurrentStateStr()
                current_state_debug_label.text = `current state: ` + cs
            }
        }
    }

    function connecting() {
        console.log("connecting")
        stackView.clear()
        stackView.push("connecting.qml")
    }

    function connected() {
        console.log("connected!")
        stackView.clear()
        stackView.push("connected.qml")
    }
}
