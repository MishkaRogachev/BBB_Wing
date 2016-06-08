import QtQuick 2.6
import "../../Controls"

StickPad {
    spacing: dashboard.spacing
    height: configService.value("Gui/StickPad/size")
    model: configService.value("Gui/StickPad/model")
    onDeviationChanged: {
        switch (channel) {
        case "pitch":
            boardService.setTargetPitch(deviation);
            break;
        case "roll":
            boardService.setTargetRoll(deviation);
            break;
        case "course":
            boardService.setTargetCourse(deviation);
            break;
        case "speed":
            boardService.setTargetSpeed(deviation);
            break;
        }
    }
}
