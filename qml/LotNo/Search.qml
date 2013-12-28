import QtQuick 2.0

Rectangle {
    id: form
    //width: parent.width; height: parent.height
    radius:5

    Rectangle{
        z: 1
        width: form.width; height: 50
        anchors.top: form.top
        anchors.topMargin: 0
    }

    Column{
        id: row_text
        z: 1
        spacing: 40
        anchors.top: form.top
        anchors.topMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 50

        ShadowRectangle {
            id: shadow1
            color: "#434343"
            width: 210; height: 50
            TextBox {
                id: lot_no; flag: 'lot_no'
                width: parent.width; height: parent.height
                focus: true
                onFinished: {
                    dataFilter.searchData(flag, value)
                    block_no.focus = true
                }
            }
        }

        ShadowRectangle {
            color: "#434343"
            width: 210; height: 50
            TextBox {
                id: block_no; flag: 'block_no'
                width: parent.width; height: parent.height
                onFinished: {
                    dataFilter.searchData(flag, value)
                    sn.focus = true
                }
            }
        }

        ShadowRectangle {
            color: "#434343"
            width: 210; height: 50
            TextBox {
                id: sn; flag: 'sn'
                width: parent.width; height: parent.height
                onFinished: dataFilter.searchData(flag, value)
            }
        }
    }

    Connections
    {
        target: dataFilter
        onStringChanged: {
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
        z: 1
        spacing: row_text.spacing

        anchors.top: form.top
        anchors.topMargin: 50
        anchors.left: row_text.right
        anchors.leftMargin: 20

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
