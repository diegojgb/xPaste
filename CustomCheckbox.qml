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
                }
            }

            Image {
                id: lightImage

                source: {
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
