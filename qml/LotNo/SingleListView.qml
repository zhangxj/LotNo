import QtQuick 2.1
import 'func.js' as Func

Rectangle {
    id:leftMenu
    //color:"#d5d5d5";
    property variant model;//: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
    property string flag;
    signal selected(string value);
    property variant selectedSubItem;
    property variant currentData;

    ListModel{
        id: sub_list_model
    }



    Component{
        id: plugin_sub_item
        Column{
            Rectangle{
                id: list_item
                state: ""
                height: 40; width:leftMenu.width
                color: is_LastOne(modelData, leftMenu.model) == "1" ? "lightblue": "transparent"
                Text {
                    id: id_text
                    x:25
                    font.pixelSize:16
                    font.bold: true
                    text: modelData
                    color: "#474747"
                    anchors.verticalCenter: parent.verticalCenter
                }

                MouseArea {
                    id:subClick; anchors.fill:parent
                    hoverEnabled: true
                    onClicked:{
                        selected(modelData);
                        currentData = modelData;
                    }
                    //onEntered: enter_item(list_item);
                    //onExited: exit_item(list_item);
                }

                states: [
                    State{
                        name:"selected"
                        PropertyChanges{
                            target:list_item;
                            color: "lightblue"
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
                width:leftMenu.width;
            }
        }
    }

    ListView{
        id: listView
        width: leftMenu.width
        anchors.fill: parent
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

    function enter_item(item){
        if(selectedSubItem != item)
            item.state = "entered"
    }
    function exit_item(item){
        if(selectedSubItem != item)
            item.state = ""
    }
}


