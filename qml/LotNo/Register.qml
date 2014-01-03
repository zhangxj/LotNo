import QtQuick 2.0

Rectangle {
    color: "#ece9d8"
    signal checked(int r)

    Column{
        id: column1
        spacing: 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 150
        Row{
            spacing: 10
            Text{
                text: '机器码:'
                font.pixelSize: 20
                font.bold: true
                anchors.verticalCenter: s1.verticalCenter
            }

            SearchBox{
                id: s1
                width: 400
                defaultText: dataFilter.getHardMD5()
            }
        }

        Row{
            spacing: 10
            Text{
                text: '校验码:'
                font.pixelSize: 20
                font.bold: true
                anchors.verticalCenter: s2.verticalCenter
            }
            SearchBox{
                id: s2
                width: 400
                onTextBox: dataFilter.checkCode(value)
            }
        }
    }

    Text{
        text: '请将机器码发送到厂家， 厂家生成校验码方可使用'
        font.pixelSize: 20
        font.bold: true
        color: 'blue'
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 40
    }
}
