import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    property var cycle

    Repeater {
        id: repeaterModel
        model: cycle.getCycleSize()

        delegate: Item {
            width: 400
            height: 600

            Loader {
                id: kBoxLoader
                source: "KBox.qml"
                onLoaded: {
                    if(item) {
                        item.display_name = cycle.getKb(index).full;
                        item.display_index = index;
                    }
                }
            }

            Connections {
                target: add_button

                function onButtonSignal() {
                    repeaterModel.model = cycle.getCycleSize()
                }
            }
        }
    }

    ComboBox {
        id: keyboard_select

        width: 200
        model: kbList.kbList
        textRole: "full"
    }

    Text {
        text: cycle.getCycleSize()
    }

    Button {
        id: "add_button"
        text: "Add"

        signal buttonSignal()

        onClicked: {
            cycle.addKb(kbList.getKb(keyboard_select.currentIndex));
            buttonSignal()
        }
    }

    Connections {
        target: cycle
    }
}
