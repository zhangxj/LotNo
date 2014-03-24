import QtQuick 1.1
import "func.js" as Func

Rectangle {
    id: form
    color: "transparent"

    Column{
        id: row_text
        spacing: 30
        anchors.centerIn: parent

        Row{
            spacing: 10
            Text{
                text: '文件路径:'
                font.pixelSize: 20
                anchors.verticalCenter: dir_path.verticalCenter
            }
            TextInput_1{
                id: dir_path
                focus: true
                text: dataFilter.getDirPath()
                width: 800; height: 50
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        dir_path.text = dataFilter.setFilePath()
                    }
                }
            }
        }
    }

}
