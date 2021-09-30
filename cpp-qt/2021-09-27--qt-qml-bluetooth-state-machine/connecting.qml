import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    Label {
        text: "connecting"
        x: 10
        y: 10
        font.pixelSize: 30
    }

    BusyIndicator {
        anchors.fill: parent
        running: true
    }
}
