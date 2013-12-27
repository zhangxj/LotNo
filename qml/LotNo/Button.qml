import QtQuick 2.1
import 'func.js' as Func

Rectangle{
    id:button
    signal clicked;

    radius:3;
    border.width: 1
    border.color:"#E5E5E5"

    property string color_1: "#0527AF"
    property string color_2: "blue"
    property alias text: text.text
    property alias text_color:text.color
    property alias text_pixelSize:text.font.pixelSize

    gradient: Gradient {
        GradientStop {id: s1; position: 0.3; color: color_1 }
        GradientStop {id: s2; position: 1.0; color: color_2 }
    }

    Text{
        id:text
        anchors.centerIn:parent
        font.pixelSize:24;
        font.bold: true
    }
    MouseArea{
        anchors.fill:button
        hoverEnabled:true
        onClicked: button.clicked()
        onPressed: button.state = "press"
        onReleased: button.state = ""
    }

    states: [
        State{
            name: "press"
            PropertyChanges { target: s1; color: button.color_2}
            PropertyChanges { target: s2; color:button.color_1 }
        }
    ]
}
