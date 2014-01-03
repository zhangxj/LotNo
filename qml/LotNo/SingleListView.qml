import QtQuick 2.1
import 'func.js' as Func

Rectangle {
    id:leftMenu
    property variant model;//: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
    property string flag;
    signal selected(string value);
    property variant selectedSubItem;
    property variant currentData;
    color: "transparent"
    border.width: 2
    border.color: "blue"
    property int item_height: 40

    ListModel{
        id: sub_list_model
    }


    Rectangle{
        id: top
        z: 3
        color: "lightgrey"
        width: leftMenu.width; height: item_height
        anchors.top: parent.top
        Text{
            text: flag
            font.bold: true
            font.pixelSize: 20
            anchors.centerIn: parent
        }

        Rectangle{
            width: parent.width; height:1
            anchors.bottom: parent.bottom
            color: "blue"
        }
    }


    Component{
        id: plugin_sub_item
        Column{
            Rectangle{
                id: list_item
                state: ""
                height: item_height; width:leftMenu.width
                color: is_LastOne(modelData, leftMenu.model) == "1" ? "#0527af": "transparent"
                Text {
                    id: id_text
                    font.pixelSize:18
                    font.bold: true
                    text: modelData
                    color: is_LastOne(modelData, leftMenu.model) == "1" ? "white": "#474747"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                MouseArea {
                    id:subClick; anchors.fill:parent
                    hoverEnabled: true
                    onClicked:{
                        selected(modelData);
                        currentData = modelData;
                    }
                }

                states: [
                    State{
                        name:"selected"
                        PropertyChanges{
                            target:list_item;
                            color: "#0527af"
                            width:leftMenu.width + 1;
                        }
                    },
                    State{
                        name:"entered"
                        PropertyChanges {
                            target: list_item;
                            color:"#f3f3f3"
                        }
                    }
                ]
            }

            Image{
                source: Func.get_image_path("dotted_line2.png");
                fillMode:Image.TileHorizontally;
                height: 2
                width:leftMenu.width - 2;
            }
        }
    }

    ListView{
        id: listView
        width: leftMenu.width
        //anchors.fill: parent
        anchors.top: top.bottom
        anchors.bottom: parent.bottom
        model: leftMenu.model
        delegate: plugin_sub_item
        onCurrentIndexChanged: {
            positionViewAtEnd()
        }
    }

    function is_LastOne(v, src){
        //console.log("***************************");
        for(var i = 0; i < src.length; i++){
            if(currentData == src[i] && currentData == v){
                return "1";
            }
        }

        if(!currentData && v == src[src.length - 1]){
            return "1"
        }else
            return "0"
    }
}


