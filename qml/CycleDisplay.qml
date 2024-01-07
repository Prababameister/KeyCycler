import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    property var cycle
    property var i

    Repeater {
        id: kbRepeater
        model: cycle.getCycleSize()

        delegate: Item {
            width: 400
            height: 600

            Loader {
                id: kBoxLoader
                source: "KBox.qml"
                onLoaded: {
                    if(item) {
                        item.nameDisplay = cycle.getKb(index).full;
                        item.cycleIndex = index;
                    }
                }
            }
        }
    }

    ComboBox {
        id: keyboardDD

        width: 200
        model: kbList.kbList
        textRole: "full"
    }

    Button {
        id: addKbButton
        text: "Add"

        onClicked: {
            cycle.addKb(kbList.getKb(keyboardDD.currentIndex));
            kbRepeater.model = cycle.getCycleSize();
        }
    }

    Button {
        id: removeCycleButton
        text: "Remove Cycle"

        onClicked: {
            cycleList.removeCycle(i);
            cycleRepeater.model = cycleList.getCycleListSize();
        }
    }
}
