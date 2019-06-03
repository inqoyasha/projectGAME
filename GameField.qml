import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

import GameField 1.0


GridView {
    id: gridView
    property var lvlCount: 1
    property var maxLvls: 2
    property var startAnimation: 0
    implicitWidth: 800
    implicitHeight: 800

    focus: true
    model: GameFieldModel {
        id: gameModel
        onStepChanged:  txt1.text = "Steps: " + step
        onBoxesOnPositionChanged: txt2.text = "Boxes: " + boxesOnPosition + "/" + boxes
        onIsCompleteChanged: {
            gridView.focus = (gameModel.isComplete === false) ? true : false
        }
    }
    delegate: Image {
                source: iconSource
              }
    populate: Transition {
            PropertyAnimation {
                property: if (gridView.startAnimation === 0) {"y"} else {""} duration: 1000; easing.type: Easing.InQuad}
        }

    Keys.onPressed: {
        if (event.key === Qt.Key_Left) {
            console.log("move left");
            gameModel.moveLeft();
            event.accepted = true;
        }
        if (event.key === Qt.Key_Right) {
            console.log("move right");
            gameModel.moveRight();
            event.accepted = true;
        }
        if (event.key === Qt.Key_Up) {
            console.log("move up");
            gameModel.moveUp();
            event.accepted = true;
        }
        if (event.key === Qt.Key_Down) {
            console.log("move down");
            gameModel.moveDown();
            event.accepted = true;
        }
        gridView.startAnimation++;
    }

        Rectangle {
            id: infoFrame
            x: 800
            y: 200
            width: 100
            height: 200
            color: "lightgray"
            Text {
                id: txt0
                anchors.horizontalCenter: infoFrame.horizontalCenter
                text: "LVL: "+ gridView.lvlCount
                color: "black"
            }
            Text {
                id: txt1
                anchors.horizontalCenter: infoFrame.horizontalCenter
                text: "Steps: "+"0"
                color: "black"
                y:60
            }
            Text {
                id: txt2
                anchors.horizontalCenter: infoFrame.horizontalCenter
                text: "Boxes: "+"0"+"/"+ gameModel.boxes
                color: "black"
                y:90
            }
        }

    Loader {
        id: loader
        anchors.centerIn: parent
        sourceComponent: if (gameModel.isComplete === true) textWin
    }
    Component {
        id: textWin
        Rectangle {
            id: rect1
            radius: 20
            width: 200
            height: 150
            color: "lightgreen"
            opacity: 0

                NumberAnimation {
                    target: rect1
                    properties: "opacity"
                    running: true
                    from: 0
                    to: 1
                    duration: 1500
                    easing.type: Easing.InOutQuad
                }

            Text {
                id: text1
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -20
                text: "You win"
                font.pixelSize: 20
            }
            RowLayout {
                anchors.centerIn: rect1
                anchors.verticalCenterOffset: 30
                Button {
                    text: (gridView.lvlCount === 1) ? qsTr("Next") : qsTr("Restart")
                    onClicked: {
                        console.log("rect1 Restart")
                        gameModel.nextLevel()
                        gridView.startAnimation=0;
                    }
                    onReleased: {
                        if (gridView.lvlCount < maxLvls) ++gridView.lvlCount
                        txt1.text = "Steps: "+ step
                        txt2.text = "Boxes: "+ boxesOnPosition +"/"+ boxes
                    }
                }
                Button {
                    text: qsTr("Quit")
                    onClicked: {
                        console.log("quit game")
                        Qt.quit()
                    }
                }
            }
        }
    }

    Column {
        anchors.verticalCenter: gridView.verticalCenter
        anchors.left: gridView.right
        id: colButtons
        Button {
            id: but1
            width: 100
            height: 50
            text: qsTr("Step back")
            focusPolicy: Qt.NoFocus
            onClicked: if (gameModel.isComplete === false) {
                console.log("Step back")
                gameModel.stepBack()
            }
        }
        Button {
            id: but2
            width: 100
            height: 50
            text: qsTr("Reset")
            focusPolicy: Qt.NoFocus
            onClicked: if (gameModel.isComplete === false) {
                console.log("Reset");
                if (gridView.lvlCount < maxLvls) {gameModel.firstLevel()} else {gameModel.nextLevel()}
                txt1.text = "Steps: "+ step
                txt2.text = "Boxes: "+ boxesOnPosition +"/"+ boxes
            }
        }
            Button {
                id: but3
                width: 100
                height: 50
                text: qsTr("Quit")
                focusPolicy: Qt.NoFocus
                onClicked: if (gameModel.isComplete === false) {
                    console.log("quit game")
                    Qt.quit()
                }
        }
    }
}


