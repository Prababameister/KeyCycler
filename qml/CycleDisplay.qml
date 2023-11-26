import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    property var cycle

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

            Connections {
                target: addKbButton

                function onAddKbSignal() {
                    kbRepeater.model = cycle.getCycleSize();
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

        signal addKbSignal()

        onClicked: {
            cycle.addKb(kbList.getKb(keyboardDD.currentIndex));
            addKbSignal();
        }
    }
}
