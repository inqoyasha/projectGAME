import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5

Window {
    id: root
    visible: true
    width: 800
    height: 600

    GameField {
    id: field
    }
    GameButtons {
    id: buttons
    }



}
