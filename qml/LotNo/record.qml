import QtQuick 1.1
import "func.js" as Func

Rectangle{
    id: form

    Rectangle {
        id: top_rec
        z: 1
        width: parent.width; height: 150
        color: "white"
        anchors.top: parent.top
        Text{
            id: label
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 5
            font.pixelSize: 25
            font.bold: true
            color: 'red'
        }

        Row{
            id: row_text
            spacing: 50
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 50
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
                        if(dataFilter.record_LotNoBlockNo(flag, value))
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
                        dataFilter.record_LotNoBlockNo(flag, value);
                        block_no.text = "";
                    }
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
        width: sn_listview.width + 1;
        anchors.top: sn_listview.bottom
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        anchors.left: sn_listview.left
    }
}
