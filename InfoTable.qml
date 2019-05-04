import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.5

Item {
    id: textItem
    width: info1.width + 20
    height: info1.height + 20
        Text {
            id: info1
            text: "Кол-во ходов: "
            color: "black"
            width: 20
            height: 20
            anchors.fill: parent
        }

}
