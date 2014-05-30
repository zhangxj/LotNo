import QtQuick 1.1

Rectangle{
    id: top_rec
    color: "white"
    property bool pos_info: true
    property int max_luru: 12
    property int sn_flag: 0
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
                    dataFilter.clearData();
                    dataFilter.setMaxLuRu(max_luru);
                    if(dataFilter.setScan(flag, value, "", sn_flag)){
                        block_no.text = "";
                        block_no.focus = true
                        lot_no_text.text = bk_text + ":" + value
                        block_no_text.text = "";
                    }else{
                        lot_no.text = "";
                    }
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
                    dataFilter.clearBlockNo();
                    if(dataFilter.setScan(flag, value, "", sn_flag)){
                        sn.focus = true
                        block_no_text.text = bk_text + ":" + value
                    }else{
                        block_no.text = "";
                    }
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
                    if(value == "newblock" || value == "NEWBLOCK"){
                        block_no.text = "";
                        block_no.focus = true
                        block_no_text.text = "";
                        dataFilter.setScan(flag, value, dataFilter.getStringList().length + 1, sn_flag);
                    }else if(dataFilter.getStringList().length < max_luru ||
                            (value == "rescan" || value == "RESCAN") ||
                            (value == "delete" || value == "DELETE")){
                        dataFilter.setScan(flag, value, dataFilter.getStringList().length + 1, sn_flag);
                        if(dataFilter.getStringList().length == max_luru){
                            dataFilter.SNLuRuDone();
                            block_no.text = "";
                            block_no_text.text = "";
                            lot_no.text = "";
                            lot_no_text.text = "";
                            lot_no.focus = true;
                        }
                    }else{
                        label.text = "最大录入数量" + max_luru + "个";
                    }

                    sn.text = ''
                }
            }
        }
    }

    Row{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: row_text.bottom
        anchors.topMargin: 10
        Rectangle{
            width: form.width/2; height: 40
            Text{
                id: lot_no_text
                font.pixelSize: 25; font.bold: true
                color: "#0527af"
                anchors.centerIn: parent
            }
        }
        Rectangle{
            width: form.width/2; height: 40
            Text{
                id: block_no_text
                font.pixelSize: 25; font.bold: true
                color: "#0527af"
                anchors.centerIn: parent
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
            var color = 'green'
            var snList = dataFilter.getStringList();

            if(sn_flag == 0){
                pos1.color = 'transparent'; pos1.text = "";
                pos2.color = 'transparent'; pos2.text = "";
                pos3.color = 'transparent'; pos3.text = "";
                pos4.color = 'transparent'; pos4.text = "";
                pos5.color = 'transparent'; pos5.text = "";
                pos6.color = 'transparent'; pos6.text = "";
                if(max_luru == 12){
                    pos7.color = 'transparent'; pos7.text = "";
                    pos8.color = 'transparent'; pos8.text = "";
                    pos9.color = 'transparent'; pos9.text = "";
                    pos10.color = 'transparent'; pos10.text = "";
                    pos11.color = 'transparent'; pos11.text = "";
                    pos12.color = 'transparent'; pos12.text = "";
                }

                var nosample = "?";
                if(snList.length >= 1){pos1.color = color; pos1.text = snList[0].split("|")[0] == "NOSAMPLE" ? nosample:"1";}
                if(snList.length >= 2){pos2.color = color; pos2.text = snList[1].split("|")[0] == "NOSAMPLE" ? nosample:"2";}
                if(snList.length >= 3){pos3.color = color; pos3.text = snList[2].split("|")[0] == "NOSAMPLE" ? nosample:"3";}
                if(snList.length >= 4){pos4.color = color; pos4.text = snList[3].split("|")[0] == "NOSAMPLE" ? nosample:"4";}
                if(snList.length >= 5){pos5.color = color; pos5.text = snList[4].split("|")[0] == "NOSAMPLE" ? nosample:"5";}
                if(snList.length >= 6){pos6.color = color; pos6.text = snList[5].split("|")[0] == "NOSAMPLE" ? nosample:"6";}
                if(max_luru == 12){
                    if(snList.length >= 7){pos7.color = color; pos7.text = snList[6].split("|")[0] == "NOSAMPLE" ? nosample:"7";}
                    if(snList.length >= 8){pos8.color = color; pos8.text = snList[7].split("|")[0] == "NOSAMPLE" ? nosample:"8";}
                    if(snList.length >= 9){pos9.color = color; pos9.text = snList[8].split("|")[0] == "NOSAMPLE" ? nosample:"9";}
                    if(snList.length >= 10){pos10.color = color; pos10.text = snList[9].split("|")[0] == "NOSAMPLE" ? nosample:"10";}
                    if(snList.length >= 11){pos11.color = color; pos11.text = snList[10].split("|")[0] == "NOSAMPLE" ? nosample:"11";}
                    if(snList.length >= 12){pos12.color = color; pos12.text = snList[11].split("|")[0] == "NOSAMPLE" ? nosample:"12";}
                }
            }
        }
    }
}
