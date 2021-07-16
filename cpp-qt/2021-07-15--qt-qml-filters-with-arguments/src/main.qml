import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import QtQuick.Dialogs 1.3

Window {
    width: 840
    height: 480
    visible: true
    title: qsTr("Hello World")

    function refreshImages() {}

    FileDialog {
        id: imageFileDialog
        title: "Please choose an image"
        folder: shortcuts.home

        onAccepted: {
            print("file dialog, selected: " + fileUrl)
            backend.loadImage(fileUrl)
            imageOriginal.source = ""
            imageOriginal.source = "image://imageProvider/imageOriginal"
            imageDistorted.source = ""
            imageDistorted.source = "image://imageProvider/imageDistorted"
        }
        onRejected: {
            print("file dialog rejected")
        }
        Component.onCompleted: visible = false
    }

    // column 1
    Column {
        width: parent.width * 0.2
        height: parent.height

        Text {
            text: qsTr("Load/Original")
            font.pointSize: 12
        }

        Button {
            text: "Open the file dialog"
            //            font.pointSize: 11
            onClicked: {
                imageFileDialog.open()
            }
        }

        Image {
            id: imageOriginal
            width: parent.width
            height: parent.width
            source: "image://imageProvider/imageOriginal"
        }

        Text {
            text: qsTr("Categories")
            font.pointSize: 12
        }

        // ------------ listViewCategories
        ListView {
            id: listViewCategories

            width: parent.width
            height: parent.height * 0.4

            model: ListModel {}
            delegate: Rectangle {
                height: 20
                width: parent.width
                color: "lightgray"
                Text {
                    padding: 3
                    text: {
                        if (!category || category === "")
                            return "All"
                        else
                            return category
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        print("listViewCategories: clicked " + category)

                        listViewAvailable.model.clear()
                        let list = backend.getDistortionDescriptions()
                        list.forEach(function (desc) {
                            if (desc.category.includes(category))
                                listViewAvailable.model.append({
                                                                   "desc": desc
                                                               })
                        })
                    }
                }
            }
            Component.onCompleted: {
                print("listViewCategories: onCompleted")
                model.append({
                                 "category": ""
                             })

                let list = backend.getDistortionDescriptions()
                let set = new Set()
                list.forEach(desc => set.add(desc.category))
                set.forEach(cat => model.append({
                                                    "category": cat
                                                }))
            }
        } // ------------ /listViewCategories
    } // /column 1

    // column 2
    Column {
        width: parent.width * 0.3
        height: parent.height
        x: parent.width * 0.2

        Text {
            text: qsTr("Available distortions")
            font.pointSize: 12
        }

        // ------------ listViewAvailable
        ListView {
            id: listViewAvailable

            width: parent.width
            height: parent.height

            model: ListModel {}
            delegate: Rectangle {
                height: 20
                width: parent.width
                color: "gray"
                Text {
                    padding: 3
                    text: {
                        let t = desc.name
                        return t
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        print("listViewAvailable: clicked")
                        listViewSelected.model.append({
                                                          "desc": desc
                                                      })
                    }
                }
            }
            Component.onCompleted: {
                print("listViewAvailable: onCompleted")

                let list = backend.getDistortionDescriptions()
                list.forEach(function (desc) {
                    model.append({
                                     "desc": desc
                                 })
                })
            }
        } // ------------ /listViewAvailable
    } // /column 2

    // column 3
    Column {
        width: parent.width * 0.3
        height: parent.height
        x: parent.width * 0.5

        Text {
            text: qsTr("Selected distortions")
            font.pointSize: 12
        }
        // ------------ listViewSelected
        ListView {
            id: listViewSelected
            width: parent.width
            height: parent.height * 0.5

            model: ListModel {}
            delegate: Rectangle {
                height: 20
                width: parent.width
                color: "lightgray"

                Text {
                    text: {
                        print("listViewSelected: delegate")

                        let t = desc.name
                        t += " ["
                        Object.keys(desc.arguments).forEach(function (a) {
                            t += ""
                            t += desc.arguments[a].name
                            t += ": "
                            t += desc.arguments[a].value
                            t += "; "
                        })
                        t += "]"
                        print("listViewSelected: delegate done")
                        return t
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        print("listViewSelected: clicked name, id: ",
                              desc.name, index)
                        listViewArguments.model.clear()
                        Object.keys(desc.arguments).forEach(function (key) {
                            listViewArguments.model.append({
                                                               "desc": desc,
                                                               "key": key,
                                                               "index": index,
                                                               "arg": desc.arguments[key]
                                                           })
                        })
                    }
                }
            }
        } // ------------ /listViewSelected

        Text {
            text: qsTr("Arguments")
            font.pointSize: 12
        }
        // ------------ listViewArguments
        ListView {
            id: listViewArguments
            width: parent.width
            height: parent.height * 0.5

            model: ListModel {}
            delegate: Rectangle {
                height: 20
                // width: parent.width
                color: "gray"

                Row {
                    Text {
                        text: {
                            `${arg.name}: [${arg.min}; ${arg.min}]`
                        }
                    }
                    Slider {
                        from: {
                            arg.min
                        }
                        value: {
                            arg.value
                        }
                        to: {
                            arg.max
                        }
                        onMoved: {
                            print("Argument changed from to: ", arg.name,
                                  arg.value, value)

                            let o = listViewSelected.model.get(index)
                            let d = o.desc
                            d.arguments[key].value = value
                            arg = d.arguments[key]
                            o.desc = d
                            listViewSelected.model.set(index, o)
                        }
                    }
                    Text {
                        id: valueText
                        text: {
                            `: ${arg.value.toFixed(2)}`
                        }
                    }
                }
            }
        } // ------------ /listViewArguments
    } // /column 3

    // column 4
    Column {
        width: parent.width * 0.3
        height: parent.height
        x: parent.width * 0.8

        Text {
            text: qsTr("Preview/save")
            font.pointSize: 12
        }

        Button {
            text: "Distort"
            onClicked: {
                print("distorting")
                let arr = []
                for (var i = 0; i < listViewSelected.model.count; i++) {
                    arr.push(listViewSelected.model.get(i).desc)
                }
                backend.distort(arr)
                imageDistorted.source = ""
                imageDistorted.source = "image://imageProvider/imageDistorted"
            }
        }

        Image {
            id: imageDistorted
            width: imageOriginal.width
            height: imageOriginal.width
            source: "image://imageProvider/imageDistorted"
        }
    } // /column 4
}
