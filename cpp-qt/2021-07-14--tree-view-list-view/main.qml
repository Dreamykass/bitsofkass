import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import Tree 1.0
import QtQml.Models 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Component {
        id: treeNodeComponent
        TreeNode {
            property string name: "default name"
            property var distortionDescription: null
        }
    }

    Column {
        width: parent.width * 0.5
        height: parent.height

        Text {
            text: qsTr("tree")
        }

        // ------------ treeview
        TreeView {
            id: treeView
            width: parent.width
            height: parent.height
            model: TreeModel {
                id: treeModel
                roles: ["name"]
            }

            TableViewColumn {
                role: "name"
                width: 99999
            }

            itemDelegate: MouseArea {
                Rectangle {
                    anchors.fill: parent
                    color: (styleData.row % 2 == 0) ? "white" : "lightgrey"
                    height: 20

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text: styleData.value === undefined ? "" : styleData.value // The branches don't have a description_role so styleData.value will be undefined
                    }
                    // console.log("Saving the current project...");
                }

                onDoubleClicked: {
                    let node = treeView.model.getNodeByIndex(styleData.index)
                    print("tree: double-clicked element: " + node.name)

                    if (node === null || node === undefined) {
                        print("tree: node is null or undefined")
                        return
                    }

                    if (node.distortionDescription === null
                            || node.distortionDescription === undefined) {
                        print("tree: and it is a category")
                        return
                    }

                    // "distortionDescription": node.distortionDescription
                    //"distortionDescription": {
                    //    "name": "foo"
                    //}
                    // JSON.parse(JSON.stringify(node.distortionDescription))
                    listView.model.append({
                                              "distortionDescription": node.distortionDescription
                                          })
                }
            }

            Component.onCompleted: {
                print("tree: onCompleted")

                let list = backend.getDistortionDescriptions()
                let map = new Map()

                const listForEach = function (desc) {
                    if (!map.has(desc.category)) {
                        map.set(desc.category, [desc])
                    } else {
                        map.get(desc.category).push(desc)
                    }
                }

                list.forEach(listForEach)

                const mapForEach = function (descriptions, category) {
                    console.assert(!(category === "" || category === undefined))

                    var topNode = treeNodeComponent.createObject()
                    topNode.name = category
                    model.insertNode(topNode)

                    const descriptionsForEach = function (desc) {
                        var node = treeNodeComponent.createObject()
                        node.name = desc.name
                        node.distortionDescription = desc
                        model.insertNode(node, model.getIndexByNode(topNode))
                    }
                    descriptions.forEach(descriptionsForEach)
                }
                map.forEach(mapForEach)
            }
        }
        // ------------ treeview
    }

    Column {
        width: parent.width * 0.5
        height: parent.height
        x: parent.width * 0.5

        Text {
            text: qsTr("list")
        }
        // ------------ listview
        ListView {
            id: listView
            width: parent.width
            height: parent.height

            model: ListModel {}
            delegate: Text {
                text: {
                    print("list: delegate")

                    let t = distortionDescription.name
                    t += " ["
                    Object.keys(distortionDescription.arguments).forEach(
                                function (a) {
                                    t += ""
                                    t += distortionDescription.arguments[a].name
                                    t += ": "
                                    t += distortionDescription.arguments[a].value
                                    t += "; "
                                })
                    t += "]"
                    print("list: delegate done")
                    return t
                }
            }
        }
        // ------------ listview
    }
}
