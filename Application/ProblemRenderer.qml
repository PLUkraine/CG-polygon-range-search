import QtQuick 2.0
import SceneRenderer 1.0

MouseArea {
    id: root

    property var modeToInt: {
        // canvas move in progres
        "Moving": 0,
        // move canvas action
        "Move"  : 1,
    }

    property alias pointCount: scene.pointCount
    property alias polygonSize: scene.polygonSize
    property alias canvasScale: scene.scale
    property alias canvasCenter: scene.canvasCenter
    property int mouseMode: modeToInt["Move"]
    property bool firstMouseMove: true
    property point prevMousePos

    signal errorOccured(string errorMessage)
    signal openFileDialog

    function readSceneFromFile(filename) {
        var err = scene.readSceneFromFile(filename);
        if (err) {
            errorOccured(err);
        }
    }
    function tryParseInt(str) {
         var retValue = -1;
         if(str !== null) {
             if(str.length > 0) {
                 if (!isNaN(str)) {
                     retValue = parseInt(str);
                 }
             }
         }
         return retValue;
    }


    hoverEnabled: true

    onPositionChanged: {
        var newPos = Qt.point(mouse.x, mouse.y);

        switch (mouseMode) {
        case modeToInt["Moving"]:
            if (firstMouseMove) {
                // set first mouse position
                firstMouseMove = false;
                prevMousePos = newPos;
            } else {
                // compute difference between previous and current mouse position
                var dx = newPos.x - prevMousePos.x;
                var dy = newPos.y - prevMousePos.y;
                scene.moveCanvas(-dx, dy);
                prevMousePos = newPos;
            }
            break;
         default:
             // just ignore
             break;
        }
    }

    onPressed: {
        if (mouse.button === Qt.LeftButton) {
            switch (root.mouseMode) {
            case modeToInt["Move"]:
                // begin moving canvas
                mouseMode = modeToInt["Moving"];
                firstMouseMove = true;
                // change cursor to movement cursor
                root.cursorShape = Qt.SizeAllCursor;
                break;
            }
        }
    }
    onDoubleClicked: {
        if (mouse.button === Qt.LeftButton) {
            root.canvasCenter = Qt.point(0,0);
        }
    }
    onReleased: {
        if (mouse.button === Qt.LeftButton
                && root.mouseMode === modeToInt["Moving"])
        {
            // stop moving canvas
            mouseMode = modeToInt["Move"];
            // change cursor back to arrow
            root.cursorShape = Qt.ArrowCursor;
        }
    }
    onWheel: {
        if (wheel.angleDelta.y > 0) {
            scene.scale *= 2;
        }
        else if (wheel.angleDelta.y < 0) {
            scene.scale /= 2;
        }
    }

    Keys.onPressed: {
        switch (event.key) {
        case Qt.Key_Plus: case Qt.Key_Equal:
            scene.scale *= 2;
            break;
        case Qt.Key_Minus:
            scene.scale /= 2;
            break;
        case Qt.Key_G:
            getN.open();
            break;
        case Qt.Key_L:
            openFileDialog();
            break;
        case Qt.Key_Escape:
            Qt.quit();
            break;
        }
    }

    GeometrySearchPlugin {
        id: scene

        shaders: ":/shaders/s"
    }

    InputDialog {
        id: getN

        property int val: 0
        text: "Write n"

        onInputProvided: {
            val = tryParseInt(input);
            if (val < 0) {
                errorOccured("n must be positive integer");
                return;
            }

            getK.open();
        }
    }
    InputDialog {
        id: getK

        property int val: 0
        text: "Write k"

        onInputProvided: {
            val = tryParseInt(input);
            if (val < 0) {
                errorOccured("k must be positive integer");
                return;
            }

            scene.generateRandomScene(getN.val, val);
        }
    }


}
