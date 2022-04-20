import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    id: dropBox
    width: 100
    height: 50
    z: 100;
    property alias items: listView.model
    property alias selectedIndex: listView.currentIndex
    signal itemChanged;

    Rectangle {
        id: selectedItem
        anchors.fill: parent
        radius: 10
        color: "#2b00ff"
        border.color: "#000000"
        border.width: 3
        clip: true

        Text {
            id: selectedItemText
            anchors.fill: parent
            anchors.margins: 5
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: dropBox.items.get(selectedIndex).text
            font.family: "Arial"
            font.pointSize: 16
            font.bold: true
            color: "#ffffff"
            wrapMode : Text.WordWrap
        }

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                dropBox.state = dropBox.state==="dropDown"?"":"dropDown"
            }
        }
    }

    Rectangle {
        id: dropDown
        width: parent.width
        height: 0
        radius: 10
        anchors.top: selectedItem.bottom
        anchors.margins: 2
        clip: true
        color: "lightgray"

        ScrollView {
            id: scrollView
            anchors.fill: parent
            ListView {
                anchors.fill: parent
                id: listView
                spacing: 10
                currentIndex: 0

                delegate: Item {
                    width: dropBox.width
                    height: 25

                    Text {
                        id: itemText
                        anchors.fill: parent
                        anchors.margins: 5
                        text: model.text
                        font.family: "Arial"
                        font.pointSize: 14
                        font.bold: listView.currentIndex === index
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            dropBox.state = "";
                            if (listView.currentIndex !== index) {
                                listView.currentIndex = index;
                                dropBox.itemChanged();
                            }
                        }
                    }
                }
            }
        }
    }

    states: State {
        name: "dropDown";
        PropertyChanges { target: dropDown; height: 400 }
    }

    transitions: Transition {
        NumberAnimation { target: dropDown; properties: "height"; easing.type: Easing.OutExpo; duration: 300 }
    }
}
