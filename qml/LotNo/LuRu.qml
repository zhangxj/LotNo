import QtQuick 1.1
import "func.js" as Func

Rectangle {
    id: form
    color: "white"

    Text{
        id: label
        z: 1
        anchors.horizontalCenter: form.horizontalCenter
        anchors.top: form.top
        anchors.topMargin: 0
        font.pixelSize: 25
        color: 'red'
    }

    Row{
        id: row_text
        z: 1
        spacing: 50
        anchors.horizontalCenter: form.horizontalCenter
        anchors.top: form.top
        anchors.topMargin: 50
        ShadowRectangle {
            id: shadow1
            color: "#434343"
            width: 210; height: 50
            TextBox {
                id: lot_no; flag: 'lot_no'
                width: parent.width; height: parent.height
                focus: true
                onFinished: {
                    dataFilter.setScan(flag, value)
                    block_no.focus = true
                    lot_no_text.text = 'lot_no: ' + value
                }
            }
        }
        ShadowRectangle {
            id: shadow2
            color: "#434343"
            width: 210; height: 50
            TextBox {
                id: block_no; flag: 'block_no'
                width: parent.width; height: parent.height
                onFinished: {
                    dataFilter.setScan(flag, value)
                    sn.focus = true
                    block_no_text.text = 'block_no: ' + value
                }
            }
        }

        ShadowRectangle {
            id: shadow3
            color: "#434343"
            width: 210; height: 50
            TextBox {
                id: sn; flag: 'sn'
                width: parent.width; height: parent.height
                onFinished: dataFilter.setScan(flag, value)
            }
        }

    }

    Row{
        spacing: 50
        anchors.horizontalCenter: form.horizontalCenter
        anchors.top: row_text.bottom
        anchors.topMargin: 15

        Text{
            id: lot_no_text
            width: 210;
            text: ''
            font.pixelSize: 25
            color: 'red'
        }
        Text{
            id: block_no_text
            width: 210;
            text: ''
            font.pixelSize: 25
            color: 'red'
        }
    }

    Connections
    {
        target: dataFilter
        onStringChanged: {
            label.text = dataFilter.getString()
        }

        onLotNoListChanged:{
            //lot_no_listview.model = dataFilter.getLotNoList()
            //lot_no_listview.currentData = "";
        }

        onBlockNoListChanged:{
            //block_no_listview.model = dataFilter.getBlockNoList()
            //block_no_listview.currentData = "";
        }

        onSnListChanged:{
            //sn_listview.model = dataFilter.getSnList()
            //sn_listview.currentData = "";
        }
    }


    Image {
        id: pic
        width: parent.width - 40
        anchors.top: row_text.bottom
        anchors.topMargin: 60
        anchors.horizontalCenter: parent.horizontalCenter
        source:Func.get_image_path("6ADKN.jpg")
    }


    Grid {
        z: 1
        columns: 3
        spacing: 200
        anchors.top: pic.top
        anchors.topMargin: 80
        anchors.left: pic.left
        anchors.leftMargin: 100
        Rectangle { color: "red"; width: 40; height: 35 }
        Rectangle { color: "green"; width: 40; height: 35 }
        Rectangle { color: "blue"; width: 40; height: 35 }
        Rectangle { color: "blue"; width: 40; height: 35 }
        Rectangle { color: "blue"; width: 40; height: 35 }
        Rectangle { color: "blue"; width: 40; height: 35 }
    }

}
