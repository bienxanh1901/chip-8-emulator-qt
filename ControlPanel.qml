import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import QtQuick.Dialogs
import backend 1.0

Rectangle {
//    color: "#abfffc"
//    focus: true

    RowLayout {
        anchors.fill: parent
        ColumnLayout {
            Layout.alignment: Qt.AlignLeft
            Layout.preferredWidth: parent.width/4
            Layout.preferredHeight: parent.height

            ComboBox {
                id: selectROMComboBox
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width/1.5
                Layout.preferredHeight: parent.height/7
                background: Rectangle {
                    anchors.fill: parent
                    color: "#00ff00"
                }

                textRole: 'text'
                model: RomList{}

                onActivated: {
                    chip8.startProgram(model.get(currentIndex).path)
                }
            }

            ButtonC {
                id: pauseButton
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width/1.5
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
                Layout.preferredWidth: parent.width/1.5
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
