import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: parent.width
    height: parent.height

    title: qsTr("Home")

    background: Rectangle {
        color: "#05071b"
    }

    Column {
        anchors.centerIn: parent

        //        Label {
        //            text: qsTr("Select workout type and activity")
        //            color: "white"
        //            // anchors.centerIn: parent
        //        }
        Flickable {

            // ...
            // anchors.centerIn: parent
            ScrollBar.horizontal: ScrollBar {}

            Row {
                //                Item {
                Label {
                    text: qsTr("Select workout type and activity")
                    color: "white"
                }
                //                }
                //                Item {
                Label {
                    text: qsTr("Select workout type and activity")
                    color: "white"
                }
                //                }
                //                Item {
                Label {
                    text: qsTr("Select workout type and activity")
                    color: "white"
                }
                //                }
            }
        }
    }

    Rectangle {
        anchors.bottom: parent.bottom
        color: "#e52821"
        width: page.width
        height: 100

        Text {
            id: name
            text: qsTr("START")
            color: "white"
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("pressed")
                stackView.push("Page1Form.qml")
            }
        }
    }
}
