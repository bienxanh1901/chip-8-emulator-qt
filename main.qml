import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import backend 1.0

ApplicationWindow {
    minimumWidth: 768
    minimumHeight: 768
    maximumWidth: 768
    maximumHeight: 768
    flags: Qt.Dialog
    visible: true
    title: "Chip8 Emulator QT"

    Chip8Emulator {
        id: chip8
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 2
        Rectangle {
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height/2
            GridView {
                id: display
                anchors.fill: parent
                cellWidth: width/64
                cellHeight: height/32
                model: chip8
                delegate: Rectangle {
                    id: delegate
                    width: display.cellWidth
                    height: display.cellHeight
                    color: model.status ? "#00ffe5" : "#000000"
                }
            }
        }

        ControlPanel {
            id: controlPanel
            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height/2
        }

    }

    Component.onCompleted: {
        chip8.startProgram(':/roms/Chip8 Picture.ch8')
    }

}
