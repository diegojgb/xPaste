import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ApplicationWindow {
    id: root

    visible: false
    title: qsTr('xPaste')

    width: 700
    height: 483
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    enum View {
        SettingsView,
        AboutView
    }

    property int transitionDuration: 250
    property bool darkEnabled: ThemeSetter.darkEnabled
    property int activeView: Main.View.SettingsView

    onClosing: close => {
                   if (Manager.settings.closeBtnExits) {
                       return
                   }

                   hide()
                   close.accepted = false
               }

    onWindowStateChanged: windowState => {
                              if (Manager.settings.hideOnMinimize
                                  && windowState === Qt.WindowMinimized) {
                                  hide()
                              }
                          }

    onDarkEnabledChanged: {
        ThemeSetter.darkEnabled = root.darkEnabled
    }

    Component.onCompleted: {
        if (root.darkEnabled)
            ThemeSetter.updateWindowTheme()

        root.visible = !Manager.settings.startMinimized
    }

    palette: root.darkEnabled ? darkTheme : lightTheme

    function currentTheme() {
        if (root.darkEnabled)
            return "dark"
        return "light"
    }

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

            Behavior on color {
                ColorAnimation {
                    duration: root.transitionDuration
                }
            }

            ColumnLayout {
                anchors.fill: parent
                spacing: 0

                Rectangle {
                    id: on_off_switch

                    property bool checked: Manager.settings.pasteActive

                    color: root.darkEnabled ? '#333' : '#e4e4e4'
                    Layout.fillWidth: true
                    Layout.preferredHeight: 75

                    onCheckedChanged: {
                        Manager.settings.pasteActive = checked
                    }

                    Behavior on color {
                        ColorAnimation {
                            duration: root.transitionDuration
                        }
                    }

                    Image {
                        source: Manager.settings.pasteActive ? 'assets/on_switch.png' : 'assets/off_switch.png'
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

                    onClicked: root.activeView = Main.View.SettingsView
                }

                Tab {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 48
                    text: 'About'
                    darkEnabled: root.darkEnabled
                    dark_image: "assets/dark/about.png"
                    light_image: "assets/light/about.png"

                    onClicked: root.activeView = Main.View.AboutView
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

                        onCurrentIndexChanged: {
                            if (currentIndex === 0) {
                                ThemeSetter.darkEnabled = false
                            } else if (currentIndex === 1) {
                                ThemeSetter.darkEnabled = true
                            }
                        }
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

            Behavior on color {
                ColorAnimation {
                    duration: root.transitionDuration
                }
            }

            SettingsPage {
                width: parent.width
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 27
                anchors.leftMargin: 24

                visible: root.activeView === Main.View.SettingsView
            }

            AboutPage {
                width: parent.width
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 32
                anchors.leftMargin: 28

                visible: root.activeView === Main.View.AboutView
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
