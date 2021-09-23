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

    // title "select workout type and activity"
    Item {
        id: title_item

        anchors.top: parent.top
        anchors.topMargin: 100
        y: 100
        width: parent.width
        height: 100

        Label {
            text: qsTr("Select workout type and activity")
            anchors.fill: parent
            anchors.centerIn: parent
            font.pixelSize: 40
            fontSizeMode: Text.Fit
            color: "white"
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
        }
    }

    // workout type
    Item {
        id: workout_type_item

        width: parent.width
        height: 40
        anchors.top: title_item.bottom
        anchors.horizontalCenter: title_item.horizontalCenter
        anchors.topMargin: 60

        SwipeView {
            width: parent.width * 0.33
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter

            Label {
                text: qsTr("RUNNING")
                color: "white"
                horizontalAlignment: Text.AlignHCenter
            }
            Label {
                text: qsTr("CYCLING")
                color: "white"
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    // activity type
    Item {
        id: activity_item

        width: parent.width
        height: 40
        anchors.top: workout_type_item.bottom
        anchors.horizontalCenter: workout_type_item.horizontalCenter
        anchors.topMargin: 10

        PathView {
            width: parent.width
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter

            model: ListModel {
                ListElement { name: "ENDURANCE"}
                ListElement { name: "INTERVAL"}
                ListElement { name: "SOMETHING"}
                ListElement { name: "WHATEVER"}
            }
            delegate: Label {
                text: model.name
                color: "white"
                horizontalAlignment: Text.AlignHCenter
            }
            path: Path {
               startX: parent.width * 0.50
               startY: 0
               PathLine {
                   x: parent.width + parent.width * 0.25
                   y: 0
               }
               PathMove {
                   x: 0 - parent.width * 0.25
                   y: 0
               }
               PathLine {
                   x: parent.width * 0.50
                   y: 0
               }
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
