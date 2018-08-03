import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4

Dialog {
    id: root

    property alias text: label.text
    signal inputProvided(string input);

    modality: Qt.WindowModal
    title: "Input"

    Column {
        id: column

        anchors.fill: parent
        spacing: 9

        Text {
            id: label
        }

        TextField {
            id: textInput

            width: parent.width
            placeholderText: "Print here..."

            Keys.onReturnPressed: {
                close();
                inputProvided(text);
            }
        }


        Keys.onPressed: {
            if (event.key === Qt.Key_Escape) {
                close();
            }
        }
    }

    onButtonClicked: {
        if (clickedButton === StandardButton.Ok) {
            inputProvided(textInput.text);
        }
    }


}
