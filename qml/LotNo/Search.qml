import QtQuick 2.0

Rectangle {
    id: form
    //width: parent.width; height: parent.height
    color: "#ece9d8"


    Rectangle{
        width: form.width - 50; height: form.height - 50
        radius: 5
        color: parent.color
        border.color: "grey"
        border.width: 1
        anchors.horizontalCenter: form.horizontalCenter
        anchors.bottom: form.bottom
        anchors.bottomMargin: 35
    }

    Column{
        id: row_text
        spacing: 30
        anchors.top: form.top
        anchors.topMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 50

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

        anchors.top: form.top
        anchors.topMargin: 50
        anchors.left: row_text.right
        anchors.leftMargin: 20

        SingleListView{
            id: lot_no_listview
            flag: "lot_no"
            width: 180; height: form.height - 130
            onSelected: dataFilter.selectItem(flag, value)
        }
        SingleListView{
            id: block_no_listview
            flag: "block_no"
            width: 180; height: form.height - 130
            onSelected: dataFilter.selectItem(flag, value)
        }

        SingleListView{
            id: sn_listview
            flag: "sn"
            width: 180; height: form.height - 130
            onSelected: dataFilter.selectItem(flag, value)
        }

    }

    Rectangle{
        color: parent.color
        width: row_list.width; height: 40
        anchors.top: row_list.bottom
        anchors.left: row_list.left
    }

}
