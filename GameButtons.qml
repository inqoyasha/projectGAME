import QtQuick 2.12
import QtQuick.Controls 2.5
//import QtQuick.Layouts 1.12



Item {
    id: item
    ButtonGroup {
          buttons: colButtons.children
    }

    Column {
        id: colButtons
        Button{
            width: 100
            height: 50
            text: qsTr("New Grid")
            onClicked: {}
        }
        Button{
            width: 100
            height: 50
            text: qsTr("Step back")
            onClicked: {}
        }
        Button{
            width: 100
            height: 50
            text: qsTr("Reset")
            onClicked: {}
        }
}
}
