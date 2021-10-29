import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12

Window {
    width: 480
    height: 640
    visible: true
    title: qsTr("Hello World")

    Page {
        anchors.fill: parent

        background: Rectangle {
            color: "gray"
        }

        footer: TabBar {
            id: layoutSelector

            TabButton {
                text: qsTr("values only")
            }
            TabButton {
                text: qsTr("one chart")
            }
            TabButton {
                text: qsTr("two charts")
            }
        }

        Rectangle {
            id: blueRect

            color: "blue"

            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            width: parent.width
            height: {
                switch (layoutSelector.currentIndex) {
                case 0:
                    return parent.height * 1.00
                case 1:
                    return parent.height * 0.25
                case 2:
                    return parent.height * 0.10
                }
            }

            Behavior on height {
                SpringAnimation {
                    velocity: 400
                }
            }

            Label {
                text: "values here"
                anchors.centerIn: parent
                font.pixelSize: parent.height * 0.8
            }
        }

        Rectangle {
            id: redYellowRect

            color: "gray"

            anchors.top: blueRect.bottom
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            width: parent.width

            Rectangle {
                id: redRect

                color: "red"

                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter

                width: parent.width
                height: {
                    switch (layoutSelector.currentIndex) {
                    case 0:
                        return parent.height * 0.00
                    case 1:
                        return parent.height * 0.00
                    case 2:
                        return parent.height * 0.30
                    }
                }

                Behavior on height {
                    SpringAnimation {
                        velocity: 400
                    }
                }
            }

            Rectangle {
                id: yellowRect

                color: "yellow"

                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter

                width: parent.width
                height: {
                    switch (layoutSelector.currentIndex) {
                    case 0:
                        return parent.height * 0.00
                    case 1:
                        return parent.height * 1.00
                    case 2:
                        return parent.height * 0.70
                    }
                }

                Behavior on height {
                    SpringAnimation {
                        velocity: 400
                    }
                }
            }
        }
    }
}
