import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.5

Item {
    id: textItem
    Rectangle {
        id: infoFrame
        width: 100
        height: 200
        color: "lightgray"
        Text {
            anchors.horizontalCenter: infoFrame.horizontalCenter
            text: "Кол-во ходов: " + stepsCount()
            color: "black"
        }
    }
}
