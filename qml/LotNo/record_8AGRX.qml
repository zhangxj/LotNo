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
        max_luru: 12
        product: "8AGRX"
    }

    Rectangle {
        id: pic
        width: parent.width - 300
        anchors.top: top_rec.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.left: parent.left
        color: "#554769"


    }

    SampleSNListView{
        id: sn_listview
        width: 230; height: item_height * 13
        anchors.left: pic.right
        anchors.top: pic.top
        item_height: 40
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
        spacing: pic.width / 360 * 35  // 1/3  放大 40倍细化位置
        anchors.top: pic.top
        anchors.topMargin: pic.height / 160 * 37   // 1/4 放大 40倍细化位置
        anchors.left: pic.left
        anchors.leftMargin: pic.width / 280 * 15   // 1/7 放大 40倍细化位置
        Rectangle {
            id: pos1
            property variant text: ''
            color:'transparent'; width: 55; height: 55
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
        Rectangle {
            id: pos2
            property variant text: ''
            color:'transparent'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos3
            property variant text: ''
            color:'transparent'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
        Rectangle {
            id: pos4
            property variant text: ''
            color:'transparent'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos5
            property variant text: ''
            color:'transparent'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
        Rectangle {
            id: pos6
            property variant text: ''
            color:'transparent'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
    }


    Row{
        spacing: row1.spacing
        anchors.top: pic.top
        anchors.topMargin: pic.height / 160 * 110   // 3/4 放大 40倍细化位置
        anchors.left: row1.left
        Rectangle {
            id: pos12
            property variant text: ''
            color:'transparent'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos11
            property variant text: ''
            color:'transparent'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize:16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos10
            property variant text: ''
            color:'transparent'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos9
            property variant text: ''
            color:'transparent'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos8
            property variant text: ''
            color:'transparent'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }

        Rectangle {
            id: pos7
            property variant text: ''
            color:'transparent'; width: pos1.width; height: pos1.height
            Text{ text: parent.text; anchors.centerIn: parent; font.pixelSize: 16; font.bold: true; color: 'black'}
        }
    }

    Row{
        spacing: row1.spacing
        anchors.top: pic.top
        anchors.topMargin: pic.height / 160 * 120   // 3/4 放大 40倍细化位置
        anchors.left: pic.left
        anchors.leftMargin: pic.width / 240 * 39   // 1/6 放大 40倍细化位置

    }

}
