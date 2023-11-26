import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


ColumnLayout {
    id: cyclesLayout
    spacing: 200

    Repeater {
        id: cycleRepeater
        model: cycleList.getCycleListSize()

        delegate: Item {
            Loader {
                id: cycleLoader
                source: "CycleDisplay.qml"
                onLoaded: {
                    item.cycle = cycleList.getCycle(index);
                }
            }

            Connections {
                target: addCycleButton

                function onAddCycleSignal() {
                    cycleRepeater.model = cycleList.getCycleListSize();
                }
            }
        }
    }

    Button {
        id: addCycleButton
        text: "Add Cycle"

        signal addCycleSignal()

        onClicked: {
            cycleList.addCycle();
            addCycleSignal();
        }
    }
}
