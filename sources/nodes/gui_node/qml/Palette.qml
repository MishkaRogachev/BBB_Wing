import QtQuick 2.5

Item {
    property color backgroundColor: configService.value("Gui/Palette/backgroundColor")
    property color foregroundColor: configService.value("Gui/Palette/foregroundColor")
    property color highlightColor: configService.value("Gui/Palette/highlightColor")
    property color textColor: configService.value("Gui/Palette/textColor")
    property color errorColor: configService.value("Gui/Palette/errorColor")

    property color skyColor: configService.value("Gui/Palette/skyColor")
    property color groundColor: configService.value("Gui/Palette/groundColor")
}
