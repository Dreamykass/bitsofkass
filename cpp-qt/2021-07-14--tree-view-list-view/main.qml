import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import Tree 1.0

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
            property var onClickedFn: function () {
                print("siema")
            }
        }
    }

    Column {
        width: parent.width * 0.5
        height: parent.height

        Text {
            text: qsTr("tree")
        }

        TreeView {
            width: parent.width
            height: parent.height
            model: TreeModel {
                id: treeModel
                roles: ["name"]
            }

            TableViewColumn {
                //                title: "Name"
                role: "name"
                width: 99999
            }

            Component.onCompleted: {
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

                //                list.forEach(x => {
                //                                 var newNode = treeNodeComponent.createObject()
                //                                 newNode.name = x.name
                //                                 model.insertNode(newNode)

                //                                 var newSubNode = treeNodeComponent.createObject()
                //                                 newSubNode.name = "foo"
                //                                 model.insertNode(newSubNode,
                //                                                  model.getIndexByNode(newNode))
                //                             })
            }
        }
    }

    Column {
        width: parent.width * 0.5
        height: parent.height
        x: parent.width * 0.5

        Text {
            text: qsTr("list")
        }

        ListView {
            width: parent.width
            height: parent.height

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
            }
        }
    }
}
