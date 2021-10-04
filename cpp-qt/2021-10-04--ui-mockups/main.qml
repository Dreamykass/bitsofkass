import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15

Window {
    width: 400
    height: 800
    visible: true
    title: qsTr("Hello World")

    StackView {
        id: mainStackView
        initialItem: "Login.qml"
        anchors.fill: parent
    }

    function changeMainStackViewPageTo(pageName) {
        mainStackView.clear()
        mainStackView.push(pageName)
    }
}
