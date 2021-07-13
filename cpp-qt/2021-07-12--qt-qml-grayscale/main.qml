import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    function text2SetText(newText) {
        text2.text += newText
    }

    FileDialog {
        id: myFileDialog
        title: "Please choose a file"
        folder: shortcuts.home

        onAccepted: {
            console.log("You chose: " + myFileDialog.fileUrl)
            model.loadImages(myFileDialog.fileUrl)
            myImage1.source = ""
            myImage1.source = "image://imageProvider/image1"
            myImage2.source = ""
            myImage2.source = "image://imageProvider/image2"
        }
        onRejected: {
            console.log("Canceled")
        }
        Component.onCompleted: visible = false
    }

    Rectangle {
        width: parent.width
        height: parent.height
        border.color: "black"
        border.width: 5
        radius: 10

        Row {
            height: parent.height
            padding: 10
            width: parent.width * 1.0

            Column {
                width: parent.width * 0.25
                padding: 4

                Text {
                    text: qsTr("Hello world!")
                    font.pointSize: 11
                }
                Text {
                    text: qsTr("Hello world!")
                    font.pointSize: 11
                }

                Button {
                    text: "Open the file dialog"
                    font.pointSize: 11
                    onClicked: {
                        myFileDialog.open()
                    }
                }

                Image {
                    id: myImage1
                    width: parent.width
                    height: parent.width
                    source: "image://imageProvider/image1"
                }
                Text {
                    text: qsTr("Hello world!")
                    font.pointSize: 11
                }
                Image {
                    id: myImage2
                    width: parent.width
                    height: parent.width
                    source: "image://imageProvider/image2"
                }
            }

            Column {
                width: parent.width * 0.3
                height: parent.height * 0.95
                padding: 4

                Text {
                    text: qsTr("Hello world!")
                    font.pointSize: 18
                }

                Rectangle {
                    width: parent.width * 0.9
                    height: parent.height * 0.7
                    border.color: "black"
                    border.width: 5
                    radius: 10

                    ListView {
                        width: parent.width
                        height: parent.height
                        rightMargin: 10
                        leftMargin: 10
                        topMargin: 10
                        bottomMargin: 10
                        clip: true

                        highlight: Rectangle {
                            color: "lightsteelblue"
                            radius: 5
                        }
                        model: ListModel {
                            ListElement {
                                name: "Bill Smith"
                                number: "555 3264"
                            }
                            ListElement {
                                name: "John Brown"
                                number: "555 8426"
                            }
                            ListElement {
                                name: "Sam Wise"
                                number: "555 0473"
                            }
                        }
                        delegate: Text {
                            text: name + ": " + number
                            font.pointSize: 11
                        }
                    }
                }

                Text {
                    text: qsTr("Hello world!")
                    font.pointSize: 11
                }
            }

            Column {
                width: parent.width * 0.5
                padding: 4

                Text {
                    id: text1
                    objectName: qsTr("text1")
                    text: qsTr("Hello world!")
                    font.pointSize: 11
                }
                Text {
                    id: text2
                    text: qsTr("Hello world!")
                    font.pointSize: 11
                }

                Button {
                    text: "Ok"
                    font.pointSize: 11
                    onClicked: model.buttonOkOnClicked()
                }
                Button {
                    text: "Cancel"
                    font.pointSize: 11
                    onClicked: model.buttonCancelOnClicked()
                }

                RangeSlider {
                    from: 1
                    to: 100
                    first.value: 25
                    second.value: 75
                    function updateText() {
                        textSliderValue.text = Math.floor(
                                    first.value) + "-" + Math.floor(
                                    second.value)
                    }
                    first.onMoved: {
                        updateText()
                    }
                    second.onMoved: {
                        updateText()
                    }
                }
                Text {
                    id: textSliderValue
                    text: qsTr("Hello world!")
                    font.pointSize: 11
                }
            }
        }
    }
}
