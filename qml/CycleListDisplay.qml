import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


RowLayout {
    id: layout
    spacing: 3

    property var cycleList
    property var kbList

    Repeater {
        model: cycleList.getCycleListSize()

        delegate: Item {
            ComboBox {
                id: "keyboard_select"

                width: 200
                model: kbList.kbList

                textRole: "full"
            }

            Loader {
                id: cycle
                source: "CycleDisplay.qml"
                onLoaded: {
                    item.kbList = cycleList.getCycle(index)
                }
            }

            Button {
                id: "add_button"
                text: "Add"

                onClicked: {
                    kbList.setCurrent(keyboard_select.currentIndex);
                    kbList.applyCurrent();
                }
            }
        }
    }
}
