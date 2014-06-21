import QtQuick 1.1
import "func.js" as Func

Rectangle{
    id: form

    Rectangle {
        id: top_rec
        z: 1
        width: parent.width; height: 130
        color: "white"
        anchors.top: parent.top
        Column{
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10

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
                            dataFilter.searchLotNoBlockNo(flag, value)
                            block_no.focus = true
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
                            dataFilter.searchLotNoBlockNo(flag, value);
                            block_no.text = "";
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

    Connections
    {
        target: dataFilter
        onStringChanged: {
            start_date.text = dataFilter.getDate('start')
            end_date.text = dataFilter.getDate('end')
        }

        onStringListChanged:{
            sn_listview.model = dataFilter.getStringList();
        }
    }


    ListView_record{
        id: sn_listview
        width: parent.width / 3 * 2;
        anchors.top: top_rec.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 41
        anchors.horizontalCenter: parent.horizontalCenter
        item_height: 40
    }

    Rectangle{
        z: 1
        color: "white"
        width: sn_listview.width + 1 + 30;
        anchors.top: sn_listview.bottom
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        anchors.left: sn_listview.left
    }
}
