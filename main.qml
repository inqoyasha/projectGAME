import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import GameField 1.0
import Player 1.0

Window {
    id: root
    visible: true
    width: 800
    height: 600



    GameField {
        id: field
        width: root.width * 0.9
        height: root.height * 0.9

//        Player {
//            id: player
//            width: parent.width * 0.06
//            height: parent.height * 0.07
//            color: "yellow"
//            x: 555
//            y: 122
//            //anchors.centerIn: parent
//            Keys.onLeftPressed:  player.moveLeft()
//            Keys.onRightPressed: player.moveRight()
//            Keys.onDownPressed:  player.moveDown()
//            Keys.onUpPressed:    player.moveUp()
//            focus: true
//       }



    }
    GameButtons {
        id: buttons
        anchors.verticalCenter: field.verticalCenter
        anchors.left: field.right
    }
}
