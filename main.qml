import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

ApplicationWindows {
    width: 640
    height: 320
    visible: true

    GridView {
        id: display
        cellWidth: parent.width/64
        cellHeight: parent.height/32

        delegate: Rectangle {
            id: delegate
            width: display.cellWidth
            height: display.cellHeight
            property bool selected: GridView.isCurrentItem
            property int actual: model.actual
            property int prediction: model.prediction
            property var candidates: model.candidates
            border.color: "#a6a6a6"
            border.width: 0.5
            color: selected ? "#87b1ff" : "transparent"
        }
    }
}
