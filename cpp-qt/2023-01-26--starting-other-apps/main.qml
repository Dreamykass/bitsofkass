import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Column {
        anchors.centerIn: parent
        width: parent.width * .90

        Label {
            text: "hmm"
        }

        Label {
            text: "hmm2"
        }

        Button {
            id: backendCheckButton
            text: "backend check"
            onClicked: {
                text = text + Backend.backendCheck()
            }
        }

        Label {
            text: "app package name: "
        }

        TextInput {
            id: packageNameInput
            width: parent.width
            height: backendCheckButton.height
            text: "org.oxy"
        }

        Button {
            text: "Backend.isAppInstalled()"
            onClicked: {
                Backend.isAppInstalled(packageNameInput.text)
            }
        }

        Button {
            text: "Backend.openPlayStoreForApp()"
            onClicked: {
                Backend.openPlayStoreForApp(packageNameInput.text)
            }
        }

        Button {
            text: "Backend.openAppByPkgName()"
            onClicked: {
                Backend.openAppByPkgName(packageNameInput.text)
            }
        }

        Button {
            text: "Backend.openAppByPkgNameOrPlayStore()"
            onClicked: {
                Backend.openAppByPkgNameOrPlayStore(packageNameInput.text)
            }
        }

        Label {
            text: "app package name: "
        }

        TextInput {
            id: strArgInput
            width: parent.width
            height: backendCheckButton.height
        }

        Button {
            text: "Backend.openAppByPkgNameWithStrArg()"
            onClicked: {
                Backend.openAppByPkgNameWithStrArg(packageNameInput.text,
                                                   strArgInput.text)
            }
        }
    }

    // -
    // -
    // -
    // -
    // -
    // -
    // -
    // -
    // -
    // -
    // -
    // -
    // -
    // -
    // -
    // -
    // -
}
