import QtQuick 2.12
import QtQuick.Controls 2.5
import QtCharts 2.15
import QtQuick.Shapes 1.0

Page {
    anchors.fill: parent

    title: qsTr("Page 1")

    background: Rectangle {
        color: "#05071b" // background blue
    }

    // top time counter
    Item {
        id: top_time_counter_item

        anchors.top: parent.top
        height: parent.height * 0.10
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
        height: parent.height * 0.08
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

    function getRandomBetween(min, max) {
        return Math.random() * (max - min) + min
    }

    function update(p) {
        console.log("updated with: " + p)

        // chart:
        if (p <= 54) {
            chart_barset_green.append(p)
            chart_barset_red.append(0)
        } else {
            chart_barset_green.append(0)
            chart_barset_red.append(p)
        }

        chart_bar_value_axis_x.max = chart_barset_green.values.length

        //---
        // percent circle:
        current_percent_circle_text.text = Math.floor(p) + "%"
    }

    Timer {
        interval: 250
        running: true
        repeat: true
        onTriggered: {
            var p = getRandomBetween(49, 59)
            update(p)
        }
    }

    // chart
    Item {
        id: chart_item

        anchors.top: stats_item.bottom
        anchors.left: parent.left
        height: parent.height * 0.50
        width: parent.width

        ChartView {
            id: chart_view

            title: "Stacked Bar series"
            anchors.fill: parent
            legend.alignment: Qt.AlignBottom
            legend.visible: false
            antialiasing: true
            backgroundColor: "#05071b"
            animationOptions: ChartView.AllAnimations

            StackedBarSeries {
                id: chart_bar_series

                barWidth: 1

                axisX: ValueAxis {
                    id: chart_bar_value_axis_x
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
                    id: chart_barset_green
                    label: "Green" // more than 54
                    color: "#28d16f"
                    borderWidth: 0
                    values: [58, 57, 56, 55, 0, 0, 0, 0]
                }
                BarSet {
                    id: chart_barset_red
                    label: "Red" // less than 54
                    color: "#df1730"
                    borderWidth: 0
                    values: [0, 0, 0, 0, 54, 53, 53, 52]
                }

//                BarSet {
//                    label: "Red" // less than 54
//                    color: "#df1730"
//                    borderWidth: 0
//                    values: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ]
//                }
            }
        }
    }

    // two dots whatever
    Item {
        id: two_dots_item

        anchors.top: chart_item.bottom
        height: parent.height * 0.06
        width: parent.width

        Rectangle {
            width: 10
            height: 10
            color: "white"
            radius: width * 0.5
            y: parent.height * 0.01
            x: parent.width * 0.50 + radius
        }
        Rectangle {
            width: 10
            height: 10
            color: "#e52821" // red
            radius: width * 0.5
            y: parent.height * 0.01
            x: parent.width * 0.50 - (radius * 3)
        }
    }

    // current percent thing
    Item {
        id: current_percent_item

        anchors.top: two_dots_item.bottom
        height: parent.height * 0.10
        width: parent.width

        // dotted line
        Item {
            id: dotted_line_item

            width: parent.width * 0.6
            height: parent.height
            anchors.centerIn: parent

            Shape {
                y: parent.height * 0.50
                width: 2
                ShapePath {
                    strokeColor: "white"
                    strokeWidth: 2
                    strokeStyle: ShapePath.DashLine
                    dashPattern: [1, 8]
                    startX: 0
                    startY: 0
                    PathLine {
                        x: parent.width * 0.6
                        y: 0
                    }
                }
            }
        }

        // small white circle left
        Rectangle {
            id: small_circle_left

            width: parent.height * 0.20
            height: parent.height * 0.20
            color: "white"
            radius: width * 0.50
            y: parent.height * 0.50 - radius
            anchors.right: dotted_line_item.left
        }

        // small white circle right
        Rectangle {
            id: small_circle_right

            width: parent.height * 0.20
            height: parent.height * 0.20
            color: "white"
            radius: width * 0.50
            y: parent.height * 0.50 - radius
            anchors.left: dotted_line_item.right
        }

        // text left "MIN"
        Item {
            width: parent.width * 0.10
            height: parent.height * 0.50
            anchors.right: small_circle_left.left
            anchors.rightMargin: 4
            y: parent.height * 0.25

            Label {
                anchors.centerIn: parent
                text: qsTr("MIN")
                color: "white"
                font.pixelSize: parent.height / 2
            }
        }

        // text right "MAX"
        Item {
            width: parent.width * 0.10
            height: parent.height * 0.50
            anchors.left: small_circle_right.right
            anchors.leftMargin: 4
            y: parent.height * 0.25

            Label {
                anchors.centerIn: parent
                text: qsTr("MAX")
                color: "white"
                font.pixelSize: parent.height / 2
            }
        }

        // text & triangle above left "MIX"
        Item {
            width: small_circle_left.width
            height: small_circle_left.height
            anchors.bottom: small_circle_left.top
            anchors.horizontalCenter: small_circle_left.horizontalCenter

            Label {
                id: small_label_left_min

                anchors.bottom: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("50%")
                color: "white"
                font.pixelSize: 12
            }

            Shape {
                width: parent.width
                height: parent.height
                anchors.centerIn: parent
                antialiasing: true
                ShapePath {
                    startX: 0
                    startY: 0
                    PathLine {
                        x: small_circle_left.width
                        y: 0
                    }
                    PathLine {
                        x: small_circle_left.width * 0.50
                        y: small_circle_left.height
                    }
                }
            }
        }

        // text & triangle above right "MAX"
        Item {
            width: small_circle_right.width
            height: small_circle_right.height
            anchors.top: small_circle_right.bottom
            anchors.horizontalCenter: small_circle_right.horizontalCenter

            Label {
                id: small_label_right_max

                anchors.top: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("59%")
                color: "white"
                font.pixelSize: 12
            }

            Shape {
                width: parent.width
                height: parent.height
                anchors.centerIn: parent
                antialiasing: true
                ShapePath {
                    startX: small_circle_left.width * 0.50
                    startY: 0
                    PathLine {
                        x: small_circle_left.width
                        y: small_circle_left.height
                    }
                    PathLine {
                        x: 0
                        y: small_circle_left.height
                    }
                }
            }
        }

        // white big middle circle
        Rectangle {
            id: current_percent_circle

            width: parent.height * 0.80
            height: parent.height * 0.80
            color: "white"
            radius: width * 0.50
            x: parent.width * 0.50 - radius
            y: parent.height * 0.50 - radius

            Text {
                id: current_percent_circle_text
                anchors.centerIn: parent
                color: "#05071b" // background blue
                text: "54%"
            }
        }
    }

    // stop/pause circles:
    Row {
        anchors.bottom: parent.bottom
        height: parent.height * 0.16
        width: parent.width

        // STOP
        Rectangle {
            width: parent.height * 0.80
            height: parent.height * 0.80
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
            width: parent.height * 0.80
            height: parent.height * 0.80
            color: "#e52821" // red
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
