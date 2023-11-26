import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    visible: true
    title: "Kill yourself"

    Text {
        text: cycleList.current
    }

    Loader {
        id: cycleListDisplayLoader
        source: "CycleListDisplay.qml"
    }
}
