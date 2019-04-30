import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.5

Item {
    id: item
    ButtonGroup {
          buttons: colButtons.children
    }

    Column {
            id: colButtons
            Button {
                id: but1
                width: txt1.width + 30
                height: txt1.height + 30
                Text {
                    id: txt1
                    color: "white"
                    anchors.centerIn: but1
                    text: qsTr("Step back")
                }
                    onClicked: {}
            }

            Button {
                id: but2
                width: txt2.width + 30
                height: txt2.height + 30
                Text {
                    id: txt2
                    color: "white"
                    anchors.centerIn: but2
                    text: qsTr("Reset")
                }
                    onClicked: {}
            }

            Button {
                id: but3
                width: txt3.width + 30
                height: txt3.height + 30
                Text {
                    id: txt3
                    color: "white"
                    anchors.centerIn: but3
                    text: qsTr("Menu")
                }
                    onClicked: {}
            }
    }
}
