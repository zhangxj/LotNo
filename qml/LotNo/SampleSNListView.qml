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

    Row{
        id: title
        z: 1
        width: parent.width; height: item_height
        Rectangle{
            id: rec_title_text
            width: parent.width - rec_title_location.width; height: parent.height
            color: "darkgrey"
            border.width: 1
            border.color: "grey"
            Text {
                id: id_text
                font.pixelSize:18
                font.bold: true
                text: "Sample SN"
                color: "#474747"
                anchors.centerIn: parent
            }
        }
        Rectangle{
            id: rec_title_location
            width: 50; height: parent.height
            color: "darkgrey"
            border.width: 1
            border.color: "grey"
            Text {
                id: id_location
                font.pixelSize:18
                font.bold: true
                text: "位置"
                color: "#474747"
                anchors.centerIn: parent
            }
        }
    }

    Component{
        id: plugin_sub_item
        Column{
            Rectangle{
                id: list_item
                state: ""
                height: item_height; width:leftMenu.width
                color: "transparent" //is_LastOne(modelData, leftMenu.model) == "1" ? "#0527af": "transparent"
                Row{
                    width: parent.width; height: parent.height
                    Rectangle{
                        id: rec_text
                        width: parent.width - rec_title_location.width; height: parent.height
                        color: "transparent"
                        border.width: 1
                        border.color: "grey"
                        Text {
                            id: id_text
                            font.pixelSize:18
                            font.bold: true
                            text: getModelData(modelData, 0)
                            color: "#474747" //is_LastOne(modelData, leftMenu.model) == "1" ? "white": "#474747"
                            anchors.centerIn: parent
                        }
                    }
                    Rectangle{
                        width: rec_title_location.width; height: parent.height
                        color: "transparent"
                        border.width: 1
                        border.color: "grey"
                        Text {
                            id: id_location
                            font.pixelSize:18
                            font.bold: true
                            text: getModelData(modelData, 1)
                            color: "#474747" //is_LastOne(modelData, leftMenu.model) == "1" ? "white": "#474747"
                            anchors.centerIn: parent
                        }
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

            /*
            Image{
                source: Func.get_image_path("dotted_line2.png");
                fillMode:Image.TileHorizontally;
                height: 2
                width:leftMenu.width - 2;
            }
            */

        }
    }

    ListView{
        id: list_view
        width: leftMenu.width
        anchors.top: title.bottom
        anchors.bottom: parent.bottom
        model: leftMenu.model
        delegate: plugin_sub_item
        onCurrentIndexChanged: positionViewAtEnd()
    }

    function getModelData(data, index){
        return data.split('|')[index];
    }

    function is_LastOne(v, src){
        if(!currentData && v == src[src.length - 1]){
            return "1";
        }
        return "0";
    }

}


