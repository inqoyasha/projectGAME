import QtQuick 2.0

Rectangle {
    property int rows: 8
    property int cols: 8
    property int squareSize: rows * cols

    width: cols * squareSize
    height: cols * squareSize

    color: "lightgreen"
}
