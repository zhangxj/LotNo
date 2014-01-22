import QtQuick 1.1
import "func.js" as Func

Rectangle {
    id: form
    color: "transparent"

    Text{
        id: label
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
                bk_text: 'SMF Lot No.'
                onFinished: {
                    dataFilter.setScan(flag, value, "")
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
                bk_text: 'Block No.'
                width: parent.width; height: parent.height
                onFinished: {
                    dataFilter.setScan(flag, value, "")
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
                bk_text: 'Sample SN'
                width: parent.width; height: parent.height
                onFinished: {
                    if(dataFilter.getSnList().length < 12|| (value == "rescan" || value == "RESCAN"))
                        dataFilter.setScan(flag, value, dataFilter.getSnList().length + 1);
                }
            }
        }

    }

    Row{
        z: 1
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

        onSnListChanged:{
            sn_listview.model = dataFilter.getSnList()
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
                pos7.color = 'transparent'; pos7.text = "";
                pos8.color = 'transparent'; pos8.text = "";
                pos9.color = 'transparent'; pos9.text = "";
                pos10.color = 'transparent'; pos10.text = "";
                pos11.color = 'transparent'; pos11.text = "";
                pos12.color = 'transparent'; pos12.text = "";
            }
            if(snList.length == 1){pos1.color = color; pos1.text = snList[0] == "NOSAMPLE" ? "NOSAMPLE":"1";}
            if(snList.length == 2){pos2.color = color; pos2.text = snList[1] == "NOSAMPLE" ? "NOSAMPLE":"2";}
            if(snList.length == 3){pos3.color = color; pos3.text = snList[2] == "NOSAMPLE" ? "NOSAMPLE":"3";}
            if(snList.length == 4){pos4.color = color; pos4.text = snList[3] == "NOSAMPLE" ? "NOSAMPLE":"4";}
            if(snList.length == 5){pos5.color = color; pos5.text = snList[4] == "NOSAMPLE" ? "NOSAMPLE":"5";}
            if(snList.length == 6){pos6.color = color; pos6.text = snList[5] == "NOSAMPLE" ? "NOSAMPLE":"6";}
            if(snList.length == 7){pos7.color = color; pos7.text = snList[6] == "NOSAMPLE" ? "NOSAMPLE":"7";}
            if(snList.length == 8){pos8.color = color; pos8.text = snList[7] == "NOSAMPLE" ? "NOSAMPLE":"8";}
            if(snList.length == 9){pos9.color = color; pos9.text = snList[8] == "NOSAMPLE" ? "NOSAMPLE":"9";}
            if(snList.length == 10){pos10.color = color; pos10.text = snList[9] == "NOSAMPLE" ? "NOSAMPLE":"10";}
            if(snList.length == 11){pos11.color = color; pos11.text = snList[10] == "NOSAMPLE" ? "NOSAMPLE":"11";}
            if(snList.length == 12){pos12.color = color; pos12.text = snList[11] == "NOSAMPLE" ? "NOSAMPLE":"12";}
        }
    }

    SampleSNListView{
        id: sn_listview
        width: 180; height: pic.height / 3
        anchors.left: pic.right
        anchors.top: pic.top
    }

    Image {
        id: pic
        width: parent.width - 230
        anchors.top: row_text.bottom
        anchors.topMargin: 40
        anchors.left: parent.left
        source:Func.get_image_path("6ADKN.png")
    }


    Row{
        spacing: 150
        anchors.top: pic.top
        anchors.topMargin: 80
        anchors.left: pic.left
        anchors.leftMargin: 60
        Rectangle {
            id: pos1
            property variant text: ''
            color:'green'; width: 35; height: 35
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos3
            property variant text: ''
            color:'green'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos5
            property variant text: ''
            color:'green'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
    }

    Row{
        spacing: 150
        anchors.top: pic.top
        anchors.topMargin: 120
        anchors.left: pic.left
        anchors.leftMargin: 100
        Rectangle {
            id: pos2
            property variant text: ''
            color:'green'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos4
            property variant text: ''
            color:'green'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos6
            property variant text: ''
            color:'green'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
    }

    Row{
        spacing: 150
        anchors.top: pic.top
        anchors.topMargin: 260
        anchors.left: pic.left
        anchors.leftMargin: 60
        Rectangle {
            id: pos12
            property variant text: ''
            color:'green'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos10
            property variant text: ''
            color:'green'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos8
            property variant text: ''
            color:'green'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
    }

    Row{
        spacing: 150
        anchors.top: pic.top
        anchors.topMargin: 300
        anchors.left: pic.left
        anchors.leftMargin: 100
        Rectangle {
            id: pos11
            property variant text: ''
            color:'green'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize:16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos9
            property variant text: ''
            color:'green'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos7
            property variant text: ''
            color:'green'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
    }

}
