import QtQuick 2.12
import QtQuick.Controls 2.5
//import QtQuick.Layouts 1.12
import GameField 1.0

GridView {
    id: gridView
    implicitWidth: 800
    implicitHeight: 800

    //clip: true


    model: GameFieldModel {
        id: gameModel
       // list: gameFieldList
    }
//    Component {
//        id: name1
//    Image {
//            id: name12
//            source: empty
//        }}

//    delegate: switch (value) {
//                  case 0: name12
//              }
        Image {
            source: empty
    }
//        Rectangle {
//                   width: 100
//                   height: 100
//                   border.color: "black"
//                   border.width: 1
//                   color: empty
//                       Text {
//                           anchors.centerIn: parent
//                           text: value
//                       }
//               }
    Keys.onLeftPressed:   gameModel.moveLeft()
    Keys.onRightPressed:  gameModel.moveRight()
    Keys.onDownPressed:   gameModel.moveDown()
    Keys.onUpPressed:     gameModel.moveUp()

}


