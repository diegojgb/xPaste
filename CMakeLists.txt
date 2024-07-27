# Bugs:
# - Can't set policy QTP0001 to NEW because it throws an error.

# Optional:
# - Add "System" option to theme.
# - Change app name to xPasteQt or maybe even xPaste.
# - Remake the up/down indicators of the SpinBox to be able to transition their color when changing themes.


cmake_minimum_required(VERSION 3.24)

project(xPasteQT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

include(FetchContent)

set(QT_DEFAULT_MAJOR_VERSION 6 CACHE STRING "Qt version to use, defaults to 6")
set(QAPPLICATION_CLASS QApplication CACHE STRING "Inheritance class for SingleApplication")

FetchContent_Declare(
    SingleApplication
    GIT_REPOSITORY https://github.com/itay-grudev/SingleApplication.git
    GIT_TAG        8c48163c4d3fbba603cfe8a5b94046c9dad71825
)

FetchContent_MakeAvailable(SingleApplication)

find_package(SingleApplication)
find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Widgets QuickControls2)

qt_standard_project_setup()

add_subdirectory(WinToast)

qt_add_executable(appxPasteQT
    main.cpp
)

qt_policy(SET QTP0001 NEW)

qt_add_qml_module(appxPasteQT
    URI xPasteQT
    VERSION 1.0

    QML_FILES
        Tab.qml
        Main.qml
        LabelSeparator.qml
        CustomCheckbox.qml
        HotkeyInput.qml
        CustomComboBox.qml
        CustomSpinBox.qml
        SettingsPage.qml
        AboutPage.qml

    SOURCES
        WindowThemeSetter.h WindowThemeSetter.cpp
        Settings.h Settings.cpp
        Hotkey.h Hotkey.cpp
        HotkeyEventFilter.h
        Paster.h Paster.cpp
        Utils.h Utils.cpp
        TrayIcon.h TrayIcon.cpp
        ToastHandler.h
        Registry.h Registry.cpp
        Manager.h Manager.cpp

    RESOURCES
        assets/light/about.png
        assets/light/settings.png
        assets/light/box-basic.png
        assets/light/box-hover.png
        assets/light/check-accent.png
        assets/light/check-hover.png
        assets/light/box-disabled.png
        assets/light/check-disabled.png

        assets/dark/about.png
        assets/dark/settings.png
        assets/dark/box-basic.png
        assets/dark/box-hover.png
        assets/dark/check-accent.png
        assets/dark/check-hover.png
        assets/dark/box-disabled.png
        assets/dark/check-disabled.png

        assets/off_switch.png
        assets/on_switch.png
        assets/xpaste_logo.png
        assets/xpaste_logo.ico
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appxPasteQT PROPERTIES
    WIN32_EXECUTABLE TRUE
    OUTPUT_NAME "xPaste"
)

target_link_libraries(appxPasteQT PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Widgets
    WinToast
    dwmapi
    ntdll

    SingleApplication::SingleApplication
)

include(GNUInstallDirs)
install(TARGETS appxPasteQT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
