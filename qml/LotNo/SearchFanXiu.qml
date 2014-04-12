import QtQuick 1.1

Rectangle {
    id: form

    Rectangle{
        id: top_rec
        width: parent.width + 1; height: 120
        z: 1
        color: "white"
        Column{
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 5
            Row{
                id: row_text
                spacing: 50
                anchors.horizontalCenter: parent.horizontalCenter
                ShadowRectangle {
                    id: shadow1
                    color: "#434343"
                    width: 300; height: 50
                    TextBox {
                        id: lot_no; flag: 'lot_no'
                        width: parent.width; height: parent.height
                        focus: true
                        bk_text: 'SMF Lot No.'
                        onFinished: {
                            dataFilter.searchData(flag, value, 1)
                            block_no.focus = true
                            block_no.text = '';
                        }
                    }
                }
                ShadowRectangle {
                    id: shadow2
                    color: "#434343"
                    width: 300; height: 50
                    TextBox {
                        id: block_no; flag: 'block_no'
                        bk_text: 'Block No.'
                        width: parent.width; height: parent.height
                        onFinished: {
                            dataFilter.searchData(flag, value, 1)
                            sn.focus = true
                        }
                    }
                }

                ShadowRectangle {
                    id: shadow3
                    color: "#434343"
                    width: 300; height: 50
                    TextBox {
                        id: sn; flag: 'sn'
                        bk_text: 'Sample SN'
                        width: parent.width; height: parent.height
                        onFinished: {
                            onFinished: {
                                dataFilter.searchData(flag, value, 1);
                            }
                            sn.text = '';
                        }
                    }
                }
            }

            Row{
                id: row_date
                spacing: 50
                anchors.horizontalCenter: parent.horizontalCenter
                Button{
                    id: start_date
                    text: dataFilter.getDate('start')
                    text_color: "black"
                    width: 300; height: 50
                    color_start: 'white'
                    color_stop: 'white'
                    border.color: "darkgrey"
                    onClicked: {
                        dataFilter.calendarShow('start', start_date.mapToItem(form.parent, 0, 0).x + start_date.width / 2,
                                                start_date.mapToItem(form.parent, 0, 0).y + start_date.height * 2)
                    }
                }

                Button{
                    id: end_date
                    text: dataFilter.getDate('end')
                    text_color: "black"
                    width: 300; height: 50
                    color_start: 'white'
                    color_stop: 'white'
                    border.color: "darkgrey"
                    onClicked: {
                        dataFilter.calendarShow('end', end_date.mapToItem(form.parent, 0, 0).x + end_date.width / 2,
                                                end_date.mapToItem(form.parent, 0, 0).y + end_date.height * 2)
                    }
                }
                Button{
                    id: searchbydate
                    width: 200; height: 50
                    text:'按日期查询'
                    onClicked: {
                        dataFilter.searchDataByDate();
                    }
                }
            }


        }


    }

    ListView_FanXiu{
        id: sn_listview
        width: parent.width / 10 * 9
        anchors.top: top_rec.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 25
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle{
        z: 1
        color: "white"
        width: sn_listview.width + 1;
        anchors.top: sn_listview.bottom
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -2
        anchors.left: sn_listview.left
    }

    Connections
    {
        target: dataFilter

        onStringChanged: {
            start_date.text = dataFilter.getDate('start')
            end_date.text = dataFilter.getDate('end')
        }

        onStringListChanged:{
            sn_listview.model = dataFilter.getStringList()
        }
    }


}
