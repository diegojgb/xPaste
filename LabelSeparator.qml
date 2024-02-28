import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

RowLayout {
    id: control

    required property bool darkEnabled
    property alias text: label.text
    property real rightMargin: 50

    Label {
        id: label
        renderType: Text.NativeRendering
        font.pointSize: 10
    }

    Rectangle {
        height: 1
        color: control.darkEnabled ? "#777" : "#a0a0a0"
        Layout.fillWidth: true
        Layout.rightMargin: control.rightMargin
        Layout.topMargin: 4
    }
}
