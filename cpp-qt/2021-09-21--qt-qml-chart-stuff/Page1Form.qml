import QtQuick 2.12
import QtQuick.Controls 2.5
import QtCharts 2.15

Page {
    anchors.fill: parent

    title: qsTr("Page 1")

    background: Rectangle {
        color: "#05071b"
    }

    // top time counter
    Item {
        id: top_time_counter_item

        anchors.top: parent.top
        height: parent.height * 0.20
        width: parent.width

        Label {
            anchors.centerIn: parent
            text: qsTr("00:21:38")
            color: "white"
            font.pixelSize: parent.height / 2
        }
    }

    // stats: distance, pace, heart rate
    Item {
        id: stats_item

        anchors.top: top_time_counter_item.bottom
        anchors.left: parent.left
        height: parent.height * 0.10
        width: parent.width

        Column {
            height: parent.height
            width: parent.width * 0.33
            anchors.left: parent.left
            anchors.top: parent.top

            Item {
                anchors.top: parent.top
                anchors.left: parent.left
                height: parent.height * 0.50
                width: parent.width
                Label {
                    anchors.centerIn: parent
                    text: qsTr("0.00 mi")
                    color: "white"
                    font.pixelSize: 20
                }
            }
            Item {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                height: parent.height * 0.50
                width: parent.width
                Label {
                    anchors.centerIn: parent
                    text: qsTr("TOTAL DISTANCE")
                    color: "#e52821"
                    font.pixelSize: 10
                }
            }
        }

        Column {
            width: parent.width * 0.33
            height: parent.height
            x: parent.width * 0.33

            Item {
                anchors.top: parent.top
                anchors.left: parent.left
                height: parent.height * 0.50
                width: parent.width
                Label {
                    anchors.centerIn: parent
                    text: qsTr("---")
                    color: "white"
                    font.pixelSize: 20
                }
            }
            Item {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                height: parent.height * 0.50
                width: parent.width
                Label {
                    anchors.centerIn: parent
                    text: qsTr("AVERAGE PACE")
                    color: "#e52821"
                    font.pixelSize: 10
                }
            }
        }
        Column {
            anchors.right: parent.right
            height: parent.height
            width: parent.width * 0.33

            Item {
                anchors.top: parent.top
                anchors.left: parent.left
                height: parent.height * 0.50
                width: parent.width
                Label {
                    anchors.centerIn: parent
                    text: qsTr("---")
                    color: "white"
                    font.pixelSize: 20
                }
            }
            Item {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                height: parent.height * 0.50
                width: parent.width
                Label {
                    anchors.centerIn: parent
                    text: qsTr("HEART RATE")
                    color: "#e52821"
                    font.pixelSize: 10
                }
            }
        }
    }

    // chart
    Item {
        id: chart_item

        anchors.top: stats_item.bottom
        anchors.left: parent.left
        height: parent.height * 0.5
        width: parent.width

        ChartView {
            title: "Stacked Bar series"
            anchors.fill: parent
            legend.alignment: Qt.AlignBottom
            legend.visible: false
            antialiasing: true
            backgroundColor: "#05071b"

            StackedBarSeries {
                axisX: ValueAxis {
                    lineVisible: false
                    gridVisible: false
                    minorGridVisible: false
                    visible: false
                }
                axisY: ValueAxis {
                    lineVisible: false
                    gridVisible: false
                    minorGridVisible: false
                    labelsVisible: true
                    labelsColor: "white"
                    visible: true
                    labelFormat: "%d%%"
                    min: 43
                    max: 63
                }

                BarSet {
                    label: "Green"
                    color: "#28d16f"
                    borderWidth: 0
                    values: [58, 57, 56, 55, 0, 0, 0, 0]
                }
                BarSet {
                    label: "Red"
                    color: "#df1730"
                    borderWidth: 0
                    values: [0, 0, 0, 0, 54, 53, 53, 52]
                }
            }
        }
    }

    // current thing
    Item {}

    // stop/pause circles:
    Row {
        anchors.bottom: parent.bottom
        height: parent.height * 0.20
        width: parent.width

        // STOP
        Rectangle {
            width: parent.width * 0.2
            height: parent.width * 0.2
            color: "#e52821"
            radius: width * 0.5
            anchors.left: parent.left
            anchors.leftMargin: radius

            Text {
                anchors.centerIn: parent
                color: "white"
                text: "STOP"
            }
        }

        // PAUSE
        Rectangle {
            width: parent.width * 0.2
            height: parent.width * 0.2
            color: "#e52821"
            radius: width * 0.5
            anchors.right: parent.right
            anchors.rightMargin: radius

            Text {
                anchors.centerIn: parent
                color: "white"
                text: "PAUSE"
            }
        }
    }
}
