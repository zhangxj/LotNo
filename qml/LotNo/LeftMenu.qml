import QtQuick 1.1
import "func.js" as Func

Rectangle {
    id:leftMenu
    property variant model;
    signal selected(string value);
    property variant selectedItem;
    property variant selectedSubItem;
    border.color:"#d5d5d5";
    border.width:1;
    ListModel{
        id: sub_list_model
    }
    Image {
        anchors.fill:parent;
        source:Func.get_image_path("conter_left.png");
        fillMode:Image.TileVertically;
    }


    Column{
        spacing: 0
        Repeater{
            model: leftMenu.model
            Column{
                Rectangle{
                    id:item;
                    height:40
                    color:"transparent";
                    state: ""//index == 1 && (selectedItem = item)? "selected":""
                    width: leftMenu.width

                    Image {
                        x:10
                        id:arrow;
                        anchors.verticalCenter:parent.verticalCenter
                        source: Func.get_image_path("gray_dott.png")
                    }

                    Text {
                        id:mText;
                        x:25
                        font.pixelSize:12
                        font.bold:true
                        anchors.verticalCenter:parent.verticalCenter
                        text:modelData.value
                    }

                    MouseArea {
                        id:buttonMouseArea;
                        anchors.fill:parent

                        onClicked: {
                            select_item(item, "selected");
                            selected(modelData.id);
                        }
                    }

                    states:[
                        State {
                            name:"selected";
                            PropertyChanges {
                                target:arrow;
                                source:Func.get_image_path("blue_dott.png")
                            }
                            PropertyChanges {
                                target:item;
                                color:"white"
                                width:leftMenu.width + 1;
                            }
                        },
                        State{
                            name:"subselected";
                            PropertyChanges {
                                target:arrow;
                                source:Func.get_image_path("blue_dott.png")
                            }
                        }

                    ]
                }


                Repeater{
                    model: modelData.items
                    Rectangle{
                        id:subItem
                        width:leftMenu.width;
                        height:40;
                        color:"transparent";
                        property variant text_color: "#474747"
                        state: modelData.checked == '1' && (select_item(item, "subselected") && select_subitem(subItem))? "selected":""
                        Text{
                            x:25
                            font.pixelSize:12
                            color: text_color
                            text:modelData.value
                            anchors.verticalCenter:parent.verticalCenter
                        }
                        MouseArea {
                            id:subClick; anchors.fill:parent
                            hoverEnabled: true
                            onClicked:{
                                if(dataFilter.ChangeProductItem(modelData.id)){
                                    select_item(item, "subselected")
                                    select_subitem(subItem)
                                    selected(modelData.id);
                                }
                            }
                        }

                        states: [
                            State{
                                name:"selected"
                                PropertyChanges{
                                    target:subItem;
                                    color: "#0527af"
                                    text_color: "white"
                                    width:leftMenu.width + 1;
                                }
                            },
                            State{
                                name:"entered"
                                PropertyChanges {
                                    target: subItem;
                                    color:"#f3f3f3"
                                }
                            }

                        ]
                        Image{
                            source:Func.get_image_path("dotted_line2.png");
                            fillMode:Image.TileHorizontally;
                            width:leftMenu.width;
                        }
                    }
                }//sub_repeater
                Image{
                    source:Func.get_image_path("dotted_line2.png");
                    fillMode:Image.TileHorizontally;
                    width:leftMenu.width;
                }
            }

        }
    }



    function get_list(src, dst){
        if(src === undefined){return dst;}
        var my_app = src[1].items
        for(var i =0; i < my_app.length; i++){
            dst.append({"sub_value": my_app[i].id, "sub_text": my_app[i].value})
        }
        return dst
    }

    function select_item(item, state){
        if(selectedItem && selectedItem != item){
            selectedItem.state = ""
        }
        selectedItem = item
        item.state = state

        if(selectedSubItem) {
            selectedSubItem.state = "";
        }
        return true;
    }

    function select_subitem(item){
        if(selectedSubItem && selectedSubItem != item){
            selectedSubItem.state = ""
        }
        item.state = "selected"
        selectedSubItem = item
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
