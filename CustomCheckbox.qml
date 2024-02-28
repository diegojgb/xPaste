import QtQuick

Item {
    id: control

    required property bool darkEnabled
    property bool checked: false
    property bool disabled: false
    property alias text: text.text

    width: childrenRect.width
    height: childrenRect.height

    Row {
        spacing: 6

        Image {
            source: {
                if (control.darkEnabled) {
                    if (control.checked) {
                        if (control.disabled) {
                            return 'assets/dark/check-disabled.png'
                        } else if (mouseArea.containsMouse) {
                            return 'assets/dark/check-hover.png'
                        } else {
                            return 'assets/dark/check-accent.png'
                        }
                    } else {
                        if (control.disabled) {
                            return 'assets/dark/box-disabled.png'
                        } else if (mouseArea.containsMouse) {
                            return 'assets/dark/box-hover.png'
                        } else {
                            return 'assets/dark/box-basic.png'
                        }
                    }
                } else {
                    if (control.checked) {
                        if (control.disabled) {
                            return 'assets/light/check-disabled.png'
                        } else if (mouseArea.containsMouse) {
                            return 'assets/light/check-hover.png'
                        } else {
                            return 'assets/light/check-accent.png'
                        }
                    } else {
                        if (control.disabled) {
                            return 'assets/light/box-disabled.png'
                        } else if (mouseArea.containsMouse) {
                            return 'assets/light/box-hover.png'
                        } else {
                            return 'assets/light/box-basic.png'
                        }
                    }
                }
            }
        }

        Text {
            id: text

            color: {
                if (control.disabled) {
                    palette.disabled.text
                } else {
                    palette.text
                }
            }

            topPadding: 1.5
            renderType: Text.NativeRendering
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            if (!control.disabled)
                control.checked = !control.checked
        }
    }
}
