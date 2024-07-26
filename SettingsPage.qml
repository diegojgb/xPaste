import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    id: page

    Label {
        text: 'General settings'
        font.pointSize: 17
        renderType: Text.NativeRendering

        Behavior on color {
            ColorAnimation {
                duration: root.transitionDuration
            }
        }
    }

    // App settings
    LabelSeparator {
        Layout.topMargin: 16
        text: 'App settings'
        darkEnabled: root.darkEnabled
    }

    ColumnLayout {
        Layout.topMargin: 10
        Layout.leftMargin: 20
        spacing: 10

        CustomCheckbox {
            text: "Start xPaste minimized to the system tray."
            darkEnabled: root.darkEnabled
        }

        CustomCheckbox {
            text: "Open from tray with a single click."
            darkEnabled: root.darkEnabled
            checked: Manager.settings.singleClick

            onCheckedChanged: Manager.settings.singleClick = checked
        }

        CustomCheckbox {
            text: "Close button exits the application."
            darkEnabled: root.darkEnabled
            checked: Manager.settings.closeBtnExits

            onCheckedChanged: Manager.settings.closeBtnExits = checked
        }

        CustomCheckbox {
            text: "Minimize to the system tray."
            darkEnabled: root.darkEnabled
        }
    }

    // Clipboard hook settings
    LabelSeparator {
        Layout.topMargin: 18
        text: 'Clipboard hook settings'
        darkEnabled: root.darkEnabled
    }

    ColumnLayout {
        Layout.topMargin: 7
        Layout.leftMargin: 20
        spacing: 10

        RowLayout {
            spacing: 6

            CustomCheckbox {
                id: paste_hotkey_checkbox
                text: "Setup a custom paste hotkey"
                darkEnabled: root.darkEnabled
                checked: Manager.settings.customHotkeyEnabled

                onCheckedChanged: Manager.settings.customHotkeyEnabled = checked
            }

            HotkeyInput {
                darkEnabled: root.darkEnabled
                text: Manager.settings.pasteHotkey.string
                Layout.topMargin: 1
                Layout.preferredWidth: 120
                Layout.preferredHeight: 25
                disabled: !paste_hotkey_checkbox.checked

                Keys.onPressed: event => {
                                    Manager.settings.pasteHotkey.setHotkey(
                                        event.key, event.modifiers,
                                        event.nativeScanCode,
                                        Manager.settings.pasteActive)
                                }
            }
        }

        RowLayout {
            spacing: 6

            CustomCheckbox {
                id: toggle_hotkey_checkbox
                text: "Setup a hotkey for toggling the hook"
                darkEnabled: root.darkEnabled
                checked: Manager.settings.toggleActive

                onCheckedChanged: Manager.settings.toggleActive = checked
            }

            HotkeyInput {
                darkEnabled: root.darkEnabled
                text: Manager.settings.toggleHotkey.string
                Layout.topMargin: 1
                Layout.preferredWidth: 120
                Layout.preferredHeight: 25
                disabled: !toggle_hotkey_checkbox.checked

                Keys.onPressed: event => {
                                    Manager.settings.toggleHotkey.setHotkey(
                                        event.key, event.modifiers,
                                        event.nativeScanCode, true)
                                }
            }
        }

        CustomCheckbox {
            Layout.leftMargin: 25
            text: "Disable on/off notifications."
            darkEnabled: root.darkEnabled
            disabled: !toggle_hotkey_checkbox.checked
            checked: Manager.settings.disableToggleToasts

            onCheckedChanged: Manager.settings.disableToggleToasts = checked
        }

        RowLayout {
            spacing: 6
            Layout.topMargin: 5

            CustomCheckbox {
                id: time_checkbox
                text: "Automatically disable the hook after"
                darkEnabled: root.darkEnabled
                checked: Manager.settings.autoDisable

                onCheckedChanged: Manager.settings.autoDisable = checked
            }

            CustomSpinBox {
                Layout.preferredWidth: 120
                darkEnabled: root.darkEnabled
                enabled: time_checkbox.checked
                editable: time_checkbox.checked
                value: Manager.settings.autoDisableSeconds

                onValueChanged: Manager.settings.autoDisableSeconds = value
            }
        }

        CustomCheckbox {
            Layout.leftMargin: 25
            text: "Disable \"Time's up\" notification."
            darkEnabled: root.darkEnabled
            disabled: !time_checkbox.checked
            checked: Manager.settings.disableTimeToast

            onCheckedChanged: Manager.settings.disableTimeToast = checked
        }
    }
}
