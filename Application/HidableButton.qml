import QtQuick 2.0

Rectangle {
    id: button

    property alias text : buttonText.text

    signal clicked

    width: buttonText.width + 20
    height: 30
    color: "darkgray"

    radius: 5
    antialiasing: true

    Text {
        id: buttonText
        text: parent.description
        anchors.centerIn: parent
        font.pixelSize: parent.height * .5
        color: "black"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            mouse.accepted = false;
            parent.clicked();
        }
        onContainsMouseChanged: {
            button.state = containsMouse ? "" : "hidden";
        }
    }


    states: [
        State {
            name: "hidden"
            PropertyChanges { target: button; opacity: 0 }
        }
    ]
}
