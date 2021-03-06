import QtQuick 1.1
import 'func.js' as Func

Rectangle {
    id:leftMenu
    property variant model;
    signal selected(string value);
    property variant selectedItem;
    property variant currentData;
    border.width: 1
    border.color: "grey"
    property int item_height: 25
    property int page_index: 1;
    property int page_size: 25;


    Row{
        id: title
        z: 1
        width: parent.width; height: item_height

        Rectangle{
            id: title1
            width: parent.width/4; height: parent.height
            color: "darkgrey"
            border.width: 1
            border.color: "grey"
            Text {
                font.pixelSize:18
                font.bold: true
                text: "SMF Lot No."
                color: "#474747"
                anchors.centerIn: parent
            }
        }

        Rectangle{
            id: title2
            width: parent.width / 4; height: parent.height
            color: "darkgrey"
            border.width: 1
            border.color: "grey"
            Text {
                font.pixelSize:18
                font.bold: true
                text: "Block No."
                color: "#474747"
                anchors.centerIn: parent
            }
        }

        Rectangle{
            id: title3
            width: parent.width / 4; height: parent.height
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

        Rectangle{
            id: title5
            width: parent.width / 4 + 30; height: parent.height
            color: "darkgrey"
            border.width: 1
            border.color: "grey"
            Text {
                font.pixelSize:18
                font.bold: true
                text: "录入时间"
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
                property variant text_color: "#474747"
                Row{
                    width: parent.width; height: parent.height
                    Rectangle{
                        width: title1.width; height: parent.height
                        color: "transparent"
                        border.width: 1
                        border.color: "grey"
                        CheckBox{
                            id: cb
                            value: getModelData(modelData, 2)
                            onClicked:{
                                dataFilter.CheckItem(cb.value);
                            }
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        Text {
                            font.pixelSize:18
                            font.bold: true
                            text: getModelData(modelData, 0) //index == 0 ? getModelData(modelData, 0): ""
                            color: list_item.text_color //is_LastOne(modelData, leftMenu.model) == "1" ? "white": "#474747"
                            anchors.centerIn: parent
                        }
                    }
                    Rectangle{
                        width: title2.width; height: parent.height
                        color: "transparent"
                        border.width: 1
                        border.color: "grey"
                        Text {
                            font.pixelSize:18
                            font.bold: true
                            text: getModelData(modelData, 1)
                            color: list_item.text_color //is_LastOne(modelData, leftMenu.model) == "1" ? "white": "#474747"
                            anchors.centerIn: parent
                        }
                    }
                    Rectangle{
                        width: title3.width; height: parent.height
                        color: "transparent"
                        border.width: 1
                        border.color: "grey"
                        Text {
                            font.pixelSize:18
                            font.bold: true
                            text: getModelData(modelData, 2)
                            color: list_item.text_color //is_LastOne(modelData, leftMenu.model) == "1" ? "white": "#474747"
                            anchors.centerIn: parent
                        }
                    }

                    Rectangle{
                        width: title5.width; height: parent.height
                        color: "transparent"
                        border.width: 1
                        border.color: "grey"
                        Text {
                            font.pixelSize:18
                            font.bold: true
                            text: getModelData(modelData, 4).substring(0, 100)
                            color: list_item.text_color //is_LastOne(modelData, leftMenu.model) == "1" ? "white": "#474747"
                            anchors.centerIn: parent
                        }
                    }
                }

     /*           MouseArea{
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
                */
            }

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

    // 滚动条
    Rectangle {
        id: scrollbar
        width: 28
        height: list_view.height
        color: "white"
        border.color: 'darkgrey'
        anchors.left: list_view.right
        anchors.top: list_view.top
        // 按钮
        Rectangle {
            id: button
            x: 0
            y: list_view.visibleArea.yPosition * scrollbar.height
            width: scrollbar.width
            height: list_view.visibleArea.heightRatio * scrollbar.height;
            color: "lightblue"
            // 鼠标区域
            MouseArea {
                id: mouseArea
                anchors.fill: button
                drag.target: button
                drag.axis: Drag.YAxis
                drag.minimumY: 0
                drag.maximumY: scrollbar.height - button.height
                // 拖动
                onMouseYChanged: {
                    list_view.contentY = button.y / scrollbar.height * list_view.contentHeight
                }
            }
        }
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


