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
        sn_flag: 1
        max_luru: 1000000
    }

    MyTableView{
        id: sn_listview
        width: parent.width / 4;
        anchors.top: top_rec.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 41
        anchors.horizontalCenter: parent.horizontalCenter
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
}
