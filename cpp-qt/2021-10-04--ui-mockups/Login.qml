import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    Text {
        text: qsTr("login screen")
    }

    Button {
        y: 300
        text: "log in"
        onClicked: {
            changeMainStackViewPageTo("Home.qml")
        }
    }
}
