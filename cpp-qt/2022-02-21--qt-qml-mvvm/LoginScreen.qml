import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12

Item {
    id: view

    anchors.fill: parent

    // to Mv
    signal setUsername(string username)

    // to controller
    signal clickedLogin

    Column {
        Label {
            text: "login screen"
            font.pixelSize: 100
        }
        TextField {
            placeholderText: qsTr("login")
            onTextChanged: {
                view.setUsername(text)
            }
        }
        Button {
            text: "login"
            onClicked: {
                clickedLogin()
            }
        }
    }
}
