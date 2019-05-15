import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Window {
    id: root
    visible: true
    width: 1000
    height: 900
    title: qsTr("Hello World")


            GameField {
                id: field
                focus: true
                anchors.centerIn: parent
            }

                GameButtons {
                    id: buttons
                    anchors.verticalCenter: field.verticalCenter
                    anchors.left: field.right
                }
                InfoTable {
                    id: infoTable
                    x: root.width-(root.width-root.height)
                    y: 250
            }
    }


//    Rectangle {
//        id: main;
//        width: 500; height: 500;
//        color: "darkgreen";

//        property int emptyBlock: 16;

//        GridView {
//            id: grid16;
//            x: 5; y: 5;
//            width: 490; height: 490;

//            model: gridModel

//            delegate: Component{
//                Rectangle {
//                    width: 118; height: 118; color: "yellow";
//                    Text {
//                        anchors.centerIn: parent
//                        font.pixelSize: 20
//                        text: value
//                    }
//                }
//            }
//        }

//        ListModel {
//          id: gridModel
//          ListElement {value: 1}
//          ListElement {value: 2}
//          ListElement {value: 3}
//          ListElement {value: 4}
//          ListElement {value: 5}
//          ListElement {value: 6}
//          ListElement {value: 7}
//          ListElement {value: 8}
//          ListElement {value: 9}
//          ListElement {value: 10}
//          ListElement {value: 11}
//          ListElement {value: 12}
//          ListElement {value: 13}
//          ListElement {value: 14}
//          ListElement {value: 15}
//          ListElement {value: 16}
//        }

//        Keys.onRightPressed: {
//          gridModel.move(grid16.currentIndex, grid16.currentIndex+1, 1)
//        }

//        Keys.onLeftPressed: {
//          gridModel.move(grid16.currentIndex, grid16.currentIndex-1, 1)
//        }

//        Keys.onUpPressed: {
//          gridModel.move(grid16.currentIndex, grid16.currentIndex-4, 1)
//        }

//        Keys.onDownPressed: {
//          gridModel.move(grid16.currentIndex, grid16.currentIndex+4, 1)
//        }


//        focus: true;
//    }
//}
