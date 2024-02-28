# Bugs:
# - Can't set policy QTP0001 to NEW because it throws an error.

# Optional:
# - Change title bar color based on the current theme (dark/light)


cmake_minimum_required(VERSION 3.16)

project(xPasteQT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS QuickControls2)

qt_standard_project_setup()

qt_add_executable(appxPasteQT
    main.cpp
)

# qt_policy(SET QTP0001 OLD)

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
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appxPasteQT
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appxPasteQT
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appxPasteQT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)



