import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: initial_page
    objectName: "initial_page"

    Label {
        text: "initial page"
        x: 10
        y: 10
        font.pixelSize: 30
    }

    Button {
        text: "start discovery"
        y: 200
        onClicked: {
            backend.startDiscovery()
            text = "start discovery... again"
        }
    }

    ListView {
        id: peripheral_list

        width: parent.width
        height: parent.height * 0.50
        y: parent.height * 0.50

        model: ListModel {}
        delegate: Button {
            text: name + " {" + address + "}"
            onClicked: {
                console.log("clicked peripheral: " + name)
                backend.selectPeripheral(name, address)
            }
        }
    }

    function foundPeripheral(name, address) {
        console.log("foundPeripheral: ", name, address)
        peripheral_list.model.append({
                                         "name": name,
                                         "address": address
                                     })
    }
}
