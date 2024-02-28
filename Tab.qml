import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

TabButton {
    id: control

    required property bool darkEnabled
    property string light_image
    property string dark_image
    property alias contentAnchors: content.anchors

    checkable: true
    autoExclusive: true
    width: parent.width
    font.pointSize: 10

    background: Rectangle {
        anchors.fill: parent
        color: {
            if (control.darkEnabled) {
                if (control.hovered) {
                    return "#4d4d4d"
                } else if (control.checked) {
                    return "#404040"
                }
            } else {
                if (control.hovered) {
                    return "#b3b3b3"
                } else if (control.checked) {
                    return "#bfbfbf"
                }
            }
            return "transparent"
        }
    }

    contentItem: RowLayout {
        id: content

        spacing: 9
        anchors.fill: parent
        anchors.leftMargin: 15

        Image {
            id: image

            source: control.darkEnabled ? control.dark_image : control.light_image
            Layout.topMargin: 2
        }

        Text {
            Layout.fillWidth: true
            Layout.topMargin: 1
            horizontalAlignment: Text.AlignLeft
            text: control.text
            font: control.font
            color: palette.text
            renderType: Text.NativeRendering
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true
        onPressed: mouse => {
                       mouse.accepted = false
                   }
    }
}
