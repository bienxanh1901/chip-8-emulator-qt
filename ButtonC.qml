import QtQuick 2.0

Rectangle {
    id: myButton
    property alias name: buttonName.text
    property alias mouse: mouseArea
    radius: 10
    border.width: 3
//    border.color: "blue"
    color: "#2b00ff"
    Text {
        id: buttonName
        anchors.centerIn: parent
        text: "My Button"
        font.pixelSize: parent.width/5
        font.bold: true
        color: "#ffffff"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
}
