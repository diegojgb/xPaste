import QtQuick
import QtQuick.Controls.Basic

ComboBox {
    id: control

    model: ["First", "Second", "Third"]

    required property bool darkEnabled

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

    indicator: Canvas {
        id: canvas
        x: control.width - width - control.rightPadding - 2
        y: control.topPadding + (control.availableHeight - height) / 2 + 1
        width: 8
        height: 4
        contextType: "2d"

        Connections {
            target: control
            function onPressedChanged() {
                canvas.requestPaint()
            }
        }

        onPaint: {
            context.reset()
            context.moveTo(0, 0)
            context.lineTo(width, 0)
            context.lineTo(width / 2, height)
            context.closePath()
            context.fillStyle = control.darkEnabled ? "#c7c7c7" : "#606060"
            context.fill()
        }
    }

    onActivated: {
        canvas.requestPaint()
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
    }

    background: Rectangle {
        implicitWidth: 128
        implicitHeight: 27
        color: {
            if (control.darkEnabled) {
                if (popup.visible || control.pressed) {
                    return '#666'
                } else {
                    return '#3a3a3a'
                }
            } else {
                if (popup.visible || control.pressed) {
                    return '#999'
                } else {
                    return '#c3c3c3'
                }
            }
        }
        border.color: control.darkEnabled ? "#555" : "#aaa"
        border.width: 1
        radius: 2
    }

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
    }

    onCurrentIndexChanged: {
        if (currentIndex === 0) {
            root.darkEnabled = false // "Light" is selected
        } else if (currentIndex === 1) {
            root.darkEnabled = true // "Dark" is selected
        }
    }
}
