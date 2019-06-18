import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

import GameField 1.0

Window {
    id: root
    visible: true
    width: 1000
    height: 900
    title: qsTr("Gruz4ik")
//    color: "lightgray"
    GameField {
        id: field
        focus: true
        anchors.centerIn: parent
    }
}




