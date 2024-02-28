import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
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
}
