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
                onFinished: {
                    if(dataFilter.getSnList().length < 6 || (value == "rescan" || value == "RESCAN"))
                        dataFilter.setScan(flag, value);
                }
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
            var color = 'green'
            var snList = dataFilter.getSnList();
            if(snList.length == 0){
                pos1.color = 'transparent'; pos1.text = "";
                pos2.color = 'transparent'; pos2.text = "";
                pos3.color = 'transparent'; pos3.text = "";
                pos4.color = 'transparent'; pos4.text = "";
                pos5.color = 'transparent'; pos5.text = "";
                pos6.color = 'transparent'; pos6.text = "";
            }
            if(snList.length == 1){pos1.color = color; pos1.text = snList[0];}
            if(snList.length == 2){pos2.color = color; pos2.text = snList[1];}
            if(snList.length == 3){pos3.color = color; pos3.text = snList[2];}
            if(snList.length == 4){pos4.color = color; pos4.text = snList[3];}
            if(snList.length == 5){pos5.color = color; pos5.text = snList[4];}
            if(snList.length == 6){pos6.color = color; pos6.text = snList[5];}
        }
    }


    Image {
        id: pic
        width: parent.width - 40
        anchors.top: row_text.bottom
        anchors.topMargin: 60
        anchors.horizontalCenter: parent.horizontalCenter
        source:Func.get_image_path("5FDKN.jpg")
    }



    Row{
        spacing: 100
        anchors.top: pic.top
        anchors.topMargin: 20
        anchors.left: pic.left
        anchors.leftMargin: 80
        Rectangle {
            id: pos1
            property variant text: ''
            color:'transparent'; width: 150; height: 35
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
        Rectangle {
            id: pos2
            property variant text: ''
            color:'transparent'; width: 150; height: 35
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
        Rectangle {
            id: pos3
            property variant text: ''
            color:'transparent'; width: 150; height: 35
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }


    }

    Row{
        spacing: 100
        anchors.top: pic.top
        anchors.topMargin: 200
        anchors.left: pic.left
        anchors.leftMargin: 90
        Rectangle {
            id: pos6
            property variant text: ''
            color:'transparent'; width: 150; height: 35
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
        Rectangle {
            id: pos5
            property variant text: ''
            color:'transparent'; width: 150; height: 35
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
        Rectangle {
            id: pos4
            property variant text: ''
            color:'transparent'; width: 150; height: 35
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
    }
}
