import QtQuick

/* ComboBoxHeader.qml */
Item {
    id: comboBox

    property var globalParent
    property var model
    property int selectedIndex

    signal comboItemSelected(int index)

    function openPopup() {
        // MAGIC:
        var marginPoint = comboBox.mapToItem(globalParent, 0, comboBox.height)

        var options = {
            "model": comboBox.model,
            "selectedIndex": comboBox.selectedIndex,
            "leftPadding": marginPoint.x,
            "topPadding": marginPoint.y
        }

        var component = Qt.createComponent("ComboBoxDropdown.qml")
        var instance = component.createObject(globalParent, options)
        instance.comboItemSelected.connect(comboBox.comboItemSelected)
    }

    Rectangle {
        id: header
        anchors.fill: parent
        color: "gray"

        Text {
            text: comboBox.model[comboBox.selectedIndex]
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                openPopup()
            }
        }
    }
}
