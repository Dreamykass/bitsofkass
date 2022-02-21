import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12

Window {
    id: mainWindow
    objectName: "mainWindow"

    width: 800
    height: 800
    visible: true
    title: qsTr("Hello World")

    function setView(viewUrl) {
        console.log("loading view: ", viewUrl)
        mainLoader.source = viewUrl
    }

    function getView() {
        console.log("getting current view")
        return mainLoader.item
    }

    Loader {
        anchors.fill: parent
        id: mainLoader
    }

    Timer {
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            console.log("current view: ", mainLoader.source)
        }
    }
}
