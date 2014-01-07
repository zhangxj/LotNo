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

    Connections
    {
        target: dataFilter
        onStringChanged: {
            label.text = dataFilter.getString()
        }

        onLotNoListChanged:{
            lot_no_listview.model = dataFilter.getLotNoList()
            lot_no_listview.currentData = "";
        }

        onBlockNoListChanged:{
            block_no_listview.model = dataFilter.getBlockNoList()
            block_no_listview.currentData = "";
        }

        onSnListChanged:{
            sn_listview.model = dataFilter.getSnList()
            sn_listview.currentData = "";
        }
    }
    Row{
        id: row_list
        spacing: row_text.spacing

        anchors.top: row_text.bottom
        anchors.topMargin: 30
        anchors.left: row_text.left

        SingleListView{
            id: lot_no_listview
            flag: "lot_no"
            width: 210; height: form.height - 190
            onSelected: dataFilter.selectItem(flag, value)
        }
        SingleListView{
            id: block_no_listview
            flag: "block_no"
            width: 210; height: form.height - 190
            onSelected: dataFilter.selectItem(flag, value)
        }

        SingleListView{
            id: sn_listview
            flag: "sn"
            width: 210; height: form.height - 190
            onSelected: dataFilter.selectItem(flag, value)
        }
    }

    Rectangle{
        color: "white"
        width: row_list.width
        anchors.top: parent.top
        anchors.bottom: row_text.top
        anchors.left: row_list.left
    }
    Rectangle{
        color: "white"
        width: row_list.width
        anchors.top: row_text.bottom
        anchors.bottom: row_list.top
        anchors.left: row_list.left
    }
    Rectangle{
        color: "white"
        width: row_list.width; height: 40
        anchors.top: row_list.bottom
        anchors.left: row_list.left
    }
}
