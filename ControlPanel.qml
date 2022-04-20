import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import QtQuick.Dialogs
import backend 1.0

Rectangle {
//    color: "#abfffc"
    focus: true

    RowLayout {
        anchors.fill: parent
        spacing: 10
        ColumnLayout {
            Layout.alignment: Qt.AlignLeft
            Layout.preferredWidth: parent.width/4
            Layout.preferredHeight: parent.height

            Item {
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width/1.1
                Layout.preferredHeight: parent.height/4
                z: 100
                Text {
                    id: text
                    width: parent.width
                    height: parent.height/3
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: "LOAD ROM"
                    font.pointSize: 12
                    font.bold: true
                    color: "#ff0000"
                }

                DropBox {
                    id: selectROMComboBox
                    width: parent.width
                    height: 2*parent.height/3
                    anchors.top: text.bottom
                    items: RomList{}
                    onItemChanged: {
                        chip8.startProgram(items.get(selectedIndex).path)
                    }
                }
            }



            ButtonC {
                id: pauseButton
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width/1.1
                Layout.preferredHeight: parent.height/7
                name: (chip8.stage === Chip8Emulator.RunningStage)?"Pause":"Resume"

                mouse.onClicked: {
                    if (chip8.stage === Chip8Emulator.RunningStage) {
                        chip8.pause();
                    } else {
                        chip8.resume();
                    }
                }
            }

            ButtonC {
                id: restartButton
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width/1.1
                Layout.preferredHeight: parent.height/7
                name: "Restart"
                mouse.onClicked: {
                    chip8.restart();
                }
            }
        }

        Keyboard {
            id: keyboard
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: parent.width/2
            Layout.preferredHeight: parent.height
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignRight
            Layout.preferredWidth: parent.width/4
            Layout.preferredHeight: parent.height

//            RoundButton {
//                id: pauseButton
//                Layout.alignment: Qt.AlignHCenter
//                Layout.preferredWidth: parent.width/1.5
//                Layout.preferredHeight: parent.height/5
//                text: "Pause"
//            }

//            RoundButton {
//                id: restartButton
//                Layout.alignment: Qt.AlignHCenter
//                Layout.preferredWidth: parent.width/1.5
//                Layout.preferredHeight: parent.height/5
//                text: "Restart"
//            }
        }
    }

    Keys.onPressed: (event) => {
        if (event.key >= Qt.Key_0 && event.key <= Qt.Key_9) {
            chip8.keyPressed = event.key - Qt.Key_0;
        } else if (event.key >= Qt.Key_A && event.key <= Qt.Key_F) {
            chip8.keyPressed = event.key - 55;
        }
    }

    Keys.onReleased: (event) => {
        chip8.keyPressed = 0xff;
    }
}
