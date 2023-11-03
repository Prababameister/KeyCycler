import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root
    visible: true
    title: "Kill yourself"
    Text {
        text: "Hello, world!"
        anchors.centerIn: parent
    }

    Rectangle {
        id: bottombar
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        color: "green"
        height: parent.height / 12
    }

    RowLayout {
        Button {
            text: "Ok"
            onClicked: model.submit()
        }
        Button {
            text: "Cancel"
            onClicked: model.revert()
        }
    }
}
