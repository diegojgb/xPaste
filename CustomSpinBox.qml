import QtQuick
import QtQuick.Controls

SpinBox {
    id: control

    required property bool darkEnabled

    hoverEnabled: control.enabled

    width: 110
    height: 40
    editable: true
    from: 0
    to: 86399 // 23:59:59 in seconds

    onDarkEnabledChanged: {
        background.state = control.darkEnabled ? "darkState" : "lightState"
    }

    // Format the displayed text as HH:MM:SS
    textFromValue: function (value) {
        let hours = Math.floor(value / 3600)
        value %= 3600
        let minutes = Math.floor(value / 60)
        let seconds = value % 60

        minutes = String(minutes).padStart(2, "0")
        hours = String(hours).padStart(2, "0")
        seconds = String(seconds).padStart(2, "0")
        return hours + ":" + minutes + ":" + seconds
    }

    valueFromText: function (value) {
        let a = value.split(':')
        return (+a[0]) * 60 * 60 + (+a[1]) * 60 + (+a[2])
    }

    validator: RegularExpressionValidator {
        regularExpression: /^([0-1]?[0-9]|2[0-3]):[0-5]?[0-9]:[0-5]?[0-9]$/
    }

    background: Rectangle {
        id: background

        implicitWidth: parent.width
        color: palette.base
        radius: 2

        border.color: {
            if (control.darkEnabled) {
                if (control.hovered || control.activeFocus) {
                    return '#bbb'
                } else {
                    return '#555'
                }
            } else {
                if (control.hovered || control.activeFocus) {
                    return '#666'
                } else {
                    return '#abadb3'
                }
            }
        }

        states: [
            State {
                name: "darkState"

                PropertyChanges {
                    target: background
                    border.color: if (control.hovered || control.activeFocus) {
                                      return '#bbb'
                                  } else {
                                      return '#555'
                                  }
                }
            },
            State {
                name: "lightState"

                PropertyChanges {
                    target: background
                    border.color: if (control.hovered || control.activeFocus) {
                                      return '#666'
                                  } else {
                                      return '#abadb3'
                                  }
                }
            }
        ]

        transitions: Transition {
            ColorAnimation {
                duration: root.transitionDuration
            }
        }

        Behavior on color {
            ColorAnimation {
                duration: root.transitionDuration
            }
        }
    }

    contentItem: TextInput {
        text: control.textFromValue(control.value, control.locale)

        font: control.font
        color: !control.enabled ? palette.disabled.text : palette.text
        selectedTextColor: palette.highlightedText
        selectionColor: palette.highlight
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        renderType: Text.NativeRendering

        readOnly: !control.editable
        validator: control.validator
        selectByMouse: control.enabled
        activeFocusOnPress: control.enabled

        Behavior on color {
            ColorAnimation {
                duration: root.transitionDuration
            }
        }
    }
}
