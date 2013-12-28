import QtQuick 2.0
import "func.js" as Func

Rectangle {
    id: form
    //width: parent.width; height: parent.height
    color: "transparent"

    Text{
        anchors.horizontalCenter: form.horizontalCenter
        anchors.top: form.top
        anchors.topMargin: 0
        id: label
        font.pixelSize: 25
        color: 'red'
    }

    Rectangle{
        width: row_text.width + 50; height: row_text.height + 25
        radius: 5
        color: parent.color
        border.color: "grey"
        border.width: 1
        anchors.horizontalCenter: row_text.horizontalCenter
        anchors.bottom: row_text.bottom
        anchors.bottomMargin: -10
    }

    Rectangle{
        width: row_list.width + 50; height: row_list.height + 25
        radius: 5
        color: parent.color
        border.color: "grey"
        border.width: 1
        anchors.horizontalCenter: row_list.horizontalCenter
        anchors.bottom: row_list.bottom
        anchors.bottomMargin: -10
    }

    Row{
        id: row_text
        spacing: 50
        anchors.horizontalCenter: form.horizontalCenter
        anchors.top: form.top
        anchors.topMargin: 50

        Column{
            spacing: 10
            Text{
                text: 'lot_no'
                font.pixelSize: 20
                anchors.horizontalCenter: shadow1.horizontalCenter
            }

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
        }
        Column{
            spacing: 10
            Text{
                text: 'block_no'
                font.pixelSize: 20
                anchors.horizontalCenter: shadow2.horizontalCenter
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
        }

        Column{
            spacing: 10
            Text{
                text: 'sn'
                font.pixelSize: 20
                anchors.horizontalCenter: shadow3.horizontalCenter
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
            width: 210; height: form.height - 200
            onSelected: dataFilter.selectItem(flag, value)
        }
        SingleListView{
            id: block_no_listview
            flag: "block_no"
            width: 210; height: form.height - 200
            onSelected: dataFilter.selectItem(flag, value)
        }

        SingleListView{
            id: sn_listview
            flag: "sn"
            width: 210; height: form.height - 200
            onSelected: dataFilter.selectItem(flag, value)
        }

    }

}
