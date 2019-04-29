import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
Rectangle {
    ButtonGroup {
          buttons: colButtons.children
    }

    Column {
            id: colButtons
            anchors.verticalCenter: field.verticalCenter
            anchors.left: field.right

            Button {
                text: qsTr("Step back")
                    onClicked: {}
            }

            Button {
                text: qsTr("Reset")
                    onClicked: {}
            }

            Button {
                text: qsTr("Menu")
                    onClicked: {}
            }
    }
}
