import QtQuick 1.1
import "func.js" as Func

Rectangle {
    width: 560
    height: 300
    color: "#ece9d8"
    Column{
        id: column1
        spacing: 20
        anchors.centerIn: parent
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
                clear: false
                onTextBox: {
                    s2.defaultText = dataFilter.JiaMi(value)
                }
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
            }
        }
    }

    Text{
        text: '校验码生成器'
        font.pixelSize: 20
        font.bold: true
        color: 'blue'
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
    }
}
