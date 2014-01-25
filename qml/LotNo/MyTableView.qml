import QtQuick 1.1
import 'func.js' as Func

Rectangle {
    id: tableView
    property variant model;
    signal selected(string value);
    property variant selectedItem;
    property variant currentData;
    border.width: 1
    border.color: "grey"
    property int item_height: 25

    Row{
        id: title
        z: 1
        width: parent.width; height: item_height

        Rectangle{
            id: title1
            width: parent.width; height: parent.height
            color: "darkgrey"
            border.width: 1
            border.color: "grey"
            Text {
                font.pixelSize:18
                font.bold: true
                text: "Sample SN"
                color: "#474747"
                anchors.centerIn: parent
            }
        }
    }

    Component{
        id: listview_component
        Column{
            Rectangle{
                id: list_item
                state: ""
                height: item_height; width:tableView.width
                color: "transparent" //is_LastOne(modelData, tableView.model) == "1" ? "#0527af": "transparent"
                property variant text_color: "#474747"
                Row{
                    width: parent.width; height: parent.height
                    Rectangle{
                        width: title1.width; height: parent.height
                        color: "transparent"
                        border.width: 1
                        border.color: "grey"
                        Text {
                            font.pixelSize:18
                            font.bold: true
                            text: getModelData(modelData, 0)
                            color: list_item.text_color //is_LastOne(modelData, tableView.model) == "1" ? "white": "#474747"
                            anchors.centerIn: parent
                        }
                    }
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        select_item(list_item)
                    }
                }

                states: [
                    State{
                        name:"selected"
                        PropertyChanges{
                            target:list_item;
                            color: "#0527af"
                            text_color: "white"
                            width:tableView.width + 1;
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
        width: tableView.width
        anchors.top: title.bottom
        anchors.bottom: parent.bottom
        model: tableView.model
        delegate: listview_component
        //onCurrentIndexChanged: positionViewAtEnd()
    }


    function getModelData(data, index){
        return data.split('|')[index];
    }

    function select_item(item){
        if(selectedItem){
            selectedItem.state = "";
        }

        item.state = "selected";
        selectedItem = item;
    }

    function is_LastOne(v, src){
        if(!currentData && v == src[src.length - 1]){
            return "1";
        }
        return "0";
    }

}


