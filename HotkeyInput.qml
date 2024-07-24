import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

TextField {
    id: control

    required property bool darkEnabled
    property bool disabled: false

    hoverEnabled: !control.disabled
    activeFocusOnPress: !control.disabled
    selectByMouse: !control.disabled
    color: control.disabled ? palette.disabled.text : palette.text
    text: "<not set>"
    readOnly: true
    font.pointSize: 9
    horizontalAlignment: TextInput.AlignHCenter
    topPadding: 0
    bottomPadding: 1
    renderType: Text.NativeRendering

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.ArrowCursor
        onPressed: mouse => {
                       mouse.accepted = false
                   }
    }

    onDarkEnabledChanged: {
        background.state = control.darkEnabled ? "darkState" : "lightState"
    }

    background: Rectangle {
        id: background

        color: palette.base
        border.width: control.activeFocus ? 2 : 1
        radius: 2

        states: [
            State {
                name: "darkState"

                PropertyChanges {
                    target: background
                    border.color: if (control.activeFocus) {
                                      return '#7eb4ea'
                                  } else if (control.hovered) {
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
                    border.color: if (control.activeFocus) {
                                      return '#7eb4ea'
                                  } else if (control.hovered) {
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

    Behavior on color {
        ColorAnimation {
            duration: root.transitionDuration
        }
    }
}
