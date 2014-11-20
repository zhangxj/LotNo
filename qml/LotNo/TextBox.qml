import QtQuick 1.1
import 'func.js' as Func

FocusScope {
    id: focusScope
    width: 600; height: 40
    property string flag;
    property alias text: textInput.text
    property variant bk_text: ''
    focus: false;
    signal finished(string value);

    BorderImage {
        source: Func.get_image_path("lineedit-bg.png");
        width: parent.width; height: parent.height
        border { left: 4; top: 4; right: 4; bottom: 4 }
    }

    Text {
        id: typeSomething
        anchors.fill: parent; anchors.leftMargin: 8
        verticalAlignment: Text.AlignVCenter
        text: bk_text
        font.pixelSize:16
        color: "gray"
    }

    MouseArea {
        anchors.fill: parent
    }

    TextInput {
        id: textInput
        anchors { left: parent.left; leftMargin: 8; right: parent.right; rightMargin: 8; verticalCenter: parent.verticalCenter }
        font.pixelSize:20
        font.bold: true
        focus: true
        onAccepted: {
            finished(textInput.text)
        }

        onFocusChanged: {
            textInput.text = '';
        }
    }

    /*
    Image {
        id: clear
        anchors { right: parent.right; rightMargin: 8; verticalCenter: parent.verticalCenter }
        //source: Func.get_image_path("clear.png");
        opacity: 0
    }*/

    states: State {
        name: "hasText"; when: textInput.text != ''
        PropertyChanges { target: typeSomething; opacity: 0 }
        //PropertyChanges { target: clear; opacity: 1 }
    }

    transitions: [
        Transition {
            from: ""; to: "hasText"
            NumberAnimation { exclude: typeSomething; properties: "opacity" }
        },
        Transition {
            from: "hasText"; to: ""
            NumberAnimation { properties: "opacity" }
        }
    ]
}
