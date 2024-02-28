import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ApplicationWindow {
    id: root

    visible: true
    title: qsTr('xPaste')

    width: 700
    height: 480
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    property bool darkEnabled: true

    palette: root.darkEnabled ? darkTheme : lightTheme

    // Makes widgets lose focus when clicked outside.
    Pane {
        anchors.fill: parent
        focusPolicy: Qt.ClickFocus
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // Sidebar
        Rectangle {
            id: sidebar

            Layout.fillHeight: true
            Layout.preferredWidth: 176
            color: root.darkEnabled ? '#2b2b2b' : '#dbdbdb'

            ColumnLayout {
                anchors.fill: parent
                spacing: 0

                Rectangle {
                    id: on_off_switch

                    property bool checked: false

                    color: root.darkEnabled ? '#333' : '#e4e4e4'
                    Layout.fillWidth: true
                    Layout.preferredHeight: 75

                    Image {
                        source: on_off_switch.checked ? 'assets/on_switch.png' : 'assets/off_switch.png'
                        anchors.centerIn: parent

                        MouseArea {
                            id: switch_mouseArea

                            anchors.fill: parent

                            onClicked: {
                                on_off_switch.checked = !on_off_switch.checked
                                forceActiveFocus()
                            }
                        }
                    }
                }

                Tab {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 48
                    text: 'Settings'
                    darkEnabled: root.darkEnabled
                    dark_image: "assets/dark/settings.png"
                    light_image: "assets/light/settings.png"
                    checked: true
                }

                Tab {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 48
                    text: 'About'
                    darkEnabled: root.darkEnabled
                    dark_image: "assets/dark/about.png"
                    light_image: "assets/light/about.png"
                }

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    CustomComboBox {
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 22
                        anchors.horizontalCenter: parent.horizontalCenter
                        darkEnabled: root.darkEnabled
                        currentIndex: 1

                        model: ["Light", "Dark"]
                    }
                }
            }
        }

        // Mainbar
        Rectangle {
            id: mainbar

            Layout.fillHeight: true
            Layout.fillWidth: true
            color: root.darkEnabled ? '#242424' : '#ebebeb'

            SettingsPage {
                width: parent.width
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 27
                anchors.leftMargin: 24
            }
        }
    }

    Palette {
        id: darkTheme
        alternateBase: "#000"
        base: "#333"
        button: "#111"
        buttonText: "#fff"
        dark: "#666"
        highlight: '#0078d4'
        highlightedText: "#fff"
        light: "#000"
        mid: "#444"
        midlight: "#333"
        placeholderText: "#80000000"
        shadow: "#888"
        text: "#fff"
        window: "#222"
        windowText: "#fff"

        disabled.text: '#aaa'
    }

    Palette {
        id: lightTheme
        alternateBase: "#fff"
        base: "#e6e6e6"
        button: "#eee"
        buttonText: "#000"
        dark: "#999"
        highlight: '#0078d4'
        highlightedText: "#fff"
        light: "#fff"
        mid: "#bbb"
        midlight: "#ccc"
        placeholderText: "#80000000"
        shadow: "#777"
        text: "#000"
        window: "#eee"
        windowText: "#000"

        disabled.text: '#737373'
    }
}
