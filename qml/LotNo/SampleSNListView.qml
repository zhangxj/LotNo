import QtQuick 1.1
import 'func.js' as Func

Rectangle {
    id:leftMenu
    property variant model;
    signal selected(string value);
    property variant selectedSubItem;
    property variant currentData;
    border.width: 1
    border.color: "grey"
    property int item_height: 40

    ListModel{
        id: list_model
    }

    Component{
        id: plugin_sub_item
        Column{
            Rectangle{
                id: list_item
                state: ""
                height: item_height; width:leftMenu.width
                color: "transparent" //is_LastOne(text, leftMenu.model) == "1" ? "#0527af": "transparent"
                Text {
                    id: id_text
                    font.pixelSize:18
                    font.bold: true
                    text: aaa
                    color: "black"
                    //color: is_LastOne(text, leftMenu.model) == "1" ? "white": "#474747"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                /*
                MouseArea {
                    id:subClick; anchors.fill:parent
                    hoverEnabled: true
                    onClicked:{
                        selected(text);
                        currentData = text;
                    }
                }*/

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
        width: leftMenu.width
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        model: getModelData(leftMenu.model, list_model)
        delegate: plugin_sub_item
        onCurrentIndexChanged: {
            positionViewAtEnd()
        }
    }

    function getModelData(src, dst){
        dst.clear()
        if(src === undefined) return;
        for(var i = 0; i < src.length; i++){
            var l = src[i].split('|')
            dst.append({'aaa': l[0], 'location': l[1]})
        }
        return dst
    }

    function is_LastOne(v, src){
        var l;
        for(var i = 0; i < src.length; i++){
            l = src[i].split('|')
            if(currentData == l[0] && currentData == v){
                return "1";
            }
        }

        var last = src[src.length - 1];
        l = last.split('|');
        if(!currentData && v == l[0]){
            return "1"
        }else
            return "0"
    }
}


