import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root
    visible: true
    title: "Kill yourself"

    Component.onCompleted: {
        if (Qt.binding(function() { return cycleList; })) {
            console.log("myContextProperty exists and is not null!");
            // Perform actions using myContextProperty
        } else {
            console.log("myContextProperty does not exist or is null.");
        }
    }

    Text {
        text: cycleList.current
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
}
