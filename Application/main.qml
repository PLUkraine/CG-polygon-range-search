import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.1

Item {
    id: root

    function approxEqual(x, y) {
        var eps = 1e-9;
        return Math.abs(x-y) < eps;
    }

    function log2(x) {
        return Math.log(x) / Math.log(2);
    }

    function convertUrlToPath(path) {
        path = path.replace(/^(file:\/{2})/,"");
        var cleanPath = decodeURIComponent(path);
        return cleanPath;
    }

    visible: true
    width: 1024
    height: 768

    ProblemRenderer {
        id: scene
        focus: true
        anchors.fill: root

        onCanvasScaleChanged: {
            var a = log2(scene.canvasScale);
            slider.value = a;
        }
        onErrorOccured: {
            errorDialog.text = errorMessage;
            errorDialog.open();
        }
        onOpenFileDialog: {
            fileDialog.open();
        }
    }

    Slider {
        id: slider

        anchors.margins: 10
        anchors.left: root.left
        anchors.right: root.right
        anchors.bottom: root.bottom

        value: 0
        maximumValue: 20
        minimumValue: -20

        onValueChanged: {
            var a = Math.pow(2, slider.value);
            if (approxEqual(a, scene.canvasScale)) return;
            scene.canvasScale = a;
        }
    }

    Text {
        id: counter

        anchors.margins: 10
        anchors.left: root.left
        anchors.top: root.top
        color: "black"

        text: "n="+scene.pointCount + " k="+scene.polygonSize
    }


    MessageDialog {
        id: errorDialog
        title: "Error"
    }
    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        onAccepted: {
            var cleanPath = convertUrlToPath(fileDialog.fileUrl.toString());
            scene.readSceneFromFile(cleanPath)
        }
    }
}
