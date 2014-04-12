import QtQuick 1.1
import 'func.js' as Func

Rectangle{
    id:button
    signal clicked;
    width:text.width + 10;
    height:40;
    property alias text: text.text
    property alias text_color:text.color
    property string color_start : "blue"
    property string color_stop : "#0527af";
    border.color:"#E5E5E5"
    radius:5;

    gradient:Gradient{
        GradientStop { id:stop1; position: 0.1; color:button.color_start; }
        GradientStop { id:stop2; position: 1; color:button.color_stop; }
    }
    Text{
        id:text
        anchors.centerIn:parent
        color: "white"
        font.pixelSize:23;
        font.bold: true
    }
    MouseArea{
        anchors.fill:button
        hoverEnabled:true
        onClicked: button.clicked()
        onPressed: {
            button.state = "press"
        }
        onReleased: button.state = ""

    }
    states:[
        State{
            name:"press"
            PropertyChanges{ target:stop1; color:button.color_stop; }
            PropertyChanges{ target:stop2; color:button.color_start; }
        }
    ]
}
