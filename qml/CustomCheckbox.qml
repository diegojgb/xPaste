import QtQuick

Item {
    id: control

    required property bool darkEnabled
    property bool checked: false
    property bool disabled: false
    property alias text: text.text

    width: childrenRect.width
    height: childrenRect.height

    onDarkEnabledChanged: {
        imageItem.state = control.darkEnabled ? "fadeInDarkImage" : "fadeInLightImage"
    }

    Row {
        spacing: 6

        Item {
            id: imageItem

            width: childrenRect.width
            height: childrenRect.height

            Image {
                id: darkImage

                source: {
                    if (control.checked) {
                        if (control.disabled) {
                            return 'qrc:/qt/qml/xPaste/assets/dark/check-disabled.png'
                        } else if (mouseArea.containsMouse) {
                            return 'qrc:/qt/qml/xPaste/assets/dark/check-hover.png'
                        } else {
                            return 'qrc:/qt/qml/xPaste/assets/dark/check-accent.png'
                        }
                    } else {
                        if (control.disabled) {
                            return 'qrc:/qt/qml/xPaste/assets/dark/box-disabled.png'
                        } else if (mouseArea.containsMouse) {
                            return 'qrc:/qt/qml/xPaste/assets/dark/box-hover.png'
                        } else {
                            return 'qrc:/qt/qml/xPaste/assets/dark/box-basic.png'
                        }
                    }
                }
            }

            Image {
                id: lightImage

                source: {
                    if (control.checked) {
                        if (control.disabled) {
                            return 'qrc:/qt/qml/xPaste/assets/light/check-disabled.png'
                        } else if (mouseArea.containsMouse) {
                            return 'qrc:/qt/qml/xPaste/assets/light/check-hover.png'
                        } else {
                            return 'qrc:/qt/qml/xPaste/assets/light/check-accent.png'
                        }
                    } else {
                        if (control.disabled) {
                            return 'qrc:/qt/qml/xPaste/assets/light/box-disabled.png'
                        } else if (mouseArea.containsMouse) {
                            return 'qrc:/qt/qml/xPaste/assets/light/box-hover.png'
                        } else {
                            return 'qrc:/qt/qml/xPaste/assets/light/box-basic.png'
                        }
                    }
                }
            }

            states: [
                State {
                    name: "fadeInLightImage"

                    PropertyChanges {
                        target: darkImage
                        opacity: 0
                    }
                    PropertyChanges {
                        target: lightImage
                        opacity: 1
                    }
                },
                State {
                    name: "fadeInDarkImage"

                    PropertyChanges {
                        target: darkImage
                        opacity: 1
                    }
                    PropertyChanges {
                        target: lightImage
                        opacity: 0
                    }
                }
            ]

            transitions: [
                Transition {
                    NumberAnimation {
                        property: "opacity"
                        easing.type: Easing.Linear
                        duration: root.transitionDuration
                    }
                }
            ]
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

            Behavior on color {
                ColorAnimation {
                    duration: root.transitionDuration
                }
            }
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            if (!control.disabled)
                control.checked = !control.checked
            forceActiveFocus()
        }
    }
}
