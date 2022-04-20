import QtQuick 2.15
import backend 1.0

Item {
    ListModel {
        id: keyboardList
        ListElement {key: 0x01; text: "1"}
        ListElement {key: 0x02; text: "2"}
        ListElement {key: 0x03; text: "3"}
        ListElement {key: 0x0C; text: "C"}
        ListElement {key: 0x04; text: "4"}
        ListElement {key: 0x05; text: "5"}
        ListElement {key: 0x06; text: "6"}
        ListElement {key: 0x0D; text: "D"}
        ListElement {key: 0x07; text: "7"}
        ListElement {key: 0x08; text: "8"}
        ListElement {key: 0x09; text: "9"}
        ListElement {key: 0x0E; text: "E"}
        ListElement {key: 0x0A; text: "A"}
        ListElement {key: 0x00; text: "0"}
        ListElement {key: 0x0B; text: "B"}
        ListElement {key: 0x0F; text: "F"}
    }

    GridView {
        id: keyBoard
        anchors.fill: parent
        cellWidth: parent.width/4
        cellHeight: parent.height/4
        model: keyboardList
        delegate: Rectangle {
            width: keyBoard.cellWidth
            height: keyBoard.cellHeight
            radius: 10
            border.width: 3
            border.color: "blue"
            color: "#5e5e5e"
            Text {
                id: keyText
                anchors.centerIn: parent
                text: model.text
                font.pixelSize: parent.width/2
                font.bold: true
                color: "#ffffff"
            }

            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: true
                onPressed: (mouse) => {
                    parent.color = "#f700ff";
                    chip8.keyPressed = model.key;
                }
                onReleased: {
                    parent.color = "#5e5e5e";
                    chip8.keyPressed = 0xff;
                }
            }
        }
    }
}
