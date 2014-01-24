import QtQuick 1.1
import "func.js" as Func

Rectangle {
    id: form
    color: "transparent"

    Control_Top1{
        id: top_rec
        width: parent.width + 1; height: 150
        z: 1
        color: "white"
        max_luru: 6
    }

    Image {
        id: pic
        width: parent.width - 300
        anchors.top: top_rec.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        source:Func.get_image_path("5FDKN.png")
    }

    SampleSNListView{
        id: sn_listview
        item_height: 40
        width: 230; height: item_height * 7
        anchors.left: pic.right
        anchors.top: pic.top
    }

    Rectangle{
        z: 1
        color: "white"
        width: sn_listview.width + 1;
        anchors.top: sn_listview.bottom
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        anchors.left: sn_listview.left
    }

    Row{
        id: row1
        spacing: pic.width / 120 * 35   //  1/3  40 倍
        anchors.top: pic.top
        anchors.topMargin: pic.height / 10
        anchors.left: pic.left
        anchors.leftMargin: pic.width / 5
        Rectangle {
            id: pos1
            property variant text: ''
            color:'transparent'; width: 35; height: 35
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
        Rectangle {
            id: pos2
            property variant text: ''
            color:'transparent'; width: 35; height: 35
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
        Rectangle {
            id: pos3
            property variant text: ''
            color:'transparent'; width: 35; height: 35
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }


    }

    Row{
        spacing: row1.spacing
        anchors.top: pic.top
        anchors.topMargin: pic.height / 10 * 8
        anchors.left: pic.left
        anchors.leftMargin: pic.width / 5
        Rectangle {
            id: pos6
            property variant text: ''
            color:'transparent'; width: 35; height: 35
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
        Rectangle {
            id: pos5
            property variant text: ''
            color:'transparent'; width: 35; height: 35
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
        Rectangle {
            id: pos4
            property variant text: ''
            color:'transparent'; width: 35; height: 35
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
    }


}
