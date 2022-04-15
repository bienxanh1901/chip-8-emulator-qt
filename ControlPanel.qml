import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import QtQuick.Dialogs
import backend 1.0

Rectangle {
    color: "#abfffc"
    focus: true

    FileDialog {
        id: fileDialog
        title: "Choose a ROM"
        onAccepted: {
            chip8.loadProgram(selectedFile)
        }
    }

    RowLayout {
        anchors.fill: parent
        ColumnLayout {
            Layout.alignment: Qt.AlignLeft
            Layout.preferredWidth: parent.width/4
            Layout.preferredHeight: parent.height

            RoundButton {
                id: loadROMButton
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width/1.5
                Layout.preferredHeight: parent.height/5
                text: "Load ROM"
                onClicked: {
                    fileDialog.open()
                }
            }

            RoundButton {
                id: speedUpButton
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width/1.5
                Layout.preferredHeight: parent.height/5
                text: "Speed up"
            }

            RoundButton {
                id: speedDownButton
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width/1.5
                Layout.preferredHeight: parent.height/5
                text: "Speed down"
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

            RoundButton {
                id: pauseButton
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width/1.5
                Layout.preferredHeight: parent.height/5
                text: "Pause"
            }

            RoundButton {
                id: restartButton
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width/1.5
                Layout.preferredHeight: parent.height/5
                text: "Restart"
            }
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
