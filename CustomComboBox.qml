import QtQuick
import QtQuick.Controls.Basic

ComboBox {
    id: control

    model: ["First", "Second", "Third"]

    required property bool darkEnabled

    property var comboBoxNormalColor: ({
                                           "dark": "#3a3a3a",
                                           "light": "#c3c3c3"
                                       })

    property var comboBoxPressedColor: ({
                                            "dark": '#666',
                                            "light": '#999'
                                        })

    onDarkEnabledChanged: {
        background.state = control.darkEnabled ? "darkState" : "lightState"
        canvasItem.state = control.darkEnabled ? "fadeInDarkCanvas" : "fadeInLightCanvas"
    }

    delegate: ItemDelegate {
        id: itemDelegate

        width: control.width
        height: 28

        contentItem: Text {
            text: modelData
            font: control.font
            color: palette.text
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            anchors.left: parent.left
            leftPadding: 8

            renderType: Text.NativeRendering
        }

        highlighted: control.highlightedIndex === index

        background: Rectangle {
            color: {
                if (itemDelegate.hovered) {
                    return "#0078d7"
                } else if (control.darkEnabled) {
                    return "#242424"
                } else {
                    return "#ebebeb"
                }
            }
        }
    }

    indicator: Item {
        id: canvasItem

        anchors.right: control.right
        anchors.rightMargin: 18
        anchors.verticalCenter: control.verticalCenter

        property color darkIndicatorColor: "#c7c7c7"
        property color lightIndicatorColor: "#606060"

        Canvas {
            id: darkCanvas

            width: 8
            height: 4
            contextType: "2d"
            anchors.verticalCenter: parent.verticalCenter

            onPaint: {
                context.reset()
                context.moveTo(0, 0)
                context.lineTo(width, 0)
                context.lineTo(width / 2, height)
                context.closePath()
                context.fillStyle = parent.darkIndicatorColor
                context.fill()
            }
        }

        Canvas {
            id: lightCanvas

            width: 8
            height: 4
            contextType: "2d"
            anchors.verticalCenter: parent.verticalCenter

            onPaint: {
                context.reset()
                context.moveTo(0, 0)
                context.lineTo(width, 0)
                context.lineTo(width / 2, height)
                context.closePath()
                context.fillStyle = parent.lightIndicatorColor
                context.fill()
            }
        }

        states: [
            State {
                name: "fadeInLightCanvas"

                PropertyChanges {
                    target: darkCanvas
                    opacity: 0
                }
                PropertyChanges {
                    target: lightCanvas
                    opacity: 1
                }
            },
            State {
                name: "fadeInDarkCanvas"

                PropertyChanges {
                    target: darkCanvas
                    opacity: 1
                }
                PropertyChanges {
                    target: lightCanvas
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

    onActivated: {
        if (control.darkEnabled) {
            darkCanvas.requestPaint()
        } else {
            lightCanvas.requestPaint()
        }
    }

    contentItem: Text {
        leftPadding: 8
        bottomPadding: 2
        rightPadding: control.indicator.width + control.spacing

        text: control.displayText
        font: control.font
        color: palette.text
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        renderType: Text.NativeRendering

        Behavior on color {
            ColorAnimation {
                duration: root.transitionDuration
            }
        }
    }

    background: Rectangle {
        id: background

        implicitWidth: 128
        implicitHeight: 27
        border.color: control.darkEnabled ? "#555" : "#aaa"
        border.width: 1
        radius: 2

        color: control.darkEnabled ? '#3a3a3a' : '#c3c3c3'

        states: [
            State {
                name: "darkState"

                PropertyChanges {
                    target: background
                    color: "#3a3a3a"
                }
            },
            State {
                name: "lightState"

                PropertyChanges {
                    target: background
                    color: "#c3c3c3"
                }
            }
        ]

        transitions: Transition {
            ColorAnimation {
                duration: root.transitionDuration
            }
        }

        Behavior on border.color {
            ColorAnimation {
                duration: root.transitionDuration
            }
        }
    }

    onPressedChanged: background.color = pressed ? control.comboBoxPressedColor[root.currentTheme()] : control.comboBoxNormalColor[root.currentTheme()]

    popup: Popup {
        id: popup

        y: control.height - 1
        width: control.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight + 2 // Don't know why, but had to add that 2 pixel correction when using a custom background for the delegateItems.
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex

            ScrollIndicator.vertical: ScrollIndicator {}
        }

        background: Rectangle {
            border.color: control.darkEnabled ? "#555" : '#aaa'
            radius: 2
        }

        onVisibleChanged: background.color = visible ? control.comboBoxPressedColor[root.currentTheme()] : control.comboBoxNormalColor[root.currentTheme()]
    }
}
