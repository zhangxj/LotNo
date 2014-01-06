import QtQuick 1.1

Rectangle {
    id: form

    Rectangle{
        z: 1
        color: "white"
        width: row_list.width; height: 40
        anchors.top: parent.top
        anchors.bottom: row_list.top
        anchors.left: row_list.left
    }

    Rectangle{
        z: 1
        color: "white"
        width: row_list.width; height: 40
        anchors.top: row_list.bottom
        anchors.left: row_list.left
    }

    Column{
        id: row_text
        spacing: 30
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 10

        Row{
            spacing: 10
            Text{
                text: ' lot_no :'
                font.pixelSize: 20
                anchors.verticalCenter: shadow1.verticalCenter
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
                        dataFilter.searchData(flag, value)
                        block_no.focus = true
                    }
                }
            }
        }

        Row{
            spacing: 10
            Text{
                text: 'block_no:'
                font.pixelSize: 20
                anchors.verticalCenter: shadow2.verticalCenter
            }


            ShadowRectangle {
                id: shadow2
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
        }

        Row{
            spacing: 10
            Text{
                text: '   sn:   '
                font.pixelSize: 20
                anchors.verticalCenter: shadow3.verticalCenter
            }

            ShadowRectangle {
                id: shadow3
                color: "#434343"
                width: 210; height: 50
                TextBox {
                    id: sn; flag: 'sn'
                    width: parent.width; height: parent.height
                    onFinished: dataFilter.searchData(flag, value)
                }
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
        spacing: row_text.spacing

        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: row_text.right
        anchors.leftMargin: 20

        Column{
            id: column
            spacing: 10
            SingleListView{
                id: lot_no_listview
                flag: "lot_no"
                width: 180; height: 80
                onSelected: dataFilter.selectItem(flag, value)
            }
            SingleListView{
                id: block_no_listview
                flag: "block_no"
                width: 180; height: form.height - 110 - lot_no_listview.height - column.spacing
                onSelected: dataFilter.selectItem(flag, value)
            }
        }

        SingleListView{
            id: sn_listview
            flag: "sn"
            width: 180; height: form.height - 110
            onSelected: dataFilter.selectItem(flag, value)
        }
    }

}
