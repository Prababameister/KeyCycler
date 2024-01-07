import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: kbox

    width: 200
    height: 200

    property string nameDisplay: "Keyboard Name"
    property int cycleIndex: -1

    color: "grey"

    Column {
        Text {
            text: nameDisplay
            font.family: "Helvetica"
            font.pointSize: 16
            color: "black"
        }

        Text {
            text: cycleIndex
            font.family: "Helvetica"
            font.pointSize: 24
            color: "black"
        }

        Button {
            id: removeKbButton
            text: "Remove"

            signal removeKbSignal()

            onClicked: {
                cycle.removeKb(cycleIndex);
                kbRepeater.model = cycle.getCycleSize();
            }
        }
    }
}
