import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

TextField {
    id: control

    required property bool darkEnabled
    property bool disabled: false
    property alias defaultHotkey: control.text

    hoverEnabled: !control.disabled
    activeFocusOnPress: !control.disabled

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.ArrowCursor
        onPressed: mouse => {
                       mouse.accepted = false
                   }
    }

    background: Rectangle {
        color: palette.base
        border.color: {
            if (control.activeFocus)
                return '#7eb4ea'
            if (control.darkEnabled) {
                if (control.hovered) {
                    return '#bbb'
                } else {
                    return '#555'
                }
            } else {
                if (control.hovered) {
                    return '#666'
                } else {
                    return '#abadb3'
                }
            }
        }
        border.width: control.activeFocus ? 2 : 1
        radius: 2
    }

    selectByMouse: !control.disabled
    color: control.disabled ? palette.disabled.text : palette.text

    text: 'CTRL+V'
    readOnly: true
    font.pointSize: 9
    horizontalAlignment: TextInput.AlignHCenter
    topPadding: 0
    bottomPadding: 1
    renderType: Text.NativeRendering
}
