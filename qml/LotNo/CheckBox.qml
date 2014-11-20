import QtQuick 1.1
import 'func.js' as Func

Rectangle{
    id:control
    width:content.width;height:content.height
    property alias text: text.text
    property alias enabled:checkMouseArea.enabled
    property bool checked: false
    property variant value;
    signal clicked
    color:"transparent"
    Row{
        id:content
        spacing:5;
        Image{
            id:box
            width:18;height:18;
            anchors.verticalCenter: parent.verticalCenter
            source:Func.get_image_path("checkbox_normal.png")
        }
        Text{
            id:text
        }
    }
    MouseArea{
        id: checkMouseArea
        anchors.fill:parent
        enabled: true
        onClicked:{
            control.checked = ! control.checked;
            control.clicked();
        }
    }
    states:[
        State{
            name:"checked"
            PropertyChanges{
                target :box
                source:Func.get_image_path("checkbox_checked.png")
            }
        }
    ]
    onCheckedChanged:{
        control.state = control.checked?"checked":"";
    }
}

