import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import GameField 1.0
//import Player 1.0

Window {
    id: root
    visible: true
    width: 800
    height: 600

    InfoTable {
        id: infotable
        anchors.right: root.right
        anchors.verticalCenter: buttons.verticalCenter
        anchors.bottom: buttons.top
    }

        GameField {
            id: field
            focus: true

            width: root.width * 0.9
            height: root.height * 0.9

            Keys.onLeftPressed:   field.moveLeft()
            Keys.onRightPressed:  field.moveRight()
            Keys.onDownPressed:   field.moveDown()
            Keys.onUpPressed:     field.moveUp()
            Keys.onEscapePressed: field.reset()
        }

//        Player {
//            id: player
//            width: parent.width * 0.9
//            height: parent.height * 0.9

//            Keys.onLeftPressed:   field.moveLeft()
//            Keys.onRightPressed:  field.moveRight()
//            Keys.onDownPressed:   field.moveDown()
//            Keys.onUpPressed:     field.moveUp()
//            Keys.onEscapePressed: field.reset()

//            Keys.onPressed: {
//                if(event.key == Qt.Key_Left)  field.moveLeft()
//                if(event.key == Qt.Key_Right) field.moveRight()
//                if(event.key == Qt.Key_Up)    field.moveUp()
//                if(event.key == Qt.Key_Down)  field.moveDown()
//            }
//       }

        GameButtons {
            id: buttons
            anchors.verticalCenter: field.verticalCenter
            anchors.left: field.right
        }

}
