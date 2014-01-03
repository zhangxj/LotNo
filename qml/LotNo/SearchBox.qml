import QtQuick 2.1
import 'func.js' as Func

Rectangle {
    id: page
    width: 614; height: 54
    color: "#7bffffff"
    radius:5
    property string defaultText;
    property bool clear;
    signal textBox(string value)

    ShadowRectangle {
        color: "#434343"
        transformOrigin: "Center"
        opacity: 0.97
        visible: true
        anchors.centerIn: parent; width: parent.width - 4; height: parent.height - 4
    }
    TextBox {
        id: search;
        width: parent.width -  10; height: parent.height - 10
        defaultText: page.defaultText
        clear: clear
        opacity: 1
        anchors.centerIn: parent
        onFinished: {
            textBox(value);
        }
    }
}

