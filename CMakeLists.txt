cmake_minimum_required(VERSION 3.24)

project(xPaste LANGUAGES CXX)

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

qt_add_executable(appxPaste
    src/main.cpp
    assets/xpaste.rc  # icon resource.
    assets/version.rc
)

qt_policy(SET QTP0001 NEW)

qt_add_qml_module(appxPaste
    URI xPaste
    VERSION 1.0

    QML_FILES
        qml/Tab.qml
        qml/Main.qml
        qml/LabelSeparator.qml
        qml/CustomCheckbox.qml
        qml/HotkeyInput.qml
        qml/CustomComboBox.qml
        qml/CustomSpinBox.qml
        qml/SettingsPage.qml
        qml/AboutPage.qml

    SOURCES
        src/WindowThemeSetter.h
        src/WindowThemeSetter.cpp
        src/Settings.h
        src/Settings.cpp
        src/Hotkey.h
        src/Hotkey.cpp
        src/Paster.h
        src/Paster.cpp
        src/Utils.h
        src/Utils.cpp
        src/TrayIcon.h
        src/TrayIcon.cpp
        src/ToastHandler.h
        src/Registry.h
        src/Registry.cpp
        src/Manager.h
        src/Manager.cpp
        src/HookHandler.h
        src/HookHandler.cpp

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

        assets/off-switch.png
        assets/on-switch.png
        assets/xpaste-logo.png
        assets/xpaste-logo.ico
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appxPaste PROPERTIES
    WIN32_EXECUTABLE TRUE
    OUTPUT_NAME "xPaste"
)

target_link_libraries(appxPaste PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Widgets
    WinToast
    dwmapi
    ntdll

    SingleApplication::SingleApplication
)

include(GNUInstallDirs)
install(TARGETS appxPaste
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
