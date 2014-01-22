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

    Component{
        id: plugin_sub_item
        Column{
            Rectangle{
                id: list_item
                state: ""
                height: item_height; width:leftMenu.width
                color: is_LastOne(modelData, leftMenu.model) == "1" ? "#0527af": "transparent"

                Rectangle{
                    width: parent.width / 3 * 2; height: parent.height
                    Text {
                        id: id_text
                        font.pixelSize:18
                        font.bold: true
                        text: getModelData(modelData, 0)
                        color: is_LastOne(modelData, leftMenu.model) == "1" ? "white": "#474747"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
                Rectangle{
                    width: parent.width / 3; height: parent.height
                    Text {
                        id: id_location
                        font.pixelSize:18
                        font.bold: true
                        text: getModelData(modelData, 1)
                        color: is_LastOne(modelData, leftMenu.model) == "1" ? "white": "#474747"
                        anchors.centerIn: parent
                    }
                }

                Image{
                    source: Func.get_image_path("dotted_line2.png");
                    fillMode:Image.TileHorizontally;
                    height: 2
                    width:leftMenu.width - 2;
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
        }
    }

    ListView{
        id: list_view
        width: leftMenu.width
        anchors.top: parent.top
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


