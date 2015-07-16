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
                text: 'BLOCK_NO 个数限制:'
                font.pixelSize: 20
                anchors.verticalCenter: id_block_no_limit.verticalCenter
            }
            TextInput_1{
                id: id_block_no_limit
                focus: true
                text: dataFilter.GetBlockNoLimitSettings()
                width: 400; height: 50
            }
            Button{
                width: 160; height: 50
                text: "设置"
                onClicked: {
                    dataFilter.SetBlockNoLimitSettings(id_block_no_limit.text)
                }
            }
        }
    }

}
