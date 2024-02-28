import QtQuick
import QtQuick.Controls

AbstractButton {
    id: root

    property alias color: button.color
    property alias width: button.width
    property alias height: button.height
    property alias text: button.text

    Rectangle {
        id: button
        color: "gray"

        Text {
            id: text

            anchors.centerIn: parent
            text: root.text
        }
    }
}
