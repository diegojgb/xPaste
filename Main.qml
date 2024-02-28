import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ApplicationWindow {
    id: root

    visible: true
    title: qsTr('xPaste')

    width: 700
    height: 480

    // maximumHeight: height
    // maximumWidth: width
    // minimumHeight: height
    // minimumWidth: width
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

            ColumnLayout {
                id: maincol

                width: parent.width
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 27
                anchors.leftMargin: 24

                Label {
                    text: 'General settings'
                    font.pointSize: 17
                    renderType: Text.NativeRendering
                }

                // App settings
                LabelSeparator {
                    Layout.topMargin: 16
                    text: 'App settings'
                    darkEnabled: root.darkEnabled
                }

                ColumnLayout {
                    Layout.topMargin: 8
                    Layout.leftMargin: 20
                    spacing: 10

                    CustomCheckbox {
                        text: qsTr("Start xPaste minimized to the system tray.")
                        darkEnabled: root.darkEnabled
                    }

                    CustomCheckbox {
                        text: qsTr("Open from tray with a single click.")
                        darkEnabled: root.darkEnabled
                    }

                    CustomCheckbox {
                        text: qsTr("Close button exits the application.")
                        darkEnabled: root.darkEnabled
                    }

                    CustomCheckbox {
                        text: qsTr("Minimize to the system tray.")
                        darkEnabled: root.darkEnabled
                    }
                }

                // Clipboard hook settings
                LabelSeparator {
                    Layout.topMargin: 16
                    text: 'Clipboard hook settings'
                    darkEnabled: root.darkEnabled
                }

                ColumnLayout {
                    Layout.topMargin: 8
                    Layout.leftMargin: 20
                    spacing: 10

                    RowLayout {
                        spacing: 6

                        CustomCheckbox {
                            text: qsTr("Setup a custom paste hotkey")
                            darkEnabled: root.darkEnabled
                        }

                        HotkeyInput {
                            darkEnabled: root.darkEnabled
                            defaultHotkey: 'CTRL+V'
                            Layout.topMargin: 1
                            Layout.preferredWidth: 120
                            Layout.preferredHeight: 25
                        }
                    }

                    RowLayout {
                        spacing: 6

                        CustomCheckbox {
                            id: hotkey_checkbox

                            text: qsTr("Setup a hotkey for toggling the hook")
                            darkEnabled: root.darkEnabled
                        }

                        HotkeyInput {
                            darkEnabled: root.darkEnabled
                            defaultHotkey: 'CTRL+V'
                            Layout.topMargin: 1
                            Layout.preferredWidth: 120
                            Layout.preferredHeight: 25
                        }
                    }

                    CustomCheckbox {
                        Layout.leftMargin: 25
                        text: qsTr("Disable on/off notifications.")
                        darkEnabled: root.darkEnabled
                        disabled: !hotkey_checkbox.checked
                    }

                    RowLayout {
                        spacing: 6
                        Layout.topMargin: 5

                        CustomCheckbox {
                            id: time_checkbox

                            text: qsTr("Automatically disable the hook after")
                            darkEnabled: root.darkEnabled
                        }

                        CustomSpinBox {
                            Layout.preferredWidth: 120
                            darkEnabled: root.darkEnabled
                        }
                    }

                    CustomCheckbox {
                        Layout.leftMargin: 25
                        text: qsTr("Disable \"Time's up\" notification.")
                        darkEnabled: root.darkEnabled
                        disabled: !time_checkbox.checked
                    }
                }
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
