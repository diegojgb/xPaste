import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

TabButton {
    id: control

    required property bool darkEnabled
    property string lightImage
    property string darkImage
    property alias contentAnchors: content.anchors

    checkable: true
    autoExclusive: true
    width: parent.width
    font.pointSize: 10

    onDarkEnabledChanged: {
        background.state = control.darkEnabled ? "darkState" : "lightState"
        imageItem.state = control.darkEnabled ? "fadeInDarkImage" : "fadeInLightImage"
    }

    background: Rectangle {
        id: background
        anchors.fill: parent

        color: control.checked ? control.darkEnabled ? '#404040' : '#bfbfbf' : "transparent"

        states: [
            State {
                name: "darkState"

                PropertyChanges {
                    target: background
                    color: {
                        if (control.hovered) {
                            return "#4d4d4d"
                        } else if (control.checked) {
                            return "#404040"
                        } else {
                            return "transparent"
                        }
                    }
                }
            },
            State {
                name: "lightState"

                PropertyChanges {
                    target: background
                    color: {
                        if (control.hovered) {
                            return "#b3b3b3"
                        } else if (control.checked) {
                            return "#bfbfbf"
                        } else {
                            return "transparent"
                        }
                    }
                }
            }
        ]

        transitions: Transition {
            ColorAnimation {
                duration: root.transitionDuration
            }
        }
    }

    contentItem: RowLayout {
        id: content

        spacing: 9
        anchors.fill: parent
        anchors.leftMargin: 15

        Item {
            id: imageItem

            Layout.topMargin: 2
            width: childrenRect.width
            height: childrenRect.height

            Image {
                id: darkImageItem
                source: control.darkImage
            }

            Image {
                id: lightImageItem
                source: control.lightImage
            }

            states: [
                State {
                    name: "fadeInLightImage"
                    PropertyChanges {
                        target: darkImageItem
                        opacity: 0
                    }
                    PropertyChanges {
                        target: lightImageItem
                        opacity: 1
                    }
                },
                State {
                    name: "fadeInDarkImage"
                    PropertyChanges {
                        target: darkImageItem
                        opacity: 1
                    }
                    PropertyChanges {
                        target: lightImageItem
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
            Layout.fillWidth: true
            Layout.topMargin: 1
            horizontalAlignment: Text.AlignLeft
            text: control.text
            font: control.font
            color: palette.text
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
        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true
        onPressed: mouse => {
                       mouse.accepted = false
                   }
    }
}
