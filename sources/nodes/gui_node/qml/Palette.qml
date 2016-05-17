import QtQuick 2.5

Item {
    id: palette

    property color backgroundColor: configService.value("Gui/Palette/background_color")
    property color middlegroundColor: configService.value("Gui/Palette/middleground_color")
    property color foregroundColor: configService.value("Gui/Palette/foreground_color")

    property color textColor: configService.value("Gui/Palette/text_color")
    property color highlightColor: configService.value("Gui/Palette/highlight_color")

    property color normalColor: configService.value("Gui/Palette/normal_color")
    property color warningColor: configService.value("Gui/Palette/warning_color")
    property color errorColor: configService.value("Gui/Palette/error_color")

    property color skyColor: configService.value("Gui/Palette/sky_color")
    property color groundColor: configService.value("Gui/Palette/ground_color")

    property color transparent: "transparent"
}
