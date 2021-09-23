import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    function updateTime(newTime) {
        console.log(newTime)
        time_value.text = newTime
    }

    Text {
        id: time_value
        anchors.centerIn: parent
        font.pixelSize: 40
        text: "123"
    }
}
