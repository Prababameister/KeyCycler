import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: keyboard_box

    width: 200
    height: 200

    property string display_name: "Keyboard Name"
    property int display_index: -1

    property int kb_index: -1

    color: "grey"

    Column {
        Text {
            text: display_name
            font.family: "Helvetica"
            font.pointSize: 16
            color: "black"
        }

        Text {
            text: display_index
            font.family: "Helvetica"
            font.pointSize: 24
            color: "black"
        }
    }
}
