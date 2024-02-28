import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    spacing: 0

    Row {
        spacing: 10

        Image {
            source: 'assets/xpaste_logo.png'
            anchors.verticalCenter: parent.verticalCenter
        }

        Column {
            Label {
                text: 'xPaste'
                font.pointSize: 18
                font.weight: Font.DemiBold
                renderType: Text.NativeRendering
            }
            Label {
                text: 'Version 2.0'
                font.pointSize: 12
            }
        }
    }

    LabelSeparator {
        Layout.topMargin: 24
        text: 'Author info'
        darkEnabled: root.darkEnabled
    }

    Label {
        Layout.leftMargin: 10
        Layout.topMargin: 10
        text: '© 2024 - Obin XYZ'
        renderType: Text.NativeRendering
    }

    Label {
        Layout.leftMargin: 24
        text: 'Release date: March 2024'
        renderType: Text.NativeRendering
    }
}
