import QtQuick 1.1

Rectangle{
    id: top_rec
    color: "white"
    property bool pos_info: true
    property int max_luru: 12
    property int sn_flag: 0
    property string product: "6ADKN"
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
                    if(dataFilter.setScan(flag, value, "", sn_flag, product)){
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
                    if(dataFilter.setScan(flag, value, "", sn_flag, product)){
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
                        dataFilter.setScan(flag, value, dataFilter.getStringList().length + 1, sn_flag, product);
                    }else if(dataFilter.getStringList().length < max_luru ||
                            (value == "rescan" || value == "RESCAN") ||
                            (value == "delete" || value == "DELETE")){
                        dataFilter.setScan(flag, value, dataFilter.getStringList().length + 1, sn_flag, product);
                        if(dataFilter.getStringList().length == max_luru){
                            dataFilter.SNLuRuDone();
                            block_no.text = "";
                            block_no_text.text = "";
                            if(dataFilter.isLast_BlockNo()){
                                lot_no.text = "";
                                lot_no_text.text = "";
                                lot_no.focus = true;
                            }else{
                                block_no.focus = true;
                            }
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
            var bad_color = 'red'
            var snList = dataFilter.getStringList();

            if(sn_flag == 0){
                pos1.color = 'transparent'; pos1.text = "";
                pos2.color = 'transparent'; pos2.text = "";
                pos3.color = 'transparent'; pos3.text = "";
                pos4.color = 'transparent'; pos4.text = "";
                pos5.color = 'transparent'; pos5.text = "";
                pos6.color = 'transparent'; pos6.text = "";
                if(max_luru >= 12){
                    pos7.color = 'transparent'; pos7.text = "";
                    pos8.color = 'transparent'; pos8.text = "";
                    pos9.color = 'transparent'; pos9.text = "";
                    pos10.color = 'transparent'; pos10.text = "";
                    pos11.color = 'transparent'; pos11.text = "";
                    pos12.color = 'transparent'; pos12.text = "";
                }

                if(max_luru >=16){
                    pos13.color = 'transparent'; pos13.text = "";
                    pos14.color = 'transparent'; pos14.text = "";
                    pos15.color = 'transparent'; pos15.text = "";
                    pos16.color = 'transparent'; pos16.text = "";
                }

                var nosample = "?";
                if(snList.length >= 1){var dd =snList[0].split("|")[0];
                    pos1.color = color;
                    pos1.text = 1;
                    if(dd == "NOSAMPLE"){
                        pos1.text = nosample;
                    }else if(dd == "Bad"){
                        pos1.color = bad_color;
                    }
                }
                if(snList.length >= 2){var dd =snList[1].split("|")[0];
                    console.log(dd);
                    pos2.color = color;
                    pos2.text = 2;
                    if(dd == "NOSAMPLE"){
                        pos2.text = nosample;
                    }else if(dd == "Bad"){
                        pos2.color = bad_color;
                    }
                }
                if(snList.length >= 3){var dd =snList[2].split("|")[0];
                    console.log(dd);
                    pos3.color = color;
                    pos3.text = 3;
                    if(dd == "NOSAMPLE"){
                        pos3.text = nosample;
                    }else if(dd == "Bad"){
                        pos3.color = bad_color;
                    }
                }

                if(snList.length >= 4){var dd =snList[3].split("|")[0];
                    pos4.color = color;
                    pos4.text = 4;
                    if(dd == "NOSAMPLE"){
                        pos4.text = nosample;
                    }else if(dd == "Bad"){
                        pos4.color = bad_color;
                    }
                }
                if(snList.length >= 5){var dd =snList[4].split("|")[0];
                    pos5.color = color;
                    pos5.text = 5;
                    if(dd == "NOSAMPLE"){
                        pos5.text = nosample;
                    }else if(dd == "Bad"){
                        pos5.color = bad_color;
                    }
                }
                if(snList.length >= 6){var dd =snList[5].split("|")[0];
                    pos6.color = color;
                    pos6.text = 6;
                    if(dd == "NOSAMPLE"){
                        pos6.text = nosample;
                    }else if(dd == "Bad"){
                        pos6.color = bad_color;
                    }
                }
                if(max_luru >= 12){
                    if(snList.length >= 7){var dd =snList[6].split("|")[0];
                        pos7.color = color;
                        pos7.text = 7;
                        if(dd == "NOSAMPLE"){
                            pos7.text = nosample;
                        }else if(dd == "Bad"){
                            pos7.color = bad_color;
                        }
                    }
                    if(snList.length >= 8){var dd =snList[7].split("|")[0];
                        pos8.color = color;
                        pos8.text = 8;
                        if(dd == "NOSAMPLE"){
                            pos8.text = nosample;
                        }else if(dd == "Bad"){
                            pos8.color = bad_color;
                        }
                    }
                    if(snList.length >= 9){var dd =snList[8].split("|")[0];
                        pos9.color = color;
                        pos9.text = 9;
                        if(dd == "NOSAMPLE"){
                            pos9.text = nosample;
                        }else if(dd == "Bad"){
                            pos9.color = bad_color;
                        }
                    }
                    if(snList.length >= 10){var dd =snList[9].split("|")[0];
                        pos10.color = color;
                        pos10.text = 10;
                        if(dd == "NOSAMPLE"){
                            pos10.text = nosample;
                        }else if(dd == "Bad"){
                            pos10.color = bad_color;
                        }
                    }
                    if(snList.length >= 11){var dd =snList[10].split("|")[0];
                        pos11.color = color;
                        pos11.text = 11;
                        if(dd == "NOSAMPLE"){
                            pos11.text = nosample;
                        }else if(dd == "Bad"){
                            pos11.color = bad_color;
                        }
                    }
                    if(snList.length >= 12){var dd =snList[11].split("|")[0];
                        pos12.color = color;
                        pos12.text = 12;
                        if(dd == "NOSAMPLE"){
                            pos12.text = nosample;
                        }else if(dd == "Bad"){
                            pos12.color = bad_color;
                        }
                    }
                }

                if(max_luru >= 16){
                    if(snList.length >= 13){var dd =snList[12].split("|")[0];
                        pos13.color = color;
                        pos13.text = 13;
                        if(dd == "NOSAMPLE"){
                            pos13.text = nosample;
                        }else if(dd == "Bad"){
                            pos13.color = bad_color;
                        }
                    }
                    if(snList.length >= 14){var dd =snList[13].split("|")[0];
                        pos14.color = color;
                        pos14.text = 14;
                        if(dd == "NOSAMPLE"){
                            pos14.text = nosample;
                        }else if(dd == "Bad"){
                            pos14.color = bad_color;
                        }
                    }
                    if(snList.length >= 15){var dd =snList[14].split("|")[0];
                        pos15.color = color;
                        pos15.text = 15;
                        if(dd == "NOSAMPLE"){
                            pos15.text = nosample;
                        }else if(dd == "Bad"){
                            pos15.color = bad_color;
                        }
                    }
                    if(snList.length >= 16){var dd =snList[15].split("|")[0];
                        pos16.color = color;
                        pos16.text = 16;
                        if(dd == "NOSAMPLE"){
                            pos16.text = nosample;
                        }else if(dd == "Bad"){
                            pos16.color = bad_color;
                        }
                    }
                }
            }
        }
    }
}
